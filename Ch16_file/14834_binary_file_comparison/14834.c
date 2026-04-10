/*
 * NTHU EE2310 - 題目 14834: Binary File Comparison
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 16 章（檔案處理）
 *   如果不知道如何解題，請參考課本第 16 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14834/
 *
 * 【題目說明】
 * 以位元組（byte）為單位，逐一比較兩個二進位檔案的內容。
 *   - 輸出所有內容不同的位元組偏移量（0-indexed），每個偏移量佔一行。
 *   - 若兩檔案長度不同，先輸出共同部分中所有不同的偏移量，
 *     再輸出「較長檔案的檔名 多出來的位元組數」。
 *   - 若兩檔案完全相同則無任何輸出。
 *
 * 【解題策略】
 * 1. 以 "rb" 模式開啟兩個二進位檔。
 * 2. 同時逐一讀取兩個檔案的位元組，若不同則輸出當前偏移量。
 * 3. 若其中一個檔案已到 EOF 而另一個尚未，
 *    計算剩餘位元組數並輸出「較長檔名 剩餘位元組數」。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 從標準輸入讀入兩個檔名 fname1、fname2，以 "rb" 模式分別開啟。
 * 2. 使用 fgetc 同時從兩個檔案各讀一個位元組 c1、c2；追蹤偏移量 offset。
 * 3. 若兩者都不是 EOF，比較 c1 與 c2：不同則輸出偏移量 offset，然後 offset++。
 * 4. 若任一為 EOF，結束共同部分的比較迴圈。
 * 5. 若 c1 != EOF（第一個檔案較長），計算剩餘位元組數 extra（從 1 開始，因 c1 已讀出），
 *    繼續讀 f1 直到 EOF，輸出 "fname1 extra"。
 * 6. 若 c2 != EOF（第二個檔案較長），同理計算並輸出 "fname2 extra"。
 * 7. 若兩者同時到 EOF，長度相同，不需額外輸出；關閉兩個檔案。
 *
 * English:
 * 1. Read two filenames fname1 and fname2 from stdin; open both in "rb" mode.
 * 2. Read one byte at a time from each file using fgetc (c1, c2); track byte offset.
 * 3. While neither c1 nor c2 is EOF, compare them: if different, print the current
 *    offset, then increment offset.
 * 4. Break out of the loop when at least one file reaches EOF.
 * 5. If c1 != EOF (first file is longer), count remaining bytes starting from 1
 *    (since c1 was already read), continue reading f1 to EOF, then print "fname1 extra".
 * 6. If c2 != EOF (second file is longer), do the same and print "fname2 extra".
 * 7. If both reach EOF simultaneously, lengths are equal; no extra output. Close files.
 */
#include <stdio.h>

int main(void) {
    char fname1[256];  /* 第一個檔案的名稱 / name of the first file */
    char fname2[256];  /* 第二個檔案的名稱 / name of the second file */

    /* 讀入兩個檔名（每個佔一行） / read two filenames (one per line) */
    if (scanf("%255s", fname1) != 1) return 0;
    if (scanf("%255s", fname2) != 1) return 0;

    /* 以二進位讀取模式開啟兩個檔案 / open both files in binary read mode */
    FILE *f1 = fopen(fname1, "rb");
    FILE *f2 = fopen(fname2, "rb");
    if (f1 == NULL || f2 == NULL) return 1;

    long offset = 0;  /* 目前的位元組偏移量（0-indexed） / current byte offset (0-indexed) */
    int c1, c2;       /* 從兩個檔案各自讀到的位元組 / bytes read from each file */

    /* 同時逐一比較兩個檔案的共同部分 / compare both files byte by byte through their common length */
    while (1) {
        c1 = fgetc(f1);
        c2 = fgetc(f2);

        if (c1 == EOF || c2 == EOF) {
            /* 至少有一個檔案已讀完，結束共同部分的比較 / at least one file ended; stop common-part comparison */
            break;
        }

        /* 若該位元組內容不同，輸出其偏移量 / if bytes differ, print the offset */
        if (c1 != c2) {
            printf("%ld\n", offset);
        }
        offset++;
    }

    /* 判斷哪個檔案有多餘的位元組 / determine which file has extra bytes */
    if (c1 != EOF) {
        /* 第一個檔案較長：計算剩餘位元組數 / first file is longer: count remaining bytes */
        long extra = 1;  /* c1 已讀出但 c2 已是 EOF / c1 already read but c2 is EOF */
        while (fgetc(f1) != EOF) {
            extra++;
        }
        printf("%s %ld\n", fname1, extra);
    } else if (c2 != EOF) {
        /* 第二個檔案較長：計算剩餘位元組數 / second file is longer: count remaining bytes */
        long extra = 1;  /* c2 已讀出但 c1 已是 EOF / c2 already read but c1 is EOF */
        while (fgetc(f2) != EOF) {
            extra++;
        }
        printf("%s %ld\n", fname2, extra);
    }
    /* 若兩者同時到 EOF，長度相同，不需要額外輸出 / if both reach EOF together, lengths are equal; no extra output */

    fclose(f1);
    fclose(f2);
    return 0;
}
