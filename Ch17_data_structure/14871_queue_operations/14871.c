/*
 * NTHU EE2310 - 題目 14871: Queue Operations（佇列操作）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 17 章（資料結構）
 *   如果不知道如何解題，請參考課本第 17 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14871/
 *
 * 【題目說明】
 * 實作以單向鏈結串列（Singly Linked List）為底層的 FIFO 佇列，
 * 並示範基本操作：初始化、判斷空佇列、enqueue（加入尾端）、
 * dequeue（從前端取出）。
 *
 * 【資料結構】
 * 每個節點（ListNode）儲存一個整數。
 * Queue 結構包含 front（出口端）和 rear（入口端）兩個指標。
 *   - enqueue：新節點接到 rear 後，rear 指向新節點。
 *   - dequeue：取出 front 節點後，front 向後移動。
 *   - 對空佇列呼叫 dequeue 防禦性回傳 -1。
 *
 * 【合併說明】
 * 本檔案將原本的 queue.h、queue.c、queue-main.c 合併為單一檔案。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 定義資料結構：ListNode 儲存整數資料與指向下一節點的指標；Queue 包含 front（出口）和 rear（入口）兩個指標。
 * 2. init()：將 front 和 rear 均設為 NULL，代表空佇列。
 * 3. enqueue(q, data)：動態配置新節點，若佇列為空則 front 和 rear 同時指向新節點；否則接在 rear 後方並更新 rear。
 * 4. dequeue(q)：取出 front 節點的值，front 向後移動；若 front 變為 NULL，也將 rear 歸零，保持一致性；最後釋放取出節點的記憶體。
 * 5. empty(q)：檢查 front == NULL，是則佇列為空。
 * 6. 主程式示範標準 FIFO 行為：依序 enqueue 2、3、4、5、6，穿插 dequeue 操作，驗證輸出順序正確。
 *
 * English:
 * 1. Define data structures: ListNode holds integer data and a next pointer; Queue holds front (dequeue end) and rear (enqueue end) pointers.
 * 2. init(): set both front and rear to NULL, representing an empty queue.
 * 3. enqueue(q, data): allocate a new node; if queue is empty, both front and rear point to the new node; otherwise append after rear and update rear.
 * 4. dequeue(q): save the front node's value, advance front; if front becomes NULL, also reset rear to NULL for consistency; free the removed node.
 * 5. empty(q): return true if front == NULL.
 * 6. The main function demonstrates standard FIFO behavior by enqueuing 2, 3, 4, 5, 6 with interleaved dequeues, verifying correct output order.
 */
#include <stdio.h>
#include <stdlib.h>

/* ---- 資料結構定義 / data structure definitions ---- */

struct listnode {
    int data;
    struct listnode *next;
};
typedef struct listnode ListNode;

struct queue {
    ListNode *front;   /* 出口端（dequeue 端） / front end (dequeue side) */
    ListNode *rear;    /* 入口端（enqueue 端） / rear end (enqueue side) */
};
typedef struct queue Queue;

/* ---- 佇列操作函式 / queue operation functions ---- */

/* 初始化空佇列 / initialize an empty queue */
void init(Queue *s) {
    s->front = NULL;
    s->rear  = NULL;
}

/* 若佇列為空，回傳 1；否則回傳 0 / return 1 if queue is empty, 0 otherwise */
int empty(Queue *s) {
    return s->front == NULL;
}

/* 將 data 加入佇列尾端 / enqueue data at the rear of the queue */
void enqueue(Queue *s, int data) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) return;
    node->data = data;
    node->next = NULL;
    if (s->rear == NULL) {
        /* 佇列原本為空，front 與 rear 均指向新節點 / queue was empty; both front and rear point to the new node */
        s->front = s->rear = node;
    } else {
        s->rear->next = node;
        s->rear = node;
    }
}

/* 從佇列前端取出並回傳值；空佇列防禦性回傳 -1 / dequeue from front and return value; defensively return -1 for empty queue */
int dequeue(Queue *s) {
    if (s->front == NULL) return -1;
    ListNode *victim = s->front;
    int value = victim->data;
    s->front = victim->next;
    if (s->front == NULL) s->rear = NULL;   /* 佇列變空，rear 也需歸零 / queue is now empty; reset rear to NULL as well */
    free(victim);
    return value;
}

/* ---- 主程式（示範用） / main program (demonstration) ---- */

int main(void) {
    Queue queue;
    Queue *q = &queue;

    init(q);
    if (empty(q)) printf("initially queue is empty\n");

    enqueue(q, 2);
    enqueue(q, 3);
    printf("%d\n", dequeue(q));   /* 輸出 2 / outputs 2 */
    enqueue(q, 4);
    printf("%d\n", dequeue(q));   /* 輸出 3 / outputs 3 */
    printf("%d\n", dequeue(q));   /* 輸出 4 / outputs 4 */
    enqueue(q, 5);
    enqueue(q, 6);
    printf("%d\n", dequeue(q));   /* 輸出 5 / outputs 5 */
    printf("%d\n", dequeue(q));   /* 輸出 6 / outputs 6 */
    return 0;
}
