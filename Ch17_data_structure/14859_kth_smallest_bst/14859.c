/*
 * NTHU EE2310 - 題目 14859: K-th Smallest Element in BST（二元搜尋樹第 K 小元素）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 17 章（資料結構）
 *   如果不知道如何解題，請參考課本第 17 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14859/
 *
 * 【題目說明】
 * 給定一棵二元搜尋樹（BST），以及多個查詢 k，
 * 對每個 k 輸出樹中第 k 小的元素。
 *
 * 【解題策略】
 * 每個節點預先計算 sub_node_count（子樹節點總數）。
 * 設 L = 左子樹大小（若為 NULL 則為 0）：
 *   若 k <= L         → 答案在左子樹中
 *   若 k == L + 1     → 當前節點即為答案
 *   否則              → 在右子樹中找第 (k - L - 1) 小
 * 每次查詢的時間複雜度為 O(樹高)。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀取第一行的整數序列，逐一呼叫 insert_sort_BS_Tree() 遞迴插入 BST（相等值往左子樹）。
 * 2. 讀完第一行後，呼叫 insert_sub_node_count() 以後序走訪計算每個節點的 sub_node_count（子樹節點總數）。
 * 3. 讀取第二行的查詢序列，對每個 k 呼叫 find_kth_min_data(root, k)。
 * 4. find_kth_min_data() 利用左子樹大小 L 決定遞迴方向：k<=L 往左子樹、k==L+1 回傳當前節點、否則以 k-L-1 往右子樹。
 * 5. 輸出找到節點的 data 值，每個查詢一行。
 * 6. 查詢結束後呼叫 delete_BS_Tree() 遞迴釋放所有節點記憶體。
 *
 * English:
 * 1. Read the first line of integers and insert each into the BST recursively via insert_sort_BS_Tree() (equal values go left).
 * 2. After reading the first line, call insert_sub_node_count() to compute sub_node_count for every node using postorder traversal.
 * 3. Read the second line of queries; for each k, call find_kth_min_data(root, k).
 * 4. find_kth_min_data() uses left-subtree size L to decide recursion direction: k<=L go left, k==L+1 return current node, otherwise recurse right with k-L-1.
 * 5. Print the found node's data value, one per line.
 * 6. After all queries, call delete_BS_Tree() to recursively free all node memory.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define debug 0

typedef struct bs_tree {
    int data;
    int sub_node_count;     /* 以此節點為根的子樹節點總數 / total node count in the subtree rooted here */
    struct bs_tree *left;
    struct bs_tree *right;
} BS_Tree;

/* 找第 k 小的節點（利用子樹大小資訊） / find the k-th smallest node using subtree size information */
BS_Tree *find_kth_min_data(BS_Tree *root, int k) {
    if (root == NULL) return NULL;
    int left_size = (root->left != NULL) ? root->left->sub_node_count : 0;
    if (k <= left_size) {
        /* 答案在左子樹 / answer lies in the left subtree */
        return find_kth_min_data(root->left, k);
    } else if (k == left_size + 1) {
        /* 當前節點即為第 k 小 / current node is the k-th smallest */
        return root;
    } else {
        /* 答案在右子樹，k 需扣掉左子樹和根 / answer in right subtree; adjust k by subtracting left size and root */
        return find_kth_min_data(root->right, k - left_size - 1);
    }
}

/* 將 data 插入 BST，回傳根節點 / insert data into BST, return root node */
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

/* 以後序走訪方式計算各節點的子樹大小 / compute subtree sizes for all nodes using postorder traversal */
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

/* 釋放整棵樹的記憶體 / free all memory of the entire tree */
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

    /* 讀取第一行的整數，建立 BST / read first-line integers and build the BST */
    do {
        if (scanf("%d", &data) != 1) break;
        root = insert_sort_BS_Tree(root, data);
    } while (getchar() != '\n');

    /* 計算各節點子樹大小 / compute subtree sizes for all nodes */
    insert_sub_node_count(root);

    /* 讀取第二行的查詢，逐一輸出第 k 小的值 / read second-line queries and print the k-th smallest value for each */
    do {
        if (scanf("%d", &k) != 1) break;
        ptr_kth_min = find_kth_min_data(root, k);
        printf("%d\n", ptr_kth_min->data);
    } while (getchar() != '\n');

    root = delete_BS_Tree(root);
    return 0;
}
