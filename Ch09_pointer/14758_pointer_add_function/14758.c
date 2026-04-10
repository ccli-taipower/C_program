/*
 * NTHU EE2310 - 題目 14758: Pointer Add Function
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 9 章（指標）
 *   如果不知道如何解題，請參考課本第 9 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14758/
 *
 * 【題目說明】
 * 實作 add_n(int *iptr, int n) 函數：
 * - 若 iptr 為 NULL，不進行任何修改，回傳 0
 * - 若 iptr 不為 NULL，將 *iptr 加上 n，並回傳新的 *iptr 值
 *
 * 【解題策略】
 * 1. 先判斷 iptr 是否為 NULL
 * 2. 若為 NULL，直接回傳 0（不可解參考 NULL 指標）
 * 3. 若不為 NULL，將 *iptr += n，然後回傳 *iptr
 */
#include <stdio.h>

int add_n(int *iptr, int n);

int main(void) {
    int i, j, k;
    scanf("%d%d", &i, &j);
    printf("i = %d\n", i);
    k = add_n(NULL, j);
    printf("i = %d, k = %d\n", i, k);
    k = add_n(&i, j);
    printf("i = %d, k = %d\n", i, k);
    return 0;
}

/* 若 iptr 為 NULL 則回傳 0；否則將 *iptr 加上 n 並回傳新值 */
int add_n(int *iptr, int n) {
    /* 若指標為 NULL，直接回傳 0，不進行任何修改 */
    if (iptr == NULL)
        return 0;

    /* 將指標所指向的值加上 n */
    *iptr = *iptr + n;

    /* 回傳修改後的值 */
    return *iptr;
}
