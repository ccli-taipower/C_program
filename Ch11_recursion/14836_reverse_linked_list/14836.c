/*
 * NTHU EE2310 - 題目 14836: Reverse Linked List
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 11 章（遞迴）
 *   如果不知道如何解題，請參考課本第 11 章的說明。
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
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* 鏈結串列節點定義 */
typedef struct ListNode {
    int data;               /* 節點儲存的整數資料 */
    struct ListNode *next;  /* 指向下一個節點的指標 */
} ListNode;

/* 以遞迴方式倒序輸出鏈結串列的所有節點值
 * （先遞迴到串列尾端，再由後往前輸出，
 *   等同於以原始插入順序輸出） */
void print_list_backward(ListNode *ptr) {
    /* 基底情況：節點為空，直接返回 */
    if (ptr == NULL) return;

    /* 先遞迴處理後繼節點 */
    print_list_backward(ptr->next);

    /* 再輸出目前節點的值 */
    printf("%d\n", ptr->data);
}

int main(void) {
    ListNode *head = NULL;  /* 串列頭指標，初始為空串列 */
    int val;                /* 讀入的整數值 */

    /* 從標準輸入讀取整數，直到 EOF 為止 */
    while (scanf("%d", &val) == 1) {
        /* 配置新節點 */
        ListNode *node = (ListNode *)malloc(sizeof(ListNode));
        assert(node != NULL);  /* 確保記憶體配置成功 */

        /* 初始化節點資料 */
        node->data = val;

        /* 前插法：將新節點插入串列頭部 */
        node->next = head;
        head = node;
    }

    /* 以遞迴方式倒序輸出整個串列 */
    print_list_backward(head);

    /* 釋放所有配置的節點記憶體 */
    while (head != NULL) {
        ListNode *tmp = head;
        head = head->next;
        free(tmp);
    }

    return 0;
}
