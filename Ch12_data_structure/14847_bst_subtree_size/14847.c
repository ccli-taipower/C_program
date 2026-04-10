/*
 * NTHU EE2310 - 題目 14847: BST Subtree Size（二元搜尋樹子樹大小）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 12 章（資料結構）
 *   如果不知道如何解題，請參考課本第 12 章的說明。
 *
 * 【題目說明】
 * 將 n 個整數依序插入二元搜尋樹（BST）。重複值插入到右子樹。
 * 對每個節點計算其子樹大小（以該節點為根的子樹共有幾個節點）。
 * 以中序走訪輸出每個節點，格式為 "值 子樹大小"，每行一筆。
 *
 * 【解題策略】
 * 1. 依序插入節點建立 BST（重複值往右子樹插入）。
 * 2. 以後序走訪計算各節點的子樹大小（先算左右子樹，再算當前節點）。
 * 3. 以中序走訪輸出各節點的值和子樹大小。
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
} Node;

/* 建立新節點 */
static Node *new_node(int v) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->val = v;
    p->size = 1;
    p->left = p->right = NULL;
    return p;
}

/*
 * 將值 v 插入 BST（重複值往右子樹插入），回傳根節點。
 */
static Node *insert(Node *root, int v) {
    if (root == NULL) return new_node(v);
    if (v < root->val) {
        root->left = insert(root->left, v);   /* 較小值往左插 */
    } else {
        root->right = insert(root->right, v); /* 較大或相等值往右插 */
    }
    return root;
}

/*
 * 以後序走訪計算各節點的子樹大小，回傳子樹大小。
 */
static int calc_size(Node *root) {
    if (root == NULL) return 0;
    int left_size  = calc_size(root->left);
    int right_size = calc_size(root->right);
    root->size = 1 + left_size + right_size;
    return root->size;
}

/*
 * 以中序走訪輸出：每行 "值 子樹大小"。
 */
static void inorder_print(Node *root) {
    if (root == NULL) return;
    inorder_print(root->left);
    printf("%d %d\n", root->val, root->size);
    inorder_print(root->right);
}

/* 釋放整棵樹的記憶體 */
static void free_tree(Node *root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void) {
    Node *root = NULL;
    int v;

    /* 讀取整數直到行尾或 EOF，依序插入 BST */
    int c;
    while (scanf("%d", &v) == 1) {
        root = insert(root, v);
        /* 讀取下一個字元：若為換行或 EOF 則停止 */
        c = getchar();
        if (c == '\n' || c == EOF) break;
        /* 否則放回緩衝區，繼續讀取 */
        ungetc(c, stdin);
    }

    /* 計算各節點子樹大小 */
    calc_size(root);

    /* 中序走訪輸出結果 */
    inorder_print(root);

    free_tree(root);
    return 0;
}
