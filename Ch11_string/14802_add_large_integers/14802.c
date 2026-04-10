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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 以字串形式讀入兩個大整數 a 和 b，取得各自的位數 la、lb。
 * 2. 初始化進位 carry = 0，結果索引 ri = 0，並將指標 ia、ib 分別指向 a、b 的最低位（最右端）。
 * 3. 當 ia >= 0、ib >= 0 或 carry > 0 時，逐位計算：
 *    - 取出 a[ia]、b[ib] 的數字（若已超出範圍則視為 0）。
 *    - 計算 sum = da + db + carry。
 *    - carry = sum / 10，結果該位 = sum % 10，存入 result[ri++]。
 * 4. 此時 result 為反向儲存，加入結尾 '\0' 後進行原地反轉。
 * 5. 輸出反轉後的 result 字串。
 *
 * English:
 * 1. Read two large integers a and b as strings; record their lengths la and lb.
 * 2. Initialize carry = 0, write index ri = 0, and set pointers ia, ib to the
 *    least-significant (rightmost) digits of a and b respectively.
 * 3. Loop while ia >= 0, ib >= 0, or carry > 0:
 *    - Extract digit from a[ia] and b[ib] (treat as 0 if out of range).
 *    - Compute sum = da + db + carry; new carry = sum / 10.
 *    - Store (sum % 10) + '0' into result[ri++].
 * 4. Null-terminate result (which is stored in reverse order), then reverse it
 *    in-place using a two-pointer swap.
 * 5. Print the reversed result string.
 */
#include <stdio.h>
#include <string.h>

#define MAXDIGITS 25   /* 結果字串緩衝區大小（最多 19 位 + 一些餘裕） / result buffer size (up to 19 digits + margin) */

int main(void) {
    char a[MAXDIGITS];    /* 第一個加數（字串） / first addend (string) */
    char b[MAXDIGITS];    /* 第二個加數（字串） / second addend (string) */
    char result[MAXDIGITS];   /* 結果字串（反向儲存，再反轉） / result string (stored reversed, then flipped) */

    /* 讀入兩個大整數 / read the two large integers */
    scanf("%s %s", a, b);

    int la = (int)strlen(a);   /* 第一個數的位數 / number of digits in a */
    int lb = (int)strlen(b);   /* 第二個數的位數 / number of digits in b */
    int carry = 0;             /* 進位值 / carry value */
    int ri = 0;                /* 結果字串的寫入索引 / write index for result */

    /* 從最低位（右端）逐位相加 / add digit by digit starting from the least significant (rightmost) */
    int ia = la - 1;   /* a 的當前位指標 / current digit pointer in a */
    int ib = lb - 1;   /* b 的當前位指標 / current digit pointer in b */

    while (ia >= 0 || ib >= 0 || carry > 0) {
        int da = (ia >= 0) ? (a[ia] - '0') : 0;   /* a 的當前位數字 / current digit of a */
        int db = (ib >= 0) ? (b[ib] - '0') : 0;   /* b 的當前位數字 / current digit of b */
        int sum = da + db + carry;                  /* 該位的和 / sum at this digit position */

        carry = sum / 10;              /* 計算新的進位 / compute new carry */
        result[ri++] = '0' + (sum % 10);   /* 儲存個位數字 / store the units digit */

        ia--;
        ib--;
    }

    /* 結果目前是反向儲存的，需要反轉 / result is currently stored in reverse, needs to be flipped */
    result[ri] = '\0';
    /* 反轉 result 字串 / reverse the result string in-place */
    for (int i = 0, j = ri - 1; i < j; i++, j--) {
        char tmp = result[i];
        result[i] = result[j];
        result[j] = tmp;
    }

    printf("%s\n", result);

    return 0;
}
