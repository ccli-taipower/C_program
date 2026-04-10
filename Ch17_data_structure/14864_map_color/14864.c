/*
 * NTHU EE2310 - 題目 14864: Map Color（地圖著色問題）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 17 章（資料結構）
 *   如果不知道如何解題，請參考課本第 17 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14864/
 *
 * 【題目說明】
 * 給定 n 個國家、c 種顏色，以及 p 個相鄰關係，
 * 用 c 種顏色為地圖上色，使相鄰國家顏色不同。
 * 輸出字典序最小的合法著色方案；若無解，輸出 "no solution"。
 *
 * 【解題策略】
 * 採用回溯法（Backtracking）：
 *   - 依序為第 1 到 n 個國家著色。
 *   - 對每個國家，以遞增順序嘗試顏色 1 到 c。
 *   - 若某顏色與已著色的相鄰國家不衝突，則選用。
 *   - 由於顏色以遞增順序嘗試，找到的第一個解即為字典序最小的解。
 *
 * 相鄰關係以二維陣列 adj[i][j] 記錄（1 表示相鄰）。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀取 n（國家數）、c（顏色數）、p（相鄰對數），並讀取 p 條相鄰關係填入對稱矩陣 adj[][]。
 * 2. 初始化 color[] 全為 0，solved = 0，呼叫 backtrack(1) 從第一個國家開始著色。
 * 3. backtrack(v)：若 v > n，表示所有國家均已著色，輸出 color[1..n] 並設 solved = 1。
 * 4. 否則對顏色 1 到 c 依序嘗試：遍歷已著色的國家 u（1 到 v-1），若 adj[v][u] 且 color[u] == k，則該顏色衝突，跳過。
 * 5. 無衝突時將 color[v] = k 並遞迴 backtrack(v+1)；遞迴返回後重置 color[v] = 0（回溯）。
 * 6. 若 backtrack(1) 返回後 solved 仍為 0，輸出 "no solution"。
 *
 * English:
 * 1. Read n (countries), c (colors), p (adjacency pairs), and fill symmetric matrix adj[][] with the p pairs.
 * 2. Initialize color[] to all zeros and solved = 0, then call backtrack(1) to start coloring from country 1.
 * 3. backtrack(v): if v > n, all countries are colored; print color[1..n] and set solved = 1.
 * 4. Otherwise, try colors 1 to c in order: for each already-colored country u (1 to v-1), if adj[v][u] && color[u] == k, the color conflicts — skip it.
 * 5. If no conflict, set color[v] = k and recurse with backtrack(v+1); after returning, reset color[v] = 0 (backtrack).
 * 6. If backtrack(1) finishes and solved is still 0, print "no solution".
 */
#include <stdio.h>
#include <string.h>

#define MAXN 128

static int n, c;                  /* 國家數、顏色數 / number of countries, number of colors */
static int adj[MAXN][MAXN];       /* 相鄰關係矩陣 / adjacency matrix */
static int color[MAXN];           /* 各國家的著色結果 / coloring result for each country */
static int solved;                /* 是否已找到解 / whether a solution has been found */

/* 回溯函式：對第 v 個國家著色 / backtracking function: assign color to country v */
static void backtrack(int v) {
    if (solved) return;
    if (v > n) {
        /* 所有國家均已著色，輸出結果 / all countries are colored, print the result */
        for (int i = 1; i <= n; ++i) {
            printf("%d%s", color[i], i == n ? "\n" : " ");
        }
        solved = 1;
        return;
    }
    /* 依序嘗試每種顏色 / try each color in order */
    for (int k = 1; k <= c && !solved; ++k) {
        int ok = 1;
        /* 檢查與已著色的相鄰國家是否衝突 / check for conflict with already-colored adjacent countries */
        for (int u = 1; u < v; ++u) {
            if (adj[v][u] && color[u] == k) { ok = 0; break; }
        }
        if (ok) {
            color[v] = k;
            backtrack(v + 1);
            color[v] = 0;   /* 回溯，取消著色 / backtrack, undo coloring */
        }
    }
}

int main(void) {
    int p;
    if (scanf("%d %d %d", &n, &c, &p) != 3) return 0;

    /* 讀取相鄰關係 / read adjacency pairs */
    for (int e = 0; e < p; ++e) {
        int i, j;
        if (scanf("%d %d", &i, &j) != 2) return 0;
        adj[i][j] = adj[j][i] = 1;
    }

    memset(color, 0, sizeof(color));
    solved = 0;
    backtrack(1);

    if (!solved) {
        printf("no solution\n");
    }
    return 0;
}
