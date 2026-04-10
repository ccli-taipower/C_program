/*
 * NTHU EE2310 - 題目 14757: Matrix Maximum
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目說明】
 * 讀入 4×4 整數矩陣，找出其中最大值並輸出。
 *
 * 【解題策略】
 * 實作函式 int max(int array[N][N])，遍歷 4×4 矩陣中所有元素，
 * 記錄並回傳最大值。
 */
#include <stdio.h>
#define N 4

int max(int array[N][N]);

int main(void) {
    int i, j;
    int array[N][N];

    /* 讀入 4×4 矩陣（row-major 順序） */
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            scanf("%d", &(array[i][j]));

    printf("%d\n", max(array));

    return 0;
}

/* 找出 4×4 矩陣中的最大值 */
int max(int array[N][N]) {
    int i, j, m;

    m = array[0][0]; /* 以第一個元素作為初始最大值 */

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (array[i][j] > m)
                m = array[i][j];
        }
    }

    return m;
}
