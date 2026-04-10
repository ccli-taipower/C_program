/*
 * NTHU EE2310 - 題目 14700: Carry System Conversion
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 5 章（迴圈）
 *   如果不知道如何解題，請參考課本第 5 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14700/
 *
 * 【題目說明】
 * 將一個數從某個進位系統（2、8 或 10 進位）轉換到另一個進位系統。
 * 輸入：
 *   第一行：來源進位（2、8 或 10）
 *   第二行：數字的位數 n
 *   接下來 n 個數：數字各位數（由高位到低位）
 *   最後一個數：目標進位（2、8 或 10）
 * 輸出：轉換後的各位數，每行一個（由高位到低位）
 *
 * 【解題策略】
 * 1. 先將輸入數字各位數依來源進位轉換為十進位整數值。
 * 2. 再將十進位整數值轉換為目標進位，用陣列儲存各位數。
 * 3. 輸出時由高位到低位，每行印一個數字。
 * 若目標進位與來源進位相同，直接輸出原始數字即可（轉換後結果相同）。
 * 若輸入值為 0，輸出 0。
 */
#include <stdio.h>

int main(void) {
    int src_base;       /* 來源進位 */
    int n;              /* 輸入數字的位數 */
    int digits[200];    /* 輸入數字各位數（由高位到低位） */
    int dst_base;       /* 目標進位 */
    long long value;    /* 十進位值 */
    int result[200];    /* 結果各位數（由低位到高位） */
    int result_len;     /* 結果位數 */
    int i;

    /* 讀入來源進位 */
    scanf("%d", &src_base);

    /* 讀入位數 n */
    scanf("%d", &n);

    /* 讀入各位數 */
    for (i = 0; i < n; i++) {
        scanf("%d", &digits[i]);
    }

    /* 讀入目標進位 */
    scanf("%d", &dst_base);

    /* 步驟一：將輸入轉換為十進位值 */
    value = 0;
    for (i = 0; i < n; i++) {
        value = value * src_base + digits[i];
    }

    /* 步驟二：將十進位值轉換為目標進位 */
    if (value == 0) {
        /* 特殊情況：值為 0 */
        printf("0\n");
        return 0;
    }

    result_len = 0;
    while (value > 0) {
        result[result_len] = (int)(value % dst_base);
        result_len++;
        value /= dst_base;
    }

    /* 步驟三：由高位到低位輸出 */
    for (i = result_len - 1; i >= 0; i--) {
        printf("%d\n", result[i]);
    }

    return 0;
}
