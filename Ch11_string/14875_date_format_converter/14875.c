/*
 * NTHU EE2310 - 題目 14875: Date Format Converter（日期格式轉換）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 11 章（字串）
 *   如果不知道如何解題，請參考課本第 11 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14875/
 *
 * 【題目說明】
 * 讀取年、月、日和格式字串（MMDDYY / DDMMYY / YYMMDD），
 * 以斜線（/）為分隔符號，依指定格式輸出日期。
 *   - 年份以 4 位數字輸出。
 *   - 月份和日期以 2 位數字輸出（不足補零）。
 *
 * 【解題策略】
 * 比對格式字串後，以對應的 printf 格式輸出即可。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 使用 scanf 讀入三個整數：year（年）、month（月）、day（日）。
 * 2. 使用 scanf 讀入格式字串 fmt（最多 15 個字元）。
 * 3. 以 strcmp 依序比對 fmt 是否為 "MMDDYY"、"DDMMYY" 或 "YYMMDD"。
 * 4. 依比對結果選擇對應的 printf 格式字串輸出：
 *    - MMDDYY → 月/日/年（月、日補零至 2 位，年補零至 4 位）
 *    - DDMMYY → 日/月/年
 *    - YYMMDD → 年/月/日
 * 5. 分隔符號固定使用斜線（/），年份固定 4 位，月日固定 2 位（不足補零）。
 *
 * English:
 * 1. Read three integers with scanf: year, month, day.
 * 2. Read the format string fmt (up to 15 characters) with scanf.
 * 3. Compare fmt against "MMDDYY", "DDMMYY", and "YYMMDD" using strcmp.
 * 4. Select the matching printf format to produce the output:
 *    - MMDDYY → month/day/year (month and day zero-padded to 2 digits, year to 4)
 *    - DDMMYY → day/month/year
 *    - YYMMDD → year/month/day
 * 5. The separator is always '/', year is always 4 digits, month/day always 2 digits.
 */
#include <stdio.h>
#include <string.h>

int main(void) {
    int year, month, day;
    char fmt[16];

    /* 讀取年、月、日 / read year, month, day */
    if (scanf("%d %d %d", &year, &month, &day) != 3) return 0;
    /* 讀取格式字串 / read the format string */
    if (scanf("%15s", fmt) != 1) return 0;

    /* 依格式輸出日期 / output date according to the format */
    if (strcmp(fmt, "MMDDYY") == 0) {
        /* 月/日/年 / month/day/year */
        printf("%02d/%02d/%04d\n", month, day, year);
    } else if (strcmp(fmt, "DDMMYY") == 0) {
        /* 日/月/年 / day/month/year */
        printf("%02d/%02d/%04d\n", day, month, year);
    } else if (strcmp(fmt, "YYMMDD") == 0) {
        /* 年/月/日 / year/month/day */
        printf("%04d/%02d/%02d\n", year, month, day);
    }
    return 0;
}
