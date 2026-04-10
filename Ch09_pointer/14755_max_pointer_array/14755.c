/*
 * NTHU EE2310 - 題目 14755: Max Pointer Array
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 9 章（指標）
 *   如果不知道如何解題，請參考課本第 9 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14755/
 *
 * 【題目說明】
 * 給定 10 個整數，透過指標陣列找出其中的最大值。
 * 實作 max(int *iptr[], int n) 函數，接受指向各元素的指標陣列，
 * 回傳所有元素中的最大值。
 *
 * 【解題策略】
 * 1. main 函數讀入 10 個整數存入 array[]，並設定 iptr[i] = &array[i]
 * 2. max 函數以 *iptr[0] 初始化最大值
 * 3. 依序透過解參考 *iptr[i] 取得各元素值並比較
 * 4. 回傳最終的最大值
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 在 main 中宣告整數陣列 array[N] 和指標陣列 iptr[N]。
 * 2. 使用 for 迴圈讀入 N=10 個整數到 array[]。
 * 3. 使用第二個 for 迴圈，將 iptr[i] 設為 &array[i]，讓每個指標指向對應的陣列元素。
 * 4. 呼叫 max(iptr, N)，傳入指標陣列和元素個數。
 * 5. 在 max 函數中，以 *(iptr[0]) 初始化最大值 m。
 * 6. 從 i=1 迴圈至 n-1，透過 *(iptr[i]) 解參考取得各元素值，若大於 m 則更新 m。
 * 7. 回傳 m，main 中輸出最大值。
 *
 * English:
 * 1. In main, declare integer array array[N] and pointer array iptr[N].
 * 2. Use a for loop to read N=10 integers into array[].
 * 3. Use a second for loop to set iptr[i] = &array[i], making each pointer point to its element.
 * 4. Call max(iptr, N), passing the pointer array and element count.
 * 5. Inside max, initialize the maximum value m with *(iptr[0]).
 * 6. Loop i from 1 to n-1; dereference *(iptr[i]) to get each element's value and update m if it is larger.
 * 7. Return m; main prints the maximum value.
 */
#include <stdio.h>

#define N 10

int max(int *iptr[], int n);

int main(void) {
    int i;           /* 迴圈索引 / loop index */
    int array[N];    /* 整數陣列 / integer array */
    int *iptr[N];    /* 指向各元素的指標陣列 / array of pointers to each element */

    /* 讀入 N 個整數 / read N integers */
    for (i = 0; i < N; i++)
        scanf("%d", &array[i]);

    /* 設定指標陣列，iptr[i] 指向 array[i] / set up pointer array so iptr[i] points to array[i] */
    for (i = 0; i < N; i++)
        iptr[i] = &array[i];

    /* 呼叫 max 函數並輸出結果 / call max function and print the result */
    printf("%d\n", max(iptr, N));

    return 0;
}

/* 透過指標陣列找出 n 個元素中的最大值 / find the maximum value among n elements via the pointer array */
int max(int *iptr[], int n) {
    int i;       /* 迴圈索引 / loop index */
    int m;       /* 目前最大值 / current maximum value */

    /* 以第 0 個元素初始化最大值 / initialize maximum with the first element */
    m = *(iptr[0]);

    /* 遍歷其餘元素，更新最大值 / traverse remaining elements and update maximum */
    for (i = 1; i < n; i++) {
        if (*(iptr[i]) > m)
            m = *(iptr[i]);
    }

    return m;
}
