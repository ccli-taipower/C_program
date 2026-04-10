/*
 * NTHU EE2310 - 題目 14822: Tic-Tac-Toe Winner
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
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
 */
#include <stdio.h>

typedef struct {
    int board[3][3]; /* 0=空，1=玩家1，2=玩家2 */
} TicTacToe;

/* 初始化棋盤（全部清零） */
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
        return -1; /* 非法移動：格子已被佔用 */
    ttt->board[x][y] = color;
    return 0;
}

/* 判斷 color 是否已獲勝（完成一行、一列或一條對角線） */
int win(TicTacToe *ttt, int color) {
    int i;

    /* 檢查三行 */
    for (i = 0; i < 3; i++) {
        if (ttt->board[i][0] == color &&
            ttt->board[i][1] == color &&
            ttt->board[i][2] == color)
            return 1;
    }

    /* 檢查三列 */
    for (i = 0; i < 3; i++) {
        if (ttt->board[0][i] == color &&
            ttt->board[1][i] == color &&
            ttt->board[2][i] == color)
            return 1;
    }

    /* 檢查主對角線（左上到右下） */
    if (ttt->board[0][0] == color &&
        ttt->board[1][1] == color &&
        ttt->board[2][2] == color)
        return 1;

    /* 檢查副對角線（右上到左下） */
    if (ttt->board[0][2] == color &&
        ttt->board[1][1] == color &&
        ttt->board[2][0] == color)
        return 1;

    return 0;
}

int main(void) {
    TicTacToe ttt;
    int pos, row, col, color;
    int turn; /* 回合計數（從 1 開始） */
    int ret;

    init(&ttt);
    turn = 1;

    /* 讀入棋步直到行尾或 EOF */
    while (scanf("%d", &pos) == 1) {
        row   = (pos - 1) / 3;
        col   = (pos - 1) % 3;
        color = (turn % 2 == 1) ? 1 : 2; /* 奇數回合為玩家 1 */

        ret = play(&ttt, color, row, col);

        if (ret == -1) {
            /* 非法移動 */
            printf("illegal move\n");
            return 0;
        }

        if (win(&ttt, color)) {
            /* 當前玩家獲勝，輸出最後一步位置 */
            printf("%d\n", pos);
            return 0;
        }

        turn++;
    }

    return 0;
}
