#include "flite/utils/file.hpp"
#include "flite/utils/math.hpp"
#include "flite/utils/socket.hpp"
#include "flite/utils/string.hpp"
#include "flite/utils/tokenstream.hpp"

#ifndef CST_NO_SOCKETS
#ifndef _MSC_VER
#include <stdlib.h>
#include <unistd.h>
#else
#include <WinSock.h>
#include <io.h>
#endif
#endif

int cst_urlp(const char* url)
{
    /* Return 1 if url is a url, 0 otherwise */
    /* This is decided by the initial substring being "http:" or "file:" */
    if ((cst_strlen(url) > 4) &&
        (cst_streqn("http:", url, 5) ||
         cst_streqn("file:", url, 5)))
        return TRUE;
    else
        return FALSE;
}

cst_file cst_url_open(const char* url)
{
    /* Always opens it for reading */
    cst_tokenstream* urlts;
    const cst_string* protocol;
    int port;
    cst_string* host;
    int fd;
    char* url_request;
    char* path;
    cst_file ofd;
    int state, n;
    char c;

    urlts = ts_open_string(url, "", ":/", "", "");

    protocol = ts_get(urlts);
    if (cst_streq(protocol, "http")) {
#ifdef CST_NO_SOCKETS
        ts_close(urlts);
        return NULL;
#else
        if (!cst_streq(ts_get(urlts), ":") ||
            !cst_streq(ts_get(urlts), "/") ||
            !cst_streq(ts_get(urlts), "/")) {
            ts_close(urlts);
            return NULL;
        }
        host = cst_strdup(ts_get(urlts));
        if (cst_streq(ts_get(urlts), ":"))
            port = (int)cst_atof(ts_get(urlts));
        else
            port = 80;

        /* Open port to web server */
        fd = cst_socket_open(host, port);
        if (fd < 0) {
            cst_free(host);
            ts_close(urlts);
            return NULL;
        }

        url_request = cst_alloc(char, cst_strlen(url) + 17);
        cst_sprintf(url_request, "GET %s HTTP/1.2\n\n", url);
        n = write(fd, url_request, cst_strlen(url_request));
        cst_free(url_request);

        /* Skip http header -- until \n\n */
        state = 0;
        while (state != 4) {
            n = read(fd, &c, 1);
            if (n == 0) { /* eof or link gone down */
                cst_free(host);
                ts_close(urlts);
                return NULL;
            }
            if ((state == 0) && (c == '\r'))
                state = 1;
            else if ((state == 1) && (c == '\n'))
                state = 2;
            else if ((state == 2) && (c == '\r'))
                state = 3;
            else if ((state == 3) && (c == '\n'))
                state = 4;
            /* Not sure you can get no CRs in the stream */
            else if ((state == 0) && (c == '\n'))
                state = 2;
            else if ((state == 2) && (c == '\n'))
                state = 4;
            else
                state = 0;
        }

        ofd = fdopen(fd, "rb");

        ts_close(urlts);
        cst_free(host);

        return ofd;
#endif
    }
    else if (cst_streq(protocol, "file")) {
        if (!cst_streq(ts_get(urlts), ":") ||
            !cst_streq(ts_get(urlts), "/") ||
            !cst_streq(ts_get(urlts), "/")) {
            ts_close(urlts);
            return NULL;
        }
        path = cst_strdup(&urlts->string_buffer[urlts->file_pos - 1]);
        /* printf("awb_debug fileurl %s\n",path); */

        ofd = cst_fopen(path, CST_OPEN_READ);

        ts_close(urlts);
        cst_free(path);

        return ofd;
    }
    else { /* Unsupported protocol */
        return NULL;
    }
}
