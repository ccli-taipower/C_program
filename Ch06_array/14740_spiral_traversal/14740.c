/*
 * NTHU EE2310 - 題目 14740: Spiral Traversal
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14740/
 *
 * 【題目說明】
 * 給定 n×n 矩陣（n 為奇數），從中心開始，以逆時針螺旋方式
 * 依序輸出每個元素，每個元素佔一行。
 *
 * 【螺旋規則】
 * 起始位置：中心 (n/2, n/2)
 * 方向順序（反覆循環）：右 → 上 → 左 → 下 → 右 → ...
 * 步長序列：1, 1, 2, 2, 3, 3, ..., (n-2), (n-2), (n-1), (n-1), (n-1)
 *   - 每個步長重複 2 次，最後的步長 (n-1) 重複 3 次以閉合螺旋。
 *
 * 範例（n=3）：5→6→3→2→1→4→7→8→9
 * 範例（n=5）：從中心 13 開始，依螺旋順序輸出所有 25 個元素。
 *
 * 【解題策略】
 * - 用 (row, col) 記錄目前位置，從 (n/2, n/2) 出發。
 * - 依方向和步長移動，每移動一格輸出一個元素。
 * - 步長序列：step = 1, 重複 2 次；step = 2, 重複 2 次；...；
 *   step = n-1, 重複 3 次（最後一輪多一次）。
 */
#include <stdio.h>

#define MAXN 101

int mat[MAXN][MAXN]; /* 輸入矩陣 */

int main(void) {
    int n, i, j;
    int row, col;     /* 目前位置 */
    int dr, dc;       /* 方向向量（delta row, delta col） */
    int step, rep;    /* 目前步長及重複次數 */
    int total;        /* 已輸出的元素數 */
    int move;         /* 目前步長中已走的步數 */

    /* 方向陣列：右、上、左、下（對應 row, col 的增量） */
    /* 右：col+1；上：row-1；左：col-1；下：row+1 */
    int dir_dr[4] = { 0, -1, 0, 1 };
    int dir_dc[4] = { 1,  0, -1, 0 };
    int dir_idx;  /* 目前方向索引 */

    /* 讀入矩陣 */
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);

    /* 若 n=1，直接輸出 */
    if (n == 1) {
        printf("%d\n", mat[0][0]);
        return 0;
    }

    /* 從中心開始 */
    row = n / 2;
    col = n / 2;
    dir_idx = 0; /* 第一個方向：右 */
    total = 0;

    /* 輸出起始中心元素 */
    printf("%d\n", mat[row][col]);
    total++;

    /*
     * 步長序列：1,1,2,2,3,3,...,(n-2),(n-2),(n-1),(n-1),(n-1)
     * 每個步長 step（1 到 n-2）重複 2 次；
     * 最後步長 (n-1) 重複 3 次。
     */
    for (step = 1; step <= n - 1; step++) {
        /* 決定本步長重複次數 */
        rep = (step == n - 1) ? 3 : 2;

        for (i = 0; i < rep; i++) {
            /* 取得目前方向向量 */
            dr = dir_dr[dir_idx];
            dc = dir_dc[dir_idx];

            /* 沿此方向走 step 步 */
            for (move = 0; move < step; move++) {
                row += dr;
                col += dc;
                printf("%d\n", mat[row][col]);
                total++;
                if (total == n * n)
                    return 0;
            }

            /* 切換到下一個方向（循環） */
            dir_idx = (dir_idx + 1) % 4;
        }
    }

    return 0;
}
