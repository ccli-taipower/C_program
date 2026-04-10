/*
 * NTHU EE2310 - 題目 14777: Graphic Rotation
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目說明】
 * 讀入一個文字圖形（n 列、m 行），將其順時針旋轉 3 次。
 * 依序輸出：原圖、旋轉1次後、旋轉2次後、旋轉3次後，共 4 個版本。
 *
 * 【順時針旋轉規則】
 * 若原圖為 rows×cols，旋轉後為 cols×rows。
 * 旋轉公式：new[col][rows-1-row] = old[row][col]
 * 亦即：new_row = col, new_col = rows-1-row
 *
 * 【解題策略】
 * - 用雙緩衝方式：buf_a 為目前圖形，buf_b 為旋轉後圖形，交替使用。
 * - 每次旋轉後，輸出新圖形。
 * - 最大尺寸假設為 500×500（包含字串終止字元）。
 */
#include <stdio.h>
#include <string.h>

#define MAXDIM 505

char buf_a[MAXDIM][MAXDIM]; /* 目前圖形 */
char buf_b[MAXDIM][MAXDIM]; /* 旋轉後圖形 */

int main(void) {
    int rows, cols;       /* 目前圖形的列數與行數 */
    int new_rows, new_cols; /* 旋轉後的列數與行數 */
    int r, c, rot;
    char line[MAXDIM];

    rows = 0;
    cols = 0;

    /* 讀入原始圖形（讀至 EOF） */
    while (fgets(line, sizeof(line), stdin) != NULL) {
        /* 移除換行符 */
        int len = (int)strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }
        if (len > cols)
            cols = len;
        strncpy(buf_a[rows], line, MAXDIM - 1);
        buf_a[rows][MAXDIM - 1] = '\0';
        rows++;
    }

    /* 補齊每列到相同長度（以空格填充） */
    for (r = 0; r < rows; r++) {
        int len = (int)strlen(buf_a[r]);
        for (c = len; c < cols; c++)
            buf_a[r][c] = ' ';
        buf_a[r][cols] = '\0';
    }

    /* 輸出原始圖形 */
    for (r = 0; r < rows; r++)
        printf("%s\n", buf_a[r]);

    /* 執行 3 次順時針旋轉並輸出 */
    for (rot = 0; rot < 3; rot++) {
        new_rows = cols;   /* 旋轉後列數 = 原行數 */
        new_cols = rows;   /* 旋轉後行數 = 原列數 */

        /* 計算旋轉後圖形：new[col][rows-1-row] = old[row][col] */
        for (r = 0; r < rows; r++) {
            for (c = 0; c < cols; c++) {
                buf_b[c][rows - 1 - r] = buf_a[r][c];
            }
        }

        /* 更新尺寸 */
        rows = new_rows;
        cols = new_cols;

        /* 加入字串終止字元 */
        for (r = 0; r < rows; r++)
            buf_b[r][cols] = '\0';

        /* 輸出旋轉後圖形 */
        for (r = 0; r < rows; r++)
            printf("%s\n", buf_b[r]);

        /* 將 buf_b 複製回 buf_a，以供下一次旋轉使用 */
        for (r = 0; r < rows; r++)
            strncpy(buf_a[r], buf_b[r], MAXDIM - 1);
    }

    return 0;
}
