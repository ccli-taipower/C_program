/*
 * NTHU EE2310 - 題目 14685: Sum of four-digit integer
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 3 章（運算）
 *   如果不知道如何解題，請參考課本第 3 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14685/
 *
 * 【題目說明】
 * 輸入一個四位整數，計算並輸出各位數字之和。
 * 例如輸入 1234，各位數字為 1、2、3、4，總和為 10。
 *
 * 【解題策略】
 * 1. 讀入一個四位整數 n
 * 2. 利用整數除法和取餘數來分解各位數字：
 *    - 千位數：n / 1000
 *    - 百位數：(n / 100) % 10
 *    - 十位數：(n / 10) % 10
 *    - 個位數：n % 10
 * 3. 將四個位數相加後輸出
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 宣告整數 n 儲存輸入的四位數，以及 d1~d4 分別存放千、百、十、個位，
 *    sum 存放各位數字之和。
 * 2. 使用 scanf 讀入整數 n。
 * 3. 提取千位數 d1：對 1000 做整數除法，去掉後三位，只保留千位的數值。
 * 4. 提取百位數 d2：先除以 100 去掉後兩位，再對 10 取餘數，
 *    剝去千位，只保留百位。
 * 5. 提取十位數 d3：先除以 10 去掉個位，再對 10 取餘數，
 *    剝去百位以上，只保留十位。
 * 6. 提取個位數 d4：直接對 10 取餘數，取得最低位。
 * 7. 將四個位數相加得到 sum，用 printf 輸出後換行。
 *
 * English:
 * 1. Declare integer n for the four-digit input, d1–d4 for the thousands,
 *    hundreds, tens, and ones digits respectively, and sum for their total.
 * 2. Use scanf to read the integer n.
 * 3. Extract the thousands digit d1: integer-divide by 1000 to discard the lower
 *    three digits, leaving only the thousands place.
 * 4. Extract the hundreds digit d2: divide by 100 to remove the last two digits,
 *    then take the remainder mod 10 to strip the thousands place.
 * 5. Extract the tens digit d3: divide by 10 to remove the ones digit, then
 *    mod 10 to strip everything above the tens place.
 * 6. Extract the ones digit d4: simply take n mod 10 to get the lowest digit.
 * 7. Sum all four digits into sum and print the result with a newline.
 */
#include <stdio.h>

int main(void) {
    int n;        /* 輸入的四位整數 / the four-digit integer input */
    int d1;       /* 千位數字 / thousands digit */
    int d2;       /* 百位數字 / hundreds digit */
    int d3;       /* 十位數字 / tens digit */
    int d4;       /* 個位數字 / ones digit */
    int sum;      /* 各位數字之和 / sum of all digits */

    /* 讀入四位整數 / read the four-digit integer */
    scanf("%d", &n);

    /* 分解各位數字 / extract each individual digit */
    d1 = n / 1000;          /* 千位：整除 1000 取整數部分 / thousands: integer-divide by 1000 */
    d2 = (n / 100) % 10;    /* 百位：先整除 100，再取餘數 10 / hundreds: divide by 100 then mod 10 */
    d3 = (n / 10) % 10;     /* 十位：先整除 10，再取餘數 10 / tens: divide by 10 then mod 10 */
    d4 = n % 10;            /* 個位：直接取餘數 10 / ones: directly mod 10 */

    /* 計算各位數字總和 / compute the sum of all digits */
    sum = d1 + d2 + d3 + d4;

    /* 輸出結果 / print the result */
    printf("%d\n", sum);

    return 0;
}
