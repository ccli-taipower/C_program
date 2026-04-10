/*
 * NTHU ACM 14856 - File Splitting (make-up test)
 * Contest: EE2310 Quiz 9 make-up
 *
 * Read an input filename and a split size m (bytes). Cut the file into
 * consecutive chunks of exactly m bytes and write each chunk to
 * "<filename>.1", "<filename>.2", ...  If the final chunk is shorter than
 * m bytes, pad it with '*' (ASCII 42) until it is exactly m bytes long.
 *
 * Notes:
 *   - 0 < m < 1024, filename length n <= 80.
 *   - Nothing is printed to stdout.
 *   - OJ does not support file I/O, so output files must be verified manually.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXNAME 128
#define PAD_CHAR '*'

int main(void) {
    char fname[MAXNAME];
    int m;

    if (scanf("%100s", fname) != 1) return 0;
    if (scanf("%d", &m) != 1) return 0;
    if (m <= 0) return 0;

    FILE *in = fopen(fname, "rb");
    if (in == NULL) return 0;

    char *buf = (char *)malloc((size_t)m);
    if (buf == NULL) { fclose(in); return 0; }

    int index = 1;
    while (1) {
        size_t got = fread(buf, 1, (size_t)m, in);
        if (got == 0) break; /* EOF exactly at a chunk boundary */

        /* Pad the last (partial) chunk with '*' up to m bytes. */
        if ((int)got < m) {
            memset(buf + got, PAD_CHAR, (size_t)m - got);
        }

        /* Build output filename "<fname>.<index>" */
        char out_name[MAXNAME + 16];
        snprintf(out_name, sizeof(out_name), "%s.%d", fname, index);
        FILE *out = fopen(out_name, "wb");
        if (out == NULL) { free(buf); fclose(in); return 0; }
        fwrite(buf, 1, (size_t)m, out);
        fclose(out);

        ++index;
        if ((int)got < m) break; /* last chunk already written */
    }

    free(buf);
    fclose(in);
    return 0;
}
