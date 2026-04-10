/*
 * NTHU EE2310 - 題目 14843: File Comparison
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 16 章（檔案處理）
 *   如果不知道如何解題，請參考課本第 16 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14843/
 *
 * 【題目說明】
 * 以行（line）為單位，逐行比較兩個文字檔案。
 *   - 輸出所有內容不同的行號（0-indexed），每個行號佔一行。
 *   - 若兩檔案行數不同，先輸出共同部分中所有不同的行號，
 *     再輸出「行數較多的檔名 多出來的行數」。
 *   - 例：fileA_0.txt 與 fileB_0.txt 比較結果為：
 *       第 1 行和第 4 行不同，且 fileB_0.txt 多出 2 行
 *       → 輸出 "1\n4\nfileB_0.txt 2"
 *   - 注意：本題在 OJ 上不支援檔案操作，將以人工批改為主，
 *     請確保程式邏輯正確。
 *
 * 【解題策略】
 * 1. 以 "r" 模式開啟兩個文字檔。
 * 2. 使用 fgets 逐行讀取並以 strcmp 比較。
 * 3. 追蹤行號（0-indexed），若不同則輸出。
 * 4. 若其中一個檔案先讀完，計算另一個剩餘行數並輸出較長檔名。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 從標準輸入讀入兩個檔名 fname1、fname2，以 "r"（文字）模式分別開啟。
 * 2. 使用 fgets 同時從兩個檔案各讀一行 line1、line2，追蹤行號 linenum（0-indexed）。
 * 3. 若兩者都讀到內容，呼叫 strcmp(line1, line2) 比較（含換行符）；不同則輸出 linenum。
 *    行號 linenum++ 後繼續下一輪。
 * 4. 若 r1 == NULL 且 r2 == NULL，兩檔案行數相同，比較結束，跳出迴圈。
 * 5. 若 r1 == NULL（第一個檔案先結束），r2 已讀出（extra 從 1 開始），
 *    繼續讀 f2 直到 NULL，累計 extra，輸出 "fname2 extra"。
 * 6. 若 r2 == NULL（第二個檔案先結束），同理計算並輸出 "fname1 extra"。
 * 7. 關閉兩個檔案並結束。
 *
 * English:
 * 1. Read two filenames fname1 and fname2 from stdin; open both in "r" (text) mode.
 * 2. Use fgets to read one line at a time from each file into line1 and line2;
 *    track the 0-indexed line number linenum.
 * 3. While both reads succeed, use strcmp(line1, line2) to compare (including newlines);
 *    if different, print linenum. Increment linenum and continue.
 * 4. If both r1 and r2 are NULL, the files have equal line counts; break.
 * 5. If r1 is NULL (first file ended first), r2 already holds a line (extra starts at 1);
 *    keep reading f2 until NULL, accumulate extra, then print "fname2 extra".
 * 6. If r2 is NULL (second file ended first), do the same and print "fname1 extra".
 * 7. Close both files and exit.
 */
#include <stdio.h>
#include <string.h>

#define MAXLINE 4096  /* 每行最大字元數（含換行符與結尾 '\0'） / max characters per line (including newline and '\0') */

int main(void) {
    char fname1[256];  /* 第一個檔案的名稱 / name of the first file */
    char fname2[256];  /* 第二個檔案的名稱 / name of the second file */

    /* 讀入兩個檔名（每個佔一行） / read two filenames (one per line) */
    if (scanf("%255s", fname1) != 1) return 0;
    if (scanf("%255s", fname2) != 1) return 0;

    /* 以文字讀取模式開啟兩個檔案 / open both files in text read mode */
    FILE *f1 = fopen(fname1, "r");
    FILE *f2 = fopen(fname2, "r");
    if (f1 == NULL || f2 == NULL) return 1;

    char line1[MAXLINE];  /* 第一個檔案目前讀到的行 / current line read from the first file */
    char line2[MAXLINE];  /* 第二個檔案目前讀到的行 / current line read from the second file */
    long linenum = 0;     /* 目前行號（0-indexed） / current line number (0-indexed) */

    /* 同時逐行讀取兩個檔案的共同部分 / read both files line by line through their common length */
    while (1) {
        char *r1 = fgets(line1, MAXLINE, f1);
        char *r2 = fgets(line2, MAXLINE, f2);

        if (r1 == NULL || r2 == NULL) {
            /* 至少有一個檔案已讀完，結束共同部分的比較 / at least one file ended; stop common-part comparison */
            if (r1 == NULL && r2 == NULL) {
                /* 兩檔行數相同，比較結束 / both files have equal line counts; comparison done */
            } else if (r1 == NULL) {
                /* 第一個檔案較短：r2 已讀出，再計算剩餘行數 / first file shorter: r2 already read, count remaining lines */
                long extra = 1;
                while (fgets(line2, MAXLINE, f2) != NULL) {
                    extra++;
                }
                printf("%s %ld\n", fname2, extra);
            } else {
                /* 第二個檔案較短：r1 已讀出，再計算剩餘行數 / second file shorter: r1 already read, count remaining lines */
                long extra = 1;
                while (fgets(line1, MAXLINE, f1) != NULL) {
                    extra++;
                }
                printf("%s %ld\n", fname1, extra);
            }
            break;
        }

        /* 比較兩行內容（含換行符），若不同則輸出行號 / compare both lines (including newlines); print line number if different */
        if (strcmp(line1, line2) != 0) {
            printf("%ld\n", linenum);
        }
        linenum++;
    }

    fclose(f1);
    fclose(f2);
    return 0;
}
