/*
 * NTHU EE2310 - 題目 14850: The Skyline Problem
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 11 章（遞迴）
 *   如果不知道如何解題，請參考課本第 11 章的說明。
 *   （本題使用掃描線演算法，歸類於第 11 章）
 *
 * 【題目說明】
 * 給定 n 棟矩形建築物 [L, R, H]（位於地面上），
 * 輸出外輪廓線（skyline）的關鍵點。
 * 關鍵點 [x, y] 表示輪廓線高度在 x 位置發生變化。
 * 不得輸出多餘的共線點（即高度未改變時不輸出）。
 *
 * 【掃描線演算法（Sweep-Line）】
 * 1. 每棟建築物產生兩個事件邊：
 *    - 起始邊（x = L, height = H）：加入高度
 *    - 結束邊（x = R, height = H）：移除高度
 * 2. 將所有事件邊依 x 座標排序。
 * 3. 從左到右掃描：
 *    - 對相同 x 的所有事件邊，先全部處理（加入或移除高度）。
 *    - 計算目前最大高度。
 *    - 若最大高度與上一個不同，輸出關鍵點 (x, 目前最大高度)。
 *
 * 時間複雜度：O(n^2)，在本題限制下完全可行。
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXBLDG 10005              /* 建築物數量上限 */
#define MAXEDGE (2 * MAXBLDG)      /* 事件邊數量上限（每棟建築物產生 2 個事件邊） */

/* 事件邊資料結構 */
typedef struct {
    int x;       /* 事件邊的 x 座標 */
    int height;  /* 對應的建築物高度 */
    int type;    /* 1 = 起始邊（加入高度），0 = 結束邊（移除高度） */
} Edge;

/* 事件邊比較函式（依 x 座標排序，供 qsort 使用） */
static int compareEdges(const void *pa, const void *pb) {
    const Edge *a = (const Edge *)pa;
    const Edge *b = (const Edge *)pb;
    return a->x - b->x;
}

/* ---- 活躍高度多重集合（unsorted array 實作）---- */
static int active[MAXEDGE];  /* 目前活躍中的建築物高度 */
static int active_n;         /* 活躍高度的數量 */

/* 將高度 h 加入活躍集合 */
static void add_height(int h) {
    active[active_n++] = h;
}

/* 從活躍集合中移除一個高度 h */
static void remove_height(int h) {
    int i;
    for (i = 0; i < active_n; i++) {
        if (active[i] == h) {
            /* 以最後一個元素填補空缺，縮小陣列大小 */
            active[i] = active[--active_n];
            return;
        }
    }
}

/* 查詢活躍集合中的最大高度（0 表示無活躍建築物）*/
static int max_height(void) {
    int m = 0;
    int i;
    for (i = 0; i < active_n; i++) {
        if (active[i] > m) m = active[i];
    }
    return m;
}
/* ------------------------------------------------ */

/* 掃描線主函式：處理所有事件邊並輸出輪廓線關鍵點 */
static void getSkyline(Edge *edges, int e_count) {
    int i;
    int prev = 0;  /* 前一個輸出的高度，初始為地面高度 0 */

    /* 依 x 座標排序所有事件邊 */
    qsort(edges, (size_t)e_count, sizeof(Edge), compareEdges);

    i = 0;
    while (i < e_count) {
        int cur_x = edges[i].x;

        /* 批次處理所有位於 cur_x 的事件邊 */
        while (i < e_count && edges[i].x == cur_x) {
            if (edges[i].type == 1) {
                add_height(edges[i].height);     /* 起始邊：加入高度 */
            } else {
                remove_height(edges[i].height);  /* 結束邊：移除高度 */
            }
            i++;
        }

        /* 計算目前最大高度 */
        int cur = max_height();

        /* 若高度發生變化，輸出關鍵點 */
        if (cur != prev) {
            printf("%d %d\n", cur_x, cur);
            prev = cur;
        }
    }
}

int main(void) {
    int n;  /* 建築物數量 */
    int i;

    if (scanf("%d", &n) != 1) return 0;

    static Edge edges[MAXEDGE];  /* 所有事件邊 */
    int e_count = 0;             /* 事件邊總數 */

    /* 讀入每棟建築物並產生對應的兩個事件邊 */
    for (i = 0; i < n; i++) {
        int L, R, H;  /* 建築物的左邊界、右邊界、高度 */
        if (scanf("%d %d %d", &L, &R, &H) != 3) return 0;

        /* 起始邊：在 x = L 加入高度 H */
        edges[e_count].x      = L;
        edges[e_count].height = H;
        edges[e_count].type   = 1;
        e_count++;

        /* 結束邊：在 x = R 移除高度 H */
        edges[e_count].x      = R;
        edges[e_count].height = H;
        edges[e_count].type   = 0;
        e_count++;
    }

    /* 執行掃描線演算法並輸出輪廓線關鍵點 */
    active_n = 0;
    getSkyline(edges, e_count);

    return 0;
}
