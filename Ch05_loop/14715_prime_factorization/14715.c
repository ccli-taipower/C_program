/*
 * NTHU EE2310 - 題目 14715: Prime Factorization
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 5 章（迴圈）
 *   如果不知道如何解題，請參考課本第 5 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14715/
 *
 * 【題目說明】
 * 對一個正整數 n 做質因數分解。
 * 輸出所有質因數及其指數，格式為「質因數 指數 」，由小到大排列。
 * 注意：每個指數後面有一個空格（包含最後一個，即 trailing space）。
 *
 * 範例：
 *   123456 = 2^6 * 3^1 * 643^1 → 輸出："2 6 3 1 643 1 "
 *   67099 = 17^1 * 3947^1 → 輸出："17 1 3947 1 "
 *
 * 【解題策略】
 * 1. 從因數 2 開始，嘗試整除 n。
 * 2. 若能整除，記錄該因數與指數（連續整除直到不能整除為止）。
 * 3. 將因數加 1，繼續嘗試，直到 n 等於 1 為止。
 * 4. 因為每次找到因數時，n 已無法被更小的合數整除，所以找到的必為質因數。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入正整數 n（使用 long long 型別支援大數）。
 * 2. 讓 factor 從 2 開始遞增，只需嘗試到 sqrt(n)（即 factor*factor <= n）。
 * 3. 若 n 能被 factor 整除，表示找到一個質因數；進入 while 迴圈連續整除，同時累計指數 exponent。
 * 4. 每次找到質因數時，輸出「factor exponent 」（包含 trailing space）。
 * 5. 外層 for 迴圈結束後，若 n 仍大於 1，表示 n 本身就是一個質因數（指數為 1），輸出它。
 * 6. 最後輸出換行符號。
 *
 * English:
 * 1. Read positive integer n using long long to handle large values.
 * 2. Increment factor starting from 2; only iterate while factor*factor <= n (equivalent to sqrt(n)).
 * 3. If n is divisible by factor, a prime factor is found; divide n repeatedly while divisible and count the exponent.
 * 4. Print "factor exponent " (with trailing space) for each prime factor found.
 * 5. After the for loop, if n > 1 remains, n itself is a prime factor with exponent 1; print it.
 * 6. Print a newline at the end.
 */
#include <stdio.h>

int main(void) {
    long long n;      /* 輸入的正整數 / input positive integer */
    long long factor; /* 當前嘗試的因數 / current trial factor */
    int exponent;     /* 當前因數的指數 / exponent of the current factor */

    /* 讀入正整數 / read the positive integer */
    scanf("%lld", &n);

    /* 從 2 開始嘗試每個因數，只需試到 sqrt(n) / try each factor from 2 up to sqrt(n) */
    for (factor = 2; factor * factor <= n; factor++) {
        if (n % factor == 0) {
            /* 找到因數，計算指數 / factor found, count its exponent */
            exponent = 0;
            while (n % factor == 0) {
                exponent++;
                n /= factor;
            }
            /* 輸出「質因數 指數 」（trailing space） / print "prime_factor exponent " (with trailing space) */
            printf("%lld %d ", factor, exponent);
        }
    }
    /* 若 n > 1，代表 n 本身是質因數 / if n > 1 remains, n itself is a prime factor */
    if (n > 1) {
        printf("%lld %d ", n, 1);
    }
    printf("\n");

    return 0;
}
