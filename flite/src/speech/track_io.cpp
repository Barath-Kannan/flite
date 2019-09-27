#include "flite/synthcommon/track.hpp"
#include "flite/utils/endian.hpp"
#include "flite/utils/string.hpp"
#include "flite/utils/tokenstream.hpp"

int cst_track_save_est(cst_track* t, const char* filename)
{
    cst_file fd;
    int i, j;

    if ((fd = cst_fopen(filename, CST_OPEN_WRITE | CST_OPEN_BINARY)) == NULL) {
        cst_errmsg("cst_track_save_est: can't open file \"%s\"\n", filename);
        return -1;
    }

    cst_fprintf(fd, "EST_File Track\n");
    cst_fprintf(fd, "DataType ascii\n");
    cst_fprintf(fd, "NumFrames %d\n", t->num_frames);
    cst_fprintf(fd, "NumChannels %d\n", t->num_channels);
    cst_fprintf(fd, "BreaksPresent true\n");
    cst_fprintf(fd, "EST_Header_End\n");

    for (i = 0; i < t->num_frames; i++) {
        cst_fprintf(fd, "%f\t1 \t", t->times[i]);
        for (j = 0; j < t->num_channels; j++)
            cst_fprintf(fd, "%f ", t->frames[i][j]);
        cst_fprintf(fd, "\n");
    }

    cst_fclose(fd);

    return 0;
}

int cst_track_save_est_binary(cst_track* t, const char* filename)
{
    cst_file fd;
    float foo;
    int i, j;

    if ((fd = cst_fopen(filename, CST_OPEN_WRITE | CST_OPEN_BINARY)) == NULL) {
        cst_errmsg("cst_track_save_est_binary: can't open file \"%s\"\n", filename);
        return -1;
    }

    cst_fprintf(fd, "EST_File Track\n");
    cst_fprintf(fd, "DataType binary\n");
    cst_fprintf(fd, "ByteOrder %s\n", CST_LITTLE_ENDIAN ? BYTE_ORDER_LITTLE : BYTE_ORDER_BIG);
    cst_fprintf(fd, "NumFrames %d\n", t->num_frames);
    cst_fprintf(fd, "NumChannels %d\n", t->num_channels);
    cst_fprintf(fd, "BreaksPresent true\n");
    cst_fprintf(fd, "EST_Header_End\n");

    foo = 1.0; /* put a bogus 'breaks' value in for now */
    for (i = 0; i < t->num_frames; i++) {
        cst_fwrite(fd, t->times + i, sizeof(float), 1);
        cst_fwrite(fd, &foo, sizeof(float), 1);
        for (j = 0; j < t->num_channels; j++)
            cst_fwrite(fd, &(t->frames[i][j]), sizeof(float), 1);
    }

    cst_fclose(fd);

    return 0;
}

static int load_frame_ascii(cst_track* t, int i, cst_tokenstream* ts)
{
    int j;

    t->times[i] = cst_atof(ts_get(ts));
    ts_get(ts); /* the can be only 1 */
    for (j = 0; j < t->num_channels; j++)
        t->frames[i][j] = cst_atof(ts_get(ts));
    if ((i + 1 < t->num_frames) && (ts_eof(ts))) {
        return -1;
    }
    return 0;
}

static int load_frame_binary(cst_track* t, int i, cst_tokenstream* ts, int swap)
{
    float val;
    int j;

    if (cst_fread(ts->fd, &val, sizeof(float), 1) != 1)
        return -1;
    if (swap)
        swapfloat(&val);
    t->times[i] = val;

    /* Ignore the 'breaks' field */
    if (cst_fread(ts->fd, &val, sizeof(float), 1) != 1)
        return -1;

    for (j = 0; j < t->num_channels; j++) {
        if (cst_fread(ts->fd, &val, sizeof(float), 1) != 1)
            return -1;
        if (swap)
            swapfloat(&val);
        t->frames[i][j] = val;
    }

    return 0;
}

int cst_track_load_est(cst_track* t, const char* filename)
{
    cst_tokenstream* ts;
    const char* tok;
    int num_frames, num_channels;
    int i, ascii = 1, swap = 0, rv;

    num_frames = 0;
    num_channels = 0;
    ts = ts_open(filename, NULL, NULL, NULL, NULL);
    if (ts == NULL) {
        cst_errmsg("cst_track_load: can't open file \"%s\"\n", filename);
        return -1;
    }

    if (!cst_streq(ts_get(ts), "EST_File")) {
        cst_errmsg("cst_track_load: not an EST file \"%s\"\n", filename);
        ts_close(ts);
        return -1;
    }
    if (!cst_streq(ts_get(ts), "Track")) {
        cst_errmsg("cst_track_load: not an track file \"%s\"\n", filename);
        ts_close(ts);
        return -1;
    }

    while (!cst_streq("EST_Header_End", (tok = ts_get(ts)))) {
        if (cst_streq("DataType", tok)) {
            tok = ts_get(ts);
            if (cst_streq("ascii", tok)) {
                ascii = 1;
            }
            else if (cst_streq("binary", tok)) {
                ascii = 0;
            }
            else {
                cst_errmsg(
                    "cst_track_load: don't know how to deal "
                    "with type \"%s\"\n",
                    tok);
                ts_close(ts);
                return -1;
            }
        }
        else if (cst_streq("ByteOrder", tok)) {
            tok = ts_get(ts);
            swap = (cst_streq(tok, BYTE_ORDER_BIG) && CST_LITTLE_ENDIAN) || (cst_streq(tok, BYTE_ORDER_LITTLE) && CST_BIG_ENDIAN);
        }
        else if (cst_streq("NumFrames", tok))
            num_frames = atoi(ts_get(ts));
        else if (cst_streq("NumChannels", tok))
            num_channels = atoi(ts_get(ts));
        else
            ts_get(ts);
        if (ts_eof(ts)) {
            cst_errmsg("cst_track_load: EOF in header \"%s\"\n", filename);
            ts_close(ts);
            return -1;
        }
    }

    cst_track_resize(t, num_frames, num_channels);

    for (i = 0; i < t->num_frames; i++) {
        if (ascii)
            rv = load_frame_ascii(t, i, ts);
        else
            rv = load_frame_binary(t, i, ts, swap);
        if (rv < 0) {
            ts_close(ts);
            cst_errmsg("cst_track_load: EOF in data \"%s\"\n", filename);
            return rv;
        }
    }

    ts_get(ts);
    if (!ts_eof(ts)) {
        cst_errmsg("cst_track_load: not EOF when expected \"%s\"\n", filename);
        ts_close(ts);
        return -1;
    }

    ts_close(ts);

    return 0;
}
