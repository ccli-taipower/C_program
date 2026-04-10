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
 */
#include <stdio.h>
#include <stdlib.h>

/* ---- 資料結構定義 ---- */

struct listnode {
    int data;
    struct listnode *next;
};
typedef struct listnode ListNode;

struct queue {
    ListNode *front;   /* 出口端（dequeue 端） */
    ListNode *rear;    /* 入口端（enqueue 端） */
};
typedef struct queue Queue;

/* ---- 佇列操作函式 ---- */

/* 初始化空佇列 */
void init(Queue *s) {
    s->front = NULL;
    s->rear  = NULL;
}

/* 若佇列為空，回傳 1；否則回傳 0 */
int empty(Queue *s) {
    return s->front == NULL;
}

/* 將 data 加入佇列尾端 */
void enqueue(Queue *s, int data) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) return;
    node->data = data;
    node->next = NULL;
    if (s->rear == NULL) {
        /* 佇列原本為空，front 與 rear 均指向新節點 */
        s->front = s->rear = node;
    } else {
        s->rear->next = node;
        s->rear = node;
    }
}

/* 從佇列前端取出並回傳值；空佇列防禦性回傳 -1 */
int dequeue(Queue *s) {
    if (s->front == NULL) return -1;
    ListNode *victim = s->front;
    int value = victim->data;
    s->front = victim->next;
    if (s->front == NULL) s->rear = NULL;   /* 佇列變空，rear 也需歸零 */
    free(victim);
    return value;
}

/* ---- 主程式（示範用） ---- */

int main(void) {
    Queue queue;
    Queue *q = &queue;

    init(q);
    if (empty(q)) printf("initially queue is empty\n");

    enqueue(q, 2);
    enqueue(q, 3);
    printf("%d\n", dequeue(q));   /* 輸出 2 */
    enqueue(q, 4);
    printf("%d\n", dequeue(q));   /* 輸出 3 */
    printf("%d\n", dequeue(q));   /* 輸出 4 */
    enqueue(q, 5);
    enqueue(q, 6);
    printf("%d\n", dequeue(q));   /* 輸出 5 */
    printf("%d\n", dequeue(q));   /* 輸出 6 */
    return 0;
}
