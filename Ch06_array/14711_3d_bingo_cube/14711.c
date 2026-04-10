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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入邊長 n，再以 row-major 順序（z → y → x）讀入 n³ 個數值，
 *    填入 cube[z][y][x]，同時建立查詢表 pos_z/pos_y/pos_x，
 *    讓每個數值能以 O(1) 找到其三維座標。
 * 2. 初始化標記陣列 marked[] 全為 0。
 * 3. 依序讀入抽出的數字 draw，設 marked[draw] = 1。
 * 4. 呼叫 check_bingo() 檢查所有類型的直線：
 *    (a) n² 條沿 x 方向的行（固定 z, y）
 *    (b) n² 條沿 y 方向的列（固定 z, x）
 *    (c) n² 條沿 z 方向的柱（固定 y, x）
 *    (d) 各面對角線（固定 z/y/x 各平面各 2 條，共 6n 條）
 *    (e) 4 條貫穿整個立方體的空間對角線
 * 5. check_bingo() 內部以 line_done() 輔助函式驗證每條直線，
 *    一旦發現某條直線全被標記即返回 1。
 * 6. 若 check_bingo() 返回 1，立即輸出當前抽到的數字並結束程式。
 *
 * English:
 * 1. Read edge length n, then fill cube[z][y][x] in row-major order,
 *    simultaneously building lookup tables pos_z/pos_y/pos_x for O(1)
 *    coordinate lookup by value.
 * 2. Initialize the marked[] array to all zeros.
 * 3. For each drawn number, set marked[draw] = 1.
 * 4. Call check_bingo() to test all line types:
 *    (a) n² rows along x (fixed z, y)
 *    (b) n² columns along y (fixed z, x)
 *    (c) n² pillars along z (fixed y, x)
 *    (d) face diagonals on fixed-z, fixed-y, fixed-x planes (6n lines)
 *    (e) 4 space diagonals spanning the full cube
 * 5. line_done() verifies whether every cell on a given line is marked.
 * 6. As soon as check_bingo() returns 1, print the triggering draw value
 *    and exit immediately.
 */
#include <stdio.h>

#define MAXN 10

int cube[MAXN][MAXN][MAXN];       /* 方塊內容，cube[z][y][x] / cube contents, cube[z][y][x] */
int marked[MAXN * MAXN * MAXN + 1]; /* marked[v]=1 表示數值 v 已被抽出 / marked[v]=1 means value v has been drawn */
int pos_z[1001], pos_y[1001], pos_x[1001]; /* 數值到座標的查詢表 / value-to-coordinate lookup tables */

int n;  /* 方塊邊長 / cube edge length */

/* 檢查某條直線是否全部被標記（以一組 n 個座標判斷）/ check if an entire line (given n coordinate sets) is fully marked */
int line_done(int az[], int ay[], int ax[]) {
    int i;
    for (i = 0; i < n; i++) {
        if (!marked[cube[az[i]][ay[i]][ax[i]]])
            return 0;
    }
    return 1;
}

/* 檢查是否有任何直線完成 / check if any line is fully completed */
int check_bingo(void) {
    int i, j, k;
    int az[MAXN], ay[MAXN], ax[MAXN];

    /* 1. 沿 x 方向的行：固定 (z, y)，x 從 0 到 n-1 / rows along x: fixed (z,y), x from 0 to n-1 */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                az[k] = i; ay[k] = j; ax[k] = k;
            }
            if (line_done(az, ay, ax)) return 1;
        }
    }

    /* 2. 沿 y 方向的列：固定 (z, x)，y 從 0 到 n-1 / columns along y: fixed (z,x), y from 0 to n-1 */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                az[k] = i; ay[k] = k; ax[k] = j;
            }
            if (line_done(az, ay, ax)) return 1;
        }
    }

    /* 3. 沿 z 方向的柱：固定 (y, x)，z 從 0 到 n-1 / pillars along z: fixed (y,x), z from 0 to n-1 */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                az[k] = k; ay[k] = i; ax[k] = j;
            }
            if (line_done(az, ay, ax)) return 1;
        }
    }

    /* 4a. 固定 z 的面對角線（每層 2 條）/ face diagonals on fixed-z planes (2 per layer) */
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

    /* 4b. 固定 y 的面對角線（每層 2 條）/ face diagonals on fixed-y planes (2 per slice) */
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

    /* 4c. 固定 x 的面對角線（每列 2 條）/ face diagonals on fixed-x planes (2 per column) */
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

    /* 5. 4 條空間對角線 / 4 space diagonals */
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

    /* 讀入邊長 / read edge length */
    scanf("%d", &n);

    /* 讀入方塊內容（row-major：依 z、y、x 順序）/ read cube contents (row-major: z, y, x order) */
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

    /* 初始化標記陣列 / initialize the marked array */
    for (i = 0; i <= n * n * n; i++)
        marked[i] = 0;

    /* 依序抽數字，每次標記後檢查是否 Bingo / draw numbers in order, check for bingo after each mark */
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
