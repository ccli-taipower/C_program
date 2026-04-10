/*
 * NTHU EE2310 - 題目 14849: Bookshelf Linked List（書架鏈結串列）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 17 章（資料結構）
 *   如果不知道如何解題，請參考課本第 17 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14849/
 *
 * 【題目說明】
 * 書架最多可放 m 本書，書號範圍為 1 到 n。
 * 依序讀取要閱讀的書號序列，模擬書架狀態：
 *   - 若書已在書架上，不做任何改變。
 *   - 若書不在書架上：
 *       - 若書架未滿，將書加入書架最右端。
 *       - 若書架已滿，移除書架最左端的書（LRU 驅逐），再加入最右端。
 * 輸出最終書架狀態（不足 m 格以 0 填補）。
 *
 * 【解題策略】
 * 以雙向鏈結串列實作佇列（FIFO + 成員查詢）：
 *   - 使用 prev[i] / next[i] 陣列模擬雙向鏈結，其中 0 為哨兵頭節點。
 *   - on_shelf[i]：記錄書號 i 是否在書架上。
 *   - 書架以 FIFO 順序維護：新書加到尾端，驅逐時從頭端移除。
 *
 * 範例：n=5, m=3, 閱讀序列 1 2 3 4 1 5
 *   最終書架：4 1 5
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀取 n（書號上限）和 m（書架容量），初始化雙向鏈結串列的哨兵頭（head_node = n+1）和哨兵尾（tail_node = n+2）。
 * 2. 初始化 on_shelf[] 全為 0，shelf_size = 0。
 * 3. 逐一讀取書號：若書已在書架上（on_shelf[book] == 1），跳過不處理。
 * 4. 若書不在書架且書架已滿（shelf_size == m），從鏈結串列頭端取出最舊的書並從 on_shelf 中移除。
 * 5. 將新書以 list_push_back() 插入鏈結串列尾端，並設 on_shelf[book] = 1，shelf_size++。
 * 6. 讀完所有書號後，從 head_node 向後遍歷鏈結串列收集書架順序，按序輸出，不足 m 格以 0 補齊。
 *
 * English:
 * 1. Read n (max book ID) and m (shelf capacity); initialize sentinel head (head_node = n+1) and tail (tail_node = n+2) of a doubly linked list.
 * 2. Initialize on_shelf[] all to 0 and shelf_size = 0.
 * 3. Process each book ID: if the book is already on the shelf (on_shelf[book] == 1), skip it.
 * 4. If the book is not on the shelf and the shelf is full (shelf_size == m), evict the oldest book from the list front and clear its on_shelf flag.
 * 5. Insert the new book at the list tail using list_push_back(), set on_shelf[book] = 1, and increment shelf_size.
 * 6. After all book IDs are processed, traverse the linked list from head to collect the shelf order, print them, and pad with 0s to reach m slots.
 */
#include <stdio.h>
#include <string.h>

#define MAXN 1025   /* 書號最大值 + 1 / max book ID + 1 */
#define MAXM 129    /* 書架最大容量 + 1 / max shelf capacity + 1 */
#define MAXSENTINEL (MAXN + 2)  /* 哨兵節點所需的額外空間 / extra space for sentinel nodes */

/* 佇列以雙向鏈結串列實作，節點 0 為哨兵頭節點 / queue implemented as doubly linked list; node 0 is sentinel head */
static int nxt[MAXSENTINEL];     /* nxt[i]：節點 i 的下一個節點 / nxt[i]: next node of node i */
static int prv[MAXSENTINEL];     /* prv[i]：節點 i 的前一個節點 / prv[i]: previous node of node i */
static int on_shelf[MAXN]; /* on_shelf[i]：書號 i 是否在書架上 / on_shelf[i]: whether book i is currently on the shelf */

/* 書架順序陣列（用於最終輸出） / shelf order array (for final output) */
static int shelf_order[MAXM];
static int shelf_size;    /* 書架目前的書本數量 / current number of books on the shelf */

/* 哨兵頭（head）與尾（tail）節點 / sentinel head and tail nodes */
static int head_node;     /* 哨兵：head_node.nxt 指向最舊的書 / sentinel: head_node.nxt points to the oldest book */
static int tail_node;     /* 哨兵：tail_node.prv 指向最新的書 / sentinel: tail_node.prv points to the newest book */

/* 初始化雙向鏈結串列（哨兵頭尾相連） / initialize doubly linked list (connect sentinel head and tail) */
static void list_init(int head, int tail) {
    nxt[head] = tail;
    prv[tail] = head;
    nxt[tail] = 0;
    prv[head] = 0;
}

/* 將節點 book 插入到 tail 之前（即佇列尾端） / insert node book before tail (i.e., at queue rear) */
static void list_push_back(int book, int tail) {
    int prev_node = prv[tail];
    nxt[prev_node] = book;
    prv[book] = prev_node;
    nxt[book] = tail;
    prv[tail] = book;
}

/* 移除節點 book（從鏈結串列中切除） / remove node book from the linked list */
static void list_remove(int book) {
    int p = prv[book];
    int n = nxt[book];
    nxt[p] = n;
    prv[n] = p;
}

/* 回傳佇列最舊的書（head.nxt），即最左端 / return the oldest book (head.nxt), i.e., leftmost slot */
static int list_front(int head) {
    return nxt[head];
}

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    /* 使用節點 n+1 作為哨兵頭，n+2 作為哨兵尾 / use node n+1 as sentinel head, n+2 as sentinel tail */
    head_node = n + 1;
    tail_node = n + 2;
    list_init(head_node, tail_node);
    memset(on_shelf, 0, sizeof(on_shelf));
    shelf_size = 0;

    int book;
    /* 逐一讀取書號，模擬書架狀態 / read book IDs one by one, simulating shelf state */
    while (scanf("%d", &book) == 1) {
        if (on_shelf[book]) {
            /* 書已在書架上，無需操作 / book already on shelf, do nothing */
            continue;
        }
        if (shelf_size == m) {
            /* 書架已滿，驅逐最舊的書（最左端） / shelf is full, evict the oldest book (leftmost) */
            int evict = list_front(head_node);
            list_remove(evict);
            on_shelf[evict] = 0;
            shelf_size--;
        }
        /* 將新書加入書架尾端 / add new book to the rear of the shelf */
        list_push_back(book, tail_node);
        on_shelf[book] = 1;
        shelf_size++;
    }

    /* 收集書架上的書（從最舊到最新） / collect books on the shelf (oldest to newest) */
    int cnt = 0;
    int cur = list_front(head_node);
    while (cur != tail_node) {
        shelf_order[cnt++] = cur;
        cur = nxt[cur];
    }

    /* 輸出書架狀態，不足 m 格以 0 補齊 / print shelf state, pad with 0s to reach m slots */
    for (int i = 0; i < m; ++i) {
        if (i < cnt) {
            printf("%d", shelf_order[i]);
        } else {
            printf("0");
        }
        if (i < m - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
