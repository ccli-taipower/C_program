/*
 * NTHU EE2310 - 題目 14874: Build Binary Tree（建立二元樹）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 17 章（資料結構）
 *   如果不知道如何解題，請參考課本第 17 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14874/
 *
 * 【題目說明】
 * 給定一棵二元樹的中序（inorder）和後序（postorder）走訪序列，
 * 重建唯一確定的二元樹，並輸出其前序（preorder）走訪序列。
 *
 * 【解題策略】
 * 採用分治法（Divide and Conquer）：
 *   - 後序序列的最後一個元素為根節點。
 *   - 在中序序列中找到根節點的位置，左側為左子樹，右側為右子樹。
 *   - 對左右子樹遞迴重建。
 * 時間複雜度：O(n^2)（每層需線性搜尋根節點位置）。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 128

typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

/* 建立新節點 */
static Node *new_node(int v) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->val = v;
    p->left = p->right = NULL;
    return p;
}

/*
 * 建立子樹：
 *   in[il..ir]   ：中序序列的區間
 *   post[pl..pr] ：後序序列的區間（與中序區間大小相同）
 */
static Node *build(const int *in, int il, int ir,
                   const int *post, int pl, int pr) {
    if (il > ir) return NULL;
    int root_val = post[pr];            /* 後序最後一個元素為根 */
    Node *root = new_node(root_val);
    if (il == ir) return root;

    /* 在中序序列中找根節點的位置 */
    int k = il;
    while (k <= ir && in[k] != root_val) ++k;

    int left_size = k - il;             /* 左子樹節點數 */
    root->left  = build(in, il, k - 1, post, pl, pl + left_size - 1);
    root->right = build(in, k + 1, ir, post, pl + left_size, pr - 1);
    return root;
}

/* 前序走訪並輸出（各元素間以空白分隔） */
static int first = 1;
static void preorder(Node *root) {
    if (!root) return;
    if (first) { printf("%d", root->val); first = 0; }
    else       { printf(" %d", root->val); }
    preorder(root->left);
    preorder(root->right);
}

/* 釋放整棵樹的記憶體 */
static void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/* 讀取一行內以空白分隔的整數；回傳讀到的個數 */
static int read_line_ints(int *buf, int cap) {
    int count = 0, v;
    int c;
    /* 跳過行首空白（保留換行符） */
    while ((c = getchar()) != EOF && c != '\n' && (c == ' ' || c == '\t')) {}
    if (c == EOF) return 0;
    if (c == '\n') return 0;
    ungetc(c, stdin);

    while (count < cap) {
        if (scanf("%d", &v) != 1) break;
        buf[count++] = v;
        /* 讀取下一個字元，若為換行或 EOF 則停止 */
        c = getchar();
        if (c == '\n' || c == EOF) break;
        ungetc(c, stdin);
    }
    return count;
}

int main(void) {
    int in[MAXN], post[MAXN];
    int n = read_line_ints(in, MAXN);     /* 讀取中序序列 */
    int m = read_line_ints(post, MAXN);   /* 讀取後序序列 */
    if (n == 0 || n != m) return 0;

    Node *root = build(in, 0, n - 1, post, 0, n - 1);
    preorder(root);
    printf("\n");
    free_tree(root);
    return 0;
}
