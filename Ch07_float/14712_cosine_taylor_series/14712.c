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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入 double 型別的輸入值 x（0 <= x <= 2π）。
 * 2. 初始化 result = 1.0 和 term = 1.0，對應泰勒展開式的第 0 項（n=0）。
 * 3. 使用 for 迴圈從 n=1 到 n=15，每次利用遞推關係更新 term：
 *    term = term * (-x²) / ((2n-1) * 2n)
 *    這樣避免了每次都重新計算 x^(2n) 和 (2n)!，大幅提升效率。
 * 4. 每次更新 term 後，將其加入 result（累加所有 16 項）。
 * 5. 迴圈結束後，以 "%.6f" 格式輸出 result（保留 6 位小數）。
 *
 * English:
 * 1. Read the double input value x (0 <= x <= 2π).
 * 2. Initialize result = 1.0 and term = 1.0, corresponding to the n=0 term of the Taylor series.
 * 3. Use a for loop from n=1 to n=15; each iteration updates term via the recurrence relation:
 *    term = term * (-x²) / ((2n-1) * 2n)
 *    This avoids recomputing x^(2n) and (2n)! from scratch each time, improving efficiency.
 * 4. After updating term, add it to result (accumulating all 16 terms).
 * 5. After the loop, print result formatted to 6 decimal places with "%.6f".
 */
#include <stdio.h>

int main(void) {
    double x;       /* 輸入值 / input value */
    double result;  /* 累加結果 / accumulated result */
    double term;    /* 當前項的值 / value of the current term */
    int n;          /* 項次索引（n = 0, 1, ..., 15） / term index (n = 0, 1, ..., 15) */

    /* 讀入 x / read x */
    scanf("%lf", &x);

    /* 初始化：第 0 項為 1 / initialize: the n=0 term equals 1 */
    result = 1.0;
    term = 1.0;

    /* 從 n=1 到 n=15，逐項計算並累加 / compute and accumulate terms from n=1 to n=15 */
    for (n = 1; n <= 15; n++) {
        /* 遞推：term_n = term_{n-1} * (-x^2) / ((2n-1) * 2n) / recurrence: term_n = term_{n-1} * (-x^2) / ((2n-1) * 2n) */
        term = term * (-x * x) / ((double)(2 * n - 1) * (double)(2 * n));
        result += term;
    }

    /* 輸出結果，保留 6 位小數 / print result with 6 decimal places */
    printf("%.6f\n", result);

    return 0;
}
