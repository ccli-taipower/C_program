/*
 * NTHU EE2310 - 題目 14866: The Winner of the Circular Game (Josephus Problem)
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 15 章（遞迴）
 *   如果不知道如何解題，請參考課本第 15 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14866/
 *
 * 【題目說明】
 * n 個朋友圍成一圈（編號 1..n），從第 1 人開始，每次順時針數到第 k 人，
 * 該人即被淘汰。重複此過程直到只剩 1 人，輸出此人的 1-indexed 編號。
 * （即 Josephus 問題）
 *
 * 限制：n, k ≤ 500
 *
 * 【解題策略】
 * 使用環狀單向鏈結串列模擬：
 * 1. 建立 1 → 2 → ... → n → （回到 1）的環狀鏈結串列。
 * 2. 每輪從 prev 的下一個節點開始計數，
 *    移動 k-1 步後，prev->next 即為被淘汰者。
 * 3. 將被淘汰者從串列中移除並釋放記憶體。
 * 4. 重複直到串列中只剩一個節點，輸出其編號。
 *
 * 時間複雜度：O(n × k)，在 n, k ≤ 500 的限制下完全可行。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入 n（人數）和 k（每次數到第幾人），建立環狀單向鏈結串列：
 *    依序配置節點 1, 2, ..., n，最後令 tail->next = head 形成環。
 * 2. 設定指標 prev 指向 tail（即 head 的前一個節點），作為「上一輪結束位置」。
 * 3. 進入淘汰迴圈：只要 prev->next != prev（串列多於一個節點），繼續：
 *    a. 將 prev 往後移動 k-1 步，使 prev->next 恰好指向第 k 個人。
 *    b. victim = prev->next，將 victim 從串列移除（prev->next = victim->next）。
 *    c. free(victim)，釋放被淘汰節點的記憶體。
 *    d. prev 保持不動，下一輪再從 prev->next 重新開始計數。
 * 4. 迴圈結束時 prev 即為最後存活者，輸出其 id 並釋放記憶體。
 *
 * English:
 * 1. Read n (number of people) and k (count step); build a circular singly linked list
 *    with nodes 1, 2, ..., n in order, then set tail->next = head to close the circle.
 * 2. Initialize pointer prev to tail (the node before head), serving as the
 *    "last-round end position".
 * 3. Enter the elimination loop: while prev->next != prev (more than one node remains):
 *    a. Advance prev by k-1 steps so that prev->next points to the k-th person.
 *    b. victim = prev->next; unlink victim (prev->next = victim->next).
 *    c. free(victim) to release its memory.
 *    d. Leave prev unchanged; the next round restarts counting from prev->next.
 * 4. When the loop ends prev is the sole survivor; print prev->id and free the node.
 */
#include <stdio.h>
#include <stdlib.h>

/* 環狀鏈結串列節點定義 / circular linked list node definition */
typedef struct node {
    int id;           /* 此人的編號（1-indexed） / person's number (1-indexed) */
    struct node *next;/* 指向下一個節點的指標 / pointer to the next node */
} Node;

int main(void) {
    int n, k;  /* n 人、每次數到第 k 人 / n people, count to the k-th person each round */
    int i;

    if (scanf("%d %d", &n, &k) != 2) return 0;

    /* 建立環狀單向鏈結串列：1 → 2 → ... → n → 1 / build circular singly linked list: 1 → 2 → ... → n → 1 */
    Node *head = (Node *)malloc(sizeof(Node));
    head->id = 1;
    Node *tail = head;

    for (i = 2; i <= n; i++) {
        Node *p = (Node *)malloc(sizeof(Node));
        p->id = i;
        tail->next = p;
        tail = p;
    }
    tail->next = head;  /* 串列尾端指回頭端，形成環狀 / tail points back to head, forming a cycle */

    /* prev 指向「目前起算點的前一個節點」， / prev points to the node before the current starting point,
     * 以便快速找到並移除被淘汰的節點。 / allowing quick identification and removal of the eliminated node.
     * 初始時 prev 指向 tail（head 的前一節點）。 / initially prev points to tail (the node before head). */
    Node *prev = tail;

    /* 重複淘汰，直到串列只剩一個節點 / repeatedly eliminate until only one node remains */
    while (prev->next != prev) {
        int step;
        /* 從目前起算點往前數 k-1 步（共走到第 k 人） / advance k-1 steps to land on the k-th person */
        for (step = 1; step < k; step++) {
            prev = prev->next;
        }

        /* prev->next 即為被淘汰的節點 / prev->next is the node to be eliminated */
        Node *victim = prev->next;
        prev->next = victim->next;  /* 從串列中移除 / unlink from the list */
        free(victim);               /* 釋放記憶體 / free memory */
        /* prev 不動，下一輪從 prev->next 重新開始計數 / leave prev unchanged; next round starts from prev->next */
    }

    /* 輸出最後存活者的編號 / print the last survivor's number */
    printf("%d\n", prev->id);
    free(prev);
    return 0;
}
