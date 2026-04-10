/*
 * NTHU ACM 14871 - Queue Operations (demo driver)
 *
 * Exercises the queue interface declared in queue.h and produces the
 * expected output from the problem statement.
 */
#include <stdio.h>
#include "queue.h"

int main(void) {
    Queue queue;
    Queue *q = &queue;

    init(q);
    if (empty(q)) printf("initially queue is empty\n");

    enqueue(q, 2);
    enqueue(q, 3);
    printf("%d\n", dequeue(q));  /* 2 */
    enqueue(q, 4);
    printf("%d\n", dequeue(q));  /* 3 */
    printf("%d\n", dequeue(q));  /* 4 */
    enqueue(q, 5);
    enqueue(q, 6);
    printf("%d\n", dequeue(q));  /* 5 */
    printf("%d\n", dequeue(q));  /* 6 */
    return 0;
}
