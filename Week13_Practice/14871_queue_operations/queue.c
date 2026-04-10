/*
 * NTHU ACM 14871 - Queue Operations (implementation)
 *
 * Linked-list FIFO queue:
 *   - enqueue appends to the rear.
 *   - dequeue removes from the front.
 *   - empty() returns 1 iff the queue has no nodes.
 *
 * dequeue() on an empty queue is undefined (returns -1 defensively).
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void init(Queue *s) {
    s->front = NULL;
    s->rear  = NULL;
}

int empty(Queue *s) {
    return s->front == NULL;
}

void enqueue(Queue *s, int data) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) return;
    node->data = data;
    node->next = NULL;
    if (s->rear == NULL) {
        s->front = s->rear = node;
    } else {
        s->rear->next = node;
        s->rear = node;
    }
}

int dequeue(Queue *s) {
    if (s->front == NULL) return -1;
    ListNode *victim = s->front;
    int value = victim->data;
    s->front = victim->next;
    if (s->front == NULL) s->rear = NULL;
    free(victim);
    return value;
}
