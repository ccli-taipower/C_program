/*
 * NTHU ACM 14874 - Build binary tree from inorder and postorder
 * Contest: EE2310 Quiz 11
 *
 * Given inorder and postorder traversals, reconstruct the unique binary tree
 * and output its preorder traversal.
 *
 * Classic divide-and-conquer:
 *   - Last element of postorder is the root.
 *   - Locate the root in inorder; everything to its left is the left subtree,
 *     everything to its right is the right subtree.
 *   - Recurse on the left and right halves.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 128

typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

static Node *new_node(int v) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->val = v;
    p->left = p->right = NULL;
    return p;
}

/* Build the tree.
 *   in[il..ir]   : inorder slice
 *   post[pl..pr] : postorder slice (same size as inorder slice)
 */
static Node *build(const int *in, int il, int ir,
                   const int *post, int pl, int pr) {
    if (il > ir) return NULL;
    int root_val = post[pr];
    Node *root = new_node(root_val);
    if (il == ir) return root;

    /* locate root in inorder slice */
    int k = il;
    while (k <= ir && in[k] != root_val) ++k;

    int left_size = k - il;
    root->left  = build(in, il, k - 1, post, pl, pl + left_size - 1);
    root->right = build(in, k + 1, ir, post, pl + left_size, pr - 1);
    return root;
}

static int first = 1;
static void preorder(Node *root) {
    if (!root) return;
    if (first) { printf("%d", root->val); first = 0; }
    else       { printf(" %d", root->val); }
    preorder(root->left);
    preorder(root->right);
}

static void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/* Read a whitespace-separated line of integers into buf. Returns count. */
static int read_line_ints(int *buf, int cap) {
    int count = 0, v;
    int c;
    /* skip leading whitespace except newline */
    while ((c = getchar()) != EOF && c != '\n' && (c == ' ' || c == '\t')) {}
    if (c == EOF) return 0;
    if (c == '\n') return 0;
    ungetc(c, stdin);

    while (count < cap) {
        if (scanf("%d", &v) != 1) break;
        buf[count++] = v;
        /* peek next character: stop at newline */
        c = getchar();
        if (c == '\n' || c == EOF) break;
        ungetc(c, stdin);
    }
    return count;
}

int main(void) {
    int in[MAXN], post[MAXN];
    int n = read_line_ints(in, MAXN);
    int m = read_line_ints(post, MAXN);
    if (n == 0 || n != m) return 0;

    Node *root = build(in, 0, n - 1, post, 0, n - 1);
    preorder(root);
    printf("\n");
    free_tree(root);
    return 0;
}
