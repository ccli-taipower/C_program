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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 在 main 中讀入整數 i 和 j，並先輸出 i 的初始值。
 * 2. 以 NULL 和 j 呼叫 add_n：由於 iptr 為 NULL，函數直接回傳 0，i 不變；輸出 i 和 k = 0。
 * 3. 以 &i 和 j 呼叫 add_n：iptr 不為 NULL，函數將 *iptr（即 i）加上 n（即 j），i 的值改變；回傳新的 i 值給 k；輸出新的 i 和 k。
 * 4. 在 add_n 函數內部：
 *    a. 首先檢查 iptr == NULL，若是則直接回傳 0，保護程式不發生空指標解參考。
 *    b. 若非 NULL，執行 *iptr = *iptr + n（修改呼叫方的變數）。
 *    c. 回傳修改後的 *iptr 值。
 *
 * English:
 * 1. In main, read integers i and j, then print the initial value of i.
 * 2. Call add_n with NULL and j: since iptr is NULL the function returns 0 immediately and i is unchanged; print i and k = 0.
 * 3. Call add_n with &i and j: iptr is not NULL, so the function adds n (j) to *iptr (i), changing i's value; the new value of i is returned as k; print the updated i and k.
 * 4. Inside add_n:
 *    a. Check if iptr == NULL; if so, return 0 immediately to prevent a null pointer dereference.
 *    b. If not NULL, execute *iptr = *iptr + n (modifying the caller's variable through the pointer).
 *    c. Return the updated *iptr value.
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

/* 若 iptr 為 NULL 則回傳 0；否則將 *iptr 加上 n 並回傳新值 / return 0 if iptr is NULL; otherwise add n to *iptr and return the new value */
int add_n(int *iptr, int n) {
    /* 若指標為 NULL，直接回傳 0，不進行任何修改 / if pointer is NULL, return 0 without any modification */
    if (iptr == NULL)
        return 0;

    /* 將指標所指向的值加上 n / add n to the value pointed to by iptr */
    *iptr = *iptr + n;

    /* 回傳修改後的值 / return the updated value */
    return *iptr;
}
