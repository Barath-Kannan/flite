#include <stdlib.h>
#include "flite/audio/audio.hpp"
#include "flite/synthcommon/wave.hpp"
#include "flite/utils/file.hpp"
#include "flite/utils/socket.hpp"
#include "flite/utils/string.hpp"

#ifndef CST_NO_SOCKETS

#ifdef _MSC_VER
#include <io.h>
#define read(fd, buffer, count) _read(fd, buffer, count)
#else
#include <unistd.h>
#endif

static int play_wave_from_socket(snd_header* header, int audiostream)
{
    /* Read audio from stream and play it to audio device, converting */
    /* it to pcm if required                                          */
    int num_samples;
    int sample_width;
    cst_audiodev* audio_device;
    int q, i, n, r;
    unsigned char bytes[CST_AUDIOBUFFSIZE];
    short shorts[CST_AUDIOBUFFSIZE];
#ifdef DEBUG
    cst_file fff;

    fff = cst_fopen("/tmp/awb.wav", CST_OPEN_WRITE | CST_OPEN_BINARY);
#endif

    if ((audio_device = audio_open(header->sample_rate, 1, (header->encoding == CST_SND_SHORT) ? CST_AUDIO_LINEAR16 : CST_AUDIO_LINEAR8)) == NULL) {
        cst_errmsg("play_wave_from_socket: can't open audio device\n");
        return -1;
    }

    if (header->encoding == CST_SND_SHORT)
        sample_width = 2;
    else
        sample_width = 1;

    num_samples = header->data_size / sample_width;
    /* we naively let the num_channels sort itself out */
    for (i = 0; i < num_samples; i += r / 2) {
        if (num_samples > i + CST_AUDIOBUFFSIZE)
            n = CST_AUDIOBUFFSIZE;
        else
            n = num_samples - i;
        if (header->encoding == CST_SND_ULAW) {
            r = read(audiostream, bytes, n);
            for (q = 0; q < r; q++)
                shorts[q] = cst_ulaw_to_short(bytes[q]);
            r *= 2;
        }
        else /* if (header->encoding == CST_SND_SHORT) */
        {
            r = read(audiostream, shorts, n * 2);
            if (CST_LITTLE_ENDIAN)
                for (q = 0; q < r / 2; q++)
                    shorts[q] = SWAPSHORT(shorts[q]);
        }

        if (r <= 0) { /* I'm not getting any data from the server */
            audio_close(audio_device);
            return CST_ERROR_FORMAT;
        }

        for (q = r; q > 0; q -= n) {
            n = audio_write(audio_device, shorts, q);
#ifdef DEBUG
            cst_fwrite(fff, shorts, 2, q);
#endif
            if (n <= 0) {
                audio_close(audio_device);
                return CST_ERROR_FORMAT;
            }
        }
    }
    audio_close(audio_device);
#ifdef DEBUG
    cst_fclose(fff);
#endif

    return CST_OK_FORMAT;
}

static int auserver_process_client(int client_name, int fd)
{
    /* Gets called for each client */
    snd_header header;
    int r;

    printf("client %d connected, ", client_name);
    fflush(stdout);
    /* Get header */
    r = read(fd, &header, sizeof(header));
    if (r != sizeof(header)) {
        cst_errmsg("socket: connection didn't give a header\n");
        return -1;
    }
    if (CST_LITTLE_ENDIAN) {
        header.magic = SWAPINT(header.magic);
        header.hdr_size = SWAPINT(header.hdr_size);
        header.data_size = SWAPINT(header.data_size);
        header.encoding = SWAPINT(header.encoding);
        header.sample_rate = SWAPINT(header.sample_rate);
        header.channels = SWAPINT(header.channels);
    }

    if (header.magic != CST_SND_MAGIC) {
        cst_errmsg("socket: client something other than snd waveform\n");
        return -1;
    }

    printf("%d bytes at %d rate, ", header.data_size, header.sample_rate);
    fflush(stdout);

    if (play_wave_from_socket(&header, fd) == CST_OK_FORMAT)
        printf("successful\n");
    else
        printf("unsuccessful\n");

    return 0;
}

int auserver(int port)
{
    return cst_socket_server("audio", port, auserver_process_client);
}

#endif
