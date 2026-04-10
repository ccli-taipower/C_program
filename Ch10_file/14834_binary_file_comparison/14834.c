/*
 * NTHU EE2310 - 題目 14834: Binary File Comparison
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 10 章（檔案）
 *   如果不知道如何解題，請參考課本第 10 章的說明。
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
 */
#include <stdio.h>

int main(void) {
    char fname1[256];  /* 第一個檔案的名稱 */
    char fname2[256];  /* 第二個檔案的名稱 */

    /* 讀入兩個檔名（每個佔一行） */
    if (scanf("%255s", fname1) != 1) return 0;
    if (scanf("%255s", fname2) != 1) return 0;

    /* 以二進位讀取模式開啟兩個檔案 */
    FILE *f1 = fopen(fname1, "rb");
    FILE *f2 = fopen(fname2, "rb");
    if (f1 == NULL || f2 == NULL) return 1;

    long offset = 0;  /* 目前的位元組偏移量（0-indexed） */
    int c1, c2;       /* 從兩個檔案各自讀到的位元組 */

    /* 同時逐一比較兩個檔案的共同部分 */
    while (1) {
        c1 = fgetc(f1);
        c2 = fgetc(f2);

        if (c1 == EOF || c2 == EOF) {
            /* 至少有一個檔案已讀完，結束共同部分的比較 */
            break;
        }

        /* 若該位元組內容不同，輸出其偏移量 */
        if (c1 != c2) {
            printf("%ld\n", offset);
        }
        offset++;
    }

    /* 判斷哪個檔案有多餘的位元組 */
    if (c1 != EOF) {
        /* 第一個檔案較長：計算剩餘位元組數 */
        long extra = 1;  /* c1 已讀出但 c2 已是 EOF */
        while (fgetc(f1) != EOF) {
            extra++;
        }
        printf("%s %ld\n", fname1, extra);
    } else if (c2 != EOF) {
        /* 第二個檔案較長：計算剩餘位元組數 */
        long extra = 1;  /* c2 已讀出但 c1 已是 EOF */
        while (fgetc(f2) != EOF) {
            extra++;
        }
        printf("%s %ld\n", fname2, extra);
    }
    /* 若兩者同時到 EOF，長度相同，不需要額外輸出 */

    fclose(f1);
    fclose(f2);
    return 0;
}
