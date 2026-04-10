/*
 * NTHU EE2310 - 題目 14778: Plural Forms
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 7 章（字串）
 *   如果不知道如何解題，請參考課本第 7 章的說明。
 *
 * 【題目說明】
 * 將英文名詞轉換為複數形式，依序讀入單字直到 EOF。
 * 轉換規則如下：
 *   1. 字尾為 ch、sh、s、x → 加上 "es"
 *      字尾為單一 z（前一個字元不是 z）→ 先重複 z，再加 "es"（如 quiz → quizzes）
 *      字尾為 zz → 直接加 "es"（如 fizz → fizzes）
 *   2. 字尾為 y：
 *      - 前一個字母為母音（a、e、i、o、u）→ 加上 "s"
 *      - 前一個字母不是母音 → 將 "y" 替換為 "ies"
 *   3. 其他情形 → 加上 "s"
 *
 * 【解題策略】
 * 使用 strlen() 取得字串長度，再根據字尾字元判斷適用哪條規則。
 * 對於規則 1，需同時檢查字尾兩個字元（ch、sh）或單一字元（s、z、x）。
 * 注意：字尾為單一 z（前一字元非 z）時，需先將 z 重複（雙寫）再加 "es"。
 */
#include <stdio.h>
#include <string.h>

/* 判斷字元是否為母音 */
static int is_vowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int main(void) {
    char word[100];   /* 存放讀入的單字 */

    /* 逐一讀入單字，直到 EOF */
    while (scanf("%s", word) == 1) {
        int len = (int)strlen(word);   /* 單字長度 */
        char last = word[len - 1];     /* 最後一個字元 */

        if (len >= 2) {
            char second_last = word[len - 2];   /* 倒數第二個字元 */

            /* 規則 1：字尾為 ch 或 sh → 加 "es" */
            if ((second_last == 'c' && last == 'h') ||
                (second_last == 's' && last == 'h')) {
                printf("%ses\n", word);
            }
            /* 規則 1：字尾為單一字元 s 或 x → 加 "es" */
            else if (last == 's' || last == 'x') {
                printf("%ses\n", word);
            }
            /* 規則 1：字尾為 z → 若前一字元不是 z，先重複 z 再加 "es"；
             *                    若前一字元已是 z（即 zz 結尾），直接加 "es" */
            else if (last == 'z') {
                if (second_last != 'z') {
                    /* 單一 z 結尾：雙寫 z 後加 "es"（如 quiz → quizzes） */
                    printf("%szes\n", word);
                } else {
                    /* zz 結尾：直接加 "es"（如 fizz → fizzes） */
                    printf("%ses\n", word);
                }
            }
            /* 規則 2：字尾為 y */
            else if (last == 'y') {
                if (is_vowel(second_last)) {
                    /* 前一個字母是母音 → 加 "s" */
                    printf("%ss\n", word);
                } else {
                    /* 前一個字母不是母音 → 去掉 "y"，加 "ies" */
                    word[len - 1] = '\0';
                    printf("%sies\n", word);
                }
            }
            /* 規則 3：其他情形 → 加 "s" */
            else {
                printf("%ss\n", word);
            }
        } else {
            /* 單字只有一個字元時的處理 */
            if (last == 's' || last == 'x') {
                printf("%ses\n", word);
            } else if (last == 'z') {
                /* 單字元 z：雙寫後加 "es" */
                printf("%szes\n", word);
            } else if (last == 'y') {
                /* 單字元 "y"，前無字母，視為非母音 → 替換為 "ies" */
                printf("ies\n");
            } else {
                printf("%ss\n", word);
            }
        }
    }

    return 0;
}
