/*
 * NTHU EE2310 - 題目 14781: Word Frequency
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14781/
 *
 * 【題目說明】
 * 讀取文字直到 EOF，統計每個「單字」出現的頻率。
 * 單字定義為以空白分隔的非空白字元序列（使用 scanf("%s") 讀取）。
 * 輸出格式：先按頻率由低到高排序，頻率相同時按字典序（ASCII）排序。
 * 每行輸出：「頻率 單字」。
 *
 * 【解題策略】
 * - 用字串陣列 words[100] 儲存不同的單字（最多 100 個）。
 * - 用 freq[100] 儲存對應頻率。
 * - 讀入每個 token，搜尋是否已存在，若是則頻率加一，否則新增。
 * - 全部讀完後，以插入排序（或選擇排序）依（頻率升序，字典序升序）排序。
 * - 輸出每組（頻率, 單字）。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 用 scanf("%s") 逐個讀取 token，直到 EOF。
 * 2. 對每個讀到的 token，線性搜尋 words[] 陣列，查看是否已存在：
 *    - 若找到（strcmp == 0），將對應的 freq[i] 加一，結束搜尋。
 *    - 若未找到（i == count），且 count < MAXWORDS，
 *      將 token 新增到 words[count]，設 freq[count] = 1，count 加一。
 * 3. 讀完所有 token 後，對 words[]/freq[] 執行選擇排序：
 *    - 比較函式 less_than(a, b)：先比頻率（升序），
 *      頻率相同則比字典序（ASCII 升序）。
 *    - 每輪找出最小元素的索引 min_idx，與當前位置 i 交換。
 * 4. 依序輸出排序後的每組「freq[i] words[i]」。
 *
 * English:
 * 1. Read tokens one by one with scanf("%s") until EOF.
 * 2. For each token, linearly search words[] for a match:
 *    - If found (strcmp == 0), increment freq[i] and stop the search.
 *    - If not found (i == count) and count < MAXWORDS, add token to
 *      words[count], set freq[count] = 1, and increment count.
 * 3. After reading all tokens, apply selection sort on the words[]/freq[]
 *    arrays using the comparator less_than(a, b):
 *    - Primary key: freq ascending; secondary key: lexicographic ascending.
 *    - Each round finds the minimum-index element and swaps it to position i.
 * 4. Print each sorted pair as "freq[i] words[i]" on its own line.
 */
#include <stdio.h>
#include <string.h>

#define MAXWORDS 100
#define MAXLEN   85  /* 每行最多 80 字元，單字長度不超過此值 */

char words[MAXWORDS][MAXLEN]; /* 不同單字 / distinct words */
int  freq[MAXWORDS];           /* 對應頻率 / corresponding frequencies */
int  count;                    /* 不同單字的數量 / number of distinct words */

/* 比較函式：先比頻率，頻率相同則比字典序 / comparator: sort by freq first, then lexicographically */
int less_than(int a, int b) {
    if (freq[a] != freq[b])
        return freq[a] < freq[b];
    return strcmp(words[a], words[b]) < 0;
}

int main(void) {
    char token[MAXLEN];
    int i, j, min_idx;
    char tmp_word[MAXLEN];
    int  tmp_freq;

    count = 0;

    /* 讀入所有 token 並統計頻率 / read all tokens and count frequencies */
    while (scanf("%s", token) == 1) {
        /* 搜尋是否已存在 / search if token already exists */
        for (i = 0; i < count; i++) {
            if (strcmp(words[i], token) == 0) {
                freq[i]++;
                break;
            }
        }
        /* 若不存在，新增 / if not found, add as a new entry */
        if (i == count && count < MAXWORDS) {
            strncpy(words[count], token, MAXLEN - 1);
            words[count][MAXLEN - 1] = '\0';
            freq[count] = 1;
            count++;
        }
    }

    /* 選擇排序：依（頻率升序，字典序升序）/ selection sort: by (freq asc, lexicographic asc) */
    for (i = 0; i < count - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < count; j++) {
            if (less_than(j, min_idx))
                min_idx = j;
        }
        if (min_idx != i) {
            /* 交換 words[i] 與 words[min_idx] / swap words[i] and words[min_idx] */
            strncpy(tmp_word, words[i], MAXLEN - 1);
            strncpy(words[i], words[min_idx], MAXLEN - 1);
            strncpy(words[min_idx], tmp_word, MAXLEN - 1);
            /* 交換 freq[i] 與 freq[min_idx] / swap freq[i] and freq[min_idx] */
            tmp_freq = freq[i];
            freq[i]  = freq[min_idx];
            freq[min_idx] = tmp_freq;
        }
    }

    /* 輸出結果 / print sorted results */
    for (i = 0; i < count; i++)
        printf("%d %s\n", freq[i], words[i]);

    return 0;
}
