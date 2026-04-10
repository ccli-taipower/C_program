/*
 * NTHU EE2310 - 題目 14836: Reverse Linked List
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 15 章（遞迴）
 *   如果不知道如何解題，請參考課本第 15 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14836/
 *
 * 【題目說明】
 * 從標準輸入讀取整數，直到 EOF 為止。
 * 每個整數插入鏈結串列的頭部（front insertion），
 * 故串列順序與輸入順序相反。
 * 最後呼叫 print_list_backward(head)，以遞迴方式
 * 「從尾到頭」輸出串列，等同於以原始輸入順序輸出。
 *
 * 範例：輸入 3 8 1 7
 *   → 鏈結串列：7 → 1 → 8 → 3 → NULL
 *   → 倒序輸出：3, 8, 1, 7（每行一個）
 *
 * 【遞迴函式說明】
 * print_list_backward(ptr)：
 *   若 ptr 為 NULL：直接返回
 *   否則：先遞迴處理 ptr->next，再輸出 ptr->data
 *   → 效果：先遞迴到串列尾端，再由後往前輸出
 *
 * 【注意】
 * main 函式使用前插法建立串列，已按題目規定。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 從標準輸入讀取整數，直到 EOF；每讀入一個整數，以 malloc 配置一個新節點。
 * 2. 使用前插法（front insertion）將新節點插入串列頭部：node->next = head; head = node;
 *    讀入順序為 a b c d，則串列建立後為 d → c → b → a → NULL。
 * 3. 呼叫 print_list_backward(head)，以遞迴方式倒序輸出：
 *    先遞迴呼叫 print_list_backward(ptr->next)，到達 NULL 後返回；
 *    返回途中依序輸出各節點的 data，效果為 a b c d（即原始輸入順序）。
 * 4. 遞迴基底：ptr == NULL 時直接返回，不做任何輸出。
 * 5. 輸出完成後，以迴圈逐一釋放所有節點記憶體，避免記憶體洩漏。
 *
 * English:
 * 1. Read integers from stdin until EOF; for each integer, allocate a new node with
 *    malloc.
 * 2. Use front insertion: node->next = head; head = node; so if input is a b c d,
 *    the list becomes d → c → b → a → NULL.
 * 3. Call print_list_backward(head) to recursively print in reverse order:
 *    first recurse with print_list_backward(ptr->next) all the way to NULL,
 *    then print ptr->data on the way back — producing a b c d (original input order).
 * 4. Base case: if ptr == NULL, return immediately without printing anything.
 * 5. After printing, free all nodes in a loop to avoid memory leaks.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* 鏈結串列節點定義 / linked list node definition */
typedef struct ListNode {
    int data;               /* 節點儲存的整數資料 / integer data stored in this node */
    struct ListNode *next;  /* 指向下一個節點的指標 / pointer to the next node */
} ListNode;

/* 以遞迴方式倒序輸出鏈結串列的所有節點值 / recursively print all node values in reverse list order
 * （先遞迴到串列尾端，再由後往前輸出， / (recurse to the end first, then print on the way back,
 *   等同於以原始插入順序輸出） /   equivalent to printing in original insertion order) */
void print_list_backward(ListNode *ptr) {
    /* 基底情況：節點為空，直接返回 / base case: null node, return immediately */
    if (ptr == NULL) return;

    /* 先遞迴處理後繼節點 / first recurse on the next node */
    print_list_backward(ptr->next);

    /* 再輸出目前節點的值 / then print the current node's value */
    printf("%d\n", ptr->data);
}

int main(void) {
    ListNode *head = NULL;  /* 串列頭指標，初始為空串列 / head pointer; initially empty list */
    int val;                /* 讀入的整數值 / integer value read from input */

    /* 從標準輸入讀取整數，直到 EOF 為止 / read integers from stdin until EOF */
    while (scanf("%d", &val) == 1) {
        /* 配置新節點 / allocate a new node */
        ListNode *node = (ListNode *)malloc(sizeof(ListNode));
        assert(node != NULL);  /* 確保記憶體配置成功 / ensure memory allocation succeeded */

        /* 初始化節點資料 / initialize node data */
        node->data = val;

        /* 前插法：將新節點插入串列頭部 / front insertion: insert new node at list head */
        node->next = head;
        head = node;
    }

    /* 以遞迴方式倒序輸出整個串列 / recursively print the entire list in reverse order */
    print_list_backward(head);

    /* 釋放所有配置的節點記憶體 / free all allocated node memory */
    while (head != NULL) {
        ListNode *tmp = head;
        head = head->next;
        free(tmp);
    }

    return 0;
}
