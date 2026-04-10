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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 宣告整數 n 儲存輸入值。
 * 2. 使用 scanf 讀入整數 n。
 * 3. 使用 if-else if-else 結構逐一判斷倍數關係：
 *    判斷的順序非常關鍵——必須先判斷「同時是 3 和 5 的倍數」，
 *    否則若先判斷「是 3 的倍數」，15 這類數字就會被誤判為只有 3 的倍數。
 * 4. 第一個 if：同時滿足 n%3==0 且 n%5==0（即 15 的倍數），
 *    輸出 "Multiple of 3 and 5"。
 * 5. 第一個 else if：只滿足 n%3==0，
 *    輸出 "Multiple of 3"。
 * 6. 第二個 else if：只滿足 n%5==0，
 *    輸出 "Multiple of 5"。
 * 7. else：三者皆不滿足，輸出 "Not multiple of 3 or 5"。
 *
 * English:
 * 1. Declare integer n to store the input value.
 * 2. Use scanf to read the integer n.
 * 3. Use an if-else if-else chain to check divisibility in the correct order:
 *    The order is critical — checking "both 3 and 5" first prevents a number
 *    like 15 from being misclassified as only a multiple of 3.
 * 4. First if: both n%3==0 and n%5==0 hold (i.e., multiple of 15);
 *    print "Multiple of 3 and 5".
 * 5. First else if: only n%3==0 holds; print "Multiple of 3".
 * 6. Second else if: only n%5==0 holds; print "Multiple of 5".
 * 7. else: none of the above; print "Not multiple of 3 or 5".
 */
#include <stdio.h>

int main(void) {
    int n;  /* 輸入的整數 / the integer input */

    /* 讀入整數 / read the integer */
    scanf("%d", &n);

    /* 判斷倍數關係，注意順序：先判斷最嚴格的條件 / check divisibility; order matters: most restrictive case first */
    if (n % 3 == 0 && n % 5 == 0) {
        /* 同時是 3 和 5 的倍數（即 15 的倍數） / multiple of both 3 and 5 (i.e., multiple of 15) */
        printf("Multiple of 3 and 5\n");
    } else if (n % 3 == 0) {
        /* 只是 3 的倍數 / multiple of 3 only */
        printf("Multiple of 3\n");
    } else if (n % 5 == 0) {
        /* 只是 5 的倍數 / multiple of 5 only */
        printf("Multiple of 5\n");
    } else {
        /* 既不是 3 也不是 5 的倍數 / not a multiple of 3 or 5 */
        printf("Not multiple of 3 or 5\n");
    }

    return 0;
}
