/*
 * NTHU EE2310 - 題目 14844: File Splitting
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 10 章（檔案）
 *   如果不知道如何解題，請參考課本第 10 章的說明。
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
 */
#include <stdio.h>
#include <string.h>

int main(void) {
    char fname[256];   /* 原始檔案的名稱 */
    int m;             /* 每個輸出檔案的最大位元組數 */

    /* 讀入原始檔名與分割大小 */
    if (scanf("%255s %d", fname, &m) != 2) return 0;

    /* 以二進位讀取模式開啟原始檔案 */
    FILE *fin = fopen(fname, "rb");
    if (fin == NULL) return 1;

    char outname[300];  /* 輸出檔案的名稱緩衝區 */
    int part = 1;       /* 目前輸出檔案的編號（從 1 開始） */
    int c;              /* 目前讀到的位元組 */

    /* 逐一讀取原始檔案並分批寫出 */
    while ((c = fgetc(fin)) != EOF) {
        /* 建立輸出檔名：原檔名.part */
        snprintf(outname, sizeof(outname), "%s.%d", fname, part);

        /* 以二進位寫入模式開啟輸出檔案 */
        FILE *fout = fopen(outname, "wb");
        if (fout == NULL) {
            fclose(fin);
            return 1;
        }

        /* 將第一個位元組（已讀出）寫入輸出檔案 */
        fputc(c, fout);

        /* 繼續讀取剩餘的 m-1 個位元組 */
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
