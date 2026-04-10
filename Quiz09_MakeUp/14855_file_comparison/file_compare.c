/*
 * NTHU ACM 14855 - File Comparison (make-up test)
 * Contest: EE2310 Quiz 9 make-up
 *
 * Read two filenames, open both files, compare their contents line by line.
 *   - For every line index (0-based) where the two files are identical,
 *     print that line number.
 *   - If one file has more lines than the other, after listing the matching
 *     line numbers, print "<longer_filename> <extra_line_count>".
 *
 * Notes:
 *   - Each line is at most 80 characters.
 *   - Filename length is at most 80 characters.
 *   - OJ does not support file I/O; the expected output must be verified
 *     manually against the provided test files.
 */
#include <stdio.h>
#include <string.h>

#define MAXLINE 128
#define MAXNAME 128

/* Read one line (without trailing newline) into buf. Returns 1 if a line was
 * read, 0 on EOF with no data. */
static int read_line(FILE *fp, char *buf, int cap) {
    if (fgets(buf, cap, fp) == NULL) return 0;
    size_t len = strlen(buf);
    while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
        buf[--len] = '\0';
    }
    return 1;
}

int main(void) {
    char name_a[MAXNAME], name_b[MAXNAME];
    if (scanf("%127s %127s", name_a, name_b) != 2) return 0;

    FILE *fa = fopen(name_a, "r");
    FILE *fb = fopen(name_b, "r");
    if (fa == NULL || fb == NULL) {
        if (fa) fclose(fa);
        if (fb) fclose(fb);
        return 0;
    }

    char line_a[MAXLINE], line_b[MAXLINE];
    int line_no = 0;
    int have_a, have_b;

    /* Compare matching positions line by line. */
    while (1) {
        have_a = read_line(fa, line_a, MAXLINE);
        have_b = read_line(fb, line_b, MAXLINE);
        if (!have_a || !have_b) break;
        if (strcmp(line_a, line_b) == 0) {
            printf("%d\n", line_no);
        }
        ++line_no;
    }

    /* If the shorter file ran out first, count how many extra lines the other
     * file has, then print "<longer_filename> <count>". */
    if (have_a && !have_b) {
        int extra = 1; /* we already read one line into line_a */
        while (read_line(fa, line_a, MAXLINE)) ++extra;
        printf("%s %d\n", name_a, extra);
    } else if (!have_a && have_b) {
        int extra = 1;
        while (read_line(fb, line_b, MAXLINE)) ++extra;
        printf("%s %d\n", name_b, extra);
    }

    fclose(fa);
    fclose(fb);
    return 0;
}
