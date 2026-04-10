/*
 * NTHU EE2310 - 題目 14706: Digit Rotation
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 5 章（迴圈）
 *   如果不知道如何解題，請參考課本第 5 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14706/
 *
 * 【題目說明】
 * 對一個正整數做「數字旋轉」操作：
 *   - 將最後一個數字移到最前面（成為最高位）。
 *   - 若移到最前面的數字是 0，則不保留前導零（即丟棄該 0）。
 * 輸入：初始數字、旋轉次數 k
 * 輸出：共 k+1 行，第一行是原始數字，之後每行是旋轉一次的結果。
 *
 * 範例：1100100 旋轉 9 次
 *   1100100 → 最後一位 0 移到前面 → 0110010 → 去掉前導零 → 110010
 *   110010 → 最後一位 0 移到前面 → 011001 → 去掉前導零 → 11001
 *   11001 → 最後一位 1 移到前面 → 111001... 不對，最後一位是 1
 *   11001 最後一位是 1，移到前面 → 11100
 *   依此類推...
 *
 * 【解題策略】
 * 使用字串（字元陣列）儲存數字，避免大數溢位問題。
 * 1. 讀入數字字串與旋轉次數 k。
 * 2. 每次旋轉：
 *    a. 取出最後一個字元（最低位）。
 *    b. 將其他字元向右移一位（空出最高位）。
 *    c. 將取出的字元放到最高位。
 *    d. 若最高位是 '0'，則整個字串向左移一位（去掉前導零）。
 * 3. 每次操作前輸出當前數字。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 以字串方式讀入數字（避免大數整數溢位），並讀入旋轉次數 k。
 * 2. 先輸出原始數字（第一行輸出）。
 * 3. 進行 k 次旋轉迴圈，每次操作如下：
 *    a. 取得目前字串長度 len，記錄最後一個字元 last（最低位）。
 *    b. 將字串中所有字元向右移一位（從後往前），空出最高位（index 0）。
 *    c. 把 last 放到 num[0]（最高位），完成旋轉。
 *    d. 若 num[0] == '0'，表示出現前導零：將整個字串向左移一位，並把末尾設為 '\0'，縮短長度。
 * 4. 每次旋轉完成後輸出當前數字。
 * 5. 重複步驟 3-4，共執行 k 次。
 *
 * English:
 * 1. Read the number as a string (to avoid large integer overflow) and read rotation count k.
 * 2. Print the original number (first line of output).
 * 3. Execute a loop of k rotations; each iteration does the following:
 *    a. Compute current string length len; save the last character last (least significant digit).
 *    b. Right-shift all characters by one position (from back to front) to open up index 0.
 *    c. Place last into num[0] (most significant position), completing the rotation.
 *    d. If num[0] == '0', a leading zero has appeared: left-shift the entire string by one and set the last position to '\0'.
 * 4. Print the resulting number after each rotation.
 * 5. Repeat steps 3-4 for all k rotations.
 */
#include <stdio.h>
#include <string.h>

int main(void) {
    char num[300];   /* 儲存數字的字元陣列 / character array to store the number */
    int k;           /* 旋轉次數 / number of rotations */
    int len;         /* 數字長度 / current length of the number string */
    char last;       /* 最後一個數字字元 / last digit character */
    int i, iter;

    /* 讀入數字與旋轉次數 / read the number string and rotation count */
    scanf("%s %d", num, &k);

    /* 輸出原始數字 / print the original number */
    printf("%s\n", num);

    /* 進行 k 次旋轉 / perform k rotations */
    for (iter = 0; iter < k; iter++) {
        len = (int)strlen(num);

        /* 取出最後一個字元 / save the last character (least significant digit) */
        last = num[len - 1];

        /* 將其餘字元向右移一位 / shift all other characters one position to the right */
        for (i = len - 1; i > 0; i--) {
            num[i] = num[i - 1];
        }

        /* 將最後一個字元放到最前面 / place the saved character at the front */
        num[0] = last;

        /* 若最高位為 '0'，去掉前導零（整個字串左移，長度減一）/ if leading zero appears, remove it by left-shifting the string */
        if (num[0] == '0') {
            for (i = 0; i < len - 1; i++) {
                num[i] = num[i + 1];
            }
            num[len - 1] = '\0';
        }

        /* 輸出旋轉後的數字 / print the number after rotation */
        printf("%s\n", num);
    }

    return 0;
}
