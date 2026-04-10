/*
 * NTHU EE2310 - 題目 14779: Word Similarity
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 11 章（字串）
 *   如果不知道如何解題，請參考課本第 11 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14779/
 *
 * 【題目說明】
 * 判斷兩個單字是否「相似」。滿足以下任一條件即為相似：
 *   1. 長度相同：交換其中一個字中某對相鄰字元後，可得到另一個字
 *      （需恰好一次交換，且必須真的改變字元順序）
 *   2. 長度差 1：從較長的字中刪除某一個字元後，可得到較短的字
 *
 * 【解題策略】
 * 條件 1：逐一嘗試交換相鄰字元，確認是否等於另一個字。
 *   - 若兩字原本就完全相同，則不算相似（未發生實際改變）。
 * 條件 2：逐一嘗試從較長的字刪除每個位置的字元，確認是否等於較短的字。
 *
 * 單字最大長度：80 個字元。
 */
#include <stdio.h>
#include <string.h>

#define MAXLEN 85   /* 單字最大緩衝區長度 */

/*
 * check_swap：判斷是否可透過交換 a 中某對相鄰字元得到 b
 * 前提：strlen(a) == strlen(b)
 * 回傳：1 表示可以，0 表示不行
 */
static int check_swap(const char *a, const char *b) {
    int len = (int)strlen(a);
    char tmp[MAXLEN];

    /* 若兩字完全相同，不算相似 */
    if (strcmp(a, b) == 0) {
        return 0;
    }

    /* 嘗試交換 a 中每對相鄰字元，看是否能得到 b */
    for (int i = 0; i < len - 1; i++) {
        /* 複製 a 到 tmp */
        strcpy(tmp, a);
        /* 交換位置 i 和 i+1 */
        char c = tmp[i];
        tmp[i] = tmp[i + 1];
        tmp[i + 1] = c;
        /* 比較是否等於 b */
        if (strcmp(tmp, b) == 0) {
            return 1;
        }
    }
    return 0;
}

/*
 * check_delete：判斷是否可從 longer 中刪除某個字元得到 shorter
 * 前提：strlen(longer) == strlen(shorter) + 1
 * 回傳：1 表示可以，0 表示不行
 */
static int check_delete(const char *longer, const char *shorter) {
    int llen = (int)strlen(longer);
    int slen = (int)strlen(shorter);
    char tmp[MAXLEN];

    /* 嘗試刪除 longer 中每個位置的字元 */
    for (int i = 0; i < llen; i++) {
        /* 建構刪除位置 i 後的字串 */
        int k = 0;
        for (int j = 0; j < llen; j++) {
            if (j != i) {
                tmp[k++] = longer[j];
            }
        }
        tmp[k] = '\0';
        /* 比較是否等於 shorter */
        if (strcmp(tmp, shorter) == 0) {
            return 1;
        }
    }
    (void)slen;   /* 避免未使用警告 */
    return 0;
}

int main(void) {
    char w1[MAXLEN], w2[MAXLEN];   /* 兩個輸入單字 */

    /* 逐行讀入一對單字，直到 EOF */
    while (scanf("%s %s", w1, w2) == 2) {
        int len1 = (int)strlen(w1);
        int len2 = (int)strlen(w2);
        int result = 0;   /* 預設不相似 */

        if (len1 == len2) {
            /* 長度相同：檢查交換相鄰字元 */
            result = check_swap(w1, w2);
        } else if (len1 == len2 + 1) {
            /* w1 比 w2 長 1：從 w1 刪除一個字元 */
            result = check_delete(w1, w2);
        } else if (len2 == len1 + 1) {
            /* w2 比 w1 長 1：從 w2 刪除一個字元 */
            result = check_delete(w2, w1);
        }
        /* 長度差超過 1：一定不相似 */

        printf("%s\n", result ? "yes" : "no");
    }

    return 0;
}
