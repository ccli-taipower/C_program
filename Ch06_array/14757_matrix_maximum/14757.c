/*
 * NTHU EE2310 - 題目 14757: Matrix Maximum
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14757/
 *
 * 【題目說明】
 * 讀入 4×4 整數矩陣，找出其中最大值並輸出。
 *
 * 【解題策略】
 * 實作函式 int max(int array[N][N])，遍歷 4×4 矩陣中所有元素，
 * 記錄並回傳最大值。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 在 main 中用雙重迴圈（i: 0~3, j: 0~3）依序讀入 4×4 矩陣的
 *    16 個元素，存入 array[i][j]。
 * 2. 呼叫 max(array) 函式，傳入二維陣列指標。
 * 3. max 函式初始化最大值 m = array[0][0]（以第一個元素為基準）。
 * 4. 雙重迴圈遍歷所有 16 個元素，若 array[i][j] > m，則更新 m。
 * 5. 遍歷完成後返回 m。
 * 6. 在 main 中輸出 max 的返回值。
 *
 * English:
 * 1. In main, use nested loops (i: 0-3, j: 0-3) to read 16 integers
 *    into array[i][j] in row-major order.
 * 2. Call max(array) passing the 2-D array pointer.
 * 3. max() initializes m = array[0][0] as the starting maximum candidate.
 * 4. Nested loops scan all 16 elements; update m whenever array[i][j] > m.
 * 5. Return m after the full traversal.
 * 6. Print the return value of max() in main.
 */
#include <stdio.h>
#define N 4

int max(int array[N][N]);

int main(void) {
    int i, j;
    int array[N][N];

    /* 讀入 4×4 矩陣（row-major 順序）/ read the 4x4 matrix in row-major order */
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            scanf("%d", &(array[i][j]));

    printf("%d\n", max(array));

    return 0;
}

/* 找出 4×4 矩陣中的最大值 / find the maximum value in a 4x4 matrix */
int max(int array[N][N]) {
    int i, j, m;

    m = array[0][0]; /* 以第一個元素作為初始最大值 / use the first element as the initial maximum */

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (array[i][j] > m)
                m = array[i][j];
        }
    }

    return m;
}
