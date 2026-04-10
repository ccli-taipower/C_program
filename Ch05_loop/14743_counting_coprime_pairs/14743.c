/*
 * NTHU EE2310 - 題目 14743: Counting Coprime Pairs
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 5 章（迴圈）
 *   如果不知道如何解題，請參考課本第 5 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14743/
 *
 * 【題目說明】
 * 讀入一行 n 個正整數，計算所有互質數對（i, j）的個數（i < j）。
 * 若兩個數的最大公因數（GCD）為 1，則稱為互質。
 * 限制：0 < n <= 100
 *
 * 範例：
 *   [2, 3, 4] → 互質對：(2,3), (3,4) → 2
 *   [6, 9, 15] → 無互質對 → 0
 *   [5, 10, 21] → 互質對：(5,21) → 1
 *
 * 【解題策略】
 * 1. 從標準輸入讀取一行中的所有整數，直到換行或 EOF。
 * 2. 使用輾轉相除法（Euclidean algorithm）計算兩數的 GCD。
 * 3. 用雙層迴圈枚舉所有配對 (i, j)，i < j，若 GCD 為 1 則計數加一。
 * 4. 輸出總計數。
 */
#include <stdio.h>

/* 輾轉相除法計算最大公因數 */
int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(void) {
    int nums[100]; /* 儲存輸入的正整數 */
    int n;         /* 讀入的數字個數 */
    int count;     /* 互質對的計數 */
    int i, j;

    /* 讀入一行中所有整數，直到 EOF 或換行 */
    n = 0;
    while (scanf("%d", &nums[n]) == 1) {
        n++;
    }

    /* 用雙層迴圈枚舉所有配對，計算互質對數 */
    count = 0;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (gcd(nums[i], nums[j]) == 1) {
                count++;
            }
        }
    }

    /* 輸出互質對總數 */
    printf("%d\n", count);

    return 0;
}
