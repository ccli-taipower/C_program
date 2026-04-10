/*
 * NTHU EE2310 - 題目 14844: File Splitting
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 16 章（檔案處理）
 *   如果不知道如何解題，請參考課本第 16 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14844/
 *
 * 【題目說明】
 * 將一個二進位檔案切割成每個最多 m 個位元組的小檔案。
 *   - 輸出檔名依序命名為 "原檔名.1"、"原檔名.2"、... 。
 *   - 最後一個輸出檔可能少於 m 個位元組。
 *   - 程式本身不產生任何標準輸出（stdout），只建立檔案。
 *
 * 【解題策略】
 * 1. 讀入原始檔名與分割大小 m。
 * 2. 以 "rb" 模式開啟原始檔案。
 * 3. 迴圈：每次讀取最多 m 個位元組，
 *    寫入以 "原檔名.i"（i=1,2,...）命名的新檔案（"wb" 模式）。
 * 4. 直到原始檔案讀完為止。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 從標準輸入讀入原始檔名 fname 和分割大小 m，以 "rb" 模式開啟原始檔案 fin。
 * 2. 外層迴圈：以 fgetc 讀出第一個位元組 c；若為 EOF 則結束迴圈，無需再建立新檔案。
 * 3. 使用 snprintf 組合輸出檔名 "fname.part"（part 從 1 開始）。
 * 4. 以 "wb" 模式開啟輸出檔案 fout，將已讀出的第一個位元組用 fputc 寫入。
 * 5. 內層迴圈：繼續以 fgetc 讀取至多 m-1 個位元組，逐個用 fputc 寫入 fout；
 *    若讀到 EOF 則提前結束內層迴圈（最後一個分割檔案可能不足 m bytes）。
 * 6. 關閉 fout，part++ 後回到外層迴圈，繼續處理下一個分割。
 * 7. 所有位元組讀完後關閉 fin；程式不產生任何標準輸出。
 *
 * English:
 * 1. Read the source filename fname and split size m from stdin; open the source file
 *    fin in "rb" mode.
 * 2. Outer loop: read the first byte c with fgetc; if EOF, exit the loop (no more parts
 *    to create).
 * 3. Use snprintf to construct the output filename "fname.part" (part starts at 1).
 * 4. Open output file fout in "wb" mode; write the already-read first byte with fputc.
 * 5. Inner loop: continue reading up to m-1 more bytes with fgetc, writing each with
 *    fputc to fout; break early on EOF (the last part may be smaller than m bytes).
 * 6. Close fout, increment part, and return to the outer loop for the next part.
 * 7. After all bytes are consumed, close fin; the program produces no stdout output.
 */
#include <stdio.h>
#include <string.h>

int main(void) {
    char fname[256];   /* 原始檔案的名稱 / name of the source file */
    int m;             /* 每個輸出檔案的最大位元組數 / maximum bytes per output file */

    /* 讀入原始檔名與分割大小 / read source filename and split size */
    if (scanf("%255s %d", fname, &m) != 2) return 0;

    /* 以二進位讀取模式開啟原始檔案 / open source file in binary read mode */
    FILE *fin = fopen(fname, "rb");
    if (fin == NULL) return 1;

    char outname[300];  /* 輸出檔案的名稱緩衝區 / output filename buffer */
    int part = 1;       /* 目前輸出檔案的編號（從 1 開始） / current output file number (starting at 1) */
    int c;              /* 目前讀到的位元組 / byte currently read */

    /* 逐一讀取原始檔案並分批寫出 / read source file byte by byte and write in batches */
    while ((c = fgetc(fin)) != EOF) {
        /* 建立輸出檔名：原檔名.part / construct output filename: original_name.part */
        snprintf(outname, sizeof(outname), "%s.%d", fname, part);

        /* 以二進位寫入模式開啟輸出檔案 / open output file in binary write mode */
        FILE *fout = fopen(outname, "wb");
        if (fout == NULL) {
            fclose(fin);
            return 1;
        }

        /* 將第一個位元組（已讀出）寫入輸出檔案 / write the first byte (already read) to the output file */
        fputc(c, fout);

        /* 繼續讀取剩餘的 m-1 個位元組 / continue reading up to m-1 more bytes */
        int count = 1;
        while (count < m && (c = fgetc(fin)) != EOF) {
            fputc(c, fout);
            count++;
        }

        fclose(fout);
        part++;
    }

    fclose(fin);
    return 0;
}
