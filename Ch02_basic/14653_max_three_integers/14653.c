/*
 * NTHU EE2310 - 題目 14653: Find the maximum of three integers
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 2 章：基本運算
 *   如果不知道如何解題，請參考課本第 2 章的說明。
 *
 * 【題目說明】
 * 輸入三個整數，找出其中最大的值並輸出。
 *
 * 【解題策略】
 * 1. 讀入三個整數 a、b、c
 * 2. 先假設 a 是最大值，存入 max 變數
 * 3. 若 b 大於 max，更新 max 為 b
 * 4. 若 c 大於 max，更新 max 為 c
 * 5. 輸出 max 即為三數中最大值
 */
#include <stdio.h>

int main(void) {
    int a;    /* 第一個整數 */
    int b;    /* 第二個整數 */
    int c;    /* 第三個整數 */
    int max;  /* 目前找到的最大值 */

    /* 讀入三個整數 */
    scanf("%d %d %d", &a, &b, &c);

    /* 先假設 a 是最大值 */
    max = a;

    /* 若 b 比目前最大值還大，更新最大值 */
    if (b > max) {
        max = b;
    }

    /* 若 c 比目前最大值還大，更新最大值 */
    if (c > max) {
        max = c;
    }

    /* 輸出最大值 */
    printf("%d\n", max);

    return 0;
}
