/*
 * NTHU EE2310 - 題目 14708: Longest Double Palindrome
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 8 章（函式）
 *   如果不知道如何解題，請參考課本第 8 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14708/
 *
 * 【題目說明】
 * 迴文（palindrome）是指正讀和反讀都相同的序列，長度至少為 1。
 * 雙重迴文（double palindrome）是指由兩段迴文串接而成的序列。
 * 給定 n 個整數的序列，找出最長的連續子陣列，使其為雙重迴文。
 * 若有多個長度相同的最長雙重迴文，輸出最後（最右邊）一個。
 *
 * 【解題策略】
 * 1. 用 is_palindrome(arr, start, end) 函數檢查子陣列是否為迴文
 * 2. 枚舉所有子陣列的起點 s 和終點 e
 * 3. 對每個子陣列，枚舉所有分割點 m（第一段為 [s,m]，第二段為 [m+1,e]）
 * 4. 若兩段都是迴文，則此子陣列為雙重迴文，記錄最長（同長取最後）的結果
 * 5. 輸出結果子陣列的元素（以空格分隔）
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入序列長度 n 及各整數元素到 arr[]。
 * 2. 實作 is_palindrome(arr, start, end)：使用雙指標（lo、hi）從兩端向中間比較，若任意位置不相等則返回 0，否則返回 1。
 * 3. 初始化 best_len = 0，best_s = best_e = 0，表示尚未找到任何雙重迴文。
 * 4. 以雙層 for 迴圈枚舉所有起點 s 和終點 e（長度至少為 2）；若 cur_len < best_len 則跳過（剪枝）。
 * 5. 在每個 [s,e] 範圍內，以 for 迴圈枚舉分割點 m（m 從 s 到 e-1）：
 *    - 若 arr[s..m] 和 arr[m+1..e] 都是迴文，則 [s,e] 為雙重迴文；
 *    - 若 cur_len >= best_len，更新 best_len、best_s、best_e（同長取最後出現）；
 *    - 確認後即 break，無需繼續試其他分割點。
 * 6. 所有枚舉結束後，輸出 arr[best_s..best_e]，各元素以空格分隔。
 *
 * English:
 * 1. Read sequence length n and all integer elements into arr[].
 * 2. Implement is_palindrome(arr, start, end) using two pointers (lo, hi) moving inward; return 0 if any mismatch, 1 otherwise.
 * 3. Initialize best_len = 0, best_s = best_e = 0, indicating no double palindrome found yet.
 * 4. Use nested for loops to enumerate all start s and end e (length >= 2); skip (prune) if cur_len < best_len.
 * 5. For each range [s,e], iterate over split point m from s to e-1:
 *    - If both arr[s..m] and arr[m+1..e] are palindromes, [s,e] is a double palindrome;
 *    - Update best_len, best_s, best_e if cur_len >= best_len (keeps the last occurrence for ties);
 *    - Break immediately after confirmation, no need to try other split points.
 * 6. After all enumeration, print arr[best_s..best_e] with elements separated by spaces.
 */
#include <stdio.h>

#define MAXN 100

/* 檢查 arr[start..end] 是否為迴文（正讀反讀相同） / check if arr[start..end] is a palindrome */
int is_palindrome(int arr[], int start, int end) {
    int lo = start;
    int hi = end;
    while (lo < hi) {
        if (arr[lo] != arr[hi])
            return 0;  /* 不是迴文 / not a palindrome */
        lo++;
        hi--;
    }
    return 1;  /* 是迴文 / is a palindrome */
}

int main(void) {
    int n;                  /* 序列長度 / sequence length */
    int arr[MAXN];          /* 整數序列 / integer sequence */
    int i;                  /* 迴圈索引 / loop index */
    int s, e, m;            /* 子陣列起點、終點、分割點 / subarray start, end, and split point */
    int best_s, best_e;     /* 最佳答案的起點和終點 / start and end of the best answer */
    int best_len;           /* 最佳答案的長度 / length of the best answer */
    int cur_len;            /* 當前子陣列的長度 / length of the current subarray */

    /* 讀入序列長度和各元素 / read sequence length and all elements */
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    /* 初始化：尚未找到任何雙重迴文 / initialize: no double palindrome found yet */
    best_s = 0;
    best_e = 0;
    best_len = 0;

    /* 枚舉所有子陣列的起點 s 和終點 e / enumerate all subarrays by start s and end e */
    for (s = 0; s < n; s++) {
        for (e = s + 1; e < n; e++) {
            cur_len = e - s + 1;
            /* 只考慮比目前最佳答案更長（或同長，以更新為最後出現）的子陣列 / skip subarrays shorter than current best */
            if (cur_len < best_len)
                continue;
            /* 枚舉分割點 m：第一段 [s,m]，第二段 [m+1,e] / enumerate split point m: first half [s,m], second half [m+1,e] */
            for (m = s; m < e; m++) {
                if (is_palindrome(arr, s, m) && is_palindrome(arr, m + 1, e)) {
                    /* 找到一個雙重迴文 / a double palindrome is found */
                    if (cur_len >= best_len) {
                        /* 同長度或更長，更新為最後出現的 / equal or longer length: update to this (later) occurrence */
                        best_len = cur_len;
                        best_s = s;
                        best_e = e;
                    }
                    break;  /* 此子陣列已確認為雙重迴文，不需繼續試分割點 / subarray confirmed as double palindrome, no need to try other split points */
                }
            }
        }
    }

    /* 輸出結果：各元素以空格分隔 / print the result: elements separated by spaces */
    for (i = best_s; i <= best_e; i++) {
        if (i > best_s)
            printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");

    return 0;
}
