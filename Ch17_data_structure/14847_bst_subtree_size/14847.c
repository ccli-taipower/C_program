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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 從標準輸入逐一讀取整數，呼叫迭代版 insert() 將其插入 BST（重複值往右子樹）。
 * 2. 讀到換行或 EOF 時停止讀入，此時已建好完整的 BST。
 * 3. 呼叫 calc_size_iterative()：以兩個顯式堆疊模擬後序走訪，由葉節點向上計算每個節點的子樹大小（size = 1 + 左子樹大小 + 右子樹大小）。
 * 4. 呼叫 inorder_print_iterative()：以一個顯式堆疊模擬中序走訪（左→根→右），依序輸出每個節點的 "值 子樹大小"。
 * 5. 呼叫 free_tree() 釋放所有動態配置的記憶體，避免記憶體洩漏。
 * 6. 全程避免遞迴，確保在樹深達 100,000 時不發生堆疊溢位。
 *
 * English:
 * 1. Read integers one by one from stdin; call the iterative insert() to add each into the BST (duplicates go to the right subtree).
 * 2. Stop reading when a newline or EOF is encountered; the complete BST is now built.
 * 3. Call calc_size_iterative(): use two explicit stacks to simulate postorder traversal, computing each node's subtree size bottom-up (size = 1 + left_size + right_size).
 * 4. Call inorder_print_iterative(): use one explicit stack to simulate inorder traversal (left→root→right), printing "value subtree_size" for each node.
 * 5. Call free_tree() to release all dynamically allocated memory, preventing memory leaks.
 * 6. All traversals are iterative to avoid stack overflow when tree depth reaches 100,000.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    int size;            /* 以此節點為根的子樹大小 / subtree size rooted at this node */
    struct Node *left;
    struct Node *right;
    struct Node *parent; /* 父節點指標，供迭代後序走訪使用 / parent pointer, used by iterative postorder traversal */
} Node;

/* 建立新節點 / create a new node */
static Node *new_node(int v) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->val   = v;
    p->size  = 1;
    p->left  = p->right = p->parent = NULL;
    return p;
}

/* 迭代插入（避免遞迴深度過深） / iterative insert (avoids deep recursion stack) */
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

/* 迭代後序走訪，計算各節點子樹大小 / iterative postorder traversal to compute subtree sizes */
static void calc_size_iterative(Node *root) {
    if (root == NULL) return;

    /* 使用兩個陣列模擬後序走訪的堆疊 / use two arrays to simulate postorder traversal stacks */
    Node **stack1 = (Node **)malloc(200001 * sizeof(Node *));
    Node **stack2 = (Node **)malloc(200001 * sizeof(Node *));
    int top1 = 0, top2 = 0;

    stack1[top1++] = root;

    /* 用類似前序走訪（根→右→左）產生後序走訪的逆序 / simulate root→right→left traversal to produce reverse postorder */
    while (top1 > 0) {
        Node *cur = stack1[--top1];
        stack2[top2++] = cur;

        if (cur->left)  stack1[top1++] = cur->left;
        if (cur->right) stack1[top1++] = cur->right;
    }

    /* stack2 中的順序即為後序走訪，由尾到頭計算子樹大小 / stack2 holds postorder sequence; compute subtree sizes from tail to head */
    while (top2 > 0) {
        Node *cur = stack2[--top2];
        int ls = cur->left  ? cur->left->size  : 0;
        int rs = cur->right ? cur->right->size : 0;
        cur->size = 1 + ls + rs;
    }

    free(stack1);
    free(stack2);
}

/* 迭代中序走訪，輸出各節點的值和子樹大小 / iterative inorder traversal, print each node's value and subtree size */
static void inorder_print_iterative(Node *root) {
    Node **stack = (Node **)malloc(200001 * sizeof(Node *));
    int top = 0;
    Node *cur = root;

    while (cur != NULL || top > 0) {
        /* 一直往左走，沿途壓入堆疊 / keep going left, pushing nodes onto the stack */
        while (cur != NULL) {
            stack[top++] = cur;
            cur = cur->left;
        }
        /* 取出節點並輸出 / pop a node and print it */
        cur = stack[--top];
        printf("%d %d\n", cur->val, cur->size);
        /* 轉往右子樹 / move to right subtree */
        cur = cur->right;
    }

    free(stack);
}

/* 迭代釋放整棵樹 / iteratively free the entire tree */
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

    /* 讀取整數直到行尾或 EOF，依序插入 BST / read integers until end of line or EOF, insert each into BST */
    while (scanf("%d", &v) == 1) {
        root = insert(root, v);
        c = getchar();
        if (c == '\n' || c == EOF) break;
        ungetc(c, stdin);
    }

    /* 計算各節點子樹大小（迭代後序走訪） / compute subtree sizes via iterative postorder traversal */
    calc_size_iterative(root);

    /* 中序走訪輸出結果 / print results via inorder traversal */
    inorder_print_iterative(root);

    free_tree(root);
    return 0;
}
