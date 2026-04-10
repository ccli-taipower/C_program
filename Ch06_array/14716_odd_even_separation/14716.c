/*
 * NTHU EE2310 - 題目 14716: Odd Even Separation
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14716/
 *
 * 【題目說明】
 * 讀入 n 個整數，將奇數輸出在第一行，偶數輸出在第二行。
 * 保持原始輸入順序。0 視為偶數。
 * 注意：每行最後一個數字後面也有一個空格（trailing space），再換行。
 *
 * 範例：10, [3,0,5,28,6,45,-23,6,7,-3]
 *   奇數：3 5 45 -23 7 -3 （trailing space）
 *   偶數：0 28 6 6 （trailing space）
 *
 * 【解題策略】
 * 1. 讀入 n，再讀入所有整數存入陣列。
 * 2. 遍歷陣列，將奇數（num % 2 != 0）依序輸出，每個後面加空格。
 * 3. 換行後，再遍歷陣列，將偶數（num % 2 == 0）依序輸出，每個後面加空格。
 * 4. 最後換行。
 * 注意：負數的奇偶判斷：(-23) % 2 == -1 != 0，故為奇數，判斷時用 != 0。
 */
#include <stdio.h>

int main(void) {
    int n;          /* 輸入數字個數 */
    int nums[1000]; /* 儲存所有數字 */
    int i;

    /* 讀入數字個數 */
    scanf("%d", &n);

    /* 讀入所有數字 */
    for (i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    /* 輸出奇數（trailing space） */
    for (i = 0; i < n; i++) {
        if (nums[i] % 2 != 0) {
            printf("%d ", nums[i]);
        }
    }
    printf("\n");

    /* 輸出偶數（trailing space） */
    for (i = 0; i < n; i++) {
        if (nums[i] % 2 == 0) {
            printf("%d ", nums[i]);
        }
    }
    printf("\n");

    return 0;
}
