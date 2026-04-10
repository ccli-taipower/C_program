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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 呼叫 read_line_ints() 讀取第一行的中序序列，存入 in[]，回傳讀到的元素數 n。
 * 2. 再次呼叫 read_line_ints() 讀取第二行的後序序列，存入 post[]，回傳元素數 m；確認 n == m。
 * 3. 呼叫 build(in, 0, n-1, post, 0, n-1) 遞迴重建二元樹：取後序末尾元素為根，在中序序列中線性搜尋根的位置 k，以 k 將兩序列分割為左右子樹，遞迴重建。
 * 4. build() 每次遞迴分別傳入左子樹區間（il..k-1 / pl..pl+left_size-1）和右子樹區間（k+1..ir / pl+left_size..pr-1）。
 * 5. 呼叫 preorder() 遞迴前序走訪（根→左→右），以空白分隔輸出各節點值，最後換行。
 * 6. 呼叫 free_tree() 遞迴釋放所有節點記憶體。
 *
 * English:
 * 1. Call read_line_ints() to read the first line (inorder sequence) into in[], returning count n.
 * 2. Call read_line_ints() again to read the second line (postorder sequence) into post[], returning count m; verify n == m.
 * 3. Call build(in, 0, n-1, post, 0, n-1) to recursively reconstruct the binary tree: take the last postorder element as root, linearly search for root position k in the inorder array, split both arrays at k, and recurse for left and right subtrees.
 * 4. Each build() recursion passes left-subtree ranges (il..k-1 / pl..pl+left_size-1) and right-subtree ranges (k+1..ir / pl+left_size..pr-1).
 * 5. Call preorder() to recursively print the tree in preorder (root→left→right), space-separated, followed by a newline.
 * 6. Call free_tree() to recursively free all node memory.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 128

typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

/* 建立新節點 / create a new node */
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
    int root_val = post[pr];            /* 後序最後一個元素為根 / last element of postorder is the root */
    Node *root = new_node(root_val);
    if (il == ir) return root;

    /* 在中序序列中找根節點的位置 / find the root's position in the inorder sequence */
    int k = il;
    while (k <= ir && in[k] != root_val) ++k;

    int left_size = k - il;             /* 左子樹節點數 / number of nodes in the left subtree */
    root->left  = build(in, il, k - 1, post, pl, pl + left_size - 1);
    root->right = build(in, k + 1, ir, post, pl + left_size, pr - 1);
    return root;
}

/* 前序走訪並輸出（各元素間以空白分隔） / preorder traversal and print (space-separated) */
static int first = 1;
static void preorder(Node *root) {
    if (!root) return;
    if (first) { printf("%d", root->val); first = 0; }
    else       { printf(" %d", root->val); }
    preorder(root->left);
    preorder(root->right);
}

/* 釋放整棵樹的記憶體 / free all memory of the entire tree */
static void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/* 讀取一行內以空白分隔的整數；回傳讀到的個數 / read space-separated integers from one line; return the count read */
static int read_line_ints(int *buf, int cap) {
    int count = 0, v;
    int c;
    /* 跳過行首空白（保留換行符） / skip leading whitespace (but preserve newline) */
    while ((c = getchar()) != EOF && c != '\n' && (c == ' ' || c == '\t')) {}
    if (c == EOF) return 0;
    if (c == '\n') return 0;
    ungetc(c, stdin);

    while (count < cap) {
        if (scanf("%d", &v) != 1) break;
        buf[count++] = v;
        /* 讀取下一個字元，若為換行或 EOF 則停止 / read next character; stop if newline or EOF */
        c = getchar();
        if (c == '\n' || c == EOF) break;
        ungetc(c, stdin);
    }
    return count;
}

int main(void) {
    int in[MAXN], post[MAXN];
    int n = read_line_ints(in, MAXN);     /* 讀取中序序列 / read inorder sequence */
    int m = read_line_ints(post, MAXN);   /* 讀取後序序列 / read postorder sequence */
    if (n == 0 || n != m) return 0;

    Node *root = build(in, 0, n - 1, post, 0, n - 1);
    preorder(root);
    printf("\n");
    free_tree(root);
    return 0;
}
