/*
 * NTHU EE2310 - 題目 14846: Event Triggering（事件觸發推導）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 17 章（資料結構）
 *   如果不知道如何解題，請參考課本第 17 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14846/
 *
 * 【題目說明】
 * 事件以大寫英文字母（A–Z，最多 26 個）表示。
 * 若事件 A 發生，可直接觸發其他事件；間接觸發具有傳遞性。
 * 給定 n 條觸發規則，每條格式為：
 *   "EVENT COUNT TARGET1 TARGET2 ... TARGETCOUNT"
 *   （例如 "A 3 B C D" 表示 A 觸發 B、C、D）
 * 給定 m 筆查詢，每筆格式為 "EVENT1 EVENT2"：
 *   判斷 EVENT1 是否能（直接或間接）觸發 EVENT2，輸出 "yes" 或 "no"。
 *
 * 【限制】
 * 最多 26 個事件（大寫英文字母），每個事件最多觸發 3 個其他事件，無環。
 *
 * 【解題策略】
 * 建立有向圖的鄰接串列 trigger[i]（i 為事件的字母索引）。
 * 對每筆查詢，從 EVENT1 出發進行 BFS，判斷能否到達 EVENT2。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 以二維陣列 trigger[26][3] 建立有向圖的鄰接串列，索引 0–25 對應事件 A–Z。
 * 2. 讀取 n 條觸發規則：對每條規則，解析來源事件與其觸發的目標事件，填入 trigger 陣列。
 * 3. 讀取 m 筆查詢，每筆包含兩個事件字母 ev1 和 ev2。
 * 4. 對每筆查詢，呼叫 can_reach(ev1-'A', ev2-'A') 執行 BFS。
 * 5. BFS 從 src 出發，維護 visited[] 避免重複拜訪，逐層擴展可達事件。
 * 6. 若 BFS 過程中節點 == dst，回傳 1（輸出 "yes"）；BFS 結束仍未到達則回傳 0（輸出 "no"）。
 *
 * English:
 * 1. Build a directed-graph adjacency list using a 2D array trigger[26][3], where indices 0–25 correspond to events A–Z.
 * 2. Read n trigger rules: for each rule, parse the source event and its target events, then populate the trigger array.
 * 3. Read m queries, each containing two event letters ev1 and ev2.
 * 4. For each query, call can_reach(ev1-'A', ev2-'A') to run BFS.
 * 5. BFS starts from src, uses a visited[] array to avoid revisiting, and expands reachable events level by level.
 * 6. If any BFS node == dst, return 1 (output "yes"); if BFS ends without reaching dst, return 0 (output "no").
 */
#include <stdio.h>
#include <string.h>

#define MAXEV 26       /* 最多 26 個事件（A–Z） / at most 26 events (A–Z) */
#define MAXEDGE 3      /* 每個事件最多觸發 3 個其他事件 / each event triggers at most 3 others */

/* trigger[i][j]：事件 i 觸發的第 j 個事件（-1 表示無效） / trigger[i][j]: j-th event triggered by event i (-1 = invalid) */
static int trigger[MAXEV][MAXEDGE];
/* trigger_cnt[i]：事件 i 可觸發的事件數量 / trigger_cnt[i]: number of events triggered by event i */
static int trigger_cnt[MAXEV];

/* BFS 佇列 / BFS queue */
static int bfs_queue[MAXEV];

/*
 * 判斷從事件 src 出發，是否能（直接或間接）觸發事件 dst。
 * 使用 BFS 走訪可達節點。
 */
static int can_reach(int src, int dst) {
    int visited[MAXEV] = {0};
    int head = 0, tail = 0;

    /* 將起點加入佇列 / enqueue the source node */
    bfs_queue[tail++] = src;
    visited[src] = 1;

    while (head < tail) {
        int cur = bfs_queue[head++];
        if (cur == dst) return 1;   /* 找到目標 / destination reached */

        /* 將 cur 可觸發的事件加入佇列（若尚未拜訪） / enqueue events triggered by cur if not yet visited */
        for (int j = 0; j < trigger_cnt[cur]; ++j) {
            int next = trigger[cur][j];
            if (!visited[next]) {
                visited[next] = 1;
                bfs_queue[tail++] = next;
            }
        }
    }
    return 0;   /* 無法到達 dst / dst is not reachable */
}

int main(void) {
    int n;
    char ev;
    char target;

    /* 初始化觸發表 / initialize the trigger table */
    memset(trigger_cnt, 0, sizeof(trigger_cnt));

    /* 讀取觸發規則 / read trigger rules */
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; ++i) {
        int cnt;
        /* 讀取來源事件與觸發數量 / read source event and trigger count */
        if (scanf(" %c %d", &ev, &cnt) != 2) return 0;
        int src = ev - 'A';
        /* 讀取各目標事件 / read each target event */
        for (int j = 0; j < cnt; ++j) {
            if (scanf(" %c", &target) != 1) return 0;
            trigger[src][trigger_cnt[src]++] = target - 'A';
        }
    }

    /* 讀取查詢 / read queries */
    int m;
    if (scanf("%d", &m) != 1) return 0;
    for (int q = 0; q < m; ++q) {
        char ev1, ev2;
        if (scanf(" %c %c", &ev1, &ev2) != 2) return 0;
        /* 判斷 ev1 是否能觸發 ev2 / check whether ev1 can trigger ev2 */
        if (can_reach(ev1 - 'A', ev2 - 'A')) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }
    return 0;
}
