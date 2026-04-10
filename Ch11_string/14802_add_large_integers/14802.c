/*
 * NTHU EE2310 - 題目 14802: Add Large Integers
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 11 章（字串）
 *   如果不知道如何解題，請參考課本第 11 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14802/
 *
 * 【題目說明】
 * 將兩個正整數相加，每個數最多 18 位數。
 * 以字串方式讀入，用字串加法手動計算，輸出其和。
 *
 * 【解題策略】
 * 兩個 18 位數相加，結果最多 19 位。
 * 從字串右端（個位數）開始逐位相加，記錄進位，將結果存入輸出字串。
 * 最後將結果字串反轉後輸出。
 */
#include <stdio.h>
#include <string.h>

#define MAXDIGITS 25   /* 結果字串緩衝區大小（最多 19 位 + 一些餘裕） */

int main(void) {
    char a[MAXDIGITS];    /* 第一個加數（字串） */
    char b[MAXDIGITS];    /* 第二個加數（字串） */
    char result[MAXDIGITS];   /* 結果字串（反向儲存，再反轉） */

    /* 讀入兩個大整數 */
    scanf("%s %s", a, b);

    int la = (int)strlen(a);   /* 第一個數的位數 */
    int lb = (int)strlen(b);   /* 第二個數的位數 */
    int carry = 0;             /* 進位值 */
    int ri = 0;                /* 結果字串的寫入索引 */

    /* 從最低位（右端）逐位相加 */
    int ia = la - 1;   /* a 的當前位指標 */
    int ib = lb - 1;   /* b 的當前位指標 */

    while (ia >= 0 || ib >= 0 || carry > 0) {
        int da = (ia >= 0) ? (a[ia] - '0') : 0;   /* a 的當前位數字 */
        int db = (ib >= 0) ? (b[ib] - '0') : 0;   /* b 的當前位數字 */
        int sum = da + db + carry;                  /* 該位的和 */

        carry = sum / 10;              /* 計算新的進位 */
        result[ri++] = '0' + (sum % 10);   /* 儲存個位數字 */

        ia--;
        ib--;
    }

    /* 結果目前是反向儲存的，需要反轉 */
    result[ri] = '\0';
    /* 反轉 result 字串 */
    for (int i = 0, j = ri - 1; i < j; i++, j--) {
        char tmp = result[i];
        result[i] = result[j];
        result[j] = tmp;
    }

    printf("%s\n", result);

    return 0;
}
