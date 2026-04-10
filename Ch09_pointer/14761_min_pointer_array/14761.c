/*
 * NTHU EE2310 - 題目 14761: Min Pointer Array
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 9 章（指標）
 *   如果不知道如何解題，請參考課本第 9 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14761/
 *
 * 【題目說明】
 * 給定 10 個整數，透過指標陣列找出其中的最小值。
 * 實作 min(int *iptr[], int n) 函數，接受指向各元素的指標陣列，
 * 回傳所有元素中的最小值。
 *
 * 【解題策略】
 * 1. main 函數讀入 10 個整數存入 array[]，並設定 iptr[i] = &array[i]
 * 2. min 函數以 *iptr[0] 初始化最小值
 * 3. 依序透過解參考 *iptr[i] 取得各元素值並比較
 * 4. 回傳最終的最小值
 */
#include <stdio.h>

#define N 10

int min(int *iptr[], int n);

int main(void) {
    int i;           /* 迴圈索引 */
    int array[N];    /* 整數陣列 */
    int *iptr[N];    /* 指向各元素的指標陣列 */

    /* 讀入 N 個整數 */
    for (i = 0; i < N; i++)
        scanf("%d", &array[i]);

    /* 設定指標陣列，iptr[i] 指向 array[i] */
    for (i = 0; i < N; i++)
        iptr[i] = &array[i];

    /* 呼叫 min 函數並輸出結果 */
    printf("%d\n", min(iptr, N));

    return 0;
}

/* 透過指標陣列找出 n 個元素中的最小值 */
int min(int *iptr[], int n) {
    int i;       /* 迴圈索引 */
    int m;       /* 目前最小值 */

    /* 以第 0 個元素初始化最小值 */
    m = *(iptr[0]);

    /* 遍歷其餘元素，更新最小值 */
    for (i = 1; i < n; i++) {
        if (*(iptr[i]) < m)
            m = *(iptr[i]);
    }

    return m;
}
