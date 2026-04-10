/*
 * NTHU ACM 14875 - Date format converter
 * Contest: EE2310 Quiz 11
 *
 * Reads (year month day) then a format string (MMDDYY/DDMMYY/YYMMDD) and
 * prints the date in the requested ordering with slashes as separators.
 *   - Year is printed with 4 digits.
 *   - Month and day are zero-padded to 2 digits.
 */
#include <stdio.h>
#include <string.h>

int main(void) {
    int year, month, day;
    char fmt[16];

    if (scanf("%d %d %d", &year, &month, &day) != 3) return 0;
    if (scanf("%15s", fmt) != 1) return 0;

    if (strcmp(fmt, "MMDDYY") == 0) {
        printf("%02d/%02d/%04d\n", month, day, year);
    } else if (strcmp(fmt, "DDMMYY") == 0) {
        printf("%02d/%02d/%04d\n", day, month, year);
    } else if (strcmp(fmt, "YYMMDD") == 0) {
        printf("%04d/%02d/%02d\n", year, month, day);
    }
    return 0;
}
