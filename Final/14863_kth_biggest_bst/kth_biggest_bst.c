/*
 * NTHU ACM 14863 - K-th biggest element in a binary search tree
 * Contest: EE2310 Final (20 points)
 *
 * Mirror of 14859. We recurse into the RIGHT subtree first (larger values).
 *   Let R = size of right subtree (0 if NULL).
 *   If k <= R            -> answer is in the right subtree
 *   If k == R + 1        -> current node is the answer
 *   Otherwise            -> answer is the (k - R - 1)-th biggest in the left subtree
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
BS_Tree *find_kth_max_data(BS_Tree *root, int k) {
    if (root == NULL) return NULL;
    int right_size = (root->right != NULL) ? root->right->sub_node_count : 0;
    if (k <= right_size) {
        return find_kth_max_data(root->right, k);
    } else if (k == right_size + 1) {
        return root;
    } else {
        return find_kth_max_data(root->left, k - right_size - 1);
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
    BS_Tree *ptr_kth_max;

    do {
        if (scanf("%d", &data) != 1) break;
        root = insert_sort_BS_Tree(root, data);
    } while (getchar() != '\n');

    insert_sub_node_count(root);

    do {
        if (scanf("%d", &k) != 1) break;
        ptr_kth_max = find_kth_max_data(root, k);
        printf("%d\n", ptr_kth_max->data);
    } while (getchar() != '\n');

    root = delete_BS_Tree(root);
    return 0;
}
