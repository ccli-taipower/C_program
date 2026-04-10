/*
 * NTHU EE2310 - 題目 14877: Word Sorting
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 11 章（字串）
 *   如果不知道如何解題，請參考課本第 11 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14877/
 *
 * 【題目說明】
 * 讀入若干單字（長度 ≤ m，0 < n ≤ 1e5，0 < m ≤ 80），
 * 依照以下鍵值由高到低排序後輸出：
 *   1. 較短的單字排前面。
 *   2. 大寫字母較少的排前面。
 *   3. 母音（a/e/i/o/u，不分大小寫）較少的排前面。
 *   4. 以 strcmp() 的字典順序排列。
 *
 * 【解題策略】
 * 使用 qsort() 搭配自訂比較函式，在比較函式中依序套用上述四個鍵值。
 * 因為比較函式完整編碼所有條件，即使排序不穩定也能得到正確結果。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN   100005   /* 最大單字數量 */
#define MAXLEN 128      /* 單字緩衝區長度 */

/* 全域陣列，儲存所有讀入的單字 */
static char words[MAXN][MAXLEN];

/* 判斷字元是否為母音（不分大小寫） */
static int is_vowel(char c) {
    switch (c) {
        case 'a': case 'e': case 'i': case 'o': case 'u':
        case 'A': case 'E': case 'I': case 'O': case 'U':
            return 1;
        default:
            return 0;
    }
}

/* 計算字串中大寫字母的數量 */
static int count_upper(const char *s) {
    int cnt = 0;
    for (; *s; ++s) {
        if (*s >= 'A' && *s <= 'Z') ++cnt;
    }
    return cnt;
}

/* 計算字串中母音的數量（不分大小寫） */
static int count_vowels(const char *s) {
    int cnt = 0;
    for (; *s; ++s) {
        if (is_vowel(*s)) ++cnt;
    }
    return cnt;
}

/*
 * cmp_word：qsort 比較函式
 * 依序比較四個鍵值：長度、大寫數量、母音數量、字典順序
 */
static int cmp_word(const void *pa, const void *pb) {
    const char *a = (const char *)pa;
    const char *b = (const char *)pb;

    /* 鍵值 1：長度較短的排前面 */
    int la = (int)strlen(a);
    int lb = (int)strlen(b);
    if (la != lb) return la - lb;

    /* 鍵值 2：大寫字母較少的排前面 */
    int ua = count_upper(a);
    int ub = count_upper(b);
    if (ua != ub) return ua - ub;

    /* 鍵值 3：母音較少的排前面 */
    int va = count_vowels(a);
    int vb = count_vowels(b);
    if (va != vb) return va - vb;

    /* 鍵值 4：字典順序（strcmp） */
    return strcmp(a, b);
}

int main(void) {
    int n = 0;   /* 已讀入的單字數量 */

    /* 逐一讀入單字，直到 EOF */
    while (n < MAXN && scanf("%127s", words[n]) == 1) {
        ++n;
    }

    /* 使用 qsort 排序 */
    qsort(words, (size_t)n, sizeof(words[0]), cmp_word);

    /* 輸出排序後的單字，每字一行 */
    for (int i = 0; i < n; ++i) {
        printf("%s\n", words[i]);
    }

    return 0;
}
