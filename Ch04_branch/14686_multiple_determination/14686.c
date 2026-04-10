/*
 * NTHU EE2310 - 題目 14686: Multiple determination
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 4 章（判斷）
 *   如果不知道如何解題，請參考課本第 4 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14686/
 *
 * 【題目說明】
 * 輸入一個整數 n，判斷它是否為 3 的倍數、5 的倍數、或兩者都是。
 * 輸出格式：
 *   - 同時是 3 和 5 的倍數：輸出 "Multiple of 3 and 5"
 *   - 只是 3 的倍數：輸出 "Multiple of 3"
 *   - 只是 5 的倍數：輸出 "Multiple of 5"
 *   - 都不是：輸出 "Not multiple of 3 or 5"
 *
 * 【解題策略】
 * 1. 讀入整數 n
 * 2. 判斷 n % 3 == 0（是否為 3 的倍數）
 * 3. 判斷 n % 5 == 0（是否為 5 的倍數）
 * 4. 使用 if-else if-else 結構按順序判斷
 *    注意：先判斷「兩者都是」的情況，再判斷各自的情況
 */
#include <stdio.h>

int main(void) {
    int n;  /* 輸入的整數 */

    /* 讀入整數 */
    scanf("%d", &n);

    /* 判斷倍數關係，注意順序：先判斷最嚴格的條件 */
    if (n % 3 == 0 && n % 5 == 0) {
        /* 同時是 3 和 5 的倍數（即 15 的倍數） */
        printf("Multiple of 3 and 5\n");
    } else if (n % 3 == 0) {
        /* 只是 3 的倍數 */
        printf("Multiple of 3\n");
    } else if (n % 5 == 0) {
        /* 只是 5 的倍數 */
        printf("Multiple of 5\n");
    } else {
        /* 既不是 3 也不是 5 的倍數 */
        printf("Not multiple of 3 or 5\n");
    }

    return 0;
}
