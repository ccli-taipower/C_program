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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入年、月、日，先檢查月份是否在 1~12 範圍內，無效則輸出 0 並結束。
 * 2. 依本題特殊閏年規則呼叫 is_leap(year)，調整二月的天數（28 或 29）。
 * 3. 檢查日期是否在該月合法範圍內；若日期 < 1 或超過當月天數，輸出 0 並結束。
 * 4. 若年份早於 1970，輸出 0 並結束（基準日期之前無效）。
 * 5. 初始化 total = 0，再以迴圈從 1970 年累加到 year-1 年，每年依閏年/平年加 366 或 365。
 * 6. 再以迴圈累加從 1 月到 month-1 月的各月天數。
 * 7. 最後加上 day，輸出 total 即為從 1970-1-1 起算的第幾天。
 *
 * English:
 * 1. Read year, month, day; verify month is in [1,12], output 0 and exit if invalid.
 * 2. Call is_leap(year) using the problem's special leap-year rules to set February's day count.
 * 3. Validate the day against the month's actual day count; output 0 and exit if out of range.
 * 4. If the year is before 1970, output 0 and exit (date precedes the epoch).
 * 5. Initialize total = 0, then loop from 1970 to year-1, adding 366 or 365 per year.
 * 6. Loop from month 1 to month-1, adding each month's day count to total.
 * 7. Add the day value to total and print it as the answer.
 */
#include <stdio.h>

/* 判斷是否為閏年（本題特殊規則） / determine if a year is a leap year (special rules for this problem) */
int is_leap(int year) {
    if (year % 1000 == 0) return 1;   /* 能被 1000 整除 → 閏年 / divisible by 1000 → leap year */
    if (year % 400 == 0) return 1;    /* 能被 400 整除 → 閏年 / divisible by 400 → leap year */
    if (year % 100 == 0) return 0;    /* 能被 100 整除（但不被 400） → 平年 / divisible by 100 but not 400 → common year */
    if (year % 4 == 0)   return 1;    /* 能被 4 整除 → 閏年 / divisible by 4 → leap year */
    return 0;                          /* 其他 → 平年 / otherwise → common year */
}

int main(void) {
    int year, month, day;
    int days_per_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int total;
    int i;

    /* 讀入年月日 / read year, month, and day */
    scanf("%d %d %d", &year, &month, &day);

    /* 驗證月份 / validate month */
    if (month < 1 || month > 12) {
        printf("0\n");
        return 0;
    }

    /* 根據是否為閏年調整二月天數 / adjust February day count based on leap year */
    if (is_leap(year)) {
        days_per_month[2] = 29;
    } else {
        days_per_month[2] = 28;
    }

    /* 驗證日期 / validate day */
    if (day < 1 || day > days_per_month[month]) {
        printf("0\n");
        return 0;
    }

    /* 若日期早於 1970-1-1，輸出 0 / if date is before 1970-1-1, output 0 */
    if (year < 1970) {
        printf("0\n");
        return 0;
    }
    if (year == 1970 && month == 1 && day < 1) {
        printf("0\n");
        return 0;
    }

    total = 0;

    /* 累加從 1970 到 year-1 每年的天數 / accumulate day count for each year from 1970 to year-1 */
    for (i = 1970; i < year; i++) {
        if (is_leap(i)) {
            total += 366;
        } else {
            total += 365;
        }
    }

    /* 累加該年 1 月到 month-1 月的天數 / accumulate day count for months 1 to month-1 of the target year */
    for (i = 1; i < month; i++) {
        total += days_per_month[i];
    }

    /* 加上日 / add the day */
    total += day;

    printf("%d\n", total);

    return 0;
}
