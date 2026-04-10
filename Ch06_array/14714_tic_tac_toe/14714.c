/*
 * NTHU EE2310 - 題目 14714: Tic-Tac-Toe
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14714/
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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 將所有棋步讀入陣列 moves[]（最多 9 個整數，1~9）。
 * 2. 初始化棋盤 board[3][3] 全為 0（代表空格）。
 * 3. 依序處理每一步：
 *    - 位置 p 轉換為棋盤座標：row = (p-1)/3，col = (p-1)%3。
 *    - 0-based 回合索引 i 為偶數時是玩家 1，奇數時是玩家 2。
 *    - 將 board[row][col] 設為對應玩家的編號（1 或 2）。
 * 4. 每步落子後呼叫 check_win(color)：
 *    - 檢查三條橫行（row 固定）。
 *    - 檢查三條直列（col 固定）。
 *    - 檢查兩條對角線（主對角線與反對角線）。
 *    - 若三格均等於 color，表示該玩家獲勝，返回 1。
 * 5. 若 check_win 返回 1，輸出本步落子位置 p 並結束。
 * 6. 若所有棋步均處理完畢仍無人獲勝，輸出 0（平局）。
 *
 * English:
 * 1. Read all moves into array moves[] (up to 9 integers in range 1-9).
 * 2. Initialize the 3x3 board to all zeros (empty cells).
 * 3. Process each move in order:
 *    - Convert position p to board coordinates: row = (p-1)/3, col = (p-1)%3.
 *    - Even 0-based index i means player 1; odd index means player 2.
 *    - Set board[row][col] to the current player's number (1 or 2).
 * 4. After each placement, call check_win(color):
 *    - Check three rows, three columns, and both diagonals.
 *    - Return 1 if all three cells in any line equal color.
 * 5. If check_win returns 1, print the winning move position p and exit.
 * 6. If all moves are exhausted with no winner, print 0 (draw).
 */
#include <stdio.h>

int board[3][3]; /* 0=空，1=玩家1，2=玩家2 / 0=empty, 1=player 1, 2=player 2 */

/* 檢查 color（1 或 2）是否已獲勝 / check if color (1 or 2) has won */
int check_win(int color) {
    int i;

    /* 檢查三行 / check three rows */
    for (i = 0; i < 3; i++) {
        if (board[i][0] == color && board[i][1] == color && board[i][2] == color)
            return 1;
    }

    /* 檢查三列 / check three columns */
    for (i = 0; i < 3; i++) {
        if (board[0][i] == color && board[1][i] == color && board[2][i] == color)
            return 1;
    }

    /* 檢查兩條對角線 / check both diagonals */
    if (board[0][0] == color && board[1][1] == color && board[2][2] == color)
        return 1;
    if (board[0][2] == color && board[1][1] == color && board[2][0] == color)
        return 1;

    return 0;
}

int main(void) {
    int moves[9]; /* 儲存所有棋步 / store all moves */
    int count = 0;
    int i, pos, row, col, color;

    /* 讀入棋步序列 / read the sequence of moves */
    while (count < 9 && scanf("%d", &moves[count]) == 1)
        count++;

    /* 初始化棋盤 / initialize the board */
    for (i = 0; i < 3; i++) {
        int j;
        for (j = 0; j < 3; j++)
            board[i][j] = 0;
    }

    /* 依序下棋並判斷勝負 / place pieces in order and check for a winner */
    for (i = 0; i < count; i++) {
        pos   = moves[i];
        row   = (pos - 1) / 3;
        col   = (pos - 1) % 3;
        color = (i % 2 == 0) ? 1 : 2; /* 奇數回合（0-based 偶數索引）為玩家 1 / odd turns (even 0-based index) belong to player 1 */

        board[row][col] = color;

        if (check_win(color)) {
            printf("%d\n", pos);
            return 0;
        }
    }

    /* 平局 / draw (no winner) */
    printf("0\n");

    return 0;
}
