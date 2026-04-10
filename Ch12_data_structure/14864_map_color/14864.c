/*
 * NTHU EE2310 - 題目 14864: Map Color（地圖著色問題）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 12 章（資料結構）
 *   如果不知道如何解題，請參考課本第 12 章的說明。
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
 */
#include <stdio.h>
#include <string.h>

#define MAXN 128

static int n, c;                  /* 國家數、顏色數 */
static int adj[MAXN][MAXN];       /* 相鄰關係矩陣 */
static int color[MAXN];           /* 各國家的著色結果 */
static int solved;                /* 是否已找到解 */

/* 回溯函式：對第 v 個國家著色 */
static void backtrack(int v) {
    if (solved) return;
    if (v > n) {
        /* 所有國家均已著色，輸出結果 */
        for (int i = 1; i <= n; ++i) {
            printf("%d%s", color[i], i == n ? "\n" : " ");
        }
        solved = 1;
        return;
    }
    /* 依序嘗試每種顏色 */
    for (int k = 1; k <= c && !solved; ++k) {
        int ok = 1;
        /* 檢查與已著色的相鄰國家是否衝突 */
        for (int u = 1; u < v; ++u) {
            if (adj[v][u] && color[u] == k) { ok = 0; break; }
        }
        if (ok) {
            color[v] = k;
            backtrack(v + 1);
            color[v] = 0;   /* 回溯，取消著色 */
        }
    }
}

int main(void) {
    int p;
    if (scanf("%d %d %d", &n, &c, &p) != 3) return 0;

    /* 讀取相鄰關係 */
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
