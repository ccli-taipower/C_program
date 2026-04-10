/*
 * NTHU EE2310 - 題目 14794: Evaluate Function Maximum
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 8 章（函式）
 *   如果不知道如何解題，請參考課本第 8 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14794/
 *
 * 【題目說明】
 * 給定多組 (x, y) 整數對，計算每組的函數值 f(x,y) = 4x - 6y。
 * 找出最大的函數值，以及對應的最大索引（0-based）。
 * 若有多組同樣的最大值，輸出索引最大的那組。
 * 輸入到 EOF 結束。
 *
 * 【解題策略】
 * 1. main 函數使用指標陣列 iptr，iptr[i] 指向第 i 組 (x,y) 中的 x
 * 2. iptr[i]+1 則指向對應的 y 值
 * 3. eval_f 函數遍歷所有組，計算 4*(*(iptr[i])) - 6*(*(iptr[i]+1))
 * 4. 記錄最大值與最大索引（同值取較大索引）
 * 5. 透過 *index 回傳最大索引，函數回傳值為最大函數值
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. main 宣告一個扁平整數陣列 xy[]（x 和 y 交替存放），以及指標陣列 iptr[]。
 * 2. 使用 while 迴圈持續讀入 (x, y) 配對；每次讀入後，令 iptr[n] 指向 xy[] 中對應 x 的位置，然後將 x 和 y 依序存入 xy[]。
 * 3. 讀完所有輸入後，呼叫 eval_f(iptr, n, &max_index)，傳入指標陣列、組數 n，以及用來回傳最大索引的指標。
 * 4. 在 eval_f 中，以第 0 組初始化 max_val 和 *index = 0。
 * 5. 從 i=1 迴圈至 n-1：計算 val = 4*(*(iptr[i])) - 6*(*(iptr[i]+1))；若 val >= max_val，更新 max_val 和 *index（確保取到最大索引）。
 * 6. 回傳 max_val，main 中輸出最大函數值和對應的最大索引。
 *
 * English:
 * 1. main declares a flat integer array xy[] (x and y stored alternately) and a pointer array iptr[].
 * 2. A while loop reads (x, y) pairs; for each pair, iptr[n] is set to point to the x position in xy[], then x and y are stored consecutively in xy[].
 * 3. After all input is read, call eval_f(iptr, n, &max_index) passing the pointer array, count n, and a pointer to receive the maximum index.
 * 4. Inside eval_f, initialize max_val and *index = 0 using the first group.
 * 5. Loop i from 1 to n-1: compute val = 4*(*(iptr[i])) - 6*(*(iptr[i]+1)); if val >= max_val, update max_val and *index (ensuring the largest index is kept for ties).
 * 6. Return max_val; main prints the maximum function value and its index.
 */
#include <stdio.h>

#define N 256

int eval_f(int *iptr[], int n, int *index);

int main(void) {
    int n = 0;
    int x, y;
    int xy[2 * N];
    int xy_n = 0;
    int max, max_index;
    int *iptr[N];
    while (scanf("%d%d", &x, &y) != EOF) {
        iptr[n] = &(xy[xy_n]);
        n++;
        xy[xy_n] = x;
        xy_n++;
        xy[xy_n] = y;
        xy_n++;
    }
    max = eval_f(iptr, n, &max_index);
    printf("%d %d\n", max, max_index);
    return 0;
}

/* 計算所有組的 f(x,y) = 4x - 6y，回傳最大值並透過 index 回傳最大索引 / compute f(x,y)=4x-6y for all groups, return max value and max index via pointer */
/* iptr[i] 指向第 i 組的 x，iptr[i]+1 指向對應的 y / iptr[i] points to x of group i, iptr[i]+1 points to the corresponding y */
int eval_f(int *iptr[], int n, int *index) {
    int i;       /* 迴圈索引 / loop index */
    int val;     /* 當前函數值 / current function value */
    int max_val; /* 目前最大函數值 / current maximum function value */

    /* 以第 0 組初始化最大值 / initialize maximum using group 0 */
    max_val = 4 * (*(iptr[0])) - 6 * (*(iptr[0] + 1));
    *index = 0;

    /* 遍歷所有組，找最大值（同值取較大索引） / traverse all groups to find max (keep larger index for ties) */
    for (i = 1; i < n; i++) {
        val = 4 * (*(iptr[i])) - 6 * (*(iptr[i] + 1));
        if (val >= max_val) {
            /* 大於或等於目前最大值時更新（確保取最大索引） / update when >= current max (ensures largest index is kept) */
            max_val = val;
            *index = i;
        }
    }

    return max_val;
}
