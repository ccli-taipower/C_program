/*
 * NTHU ACM 14859 - K-th smallest element in a binary search tree
 * Contest: EE2310 Quiz 10
 *
 * The main program and the BS_Tree structure/insertion are provided by the
 * problem. Only find_kth_min_data() has to be written, and it can rely on
 * the pre-computed sub_node_count field on every node.
 *
 * Algorithm:
 *   Let L = size of left subtree (0 if NULL).
 *   If k <= L            -> answer is in the left subtree
 *   If k == L + 1        -> current node is the answer
 *   Otherwise            -> answer is the (k - L - 1)-th smallest in the right subtree
 * This runs in O(tree height) per query.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define debug 0

typedef struct bs_tree {
    int data;
    int sub_node_count;
    struct bs_tree *left;
    struct bs_tree *right;
} BS_Tree;

/* ---- function to implement --------------------------------------------- */
BS_Tree *find_kth_min_data(BS_Tree *root, int k) {
    if (root == NULL) return NULL;
    int left_size = (root->left != NULL) ? root->left->sub_node_count : 0;
    if (k <= left_size) {
        return find_kth_min_data(root->left, k);
    } else if (k == left_size + 1) {
        return root;
    } else {
        return find_kth_min_data(root->right, k - left_size - 1);
    }
}
/* ------------------------------------------------------------------------ */

BS_Tree *insert_sort_BS_Tree(BS_Tree *root, int data) {
    BS_Tree *current = root;
    if (root == NULL) {
        current = (BS_Tree *)malloc(sizeof(BS_Tree));
        assert(current != NULL);
        current->data = data;
        current->left = NULL;
        current->right = NULL;
        return current;
    }
    if (data <= current->data)
        current->left = insert_sort_BS_Tree(current->left, data);
    else
        current->right = insert_sort_BS_Tree(current->right, data);
    return current;
}

int insert_sub_node_count(BS_Tree *root) {
    int left_count, right_count;
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) {
        root->sub_node_count = 1;
        return 1;
    }
    left_count = insert_sub_node_count(root->left);
    right_count = insert_sub_node_count(root->right);
    root->sub_node_count = 1 + left_count + right_count;
    return root->sub_node_count;
}

BS_Tree *delete_BS_Tree(BS_Tree *root) {
    if (root == NULL) return NULL;
    delete_BS_Tree(root->left);
    delete_BS_Tree(root->right);
    free(root);
    return NULL;
}

int main(void) {
    int data, k;
    BS_Tree *root = NULL;
    BS_Tree *ptr_kth_min;

    do {
        if (scanf("%d", &data) != 1) break;
        root = insert_sort_BS_Tree(root, data);
    } while (getchar() != '\n');

    insert_sub_node_count(root);

    do {
        if (scanf("%d", &k) != 1) break;
        ptr_kth_min = find_kth_min_data(root, k);
        printf("%d\n", ptr_kth_min->data);
    } while (getchar() != '\n');

    root = delete_BS_Tree(root);
    return 0;
}
