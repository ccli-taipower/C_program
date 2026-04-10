/*
 * NTHU EE2310 - 題目 14830: Mahjong Winning Tiles
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 15 章（遞迴）
 *   如果不知道如何解題，請參考課本第 15 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14830/
 *
 * 【題目說明】
 * 給定 13 張麻將牌（數字 1~9），找出哪些牌（1~9）可作為第 14 張聽牌。
 * 胡牌條件：1 對將牌 + 4 組順子或刻子。
 *   - 刻子：3 張相同的牌（例如 222）
 *   - 順子：3 張連續的牌（例如 123）
 *   - 同一張牌最多 4 張（不可超過）
 * 若無任何聽牌，輸出 "0"；否則依序輸出每個聽牌（每行一個）。
 *
 * 範例：輸入 [1,1,1,2,2,2,3,3,3,4,4,4,4]，聽牌為 1, 2, 3, 5
 *
 * 【解題策略】
 * 1. 統計每種牌的數量（頻率陣列 cnt[1..9]）。
 * 2. 對每個候選聽牌 c（1~9）：
 *    a. 若 cnt[c] >= 4，此牌無法摸入，跳過。
 *    b. 暫時加入：cnt[c]++。
 *    c. 對每個可能的將牌 p（1~9）：
 *       - 若 cnt[p] >= 2，暫時移除將牌：cnt[p] -= 2，
 *         再遞迴檢查剩餘 12 張牌是否能組成 4 組。
 *    d. 若成功，記錄 c 為聽牌。
 *    e. 還原：cnt[c]--。
 *
 * 【遞迴判斷是否能組成 sets 組】
 * can_form(cnt[], sets)：
 *   - 若 sets == 0：成功（所有牌都已組合完畢）
 *   - 找最小的 i（cnt[i] > 0）
 *   - 嘗試刻子：若 cnt[i] >= 3，遞迴 can_form(cnt[i]-=3, sets-1)
 *   - 嘗試順子：若 cnt[i]>0 && cnt[i+1]>0 && cnt[i+2]>0，
 *               遞迴 can_form(cnt[i]-=1,cnt[i+1]-=1,cnt[i+2]-=1, sets-1)
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入 13 張牌，統計每種牌（1~9）的出現次數至 cnt[]。
 * 2. 對每個候選聽牌 c（1~9）：若 cnt[c] >= 4 則跳過（無法再摸入）；
 *    否則暫時 cnt[c]++，模擬摸入第 14 張牌。
 * 3. 呼叫 is_winning(cnt)：嘗試每個可能的將牌 p（1~9），若 cnt[p] >= 2，
 *    複製 cnt 陣列後移除將牌（tmp[p] -= 2），再呼叫 can_form(tmp, 4)。
 * 4. can_form 遞迴：每次找最小有牌的位置 i，優先嘗試組成刻子（cnt[i]-=3），
 *    若失敗再嘗試組成順子（cnt[i]--, cnt[i+1]--, cnt[i+2]--），失敗則回溯。
 * 5. 若 sets == 0 代表 4 組已全部組合完成，回傳成功。
 * 6. 若 is_winning 回傳 1，輸出 c 為聽牌，並還原 cnt[c]--。
 * 7. 若完全沒有聽牌，輸出 "0"。
 *
 * English:
 * 1. Read 13 tiles and count occurrences of each tile (1~9) into cnt[].
 * 2. For each candidate winning tile c (1~9): skip if cnt[c] >= 4 (cannot draw more);
 *    otherwise temporarily increment cnt[c]++ to simulate drawing the 14th tile.
 * 3. Call is_winning(cnt): try each possible pair tile p (1~9); if cnt[p] >= 2, copy
 *    cnt into tmp, remove the pair (tmp[p] -= 2), then call can_form(tmp, 4).
 * 4. can_form recursion: find the smallest index i with cnt[i] > 0; first try forming a
 *    triplet (cnt[i] -= 3), then if that fails try a sequence (cnt[i]--, cnt[i+1]--,
 *    cnt[i+2]--), backtracking on failure.
 * 5. When sets == 0, all 4 melds are formed successfully; return 1.
 * 6. If is_winning returns 1, print c as a winning tile and restore cnt[c]--.
 * 7. If no winning tile is found at all, print "0".
 */
