/*
 * NTHU EE2310 - 題目 14708: Longest Double Palindrome
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 5 章（函數）
 *   如果不知道如何解題，請參考課本第 5 章的說明。
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
 */
#include <stdio.h>

#define MAXN 100

/* 檢查 arr[start..end] 是否為迴文（正讀反讀相同） */
int is_palindrome(int arr[], int start, int end) {
    int lo = start;
    int hi = end;
    while (lo < hi) {
        if (arr[lo] != arr[hi])
            return 0;  /* 不是迴文 */
        lo++;
        hi--;
    }
    return 1;  /* 是迴文 */
}

int main(void) {
    int n;                  /* 序列長度 */
    int arr[MAXN];          /* 整數序列 */
    int i;                  /* 迴圈索引 */
    int s, e, m;            /* 子陣列起點、終點、分割點 */
    int best_s, best_e;     /* 最佳答案的起點和終點 */
    int best_len;           /* 最佳答案的長度 */
    int cur_len;            /* 當前子陣列的長度 */

    /* 讀入序列長度和各元素 */
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    /* 初始化：尚未找到任何雙重迴文 */
    best_s = 0;
    best_e = 0;
    best_len = 0;

    /* 枚舉所有子陣列的起點 s 和終點 e */
    for (s = 0; s < n; s++) {
        for (e = s + 1; e < n; e++) {
            cur_len = e - s + 1;
            /* 只考慮比目前最佳答案更長（或同長，以更新為最後出現）的子陣列 */
            if (cur_len < best_len)
                continue;
            /* 枚舉分割點 m：第一段 [s,m]，第二段 [m+1,e] */
            for (m = s; m < e; m++) {
                if (is_palindrome(arr, s, m) && is_palindrome(arr, m + 1, e)) {
                    /* 找到一個雙重迴文 */
                    if (cur_len >= best_len) {
                        /* 同長度或更長，更新為最後出現的 */
                        best_len = cur_len;
                        best_s = s;
                        best_e = e;
                    }
                    break;  /* 此子陣列已確認為雙重迴文，不需繼續試分割點 */
                }
            }
        }
    }

    /* 輸出結果：各元素以空格分隔 */
    for (i = best_s; i <= best_e; i++) {
        if (i > best_s)
            printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");

    return 0;
}
