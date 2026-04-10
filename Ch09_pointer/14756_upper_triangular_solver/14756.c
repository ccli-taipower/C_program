/*
 * NTHU EE2310 - 題目 14756: Upper Triangular Solver
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 9 章（指標）
 *   如果不知道如何解題，請參考課本第 9 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14756/
 *
 * 【題目說明】
 * 求解線性方程組 Ax = y，其中 A 為上三角矩陣。
 * A 以壓縮列主序格式儲存（只存 i <= j 的元素）。
 * A[i][j]（i <= j）在壓縮陣列中的索引為：i*(2n-i+1)/2 + (j-i)
 * 也等於：i*n - i*(i-1)/2 + j - i
 *
 * 【解題策略】
 * 1. 從最後一個未知數開始，進行後向代入（back substitution）
 * 2. x[n-1] = y[n-1] / A[n-1][n-1]
 * 3. 對 i 從 n-2 遞減至 0：
 *    x[i] = (y[i] - sum(A[i][j]*x[j], j=i+1..n-1)) / A[i][i]
 * 4. 利用索引公式 idx(i,j) = i*n - i*(i-1)/2 + j - i 存取壓縮陣列
 */
#include <stdio.h>

#define N 256

void upper_solver(double *A, double *x, double *y, int n);

int main(void) {
    int i, j;
    int n;
    double A[N * (N + 1) / 2];
    double *aptr = A;
    double x[N];
    double y[N];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        for (j = i; j < n; j++) {
            scanf("%lf", aptr);
            aptr++;
        }
    for (i = 0; i < n; i++)
        scanf("%lf", &y[i]);
    upper_solver(A, x, y, n);
    for (i = 0; i < n; i++)
        printf("%f\n", x[i]);
    return 0;
}

/* 後向代入法求解上三角方程組 Ax = y */
/* A 為壓縮列主序格式，A[i][j] 的索引 = i*n - i*(i-1)/2 + j - i */
void upper_solver(double *A, double *x, double *y, int n) {
    int i, j;       /* 迴圈索引 */
    double sum;     /* 累加項 */
    int idx;        /* 壓縮陣列中的索引 */

    /* 從最後一個未知數開始求解 */
    /* x[n-1] = y[n-1] / A[n-1][n-1] */
    idx = (n - 1) * n - (n - 1) * (n - 2) / 2 + (n - 1) - (n - 1);
    x[n - 1] = y[n - 1] / A[idx];

    /* 後向代入：i 從 n-2 遞減至 0 */
    for (i = n - 2; i >= 0; i--) {
        sum = 0.0;
        /* 計算 sum = sum(A[i][j] * x[j])，j 從 i+1 到 n-1 */
        for (j = i + 1; j < n; j++) {
            /* A[i][j] 在壓縮陣列中的索引 */
            idx = i * n - i * (i - 1) / 2 + j - i;
            sum += A[idx] * x[j];
        }
        /* A[i][i] 的索引（j = i 時） */
        idx = i * n - i * (i - 1) / 2;
        x[i] = (y[i] - sum) / A[idx];
    }
}