#include <stdio.h>
#include <string.h>

#define TILES 10  /* 牌的種類：1~9，索引 0 不使用 / tile types 1~9; index 0 unused */

/* 遞迴判斷 cnt[1..9] 中的牌能否組成 sets 組（刻子或順子） / recursively check if tiles in cnt[1..9] can form 'sets' melds (triplets or sequences) */
static int can_form(int cnt[], int sets) {
    int i;

    /* 基底情況：不需要再組合任何組 / base case: no more melds needed */
    if (sets == 0) return 1;

    /* 找最小的有牌位置 / find the smallest tile index with count > 0 */
    for (i = 1; i < TILES; i++) {
        if (cnt[i] > 0) break;
    }
    /* 若沒有任何牌卻 sets > 0，失敗 / no tiles left but sets > 0: failure */
    if (i >= TILES) return 0;

    /* 嘗試組成刻子（3 張相同） / try forming a triplet (3 identical tiles) */
    if (cnt[i] >= 3) {
        cnt[i] -= 3;
        if (can_form(cnt, sets - 1)) {
            cnt[i] += 3;
            return 1;
        }
        cnt[i] += 3;
    }

    /* 嘗試組成順子（i, i+1, i+2） / try forming a sequence (tiles i, i+1, i+2) */
    if (i + 2 < TILES && cnt[i] >= 1 && cnt[i + 1] >= 1 && cnt[i + 2] >= 1) {
        cnt[i]--;
        cnt[i + 1]--;
        cnt[i + 2]--;
        if (can_form(cnt, sets - 1)) {
            cnt[i]++;
            cnt[i + 1]++;
            cnt[i + 2]++;
            return 1;
        }
        cnt[i]++;
        cnt[i + 1]++;
        cnt[i + 2]++;
    }

    return 0;  /* 無法組合成功 / cannot form the required melds */
}

/* 判斷加入候選牌後是否能胡牌 / check if adding the candidate tile results in a winning hand */
static int is_winning(int cnt[]) {
    int p, tmp[TILES];
    int j;

    /* 嘗試每個可能的將牌 p（1~9） / try every possible pair tile p (1~9) */
    for (p = 1; p < TILES; p++) {
        if (cnt[p] >= 2) {
            /* 複製頻率陣列以避免破壞原陣列 / copy frequency array to avoid modifying the original */
            for (j = 0; j < TILES; j++) tmp[j] = cnt[j];
            tmp[p] -= 2;  /* 移除將牌 / remove the pair */

            /* 遞迴判斷剩餘 12 張牌能否組成 4 組 / check if remaining 12 tiles can form 4 melds */
            if (can_form(tmp, 4)) return 1;
        }
    }
    return 0;
}

int main(void) {
    int cnt[TILES];  /* cnt[i] = 牌 i 的張數（1~9） / count of each tile type (1~9) */
    int tile;        /* 輸入的牌 / tile read from input */
    int i;

    /* 初始化頻率陣列 / initialize frequency array */
    memset(cnt, 0, sizeof(cnt));

    /* 讀入 13 張牌並統計頻率 / read 13 tiles and count their frequencies */
    for (i = 0; i < 13; i++) {
        if (scanf("%d", &tile) != 1) return 0;
        cnt[tile]++;
    }

    int found = 0;  /* 是否找到任何聽牌 / whether any winning tile was found */

    /* 對每個候選聽牌 c（1~9）進行測試 / test each candidate winning tile c (1~9) */
    for (i = 1; i < TILES; i++) {
        /* 同一張牌最多 4 張，若已有 4 張則無法再摸入 / at most 4 of the same tile; skip if already at 4 */
        if (cnt[i] >= 4) continue;

        /* 暫時加入候選牌 / temporarily add the candidate tile */
        cnt[i]++;

        /* 判斷是否能胡牌 / check if this results in a winning hand */
        if (is_winning(cnt)) {
            printf("%d\n", i);
            found = 1;
        }

        /* 還原頻率陣列 / restore the frequency array */
        cnt[i]--;
    }

    /* 若無任何聽牌，輸出 "0" / if no winning tile found, print "0" */
    if (!found) {
        printf("0\n");
    }

    return 0;
}
