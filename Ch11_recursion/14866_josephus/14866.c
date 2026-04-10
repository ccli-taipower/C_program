/*
 * NTHU EE2310 - 題目 14866: The Winner of the Circular Game (Josephus Problem)
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 11 章（遞迴）
 *   如果不知道如何解題，請參考課本第 11 章的說明。
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
 */
#include <stdio.h>
#include <stdlib.h>

/* 環狀鏈結串列節點定義 */
typedef struct node {
    int id;           /* 此人的編號（1-indexed） */
    struct node *next;/* 指向下一個節點的指標 */
} Node;

int main(void) {
    int n, k;  /* n 人、每次數到第 k 人 */
    int i;

    if (scanf("%d %d", &n, &k) != 2) return 0;

    /* 建立環狀單向鏈結串列：1 → 2 → ... → n → 1 */
    Node *head = (Node *)malloc(sizeof(Node));
    head->id = 1;
    Node *tail = head;

    for (i = 2; i <= n; i++) {
        Node *p = (Node *)malloc(sizeof(Node));
        p->id = i;
        tail->next = p;
        tail = p;
    }
    tail->next = head;  /* 串列尾端指回頭端，形成環狀 */

    /* prev 指向「目前起算點的前一個節點」，
     * 以便快速找到並移除被淘汰的節點。
     * 初始時 prev 指向 tail（head 的前一節點）。 */
    Node *prev = tail;

    /* 重複淘汰，直到串列只剩一個節點 */
    while (prev->next != prev) {
        int step;
        /* 從目前起算點往前數 k-1 步（共走到第 k 人） */
        for (step = 1; step < k; step++) {
            prev = prev->next;
        }

        /* prev->next 即為被淘汰的節點 */
        Node *victim = prev->next;
        prev->next = victim->next;  /* 從串列中移除 */
        free(victim);               /* 釋放記憶體 */
        /* prev 不動，下一輪從 prev->next 重新開始計數 */
    }

    /* 輸出最後存活者的編號 */
    printf("%d\n", prev->id);
    free(prev);
    return 0;
}
