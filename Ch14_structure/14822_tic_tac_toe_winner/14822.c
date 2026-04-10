/*
 * NTHU EE2310 - 題目 14822: Tic-Tac-Toe Winner
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 14 章（結構）
 *   如果不知道如何解題，請參考課本第 14 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14822/
 *
 * 【題目說明】
 * 井字棋遊戲，使用結構體與指定函式介面。
 * 位置 1-9 對應棋盤格（1=左上，9=右下，row-major）：
 *   位置 p → row = (p-1)/3, col = (p-1)%3
 * 奇數回合為玩家 1，偶數回合為玩家 2。
 * 若嘗試落在已佔格子上，輸出 "illegal move"。
 * 若某玩家獲勝，輸出獲勝的最後一步位置編號。
 *
 * 【函式介面】
 * - init(ttt)：初始化棋盤
 * - play(ttt, color, x, y)：落子，回傳 0（合法）或 -1（非法）
 * - win(ttt, color)：判斷 color 是否獲勝，回傳 1 或 0
 *
 * 【解題策略】
 * main 讀入一行中的所有棋步（整數），依序處理。
 * 每回合呼叫 play，若回傳 -1 則輸出 "illegal move" 並結束。
 * 每回合後呼叫 win，若獲勝則輸出該步位置並結束。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 定義 TicTacToe 結構體，包含 3×3 整數棋盤（0=空，1=玩家1，2=玩家2）。
 * 2. 呼叫 init 將棋盤全部清零，turn 從 1 開始。
 * 3. 使用 scanf 依序讀入每個棋步位置 pos（1~9）。
 * 4. 將 pos 轉換為棋盤座標：row = (pos-1)/3，col = (pos-1)%3；
 *    依 turn 奇偶決定 color（奇數回合=玩家1，偶數=玩家2）。
 * 5. 呼叫 play(ttt, color, row, col)：若該格已佔用（board[row][col] != 0）回傳 -1，
 *    否則落子並回傳 0。
 * 6. 若 play 回傳 -1，輸出 "illegal move" 並結束。
 * 7. 呼叫 win 檢查三行、三列、主對角線、副對角線是否有 color 連成一線；
 *    若獲勝，輸出 pos（最後一步位置）並結束。
 * 8. turn++ 後繼續讀入下一個棋步，直到 EOF。
 *
 * English:
 * 1. Define TicTacToe struct with a 3×3 int board (0=empty, 1=player1, 2=player2).
 * 2. Call init to zero the board; start turn counter at 1.
 * 3. Read each move position pos (1-9) with scanf in a loop.
 * 4. Convert pos to board coordinates: row=(pos-1)/3, col=(pos-1)%3;
 *    determine color from turn parity (odd → player 1, even → player 2).
 * 5. Call play(ttt, color, row, col): if board[row][col] != 0 return -1 (illegal);
 *    otherwise mark the cell and return 0.
 * 6. If play returns -1, print "illegal move" and exit.
 * 7. Call win to check all three rows, three columns, main diagonal, and
 *    anti-diagonal for a complete line of color; if won, print pos and exit.
 * 8. Increment turn and continue reading moves until EOF.
 */
#include <stdio.h>

typedef struct {
    int board[3][3]; /* 0=空，1=玩家1，2=玩家2 / 0=empty, 1=player1, 2=player2 */
} TicTacToe;

/* 初始化棋盤（全部清零） / initialize the board (zero all cells) */
void init(TicTacToe *ttt) {
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            ttt->board[i][j] = 0;
}

/* 落子：在 (x, y) 落下 color（color=1 或 2）
 * 若該格已被佔用，回傳 -1（非法）；否則落子並回傳 0。
 * 此處 x 為列（row），y 為行（col）。
 */
int play(TicTacToe *ttt, int color, int x, int y) {
    if (ttt->board[x][y] != 0)
        return -1; /* 非法移動：格子已被佔用 / illegal move: cell already occupied */
    ttt->board[x][y] = color;
    return 0;
}

/* 判斷 color 是否已獲勝（完成一行、一列或一條對角線） */
int win(TicTacToe *ttt, int color) {
    int i;

    /* 檢查三行 / check three rows */
    for (i = 0; i < 3; i++) {
        if (ttt->board[i][0] == color &&
            ttt->board[i][1] == color &&
            ttt->board[i][2] == color)
            return 1;
    }

    /* 檢查三列 / check three columns */
    for (i = 0; i < 3; i++) {
        if (ttt->board[0][i] == color &&
            ttt->board[1][i] == color &&
            ttt->board[2][i] == color)
            return 1;
    }

    /* 檢查主對角線（左上到右下） / check main diagonal (top-left to bottom-right) */
    if (ttt->board[0][0] == color &&
        ttt->board[1][1] == color &&
        ttt->board[2][2] == color)
        return 1;

    /* 檢查副對角線（右上到左下） / check anti-diagonal (top-right to bottom-left) */
    if (ttt->board[0][2] == color &&
        ttt->board[1][1] == color &&
        ttt->board[2][0] == color)
        return 1;

    return 0;
}

int main(void) {
    TicTacToe ttt;
    int pos, row, col, color;
    int turn; /* 回合計數（從 1 開始） / turn counter (starts at 1) */
    int ret;

    init(&ttt);
    turn = 1;

    /* 讀入棋步直到行尾或 EOF / read moves until end of line or EOF */
    while (scanf("%d", &pos) == 1) {
        row   = (pos - 1) / 3;
        col   = (pos - 1) % 3;
        color = (turn % 2 == 1) ? 1 : 2; /* 奇數回合為玩家 1 / odd turn = player 1 */

        ret = play(&ttt, color, row, col);

        if (ret == -1) {
            /* 非法移動 / illegal move */
            printf("illegal move\n");
            return 0;
        }

        if (win(&ttt, color)) {
            /* 當前玩家獲勝，輸出最後一步位置 / current player wins, print the winning move position */
            printf("%d\n", pos);
            return 0;
        }

        turn++;
    }

    return 0;
}
