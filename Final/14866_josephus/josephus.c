/*
 * NTHU ACM 14866 - The Winner of the Circular Game (Josephus problem)
 * Contest: EE2310 Final (30 points)
 *
 * n friends in a circle, counting k clockwise; the k-th friend is eliminated
 * every round. Output the survivor's 1-indexed label.
 *
 * We use an O(n * k) circular linked-list simulation, which is well within
 * limits for n, k <= 500.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int id;
    struct node *next;
} Node;

int main(void) {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return 0;

    /* Build circular singly linked list 1 -> 2 -> ... -> n -> 1 */
    Node *head = (Node *)malloc(sizeof(Node));
    head->id = 1;
    Node *tail = head;
    for (int i = 2; i <= n; ++i) {
        Node *p = (Node *)malloc(sizeof(Node));
        p->id = i;
        tail->next = p;
        tail = p;
    }
    tail->next = head; /* close the circle */

    /* "prev" keeps pointer to node BEFORE the current starting point so we
     * can easily unlink the node that gets counted out. */
    Node *prev = tail; /* before head */
    while (prev->next != prev) {
        for (int step = 1; step < k; ++step) {
            prev = prev->next;
        }
        Node *victim = prev->next;
        prev->next = victim->next;
        free(victim);
    }

    printf("%d\n", prev->id);
    free(prev);
    return 0;
}
