/*
 * NTHU EE2310 - 題目 14825: Longest Common Subsequence
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 11 章（遞迴）
 *   如果不知道如何解題，請參考課本第 11 章的說明。
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
 */
#include <stdio.h>
#include <string.h>

#define MAXLEN 20  /* 字串最大長度（含 '\0' 緩衝） */

static char s1[MAXLEN];           /* 第一個字串 */
static char s2[MAXLEN];           /* 第二個字串 */
static int memo[MAXLEN][MAXLEN];  /* memo[i][j] = LCS(s1+i, s2+j)，-1 表示未計算 */
static int len1, len2;            /* 兩個字串的長度 */

/* 遞迴計算 LCS(s1[i..], s2[j..]) 並使用記憶化 */
static int lcs(int i, int j) {
    /* 基底情況：任一字串已到尾端 */
    if (i == len1 || j == len2) return 0;

    /* 若已計算過，直接回傳記憶的結果 */
    if (memo[i][j] != -1) return memo[i][j];

    int result;
    if (s1[i] == s2[j]) {
        /* 首字元相同：LCS 長度加 1 並遞迴處理剩餘字串 */
        result = 1 + lcs(i + 1, j + 1);
    } else {
        /* 首字元不同：取兩種遞迴結果的較大值 */
        int a = lcs(i + 1, j);   /* 跳過 s1 的首字元 */
        int b = lcs(i, j + 1);   /* 跳過 s2 的首字元 */
        result = (a > b) ? a : b;
    }

    /* 儲存計算結果以供後續使用 */
    memo[i][j] = result;
    return result;
}

int main(void) {
    int i, j;

    /* 讀入兩個字串 */
    if (scanf("%19s %19s", s1, s2) != 2) return 0;

    len1 = (int)strlen(s1);
    len2 = (int)strlen(s2);

    /* 初始化記憶化陣列（-1 表示尚未計算） */
    for (i = 0; i < MAXLEN; i++) {
        for (j = 0; j < MAXLEN; j++) {
            memo[i][j] = -1;
        }
    }

    /* 輸出最長公共子序列的長度 */
    printf("%d\n", lcs(0, 0));

    return 0;
}
