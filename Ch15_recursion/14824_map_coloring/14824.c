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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入 n（國家數）、c（顏色數）、p（相鄰對數），並建立無向鄰接矩陣 adj[][]。
 * 2. 呼叫 backtrack(1)，從第 1 個國家開始，依序嘗試顏色 1..c。
 * 3. 對每個候選顏色呼叫 is_valid()，檢查該顏色是否與所有已上色的相鄰國家衝突；
 *    若衝突則跳過，若合法則將 color[node] 設為此顏色並遞迴下一個國家。
 * 4. 當 node > n 時，表示所有國家已成功上色；依序輸出 color[1..n] 並設 found=1。
 * 5. 若遞迴返回後 found 仍為 0，則取消本國的顏色（color[node]=0）並嘗試下一種顏色。
 * 6. 若所有顏色都無法解決，函式返回；若最終 found==0，輸出 "no solution"。
 * 由於從顏色 1 開始嘗試，保證輸出的是字典序最小的合法方案。
 *
 * English:
 * 1. Read n (countries), c (colors), p (adjacency pairs) and build the undirected
 *    adjacency matrix adj[][].
 * 2. Call backtrack(1), starting from country 1 and trying colors 1..c in order.
 * 3. For each candidate color, call is_valid() to check it doesn't conflict with any
 *    already-colored neighbor; skip if conflicting, otherwise set color[node] and
 *    recurse to the next country.
 * 4. When node > n, all countries are colored successfully; print color[1..n] and
 *    set found=1.
 * 5. If the recursive call returns without finding a solution, reset color[node]=0
 *    (backtrack) and try the next color.
 * 6. If no color works at this node the function returns; if found==0 after the top
 *    call, print "no solution".
 * Trying colors from 1 upward guarantees the lexicographically smallest solution.
 */
#include <stdio.h>

#define MAXN 105   /* 國家數量上限 / maximum number of countries */
#define MAXC 105   /* 顏色數量上限 / maximum number of colors */

static int n, c, p;              /* 國家數、顏色數、相鄰對數 / number of countries, colors, adjacency pairs */
static int adj[MAXN][MAXN];      /* adj[i][j] = 1 表示 i 與 j 相鄰 / adj[i][j]=1 means i and j are adjacent */
static int color[MAXN];          /* color[i] = 國家 i 目前的顏色（0 表示未上色） / current color of country i (0 = uncolored) */
static int found;                /* 是否已找到解 / whether a solution has been found */

/* 檢查國家 node 以顏色 col 上色是否合法 / check whether coloring country node with col is valid
 * （與所有已上色的相鄰國家顏色不衝突） / (no conflict with any already-colored neighbor) */
static int is_valid(int node, int col) {
    int j;
    for (j = 1; j <= n; j++) {
        if (adj[node][j] && color[j] == col) {
            return 0;  /* 衝突：相鄰國家已使用此顏色 / conflict: neighbor already uses this color */
        }
    }
    return 1;  /* 合法 / valid */
}

/* 回溯搜尋：對國家 node（1-indexed）嘗試上色 / backtracking search: try coloring country node (1-indexed) */
static void backtrack(int node) {
    int col;

    if (found) return;  /* 已找到解，不再繼續搜尋 / solution found, stop searching */

    if (node > n) {
        /* 所有國家都已上色，輸出結果 / all countries colored, print result */
        int i;
        for (i = 1; i <= n; i++) {
            if (i > 1) printf(" ");
            printf("%d", color[i]);
        }
        printf("\n");
        found = 1;
        return;
    }

    /* 依序嘗試顏色 1..c（保證字典序最小） / try colors 1..c in order (ensures lexicographically smallest result) */
    for (col = 1; col <= c; col++) {
        if (is_valid(node, col)) {
            color[node] = col;       /* 上色 / assign color */
            backtrack(node + 1);     /* 遞迴處理下一個國家 / recurse to next country */
            if (found) return;       /* 找到解則立即返回 / return immediately if solution found */
            color[node] = 0;         /* 回溯：取消上色 / backtrack: unassign color */
        }
    }
}

int main(void) {
    int i, a, b;

    /* 讀入國家數、顏色數、相鄰對數 / read number of countries, colors, and adjacency pairs */
    if (scanf("%d %d %d", &n, &c, &p) != 3) return 0;

    /* 讀入相鄰關係（無向邊） / read adjacency relations (undirected edges) */
    for (i = 0; i < p; i++) {
        if (scanf("%d %d", &a, &b) != 2) return 0;
        adj[a][b] = 1;
        adj[b][a] = 1;
    }

    /* 初始化顏色陣列與搜尋旗標 / initialize color array and search flag */
    for (i = 0; i <= n; i++) color[i] = 0;
    found = 0;

    /* 從第 1 個國家開始回溯搜尋 / start backtracking from country 1 */
    backtrack(1);

    /* 若未找到任何合法上色方案 / if no valid coloring was found */
    if (!found) {
        printf("no solution\n");
    }

    return 0;
}
