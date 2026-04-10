/*
 * NTHU EE2310 - 題目 14699: Calculation of Days
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 5 章（迴圈）
 *   如果不知道如何解題，請參考課本第 5 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14699/
 *
 * 【題目說明】
 * 輸入一個日期（年、月、日），計算從 1970 年 1 月 1 日起到該日期
 * 共過了幾天（第一天算第 1 天）。
 * 若日期無效或早於 1970-1-1，輸出 0。
 *
 * 閏年規則（本題特殊規則）：
 *   - 不能被 4 整除 → 平年（365 天）
 *   - 能被 4 整除但不能被 100 整除 → 閏年（366 天）
 *   - 能被 400 整除 → 閏年
 *   - 能被 1000 整除 → 也是閏年（特殊規則）
 *   - 能被 100 整除但不能被 400 整除，且不能被 1000 整除 → 平年
 *
 * 【解題策略】
 * 1. 驗證月份（1~12）與日期是否合法。
 * 2. 若日期早於 1970-1-1，輸出 0。
 * 3. 累計從 1970 年到輸入年份前一年的所有天數（每年判斷平年/閏年）。
 * 4. 累計該年 1 月到輸入月份前一月的天數。
 * 5. 加上輸入的日（day）即為答案。
 */
#include <stdio.h>

/* 判斷是否為閏年（本題特殊規則） */
int is_leap(int year) {
    if (year % 1000 == 0) return 1;   /* 能被 1000 整除 → 閏年 */
    if (year % 400 == 0) return 1;    /* 能被 400 整除 → 閏年 */
    if (year % 100 == 0) return 0;    /* 能被 100 整除（但不被 400） → 平年 */
    if (year % 4 == 0)   return 1;    /* 能被 4 整除 → 閏年 */
    return 0;                          /* 其他 → 平年 */
}

int main(void) {
    int year, month, day;
    int days_per_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int total;
    int i;

    /* 讀入年月日 */
    scanf("%d %d %d", &year, &month, &day);

    /* 驗證月份 */
    if (month < 1 || month > 12) {
        printf("0\n");
        return 0;
    }

    /* 根據是否為閏年調整二月天數 */
    if (is_leap(year)) {
        days_per_month[2] = 29;
    } else {
        days_per_month[2] = 28;
    }

    /* 驗證日期 */
    if (day < 1 || day > days_per_month[month]) {
        printf("0\n");
        return 0;
    }

    /* 若日期早於 1970-1-1，輸出 0 */
    if (year < 1970) {
        printf("0\n");
        return 0;
    }
    if (year == 1970 && month == 1 && day < 1) {
        printf("0\n");
        return 0;
    }

    total = 0;

    /* 累加從 1970 到 year-1 每年的天數 */
    for (i = 1970; i < year; i++) {
        if (is_leap(i)) {
            total += 366;
        } else {
            total += 365;
        }
    }

    /* 累加該年 1 月到 month-1 月的天數 */
    for (i = 1; i < month; i++) {
        total += days_per_month[i];
    }

    /* 加上日 */
    total += day;

    printf("%d\n", total);

    return 0;
}
