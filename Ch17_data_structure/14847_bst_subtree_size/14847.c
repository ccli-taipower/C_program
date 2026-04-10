/*
 * NTHU EE2310 - 題目 14847: BST Subtree Size（二元搜尋樹子樹大小）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 17 章（資料結構）
 *   如果不知道如何解題，請參考課本第 17 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14847/
 *
 * 【題目說明】
 * 將 n 個整數依序插入二元搜尋樹（BST）。重複值插入到右子樹。
 * 對每個節點計算其子樹大小（以該節點為根的子樹共有幾個節點）。
 * 以中序走訪輸出每個節點，格式為 "值 子樹大小"，每行一筆。
 *
 * 【解題策略】
 * 1. 依序插入節點建立 BST（重複值往右子樹插入）。
 *    使用迭代插入避免深度 100,000 時的遞迴堆疊溢位。
 * 2. 以後序走訪計算各節點的子樹大小（先算左右子樹，再算當前節點）。
 *    使用迭代後序走訪（兩個顯式堆疊）。
 * 3. 以中序走訪輸出各節點的值和子樹大小。
 *    使用迭代中序走訪（一個顯式堆疊）。
 *
 * 範例：[7, 3, 10, 1, 5]
 *   中序：1 3 5 7 10
 *   子樹大小：1→1, 3→3, 5→1, 7→5, 10→1
 *   輸出：1 1 / 3 3 / 5 1 / 7 5 / 10 1
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    int size;            /* 以此節點為根的子樹大小 */
    struct Node *left;
    struct Node *right;
    struct Node *parent; /* 父節點指標，供迭代後序走訪使用 */
} Node;

/* 建立新節點 */
static Node *new_node(int v) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->val   = v;
    p->size  = 1;
    p->left  = p->right = p->parent = NULL;
    return p;
}

/* 迭代插入（避免遞迴深度過深） */
static Node *insert(Node *root, int v) {
    Node *nd = new_node(v);
    if (root == NULL) return nd;

    Node *cur = root;
    while (1) {
        if (v < cur->val) {
            if (cur->left == NULL) {
                cur->left = nd;
                nd->parent = cur;
                break;
            }
            cur = cur->left;
        } else {
            if (cur->right == NULL) {
                cur->right = nd;
                nd->parent = cur;
                break;
            }
            cur = cur->right;
        }
    }
    return root;
}

/* 迭代後序走訪，計算各節點子樹大小 */
static void calc_size_iterative(Node *root) {
    if (root == NULL) return;

    /* 使用兩個陣列模擬後序走訪的堆疊 */
    Node **stack1 = (Node **)malloc(200001 * sizeof(Node *));
    Node **stack2 = (Node **)malloc(200001 * sizeof(Node *));
    int top1 = 0, top2 = 0;

    stack1[top1++] = root;

    /* 用類似前序走訪（根→右→左）產生後序走訪的逆序 */
    while (top1 > 0) {
        Node *cur = stack1[--top1];
        stack2[top2++] = cur;

        if (cur->left)  stack1[top1++] = cur->left;
        if (cur->right) stack1[top1++] = cur->right;
    }

    /* stack2 中的順序即為後序走訪，由尾到頭計算子樹大小 */
    while (top2 > 0) {
        Node *cur = stack2[--top2];
        int ls = cur->left  ? cur->left->size  : 0;
        int rs = cur->right ? cur->right->size : 0;
        cur->size = 1 + ls + rs;
    }

    free(stack1);
    free(stack2);
}

/* 迭代中序走訪，輸出各節點的值和子樹大小 */
static void inorder_print_iterative(Node *root) {
    Node **stack = (Node **)malloc(200001 * sizeof(Node *));
    int top = 0;
    Node *cur = root;

    while (cur != NULL || top > 0) {
        /* 一直往左走，沿途壓入堆疊 */
        while (cur != NULL) {
            stack[top++] = cur;
            cur = cur->left;
        }
        /* 取出節點並輸出 */
        cur = stack[--top];
        printf("%d %d\n", cur->val, cur->size);
        /* 轉往右子樹 */
        cur = cur->right;
    }

    free(stack);
}

/* 迭代釋放整棵樹 */
static void free_tree(Node *root) {
    if (root == NULL) return;
    Node **stack = (Node **)malloc(200001 * sizeof(Node *));
    int top = 0;
    stack[top++] = root;
    while (top > 0) {
        Node *cur = stack[--top];
        if (cur->left)  stack[top++] = cur->left;
        if (cur->right) stack[top++] = cur->right;
        free(cur);
    }
    free(stack);
}

int main(void) {
    Node *root = NULL;
    int v;
    int c;

    /* 讀取整數直到行尾或 EOF，依序插入 BST */
    while (scanf("%d", &v) == 1) {
        root = insert(root, v);
        c = getchar();
        if (c == '\n' || c == EOF) break;
        ungetc(c, stdin);
    }

    /* 計算各節點子樹大小（迭代後序走訪） */
    calc_size_iterative(root);

    /* 中序走訪輸出結果 */
    inorder_print_iterative(root);

    free_tree(root);
    return 0;
}
