/*
 * NTHU EE2310 - 題目 14715: Prime Factorization
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 4 章（迴圈）
 *   如果不知道如何解題，請參考課本第 4 章的說明。
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
 */
#include <stdio.h>

int main(void) {
    long long n;      /* 輸入的正整數 */
    long long factor; /* 當前嘗試的因數 */
    int exponent;     /* 當前因數的指數 */

    /* 讀入正整數 */
    scanf("%lld", &n);

    /* 從 2 開始嘗試每個因數 */
    for (factor = 2; n > 1; factor++) {
        if (n % factor == 0) {
            /* 找到因數，計算指數 */
            exponent = 0;
            while (n % factor == 0) {
                exponent++;
                n /= factor;
            }
            /* 輸出「質因數 指數 」（trailing space） */
            printf("%lld %d ", factor, exponent);
        }
    }
    printf("\n");

    return 0;
}
