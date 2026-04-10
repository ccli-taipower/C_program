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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 使用 while 迴圈持續以 scanf 讀入整數到 nums[]，直到 EOF，同時累計個數 n。
 * 2. 實作 gcd(a, b) 函數：使用輾轉相除法（Euclidean algorithm），反覆以 b 取代 a、a%b 取代 b，直到 b 為 0，返回 a。
 * 3. 初始化計數器 count = 0，使用雙層 for 迴圈枚舉所有 (i, j) 配對（i < j）。
 * 4. 對每對 (nums[i], nums[j]) 呼叫 gcd；若結果為 1，則兩數互質，count 加一。
 * 5. 雙層迴圈結束後輸出 count 即為互質對的總個數。
 *
 * English:
 * 1. Use a while loop with scanf to read integers into nums[] until EOF, counting them in n.
 * 2. Implement gcd(a, b) using the Euclidean algorithm: repeatedly replace a with b and b with a%b until b is 0, then return a.
 * 3. Initialize count = 0 and use nested for loops to enumerate all pairs (i, j) with i < j.
 * 4. For each pair (nums[i], nums[j]), call gcd; if the result is 1 the pair is coprime and count is incremented.
 * 5. After both loops finish, print count as the total number of coprime pairs.
 */
#include <stdio.h>

/* 輾轉相除法計算最大公因數 / compute greatest common divisor using the Euclidean algorithm */
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
    int nums[100]; /* 儲存輸入的正整數 / array to store the input positive integers */
    int n;         /* 讀入的數字個數 / count of numbers read */
    int count;     /* 互質對的計數 / count of coprime pairs */
    int i, j;

    /* 讀入一行中所有整數，直到 EOF 或換行 / read all integers from input until EOF */
    n = 0;
    while (scanf("%d", &nums[n]) == 1) {
        n++;
    }

    /* 用雙層迴圈枚舉所有配對，計算互質對數 / use nested loops to enumerate all pairs and count coprime ones */
    count = 0;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (gcd(nums[i], nums[j]) == 1) {
                count++;
            }
        }
    }

    /* 輸出互質對總數 / print the total count of coprime pairs */
    printf("%d\n", count);

    return 0;
}
