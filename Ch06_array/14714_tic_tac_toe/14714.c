/*
 * NTHU EE2310 - 題目 14714: Tic-Tac-Toe
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目說明】
 * 井字棋遊戲：位置 1-9 對應棋盤格（1=左上，9=右下，row-major 順序）。
 * 奇數回合為玩家 1 下棋，偶數回合為玩家 2 下棋。
 * 若某玩家完成一行、一列或一條對角線則獲勝，輸出該玩家最後一步的位置。
 * 若平局（9 格填滿且無人獲勝），輸出 0。
 *
 * 【解題策略】
 * - 棋盤用 board[3][3] 表示，位置 p 對應 board[(p-1)/3][(p-1)%3]。
 * - 每下一步後，檢查目前下棋者是否獲勝（檢查三行、三列、兩對角線）。
 * - 讀入所有棋步（最多 9 個），依序處理。
 */
#include <stdio.h>

int board[3][3]; /* 0=空，1=玩家1，2=玩家2 */

/* 檢查 color（1 或 2）是否已獲勝 */
int check_win(int color) {
    int i;

    /* 檢查三行 */
    for (i = 0; i < 3; i++) {
        if (board[i][0] == color && board[i][1] == color && board[i][2] == color)
            return 1;
    }

    /* 檢查三列 */
    for (i = 0; i < 3; i++) {
        if (board[0][i] == color && board[1][i] == color && board[2][i] == color)
            return 1;
    }

    /* 檢查兩條對角線 */
    if (board[0][0] == color && board[1][1] == color && board[2][2] == color)
        return 1;
    if (board[0][2] == color && board[1][1] == color && board[2][0] == color)
        return 1;

    return 0;
}

int main(void) {
    int moves[9]; /* 儲存所有棋步 */
    int count = 0;
    int i, pos, row, col, color;

    /* 讀入棋步序列 */
    while (count < 9 && scanf("%d", &moves[count]) == 1)
        count++;

    /* 初始化棋盤 */
    for (i = 0; i < 3; i++) {
        int j;
        for (j = 0; j < 3; j++)
            board[i][j] = 0;
    }

    /* 依序下棋並判斷勝負 */
    for (i = 0; i < count; i++) {
        pos   = moves[i];
        row   = (pos - 1) / 3;
        col   = (pos - 1) % 3;
        color = (i % 2 == 0) ? 1 : 2; /* 奇數回合（0-based 偶數索引）為玩家 1 */

        board[row][col] = color;

        if (check_win(color)) {
            printf("%d\n", pos);
            return 0;
        }
    }

    /* 平局 */
    printf("0\n");

    return 0;
}
