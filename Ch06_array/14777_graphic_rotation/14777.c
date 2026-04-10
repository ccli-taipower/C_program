/*
 * NTHU EE2310 - 題目 14777: Graphic Rotation
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14777/
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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 用 fgets 逐行讀入原始圖形，儲存在 buf_a[][]，同時追蹤列數 rows
 *    與最大行數 cols（去除換行符後各行的最長長度）。
 * 2. 補齊各行至相同長度 cols（以空格填充），確保矩陣形狀一致。
 * 3. 輸出原始圖形（版本 0）。
 * 4. 執行 3 次順時針旋轉（rot = 0, 1, 2）：
 *    a. new_rows = cols（舊列數 → 新行數），new_cols = rows（舊行數 → 新列數）。
 *    b. 旋轉公式：buf_b[c][rows-1-r] = buf_a[r][c]，
 *       其中 r ∈ [0, rows)，c ∈ [0, cols)。
 *    c. 更新 rows/cols 為新尺寸，為 buf_b 各行加上字串終止字元。
 *    d. 輸出 buf_b 中旋轉後的圖形。
 *    e. 將 buf_b 複製回 buf_a，供下一次旋轉使用。
 * 5. 最終共輸出 4 個版本（原圖 + 旋轉 1, 2, 3 次）。
 *
 * English:
 * 1. Read the original graphic line-by-line with fgets into buf_a[][],
 *    tracking row count (rows) and the maximum line length (cols) after
 *    stripping newlines.
 * 2. Pad each row to the same length cols with spaces for a uniform matrix.
 * 3. Print the original graphic (version 0).
 * 4. Perform 3 clockwise rotations (rot = 0, 1, 2):
 *    a. new_rows = cols (old cols become new rows), new_cols = rows.
 *    b. Apply rotation: buf_b[c][rows-1-r] = buf_a[r][c]
 *       for r in [0, rows), c in [0, cols).
 *    c. Update rows/cols to the new dimensions; null-terminate each row of buf_b.
 *    d. Print the rotated graphic stored in buf_b.
 *    e. Copy buf_b back to buf_a for the next rotation.
 * 5. A total of 4 versions are output (original + 3 rotations).
 */
#include <stdio.h>
#include <string.h>

#define MAXDIM 505

char buf_a[MAXDIM][MAXDIM]; /* 目前圖形 / current graphic buffer */
char buf_b[MAXDIM][MAXDIM]; /* 旋轉後圖形 / rotated graphic buffer */

int main(void) {
    int rows, cols;       /* 目前圖形的列數與行數 / current number of rows and columns */
    int new_rows, new_cols; /* 旋轉後的列數與行數 / rows and columns after rotation */
    int r, c, rot;
    char line[MAXDIM];

    rows = 0;
    cols = 0;

    /* 讀入原始圖形（讀至 EOF）/ read original graphic until EOF */
    while (fgets(line, sizeof(line), stdin) != NULL) {
        /* 移除換行符 / strip trailing newline */
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

    /* 補齊每列到相同長度（以空格填充）/ pad each row to the same length with spaces */
    for (r = 0; r < rows; r++) {
        int len = (int)strlen(buf_a[r]);
        for (c = len; c < cols; c++)
            buf_a[r][c] = ' ';
        buf_a[r][cols] = '\0';
    }

    /* 輸出原始圖形 / print the original graphic */
    for (r = 0; r < rows; r++)
        printf("%s\n", buf_a[r]);

    /* 執行 3 次順時針旋轉並輸出 / perform 3 clockwise rotations and print each result */
    for (rot = 0; rot < 3; rot++) {
        new_rows = cols;   /* 旋轉後列數 = 原行數 / rows after rotation = original cols */
        new_cols = rows;   /* 旋轉後行數 = 原列數 / cols after rotation = original rows */

        /* 計算旋轉後圖形：new[col][rows-1-row] = old[row][col] / apply rotation formula */
        for (r = 0; r < rows; r++) {
            for (c = 0; c < cols; c++) {
                buf_b[c][rows - 1 - r] = buf_a[r][c];
            }
        }

        /* 更新尺寸 / update dimensions */
        rows = new_rows;
        cols = new_cols;

        /* 加入字串終止字元 / null-terminate each row of the rotated buffer */
        for (r = 0; r < rows; r++)
            buf_b[r][cols] = '\0';

        /* 輸出旋轉後圖形 / print the rotated graphic */
        for (r = 0; r < rows; r++)
            printf("%s\n", buf_b[r]);

        /* 將 buf_b 複製回 buf_a，以供下一次旋轉使用 / copy buf_b back to buf_a for the next rotation */
        for (r = 0; r < rows; r++)
            strncpy(buf_a[r], buf_b[r], MAXDIM - 1);
    }

    return 0;
}
