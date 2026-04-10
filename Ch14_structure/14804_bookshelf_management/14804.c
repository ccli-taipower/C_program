/*
 * NTHU EE2310 - 題目 14804: Bookshelf Management
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 14 章（結構）
 *   如果不知道如何解題，請參考課本第 14 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14804/
 *
 * 【題目說明】
 * 模擬一個有 8 個書槽的書架（類似 LRU 快取）。書籍編號為 1～255。
 * 每次取書（讀書號 b）的規則：
 *   - 若 b 已在書架上：將 b 從原位置移除，放到最右端
 *   - 若 b 不在書架上：
 *     - 書架未滿（不足 8 本）：直接將 b 放到最右端
 *     - 書架已滿（8 本）：移除最左端的書，將 b 放到最右端
 * 初始書架為空。
 * 處理完所有取書操作後，輸出書架上 8 個位置的書號（空位輸出 0）。
 *
 * 【解題策略】
 * 用長度為 8 的整數陣列模擬書架，另維護一個變數 cnt 記錄目前書本數量。
 * - 「移除書籍」：找到位置後將後面的書往左移（陣列左移）。
 * - 「加入最右端」：在 cnt 位置放入書號，cnt 加一。
 * - 「移除最左端」：等同刪除位置 0（整個陣列左移一格）。
 *
 * 輸入：一連串書號，直到 EOF
 * 輸出：書架上 8 個位置的書號，以空白分隔（一行）
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 初始化長度 8 的整數陣列 shelf，全部清零；計數器 cnt = 0。
 * 2. 持續使用 scanf 讀入書號 b，直到 EOF。
 * 3. 對每個書號，線性搜尋 shelf[0..cnt-1] 是否已有該書（記錄位置 pos）。
 * 4. 若 pos >= 0（書已在架上）：
 *    將 pos+1 以後的元素全部左移一格，cnt--（相當於從 pos 移除書本）。
 * 5. 若 pos < 0（書不在架上）：
 *    若 cnt == SHELF_SIZE（已滿），將整個陣列左移一格，cnt--（移除最左端書本）。
 * 6. 將書號 b 放入 shelf[cnt]，cnt++ （書本加到最右端）。
 * 7. 所有書號處理完後，輸出 shelf[0..7]，空位（index >= cnt）輸出 0。
 *
 * English:
 * 1. Initialize the shelf array of 8 ints to all zeros; set counter cnt = 0.
 * 2. Repeatedly read book number b with scanf until EOF.
 * 3. For each b, linearly search shelf[0..cnt-1] for b and record position pos.
 * 4. If pos >= 0 (book is already on the shelf):
 *    Shift elements from pos+1 onward one step left, then cnt-- (removes b from pos).
 * 5. If pos < 0 (book is not on the shelf):
 *    If cnt == SHELF_SIZE (full), shift the entire array left by one, cnt--
 *    (evicts the leftmost book).
 * 6. Place b at shelf[cnt], then cnt++ (appends to the right end).
 * 7. After processing all inputs, print shelf[0..7]; output 0 for empty slots.
 */
#include <stdio.h>

#define SHELF_SIZE 8   /* 書架最大容量 / maximum shelf capacity */

int main(void) {
    int shelf[SHELF_SIZE];   /* 書架陣列（0 表示空位） / shelf array (0 = empty slot) */
    int cnt = 0;             /* 目前書架上的書本數量 / current number of books on the shelf */
    int b;                   /* 讀入的書號 / book number read from input */

    /* 初始化書架為空 / initialize the shelf to empty */
    for (int i = 0; i < SHELF_SIZE; i++) {
        shelf[i] = 0;
    }

    /* 逐一讀入書號，直到 EOF / read book numbers one by one until EOF */
    while (scanf("%d", &b) == 1) {

        /* 先搜尋 b 是否已在書架上 / search whether b is already on the shelf */
        int pos = -1;   /* b 在書架上的位置，-1 表示不在 / position of b on shelf, -1 if absent */
        for (int i = 0; i < cnt; i++) {
            if (shelf[i] == b) {
                pos = i;
                break;
            }
        }

        if (pos >= 0) {
            /* b 已在書架上：從原位置移除，放到最右端 / b is on the shelf: remove from current position, place at right end */
            /* 將 pos+1 以後的書往左移一格 / shift books after pos one slot to the left */
            for (int i = pos; i < cnt - 1; i++) {
                shelf[i] = shelf[i + 1];
            }
            cnt--;   /* 移除後書本數量減一 / decrement count after removal */
        } else {
            /* b 不在書架上 / b is not on the shelf */
            if (cnt == SHELF_SIZE) {
                /* 書架已滿：移除最左端（位置 0），整體左移 / shelf full: evict leftmost (position 0), shift all left */
                for (int i = 0; i < SHELF_SIZE - 1; i++) {
                    shelf[i] = shelf[i + 1];
                }
                cnt--;   /* 移除後書本數量減一 / decrement count after eviction */
            }
            /* 書架未滿（或已騰出空間）：不需額外處理 / shelf not full (or space freed): no extra action needed */
        }

        /* 將 b 放到最右端 / place b at the right end */
        shelf[cnt] = b;
        cnt++;
    }

    /* 輸出書架上 8 個位置的書號（空位補 0） / print all 8 shelf positions; output 0 for empty slots */
    for (int i = 0; i < SHELF_SIZE; i++) {
        if (i > 0) printf(" ");
        if (i < cnt) {
            printf("%d", shelf[i]);
        } else {
            printf("0");   /* 空位輸出 0 / empty slot outputs 0 */
        }
    }
    printf("\n");

    return 0;
}
