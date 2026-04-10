/*
 * NTHU EE2310 - 題目 14711: 3D Bingo Cube
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14711/
 *
 * 【題目說明】
 * 給定一個 n×n×n 的賓果方塊（Bingo Cube），數字 1 到 n³ 以
 * row-major 順序（依層、列、行）填入方塊。每次抽出一個數字並標記，
 * 當某條「直線」上的所有格子都被標記時，即發生 Bingo。
 *
 * 需檢查的直線類型：
 *   1. 沿 x 方向的行（每層每列一條，共 n*n 條）
 *   2. 沿 y 方向的列（每層每行一條，共 n*n 條）
 *   3. 沿 z 方向的柱（每個 (y,x) 位置一條，共 n*n 條）
 *   4. 各面的對角線（每個 z 固定面 2 條，每個 y 固定面 2 條，每個 x 固定面 2 條）
 *   5. 4 條空間對角線
 *
 * 【解題策略】
 * - 用 cube[z][y][x] 儲存方塊內容，建立數值到座標的查詢表。
 * - 用 marked[v] = 1 表示數值 v 已被抽到。
 * - 每次抽出數字後，找到其座標，再逐一檢查所有直線是否全部被標記。
 */
#include <stdio.h>

#define MAXN 10

int cube[MAXN][MAXN][MAXN];       /* 方塊內容，cube[z][y][x] */
int marked[MAXN * MAXN * MAXN + 1]; /* marked[v]=1 表示數值 v 已被抽出 */
int pos_z[1001], pos_y[1001], pos_x[1001]; /* 數值到座標的查詢表 */

int n;  /* 方塊邊長 */

/* 檢查某條直線是否全部被標記（以一組 n 個座標判斷） */
int line_done(int az[], int ay[], int ax[]) {
    int i;
    for (i = 0; i < n; i++) {
        if (!marked[cube[az[i]][ay[i]][ax[i]]])
            return 0;
    }
    return 1;
}

/* 檢查是否有任何直線完成 */
int check_bingo(void) {
    int i, j, k;
    int az[MAXN], ay[MAXN], ax[MAXN];

    /* 1. 沿 x 方向的行：固定 (z, y)，x 從 0 到 n-1 */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                az[k] = i; ay[k] = j; ax[k] = k;
            }
            if (line_done(az, ay, ax)) return 1;
        }
    }

    /* 2. 沿 y 方向的列：固定 (z, x)，y 從 0 到 n-1 */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                az[k] = i; ay[k] = k; ax[k] = j;
            }
            if (line_done(az, ay, ax)) return 1;
        }
    }

    /* 3. 沿 z 方向的柱：固定 (y, x)，z 從 0 到 n-1 */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                az[k] = k; ay[k] = i; ax[k] = j;
            }
            if (line_done(az, ay, ax)) return 1;
        }
    }

    /* 4a. 固定 z 的面對角線（每層 2 條） */
    for (i = 0; i < n; i++) {
        for (k = 0; k < n; k++) {
            az[k] = i; ay[k] = k; ax[k] = k;
        }
        if (line_done(az, ay, ax)) return 1;
        for (k = 0; k < n; k++) {
            az[k] = i; ay[k] = k; ax[k] = n - 1 - k;
        }
        if (line_done(az, ay, ax)) return 1;
    }

    /* 4b. 固定 y 的面對角線（每層 2 條） */
    for (i = 0; i < n; i++) {
        for (k = 0; k < n; k++) {
            az[k] = k; ay[k] = i; ax[k] = k;
        }
        if (line_done(az, ay, ax)) return 1;
        for (k = 0; k < n; k++) {
            az[k] = k; ay[k] = i; ax[k] = n - 1 - k;
        }
        if (line_done(az, ay, ax)) return 1;
    }

    /* 4c. 固定 x 的面對角線（每列 2 條） */
    for (i = 0; i < n; i++) {
        for (k = 0; k < n; k++) {
            az[k] = k; ay[k] = k; ax[k] = i;
        }
        if (line_done(az, ay, ax)) return 1;
        for (k = 0; k < n; k++) {
            az[k] = k; ay[k] = n - 1 - k; ax[k] = i;
        }
        if (line_done(az, ay, ax)) return 1;
    }

    /* 5. 4 條空間對角線 */
    /* (0,0,0) → (n-1,n-1,n-1) */
    for (k = 0; k < n; k++) { az[k] = k; ay[k] = k; ax[k] = k; }
    if (line_done(az, ay, ax)) return 1;

    /* (n-1,0,0) → (0,n-1,n-1) */
    for (k = 0; k < n; k++) { az[k] = n-1-k; ay[k] = k; ax[k] = k; }
    if (line_done(az, ay, ax)) return 1;

    /* (0,n-1,0) → (n-1,0,n-1) */
    for (k = 0; k < n; k++) { az[k] = k; ay[k] = n-1-k; ax[k] = k; }
    if (line_done(az, ay, ax)) return 1;

    /* (0,0,n-1) → (n-1,n-1,0) */
    for (k = 0; k < n; k++) { az[k] = k; ay[k] = k; ax[k] = n-1-k; }
    if (line_done(az, ay, ax)) return 1;

    return 0;
}

int main(void) {
    int i, j, k, v, draw;

    /* 讀入邊長 */
    scanf("%d", &n);

    /* 讀入方塊內容（row-major：依 z、y、x 順序） */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                scanf("%d", &cube[i][j][k]);
                v = cube[i][j][k];
                pos_z[v] = i;
                pos_y[v] = j;
                pos_x[v] = k;
            }
        }
    }

    /* 初始化標記陣列 */
    for (i = 0; i <= n * n * n; i++)
        marked[i] = 0;

    /* 依序抽數字，每次標記後檢查是否 Bingo */
    for (i = 0; i < n * n * n; i++) {
        scanf("%d", &draw);
        marked[draw] = 1;

        if (check_bingo()) {
            printf("%d\n", draw);
            return 0;
        }
    }

    return 0;
}
