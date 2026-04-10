/*
 * NTHU EE2310 - 題目 14824: Map Coloring
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 15 章（遞迴）
 *   如果不知道如何解題，請參考課本第 15 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14824/
 *
 * 【題目說明】
 * 給定 n 個國家（編號 1..n）、c 種顏色、p 對相鄰關係，
 * 判斷能否以 c 種顏色替所有國家上色，使相鄰的兩國顏色不同。
 *   - 若可行，輸出字典序最小的上色方案（n 個顏色編號以空格分隔）。
 *   - 若不可行，輸出 "no solution"。
 *
 * 範例：
 *   3 3 3，相鄰對 [(1,2),(2,3),(3,1)] → "1 2 3"
 *   4 2 3，相鄰對 [(1,2),(2,3),(3,4)]  → "1 2 1 2"
 *   4 3 6（完全圖）                     → "no solution"（需要 4 種顏色）
 *
 * 【解題策略】
 * 使用回溯法（backtracking）：
 * 1. 依照國家編號 1..n 的順序，逐一嘗試顏色 1..c（字典序最小）。
 * 2. 若目前顏色與已上色的相鄰國家不衝突，則繼續遞迴下一個國家。
 * 3. 若所有 n 個國家都已上色，輸出結果並結束。
 * 4. 若所有顏色都衝突，則回溯（backtrack）。
 */
#include <stdio.h>

#define MAXN 105   /* 國家數量上限 */
#define MAXC 105   /* 顏色數量上限 */

static int n, c, p;              /* 國家數、顏色數、相鄰對數 */
static int adj[MAXN][MAXN];      /* adj[i][j] = 1 表示 i 與 j 相鄰 */
static int color[MAXN];          /* color[i] = 國家 i 目前的顏色（0 表示未上色） */
static int found;                /* 是否已找到解 */

/* 檢查國家 node 以顏色 col 上色是否合法
 * （與所有已上色的相鄰國家顏色不衝突） */
static int is_valid(int node, int col) {
    int j;
    for (j = 1; j <= n; j++) {
        if (adj[node][j] && color[j] == col) {
            return 0;  /* 衝突：相鄰國家已使用此顏色 */
        }
    }
    return 1;  /* 合法 */
}

/* 回溯搜尋：對國家 node（1-indexed）嘗試上色 */
static void backtrack(int node) {
    int col;

    if (found) return;  /* 已找到解，不再繼續搜尋 */

    if (node > n) {
        /* 所有國家都已上色，輸出結果 */
        int i;
        for (i = 1; i <= n; i++) {
            if (i > 1) printf(" ");
            printf("%d", color[i]);
        }
        printf("\n");
        found = 1;
        return;
    }

    /* 依序嘗試顏色 1..c（保證字典序最小） */
    for (col = 1; col <= c; col++) {
        if (is_valid(node, col)) {
            color[node] = col;       /* 上色 */
            backtrack(node + 1);     /* 遞迴處理下一個國家 */
            if (found) return;       /* 找到解則立即返回 */
            color[node] = 0;         /* 回溯：取消上色 */
        }
    }
}

int main(void) {
    int i, a, b;

    /* 讀入國家數、顏色數、相鄰對數 */
    if (scanf("%d %d %d", &n, &c, &p) != 3) return 0;

    /* 讀入相鄰關係（無向邊） */
    for (i = 0; i < p; i++) {
        if (scanf("%d %d", &a, &b) != 2) return 0;
        adj[a][b] = 1;
        adj[b][a] = 1;
    }

    /* 初始化顏色陣列與搜尋旗標 */
    for (i = 0; i <= n; i++) color[i] = 0;
    found = 0;

    /* 從第 1 個國家開始回溯搜尋 */
    backtrack(1);

    /* 若未找到任何合法上色方案 */
    if (!found) {
        printf("no solution\n");
    }

    return 0;
}
