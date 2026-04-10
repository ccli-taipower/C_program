/*
 * NTHU EE2310 - 題目 14653: Find the maximum of three integers
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 4 章（判斷）
 *   如果不知道如何解題，請參考課本第 4 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14653/
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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 宣告三個整數 a、b、c 儲存輸入值，並宣告 max 儲存目前已知的最大值。
 * 2. 使用 scanf 讀入三個整數。
 * 3. 初始化 max = a：在尚未比較任何數之前，先假定第一個數為最大值，
 *    這是「線性掃描求最大值」演算法的起點。
 * 4. 將 b 與 max 比較：若 b > max，表示 b 更大，更新 max = b。
 *    此時 max 已保存 a 和 b 中的較大值。
 * 5. 將 c 與 max 比較：若 c > max，表示 c 更大，更新 max = c。
 *    此時 max 保存三個數中的最大值。
 * 6. 用 printf 輸出 max，即為所求的三數最大值。
 *
 * English:
 * 1. Declare integers a, b, c for the three inputs and max to track the current maximum.
 * 2. Use scanf to read all three integers.
 * 3. Initialize max = a: before any comparisons, assume the first number is the maximum.
 *    This is the standard starting point for the linear-scan maximum algorithm.
 * 4. Compare b with max: if b > max, b is larger, so update max = b.
 *    At this point max holds the larger of a and b.
 * 5. Compare c with max: if c > max, c is larger, so update max = c.
 *    After this step max holds the largest of all three numbers.
 * 6. Print max with printf; it is the answer to the problem.
 */
#include <stdio.h>

int main(void) {
    int a;    /* 第一個整數 / first integer */
    int b;    /* 第二個整數 / second integer */
    int c;    /* 第三個整數 / third integer */
    int max;  /* 目前找到的最大值 / current maximum value found so far */

    /* 讀入三個整數 / read three integers */
    scanf("%d %d %d", &a, &b, &c);

    /* 先假設 a 是最大值 / initially assume a is the maximum */
    max = a;

    /* 若 b 比目前最大值還大，更新最大值 / if b exceeds current max, update max */
    if (b > max) {
        max = b;
    }

    /* 若 c 比目前最大值還大，更新最大值 / if c exceeds current max, update max */
    if (c > max) {
        max = c;
    }

    /* 輸出最大值 / print the maximum value */
    printf("%d\n", max);

    return 0;
}
