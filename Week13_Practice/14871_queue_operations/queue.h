/*
 * NTHU ACM 14871 - Queue Operations
 * Contest: EE2310 Week 13 Practice
 *
 * Public interface for a FIFO queue implemented as a singly-linked list.
 * Each node holds one integer; `front` is the dequeue end, `rear` is the
 * enqueue end.
 */
#ifndef QUEUE_H
#define QUEUE_H

struct listnode {
    int data;
    struct listnode *next;
};
typedef struct listnode ListNode;

struct queue {
    ListNode *front;
    ListNode *rear;
};
typedef struct queue Queue;

void init(Queue *s);
int  empty(Queue *s);
void enqueue(Queue *s, int data);
int  dequeue(Queue *s);

#endif /* QUEUE_H */
