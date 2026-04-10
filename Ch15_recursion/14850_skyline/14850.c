/*
 * NTHU EE2310 - 題目 14850: The Skyline Problem
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 15 章（遞迴）
 *   如果不知道如何解題，請參考課本第 15 章的說明。
 *   （本題使用掃描線演算法，歸類於第 11 章）
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14850/
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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入 n 棟建築物，每棟產生兩個事件邊：起始邊（type=1, x=L, height=H）和
 *    結束邊（type=0, x=R, height=H），存入 edges[] 陣列。
 * 2. 呼叫 getSkyline()，先以 qsort 依 x 座標排序所有事件邊。
 * 3. 從左到右掃描事件邊；對相同 x 的所有事件邊批次處理：
 *    起始邊呼叫 add_height() 將高度加入活躍集合，
 *    結束邊呼叫 remove_height() 從活躍集合移除對應高度。
 * 4. 處理完同一 x 的所有事件後，呼叫 max_height() 線性掃描活躍集合取得目前最大高度。
 * 5. 若目前最大高度 cur 與前一個輸出高度 prev 不同，輸出關鍵點 (cur_x, cur) 並更新 prev。
 * 6. 繼續掃描下一個 x，直到所有事件邊都處理完畢。
 *
 * English:
 * 1. Read n buildings; for each building produce two events: a start edge
 *    (type=1, x=L, height=H) and an end edge (type=0, x=R, height=H), stored in edges[].
 * 2. Call getSkyline(), which first sorts all edges by x using qsort.
 * 3. Sweep left to right; batch-process all edges sharing the same x:
 *    start edges call add_height() to insert the height into the active set,
 *    end edges call remove_height() to delete the matching height.
 * 4. After processing all events at the current x, call max_height() to linearly scan
 *    the active set for the current maximum height.
 * 5. If the current maximum cur differs from the previous output height prev, emit the
 *    critical point (cur_x, cur) and update prev.
 * 6. Continue scanning the next x until all events are consumed.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXBLDG 10005              /* 建築物數量上限 / maximum number of buildings */
#define MAXEDGE (2 * MAXBLDG)      /* 事件邊數量上限（每棟建築物產生 2 個事件邊） / max edges (each building generates 2 events) */

/* 事件邊資料結構 / event edge data structure */
typedef struct {
    int x;       /* 事件邊的 x 座標 / x-coordinate of the event edge */
    int height;  /* 對應的建築物高度 / corresponding building height */
    int type;    /* 1 = 起始邊（加入高度），0 = 結束邊（移除高度） / 1=start edge (add height), 0=end edge (remove height) */
} Edge;

/* 事件邊比較函式（依 x 座標排序，供 qsort 使用） / edge comparator (sort by x coordinate, for qsort) */
static int compareEdges(const void *pa, const void *pb) {
    const Edge *a = (const Edge *)pa;
    const Edge *b = (const Edge *)pb;
    return a->x - b->x;
}

/* ---- 活躍高度多重集合（unsorted array 實作）---- / active height multiset (unsorted array implementation) */
static int active[MAXEDGE];  /* 目前活躍中的建築物高度 / currently active building heights */
static int active_n;         /* 活躍高度的數量 / number of active heights */

/* 將高度 h 加入活躍集合 / add height h to the active set */
static void add_height(int h) {
    active[active_n++] = h;
}

/* 從活躍集合中移除一個高度 h / remove one instance of height h from the active set */
static void remove_height(int h) {
    int i;
    for (i = 0; i < active_n; i++) {
        if (active[i] == h) {
            /* 以最後一個元素填補空缺，縮小陣列大小 / fill the gap with the last element and shrink the array */
            active[i] = active[--active_n];
            return;
        }
    }
}

/* 查詢活躍集合中的最大高度（0 表示無活躍建築物）/ query maximum height in active set (0 if no active buildings) */
static int max_height(void) {
    int m = 0;
    int i;
    for (i = 0; i < active_n; i++) {
        if (active[i] > m) m = active[i];
    }
    return m;
}
/* ------------------------------------------------ */

/* 掃描線主函式：處理所有事件邊並輸出輪廓線關鍵點 / sweep-line main function: process all events and output skyline critical points */
static void getSkyline(Edge *edges, int e_count) {
    int i;
    int prev = 0;  /* 前一個輸出的高度，初始為地面高度 0 / last printed height; initialized to ground level 0 */

    /* 依 x 座標排序所有事件邊 */
    qsort(edges, (size_t)e_count, sizeof(Edge), compareEdges);

    i = 0;
    while (i < e_count) {
        int cur_x = edges[i].x;

        /* 批次處理所有位於 cur_x 的事件邊 / batch-process all events at the current x */
        while (i < e_count && edges[i].x == cur_x) {
            if (edges[i].type == 1) {
                add_height(edges[i].height);     /* 起始邊：加入高度 / start edge: add height */
            } else {
                remove_height(edges[i].height);  /* 結束邊：移除高度 / end edge: remove height */
            }
            i++;
        }

        /* 計算目前最大高度 / compute current maximum height */
        int cur = max_height();

        /* 若高度發生變化，輸出關鍵點 / if height changed, output a critical point */
        if (cur != prev) {
            printf("%d %d\n", cur_x, cur);
            prev = cur;
        }
    }
}

int main(void) {
    int n;  /* 建築物數量 / number of buildings */
    int i;

    if (scanf("%d", &n) != 1) return 0;

    static Edge edges[MAXEDGE];  /* 所有事件邊 / all event edges */
    int e_count = 0;             /* 事件邊總數 / total number of event edges */

    /* 讀入每棟建築物並產生對應的兩個事件邊 / read each building and produce its two event edges */
    for (i = 0; i < n; i++) {
        int L, R, H;  /* 建築物的左邊界、右邊界、高度 / building left boundary, right boundary, height */
        if (scanf("%d %d %d", &L, &R, &H) != 3) return 0;

        /* 起始邊：在 x = L 加入高度 H / start edge: add height H at x = L */
        edges[e_count].x      = L;
        edges[e_count].height = H;
        edges[e_count].type   = 1;
        e_count++;

        /* 結束邊：在 x = R 移除高度 H / end edge: remove height H at x = R */
        edges[e_count].x      = R;
        edges[e_count].height = H;
        edges[e_count].type   = 0;
        e_count++;
    }

    /* 執行掃描線演算法並輸出輪廓線關鍵點 / run the sweep-line algorithm and print skyline critical points */
    active_n = 0;
    getSkyline(edges, e_count);

    return 0;
}
