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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入 n，再以 aptr 指標逐行逐列讀入上三角矩陣的非零元素（只存 i<=j 的元素）到壓縮陣列 A[]。
 * 2. 讀入右側向量 y[]（共 n 個值）。
 * 3. 呼叫 upper_solver(A, x, y, n) 進行後向代入求解。
 * 4. 在 upper_solver 中，先用索引公式計算 A[n-1][n-1] 的壓縮索引，求解 x[n-1] = y[n-1]/A[n-1][n-1]。
 * 5. 從 i = n-2 遞減至 0，對每個 i：
 *    a. 計算 sum = Σ A[i][j]*x[j]（j 從 i+1 到 n-1），每個 A[i][j] 用公式 idx = i*n - i*(i-1)/2 + j - i 取得。
 *    b. 計算 A[i][i] 的索引 idx = i*n - i*(i-1)/2，求解 x[i] = (y[i] - sum) / A[i][i]。
 * 6. 後向代入完成後，輸出 x[0] 到 x[n-1]。
 *
 * English:
 * 1. Read n, then use pointer aptr to read the upper triangular matrix elements (only i<=j entries) row by row into compressed array A[].
 * 2. Read the right-hand side vector y[] (n values).
 * 3. Call upper_solver(A, x, y, n) to solve by back substitution.
 * 4. Inside upper_solver, compute the compressed index for A[n-1][n-1] and solve x[n-1] = y[n-1]/A[n-1][n-1].
 * 5. Decrement i from n-2 to 0; for each i:
 *    a. Compute sum = Σ A[i][j]*x[j] (j from i+1 to n-1), accessing A[i][j] via idx = i*n - i*(i-1)/2 + j - i.
 *    b. Compute index for A[i][i] as idx = i*n - i*(i-1)/2, then solve x[i] = (y[i] - sum) / A[i][i].
 * 6. After back substitution is complete, print x[0] through x[n-1].
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

/* 後向代入法求解上三角方程組 Ax = y / solve upper triangular system Ax = y by back substitution */
/* A 為壓縮列主序格式，A[i][j] 的索引 = i*n - i*(i-1)/2 + j - i / A is stored in compressed row-major format; index of A[i][j] = i*n - i*(i-1)/2 + j - i */
void upper_solver(double *A, double *x, double *y, int n) {
    int i, j;       /* 迴圈索引 / loop indices */
    double sum;     /* 累加項 / accumulated sum */
    int idx;        /* 壓縮陣列中的索引 / index into the compressed array */

    /* 從最後一個未知數開始求解 / start solving from the last unknown */
    /* x[n-1] = y[n-1] / A[n-1][n-1] / x[n-1] = y[n-1] / A[n-1][n-1] */
    idx = (n - 1) * n - (n - 1) * (n - 2) / 2 + (n - 1) - (n - 1);
    x[n - 1] = y[n - 1] / A[idx];

    /* 後向代入：i 從 n-2 遞減至 0 / back substitution: decrement i from n-2 to 0 */
    for (i = n - 2; i >= 0; i--) {
        sum = 0.0;
        /* 計算 sum = sum(A[i][j] * x[j])，j 從 i+1 到 n-1 / compute sum = Σ A[i][j]*x[j] for j from i+1 to n-1 */
        for (j = i + 1; j < n; j++) {
            /* A[i][j] 在壓縮陣列中的索引 / compressed array index for A[i][j] */
            idx = i * n - i * (i - 1) / 2 + j - i;
            sum += A[idx] * x[j];
        }
        /* A[i][i] 的索引（j = i 時） / compressed array index for the diagonal element A[i][i] (j = i) */
        idx = i * n - i * (i - 1) / 2;
        x[i] = (y[i] - sum) / A[idx];
    }
}
