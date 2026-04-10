/*
 * NTHU EE2310 - 題目 14702: Print Values in Sequence
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14702/
 *
 * 【題目說明】
 * 輸入 n 個數，將奇數位置（第 1、3、5... 個）的數印在第一行，
 * 偶數位置（第 2、4、6... 個）的數印在第二行。
 * 每行末尾數字後面有一個空格，然後換行。
 *
 * 【解題策略】
 * 1. 讀入 n，再用迴圈讀入每個數字。
 * 2. 判斷索引（從 1 開始）的奇偶性：
 *    - 奇數索引 → 印到第一行緩衝
 *    - 偶數索引 → 印到第二行緩衝
 * 3. 輸出格式：每個數字後面緊跟一個空格，最後換行。
 *    （即每行末尾有 trailing space）
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入整數 n，表示接下來有 n 個數字要輸入。
 * 2. 用迴圈將 n 個數字依序讀入陣列 nums[0..n-1] 儲存。
 * 3. 第一行輸出：從索引 0 開始，每次跳 2（即 0, 2, 4...），
 *    這些對應第 1, 3, 5... 個輸入數字（奇數位置）。
 *    每個數字後面接一個空格，全部輸出後換行。
 * 4. 第二行輸出：從索引 1 開始，每次跳 2（即 1, 3, 5...），
 *    這些對應第 2, 4, 6... 個輸入數字（偶數位置）。
 *    每個數字後面接一個空格，全部輸出後換行。
 * 5. 注意：題目要求每行末尾有 trailing space，故直接 printf("%d ", x)。
 *
 * English:
 * 1. Read integer n, indicating how many numbers will follow.
 * 2. Use a loop to read all n numbers into array nums[0..n-1].
 * 3. First output line: iterate indices 0, 2, 4, ... (odd-position numbers,
 *    1-based), printing each followed by a space, then a newline.
 * 4. Second output line: iterate indices 1, 3, 5, ... (even-position numbers,
 *    1-based), printing each followed by a space, then a newline.
 * 5. Note: trailing space after the last number on each line is intentional
 *    per the problem specification.
 */
#include <stdio.h>

int main(void) {
    int n;           /* 輸入數字個數 / number of input integers */
    int nums[1000];  /* 儲存所有數字 / store all numbers */
    int i;

    /* 讀入數字個數 / read the count of numbers */
    scanf("%d", &n);

    /* 讀入所有數字 / read all numbers */
    for (i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    /* 輸出奇數位置（索引 0, 2, 4...，即第 1, 3, 5... 個）/ print odd-position numbers (indices 0,2,4,...) */
    for (i = 0; i < n; i += 2) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    /* 輸出偶數位置（索引 1, 3, 5...，即第 2, 4, 6... 個）/ print even-position numbers (indices 1,3,5,...) */
    for (i = 1; i < n; i += 2) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}
