/*
 * NTHU EE2310 - 題目 14712: Cosine Taylor Series
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 7 章（浮點數）
 *   如果不知道如何解題，請參考課本第 7 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14712/
 *
 * 【題目說明】
 * 使用泰勒展開式計算 cos(x)：
 *   cos(x) = Σ_{n=0}^{15} (-1)^n * x^(2n) / (2n)!
 *           = 1 - x²/2! + x⁴/4! - x⁶/6! + ... + x^30/30!
 * 輸入：double x（0 <= x <= 2π）
 * 輸出：結果，保留 6 位小數
 *
 * 【解題策略】
 * 逐項累加，利用遞推關係避免重複計算：
 *   - 第 n 項為：term = (-1)^n * x^(2n) / (2n)!
 *   - 從第 n 項到第 n+1 項的遞推關係：
 *     term_{n+1} = term_n * (-x²) / ((2n+1) * (2n+2))
 * 以此方式，每次只需對上一項做一次乘法和除法，效率更高。
 */
#include <stdio.h>

int main(void) {
    double x;       /* 輸入值 */
    double result;  /* 累加結果 */
    double term;    /* 當前項的值 */
    int n;          /* 項次索引（n = 0, 1, ..., 15） */

    /* 讀入 x */
    scanf("%lf", &x);

    /* 初始化：第 0 項為 1 */
    result = 1.0;
    term = 1.0;

    /* 從 n=1 到 n=15，逐項計算並累加 */
    for (n = 1; n <= 15; n++) {
        /* 遞推：term_n = term_{n-1} * (-x^2) / ((2n-1) * 2n) */
        term = term * (-x * x) / ((double)(2 * n - 1) * (double)(2 * n));
        result += term;
    }

    /* 輸出結果，保留 6 位小數 */
    printf("%.6f\n", result);

    return 0;
}
