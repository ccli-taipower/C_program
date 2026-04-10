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
 */
#include <stdio.h>
#include <string.h>

int main(void) {
    int year, month, day;
    char fmt[16];

    /* 讀取年、月、日 */
    if (scanf("%d %d %d", &year, &month, &day) != 3) return 0;
    /* 讀取格式字串 */
    if (scanf("%15s", fmt) != 1) return 0;

    /* 依格式輸出日期 */
    if (strcmp(fmt, "MMDDYY") == 0) {
        /* 月/日/年 */
        printf("%02d/%02d/%04d\n", month, day, year);
    } else if (strcmp(fmt, "DDMMYY") == 0) {
        /* 日/月/年 */
        printf("%02d/%02d/%04d\n", day, month, year);
    } else if (strcmp(fmt, "YYMMDD") == 0) {
        /* 年/月/日 */
        printf("%04d/%02d/%02d\n", year, month, day);
    }
    return 0;
}
