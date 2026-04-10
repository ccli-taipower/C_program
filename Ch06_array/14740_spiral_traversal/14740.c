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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入 n（奇數）並填入矩陣 mat[][]。
 * 2. 若 n == 1，直接輸出唯一元素後結束。
 * 3. 初始位置為中心 (n/2, n/2)，方向索引 dir_idx = 0（右）。
 * 4. 先輸出中心元素，計數器 total = 1。
 * 5. 外層迴圈 step 從 1 到 n-1，控制每一圈的步長：
 *    - step < n-1 時，該步長重複 2 次（直走再轉彎）。
 *    - step == n-1（最外圈）時，重複 3 次（需多一次才能閉合）。
 * 6. 每次「走 step 步」：依當前方向向量 (dr, dc) 移動，
 *    每移動一格輸出 mat[row][col]，total 加一。
 *    若 total == n*n，立即結束。
 * 7. 走完一段後，dir_idx 循環遞增（右→上→左→下→右...）。
 * 8. 方向向量定義：右(0,+1)、上(-1,0)、左(0,-1)、下(+1,0)。
 *
 * English:
 * 1. Read n (odd) and fill matrix mat[][].
 * 2. If n == 1, print the single element and exit.
 * 3. Start at center (n/2, n/2) with dir_idx = 0 (right), total = 0.
 * 4. Print the center element; set total = 1.
 * 5. Outer loop: step from 1 to n-1, controlling segment length:
 *    - For step < n-1, each step length repeats 2 times.
 *    - For step == n-1 (outermost ring), repeat 3 times to close the spiral.
 * 6. For each segment, move step cells in current direction (dr, dc),
 *    printing mat[row][col] at each cell; increment total. Exit if total == n*n.
 * 7. After each segment, advance dir_idx cyclically (right→up→left→down→...).
 * 8. Direction vectors: right(0,+1), up(-1,0), left(0,-1), down(+1,0).
 */
#include <stdio.h>

#define MAXN 101

int mat[MAXN][MAXN]; /* 輸入矩陣 / input matrix */

int main(void) {
    int n, i, j;
    int row, col;     /* 目前位置 / current position */
    int dr, dc;       /* 方向向量（delta row, delta col）/ direction vector (delta row, delta col) */
    int step, rep;    /* 目前步長及重複次數 / current step length and repeat count */
    int total;        /* 已輸出的元素數 / number of elements printed so far */
    int move;         /* 目前步長中已走的步數 / steps taken in current segment */

    /* 方向陣列：右、上、左、下（對應 row, col 的增量）/ direction arrays: right, up, left, down */
    /* 右：col+1；上：row-1；左：col-1；下：row+1 / right: col+1; up: row-1; left: col-1; down: row+1 */
    int dir_dr[4] = { 0, -1, 0, 1 };
    int dir_dc[4] = { 1,  0, -1, 0 };
    int dir_idx;  /* 目前方向索引 / current direction index */

    /* 讀入矩陣 / read the matrix */
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);

    /* 若 n=1，直接輸出 / if n=1, print the single element and return */
    if (n == 1) {
        printf("%d\n", mat[0][0]);
        return 0;
    }

    /* 從中心開始 / start from the center */
    row = n / 2;
    col = n / 2;
    dir_idx = 0; /* 第一個方向：右 / initial direction: right */
    total = 0;

    /* 輸出起始中心元素 / print the starting center element */
    printf("%d\n", mat[row][col]);
    total++;

    /*
     * 步長序列：1,1,2,2,3,3,...,(n-2),(n-2),(n-1),(n-1),(n-1)
     * 每個步長 step（1 到 n-2）重複 2 次；
     * 最後步長 (n-1) 重複 3 次。
     */
    for (step = 1; step <= n - 1; step++) {
        /* 決定本步長重複次數 / determine repeat count for this step length */
        rep = (step == n - 1) ? 3 : 2;

        for (i = 0; i < rep; i++) {
            /* 取得目前方向向量 / get current direction vector */
            dr = dir_dr[dir_idx];
            dc = dir_dc[dir_idx];

            /* 沿此方向走 step 步 / walk step cells in the current direction */
            for (move = 0; move < step; move++) {
                row += dr;
                col += dc;
                printf("%d\n", mat[row][col]);
                total++;
                if (total == n * n)
                    return 0;
            }

            /* 切換到下一個方向（循環）/ switch to next direction (cyclic) */
            dir_idx = (dir_idx + 1) % 4;
        }
    }

    return 0;
}
