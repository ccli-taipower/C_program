/*
 * NTHU EE2310 - 題目 14825: Longest Common Subsequence
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 15 章（遞迴）
 *   如果不知道如何解題，請參考課本第 15 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14825/
 *
 * 【題目說明】
 * 給定兩個英文小寫字串（長度各至多 16），以遞迴方式計算最長公共子序列（LCS）的長度。
 *
 * 範例：
 *   "kqblt" 與 "btqlk"  → 2
 *   "program" 與 "gramming" → 5
 *   "abcxyz" 與 "xyzabc" → 3
 *
 * 【遞迴公式】（題目指定）
 *   LCS(s1, s2)：
 *     若 s1 或 s2 為空字串：回傳 0
 *     若 s1[0] == s2[0]：回傳 1 + LCS(s1+1, s2+1)
 *     否則：回傳 max(LCS(s1+1, s2), LCS(s1, s2+1))
 *
 * 【解題策略】
 * 直接以遞迴實作上述公式，並使用記憶化（memoization）避免重複計算。
 * 以 memo[i][j] 儲存 LCS(s1+i, s2+j) 的結果（-1 表示尚未計算）。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入兩個字串 s1、s2，計算各自長度 len1、len2。
 * 2. 將記憶化陣列 memo[i][j] 全部初始化為 -1，表示尚未計算。
 * 3. 呼叫 lcs(0, 0)，代表從兩個字串的起始位置開始比較。
 * 4. 遞迴基底：若 i == len1 或 j == len2，表示至少一個字串已耗盡，回傳 0。
 * 5. 若 memo[i][j] != -1，直接回傳已快取的結果，避免重複計算（記憶化核心）。
 * 6. 若 s1[i] == s2[j]，兩字串首字元相同，LCS 長度加 1，遞迴計算 lcs(i+1, j+1)。
 * 7. 否則取 lcs(i+1, j) 與 lcs(i, j+1) 的較大值，對應跳過 s1 或 s2 的當前字元。
 * 8. 將計算結果存入 memo[i][j] 後回傳，最終輸出 lcs(0,0) 即為答案。
 *
 * English:
 * 1. Read two strings s1 and s2; compute their lengths len1 and len2.
 * 2. Initialize the memoization table memo[i][j] to -1 (not yet computed).
 * 3. Call lcs(0, 0) to begin comparing both strings from position 0.
 * 4. Base case: if i == len1 or j == len2, at least one string is exhausted; return 0.
 * 5. If memo[i][j] != -1, return the cached value immediately (the memoization key).
 * 6. If s1[i] == s2[j], the first characters match; add 1 and recurse with lcs(i+1, j+1).
 * 7. Otherwise, take the maximum of lcs(i+1, j) and lcs(i, j+1), skipping one character
 *    from either string.
 * 8. Store the result in memo[i][j] before returning; lcs(0,0) is the final answer.
 */
#include <stdio.h>
#include <string.h>

#define MAXLEN 20  /* 字串最大長度（含 '\0' 緩衝） / max string length (including '\0' buffer) */

static char s1[MAXLEN];           /* 第一個字串 / first string */
static char s2[MAXLEN];           /* 第二個字串 / second string */
static int memo[MAXLEN][MAXLEN];  /* memo[i][j] = LCS(s1+i, s2+j)，-1 表示未計算 / -1 means not yet computed */
static int len1, len2;            /* 兩個字串的長度 / lengths of the two strings */

/* 遞迴計算 LCS(s1[i..], s2[j..]) 並使用記憶化 / recursively compute LCS(s1[i..], s2[j..]) with memoization */
static int lcs(int i, int j) {
    /* 基底情況：任一字串已到尾端 / base case: one string is exhausted */
    if (i == len1 || j == len2) return 0;

    /* 若已計算過，直接回傳記憶的結果 / return cached result if already computed */
    if (memo[i][j] != -1) return memo[i][j];

    int result;
    if (s1[i] == s2[j]) {
        /* 首字元相同：LCS 長度加 1 並遞迴處理剩餘字串 / first chars match: LCS length +1, recurse on remainders */
        result = 1 + lcs(i + 1, j + 1);
    } else {
        /* 首字元不同：取兩種遞迴結果的較大值 / first chars differ: take max of two recursive results */
        int a = lcs(i + 1, j);   /* 跳過 s1 的首字元 / skip s1's first char */
        int b = lcs(i, j + 1);   /* 跳過 s2 的首字元 / skip s2's first char */
        result = (a > b) ? a : b;
    }

    /* 儲存計算結果以供後續使用 / store result for future reuse */
    memo[i][j] = result;
    return result;
}

int main(void) {
    int i, j;

    /* 讀入兩個字串 / read two strings */
    if (scanf("%19s %19s", s1, s2) != 2) return 0;

    len1 = (int)strlen(s1);
    len2 = (int)strlen(s2);

    /* 初始化記憶化陣列（-1 表示尚未計算） / initialize memoization table (-1 = not yet computed) */
    for (i = 0; i < MAXLEN; i++) {
        for (j = 0; j < MAXLEN; j++) {
            memo[i][j] = -1;
        }
    }

    /* 輸出最長公共子序列的長度 / print the length of the longest common subsequence */
    printf("%d\n", lcs(0, 0));

    return 0;
}
