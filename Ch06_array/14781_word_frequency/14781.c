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
 */
#include <stdio.h>
#include <string.h>

#define MAXWORDS 100
#define MAXLEN   85  /* 每行最多 80 字元，單字長度不超過此值 */

char words[MAXWORDS][MAXLEN]; /* 不同單字 */
int  freq[MAXWORDS];           /* 對應頻率 */
int  count;                    /* 不同單字的數量 */

/* 比較函式：先比頻率，頻率相同則比字典序 */
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

    /* 讀入所有 token 並統計頻率 */
    while (scanf("%s", token) == 1) {
        /* 搜尋是否已存在 */
        for (i = 0; i < count; i++) {
            if (strcmp(words[i], token) == 0) {
                freq[i]++;
                break;
            }
        }
        /* 若不存在，新增 */
        if (i == count && count < MAXWORDS) {
            strncpy(words[count], token, MAXLEN - 1);
            words[count][MAXLEN - 1] = '\0';
            freq[count] = 1;
            count++;
        }
    }

    /* 選擇排序：依（頻率升序，字典序升序） */
    for (i = 0; i < count - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < count; j++) {
            if (less_than(j, min_idx))
                min_idx = j;
        }
        if (min_idx != i) {
            /* 交換 words[i] 與 words[min_idx] */
            strncpy(tmp_word, words[i], MAXLEN - 1);
            strncpy(words[i], words[min_idx], MAXLEN - 1);
            strncpy(words[min_idx], tmp_word, MAXLEN - 1);
            /* 交換 freq[i] 與 freq[min_idx] */
            tmp_freq = freq[i];
            freq[i]  = freq[min_idx];
            freq[min_idx] = tmp_freq;
        }
    }

    /* 輸出結果 */
    for (i = 0; i < count; i++)
        printf("%d %s\n", freq[i], words[i]);

    return 0;
}
