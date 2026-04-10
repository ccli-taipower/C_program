/*
 * NTHU EE2310 - 題目 14780: Uniform Invoice Prize
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 5 章（迴圈）
 *   如果不知道如何解題，請參考課本第 5 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14780/
 *
 * 【題目說明】
 * 台灣統一發票對獎程式。
 * 輸入：
 *   - 3 個特別獎號碼（8 位數）
 *   - 3 個頭獎號碼（8 位數）
 *   - 多張收據號碼（8 位數），直到 EOF
 *
 * 對獎規則（針對每張收據對所有頭獎號碼比對，取最高獎項）：
 *   - 與特別獎完全相同（8 碼）→ 2,000,000 元
 *   - 與頭獎完全相同（8 碼）→ 200,000 元
 *   - 後 7 碼與頭獎相同 → 40,000 元
 *   - 後 6 碼相同 → 10,000 元
 *   - 後 5 碼相同 → 4,000 元
 *   - 後 4 碼相同 → 1,000 元
 *   - 後 3 碼相同 → 200 元
 *   - 不符合 → 0 元
 * 輸出：所有收據的總得獎金額。
 *
 * 【解題策略】
 * 1. 讀入特別獎和頭獎號碼，以字串形式儲存（方便比較後幾位）。
 * 2. 對每張收據，先對所有特別獎號碼做完整比對。
 * 3. 再對所有 3 個頭獎號碼逐一做後幾碼比對，取得最高獎項。
 * 4. 累加每張收據的獎金。
 * 5. 用 strcmp 比較 8 碼全部，用比較末尾 k 碼判斷各獎項。
 *    比較末尾 k 碼：取字串末 k 個字元來比對（因為號碼固定 8 碼）。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入 3 個特別獎號碼（8 碼字串）和 3 個頭獎號碼（8 碼字串），分別存入 special[][] 和 first[][] 陣列。
 * 2. 初始化總獎金 total = 0，進入 while 迴圈逐張讀入收據號碼。
 * 3. 對每張收據，先對 3 個特別獎全碼比對（strcmp）；若完全相符，prize = 2,000,000，並跳過頭獎比對。
 * 4. 若未中特別獎，對 3 個頭獎逐一比對：
 *    a. 全碼相符（8 碼）→ best = 200,000。
 *    b. 否則依後 7、6、5、4、3 碼順序比對，利用指標偏移 receipt+(8-k) 與 first[i]+(8-k) 比較末 k 碼。
 *    c. 找到最長匹配後設定對應獎金並 break。
 * 5. 對 3 個頭獎取最高的 best，更新 prize。
 * 6. 將 prize 累加到 total，處理完所有收據後輸出 total。
 *
 * English:
 * 1. Read 3 special prize numbers and 3 first-prize numbers (each 8 digits) into special[][] and first[][] arrays.
 * 2. Initialize total = 0 and enter a while loop to read receipt numbers one at a time.
 * 3. For each receipt, compare against all 3 special prize numbers using strcmp; if fully matched, set prize = 2,000,000 and skip first-prize checking.
 * 4. If no special prize, compare against each of the 3 first-prize numbers:
 *    a. Full 8-digit match → best = 200,000.
 *    b. Otherwise try matching the last 7, 6, 5, 4, 3 digits using pointer offset receipt+(8-k) vs first[i]+(8-k).
 *    c. Set the prize amount for the longest suffix match found and break.
 * 5. Take the highest best across all 3 first-prize comparisons and update prize.
 * 6. Accumulate prize into total; after all receipts are processed, print total.
 */
#include <stdio.h>
#include <string.h>

int main(void) {
    char special[3][9];  /* 3 個特別獎號碼（8 位數 + '\0'） / 3 special prize numbers (8 digits + null terminator) */
    char first[3][9];    /* 3 個頭獎號碼 / 3 first-prize numbers */
    char receipt[9];     /* 收據號碼 / receipt number */
    long long total;     /* 總獎金 / total prize amount */
    int prize;           /* 單張收據的獎金 / prize amount for a single receipt */
    int best;            /* 對單個頭獎的最高獎金 / best prize from one first-prize comparison */
    int i, k;
    int match;           /* 比對後幾碼是否相同 / flag: whether suffix digits match */

    /* 讀入 3 個特別獎號碼 / read 3 special prize numbers */
    for (i = 0; i < 3; i++) {
        scanf("%s", special[i]);
    }

    /* 讀入 3 個頭獎號碼 / read 3 first-prize numbers */
    for (i = 0; i < 3; i++) {
        scanf("%s", first[i]);
    }

    total = 0;

    /* 逐張讀入收據號碼並對獎 / read each receipt and determine its prize */
    while (scanf("%s", receipt) == 1) {
        prize = 0;

        /* 先檢查特別獎（完整 8 碼相符）/ first check special prizes (full 8-digit match) */
        for (i = 0; i < 3; i++) {
            if (strcmp(receipt, special[i]) == 0) {
                prize = 2000000;
                break;
            }
        }

        /* 若尚未中特別獎，對頭獎進行比對 / if no special prize, check first prizes */
        if (prize == 0) {
            /* 對 3 個頭獎號碼逐一比對，取最高獎 / compare against each first prize and keep the best */
            for (i = 0; i < 3; i++) {
                best = 0;

                /* 檢查 8 碼完全相符（頭獎）/ check full 8-digit match (first prize) */
                if (strcmp(receipt, first[i]) == 0) {
                    best = 200000;
                } else {
                    /* 依序比較後 7、6、5、4、3 碼 / compare last 7, 6, 5, 4, 3 digits in order */
                    /* 號碼固定 8 碼，後 k 碼從第 (8-k) 個字元開始 / fixed 8-digit numbers: last k digits start at position (8-k) */
                    for (k = 7; k >= 3; k--) {
                        match = (strcmp(receipt + (8 - k), first[i] + (8 - k)) == 0);
                        if (match) {
                            if (k == 7) best = 40000;
                            else if (k == 6) best = 10000;
                            else if (k == 5) best = 4000;
                            else if (k == 4) best = 1000;
                            else if (k == 3) best = 200;
                            break; /* 已找到最高匹配，跳出 / best suffix match found, stop */
                        }
                    }
                }

                /* 取對所有頭獎比對中的最高獎 / update prize with the best result across all first prizes */
                if (best > prize) {
                    prize = best;
                }
            }
        }

        total += prize;
    }

    printf("%lld\n", total);

    return 0;
}
