/*
 * NTHU EE2310 - 題目 14739: Mirror Room
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14739/
 *
 * 【題目說明】
 * 一個 W×D 的房間，內含「\」方向的鏡子（值為 1，無鏡子為 0）。
 * 房間四周共有 2*(W+D) 個窗口，從底部左端開始逆時針編號：
 *   - 底邊（由左到右）：0 .. W-1，光線向上（UP）進入
 *   - 右邊（由下到上）：W .. W+D-1，光線向左（LEFT）進入
 *   - 頂邊（由右到左）：W+D .. 2W+D-1，光線向下（DOWN）進入
 *   - 左邊（由上到下）：2W+D .. 2W+2D-1，光線向右（RIGHT）進入
 *
 * 鏡子反射規則（「\」鏡）：
 *   向右 → 向下，向下 → 向右
 *   向左 → 向上，向上 → 向左
 *
 * 對每個窗口，模擬光線行進，輸出光線離開的窗口編號。
 *
 * 【解題策略】
 * - grid[row][col]（row 0 = 頂端，row D-1 = 底端）
 * - 對每個窗口計算入射位置和方向，模擬到光線出格為止。
 * - 出格後，根據出格位置計算對應的窗口編號。
 */
#include <stdio.h>

#define MAXWD 105

int W, D;
int grid[MAXWD][MAXWD]; /* grid[row][col]，row 0 = 頂端 */

/* 方向常數 */
#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

/* 根據出格位置計算窗口編號 */
int exit_window(int row, int col, int dir) {
    /* 從底部出去（row == D，方向向下） */
    if (dir == DOWN)
        return col; /* 底邊窗口 0..W-1 */

    /* 從左邊出去（col == -1，方向向左） */
    if (dir == LEFT)
        return 2 * W + D + row; /* 左邊窗口 2W+D..2W+2D-1（由上到下） */

    /* 從頂部出去（row == -1，方向向上） */
    if (dir == UP)
        return W + D + (W - 1 - col); /* 頂邊窗口 */

    /* 從右邊出去（col == W，方向向右） */
    /* dir == RIGHT */
    return W + (D - 1 - row); /* 右邊窗口 W..W+D-1（由下到上） */
}

/* 模擬光線從窗口 w 進入，返回出去的窗口編號 */
int simulate(int w) {
    int row, col, dir;

    /* 根據窗口編號決定入射位置和方向 */
    if (w < W) {
        /* 底邊窗口：從底部進入，向上行進 */
        col = w;
        row = D - 1;
        dir = UP;
    } else if (w < W + D) {
        /* 右邊窗口：從右側進入，向左行進 */
        row = D - 1 - (w - W);
        col = W - 1;
        dir = LEFT;
    } else if (w < 2 * W + D) {
        /* 頂邊窗口：從頂部進入，向下行進 */
        col = W - 1 - (w - W - D);
        row = 0;
        dir = DOWN;
    } else {
        /* 左邊窗口：從左側進入，向右行進 */
        row = w - 2 * W - D;
        col = 0;
        dir = RIGHT;
    }

    /* 模擬光線行進 */
    while (1) {
        /* 若當前格有鏡子（「\」），反射 */
        if (row >= 0 && row < D && col >= 0 && col < W) {
            if (grid[row][col] == 1) {
                /* 「\」鏡反射規則 */
                if (dir == UP)    dir = LEFT;
                else if (dir == DOWN)  dir = RIGHT;
                else if (dir == LEFT)  dir = UP;
                else                   dir = DOWN; /* RIGHT → DOWN */
            }
        }

        /* 向前移動一格 */
        if (dir == UP)         row--;
        else if (dir == DOWN)  row++;
        else if (dir == LEFT)  col--;
        else                   col++; /* RIGHT */

        /* 檢查是否出格 */
        if (row < 0 || row >= D || col < 0 || col >= W)
            return exit_window(row, col, dir);
    }
}

int main(void) {
    int i, j, total;

    /* 讀入房間尺寸 */
    scanf("%d %d", &W, &D);

    /* 讀入房間格子（D 行，每行 W 個值；row 0 = 頂端） */
    for (i = 0; i < D; i++)
        for (j = 0; j < W; j++)
            scanf("%d", &grid[i][j]);

    total = 2 * (W + D);

    /* 對每個窗口模擬並輸出結果 */
    for (i = 0; i < total; i++)
        printf("%d\n", simulate(i));

    return 0;
}
