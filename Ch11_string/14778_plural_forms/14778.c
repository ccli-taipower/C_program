/*
 * NTHU EE2310 - 題目 14778: Plural Forms
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 11 章（字串）
 *   如果不知道如何解題，請參考課本第 11 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14778/
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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 使用 scanf 持續讀入單字，直到 EOF 為止。
 * 2. 取得單字長度 len，並記錄最後一個字元 last 與倒數第二個字元 second_last。
 * 3. 若長度 >= 2，先判斷字尾是否為 "ch" 或 "sh"（兩字元後綴），是則加 "es"。
 * 4. 接著檢查字尾單一字元：s 或 x → 加 "es"；z → 再看前一字元是否也是 z：
 *    - 若非 z（單一 z），則加 "zes"（等同雙寫 z 後加 "es"）；
 *    - 若是 z（zz 結尾），則直接加 "es"。
 * 5. 字尾為 y 時，呼叫 is_vowel 判斷前一字元：
 *    - 是母音 → 加 "s"；
 *    - 非母音 → 截斷 y，加 "ies"。
 * 6. 其餘所有情形一律加 "s"。
 * 7. 對長度為 1 的單字，以相同邏輯做特殊處理（無 second_last 可用）。
 *
 * English:
 * 1. Read words one by one with scanf until EOF.
 * 2. Record the word length, the last character, and the second-to-last character.
 * 3. For length >= 2, first check if the suffix is "ch" or "sh" → append "es".
 * 4. Then check single-character suffixes: s or x → "es"; z → inspect the
 *    preceding character: single z → append "zes"; double z → append "es".
 * 5. For suffix 'y', call is_vowel on the preceding character:
 *    vowel → append "s"; consonant → truncate 'y' and append "ies".
 * 6. All other cases → append "s".
 * 7. Handle single-character words separately with the same logic (no second_last).
 */
#include <stdio.h>
#include <string.h>

/* 判斷字元是否為母音 / check whether a character is a vowel */
static int is_vowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int main(void) {
    char word[100];   /* 存放讀入的單字 / buffer for the input word */

    /* 逐一讀入單字，直到 EOF / read words one by one until EOF */
    while (scanf("%s", word) == 1) {
        int len = (int)strlen(word);   /* 單字長度 / word length */
        char last = word[len - 1];     /* 最後一個字元 / last character */

        if (len >= 2) {
            char second_last = word[len - 2];   /* 倒數第二個字元 / second-to-last character */

            /* 規則 1：字尾為 ch 或 sh → 加 "es" / Rule 1: suffix "ch" or "sh" → append "es" */
            if ((second_last == 'c' && last == 'h') ||
                (second_last == 's' && last == 'h')) {
                printf("%ses\n", word);
            }
            /* 規則 1：字尾為單一字元 s 或 x → 加 "es" / Rule 1: single suffix 's' or 'x' → append "es" */
            else if (last == 's' || last == 'x') {
                printf("%ses\n", word);
            }
            /* 規則 1：字尾為 z → 若前一字元不是 z，先重複 z 再加 "es"；
             *                    若前一字元已是 z（即 zz 結尾），直接加 "es"
             * Rule 1: suffix 'z' → if preceded by non-z, double the z then add "es";
             *                      if preceded by 'z' (i.e., "zz" ending), just add "es" */
            else if (last == 'z') {
                if (second_last != 'z') {
                    /* 單一 z 結尾：雙寫 z 後加 "es"（如 quiz → quizzes） / single z: double it then add "es" (e.g. quiz → quizzes) */
                    printf("%szes\n", word);
                } else {
                    /* zz 結尾：直接加 "es"（如 fizz → fizzes） / "zz" ending: just add "es" (e.g. fizz → fizzes) */
                    printf("%ses\n", word);
                }
            }
            /* 規則 2：字尾為 y / Rule 2: suffix 'y' */
            else if (last == 'y') {
                if (is_vowel(second_last)) {
                    /* 前一個字母是母音 → 加 "s" / preceding letter is a vowel → append "s" */
                    printf("%ss\n", word);
                } else {
                    /* 前一個字母不是母音 → 去掉 "y"，加 "ies" / preceding letter is a consonant → remove 'y', append "ies" */
                    word[len - 1] = '\0';
                    printf("%sies\n", word);
                }
            }
            /* 規則 3：其他情形 → 加 "s" / Rule 3: all other cases → append "s" */
            else {
                printf("%ss\n", word);
            }
        } else {
            /* 單字只有一個字元時的處理 / handle single-character words */
            if (last == 's' || last == 'x') {
                printf("%ses\n", word);
            } else if (last == 'z') {
                /* 單字元 z：雙寫後加 "es" / single-char 'z': double it then add "es" */
                printf("%szes\n", word);
            } else if (last == 'y') {
                /* 單字元 "y"，前無字母，視為非母音 → 替換為 "ies" / single-char "y", no preceding letter, treated as non-vowel → replace with "ies" */
                printf("ies\n");
            } else {
                printf("%ss\n", word);
            }
        }
    }

    return 0;
}
