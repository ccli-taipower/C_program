/*
 * NTHU EE2310 - 題目 14791: Combination Sum
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14791/
 *
 * 【題目說明】
 * 計算 C(n,0) + C(n,1) + C(n,2) + ... + C(n,m) 的總和。
 * 其中 C(n,k) = n! / (k! * (n-k)!) 為二項式係數。
 * 輸入：兩個整數 n 和 m（0 < n < 15, 0 < m ≤ n）
 * 輸出：總和
 *
 * 範例：n=5, m=2 → C(5,0)+C(5,1)+C(5,2) = 1+5+10 = 16
 *
 * 【解題策略】
 * 實作函式 C(n, k) 計算二項式係數，
 * 在 main 中對 k=0 到 m 累加求和。
 * n < 15，數值不大，直接計算不需擔心溢位（int 即可）。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入 n 和 m 兩個整數。
 * 2. 初始化累加器 total = 0。
 * 3. 迴圈 k 從 0 到 m，每次呼叫 C(n, k) 並累加到 total。
 * 4. C(n, k) 函式的實作：
 *    a. 利用對稱性 C(n,k) = C(n,n-k)，若 k > n-k 則令 k = n-k，
 *       確保後續迴圈次數盡可能少。
 *    b. 以逐步相乘再相除的方式計算：
 *       result = result * (n-i) / (i+1)，i 從 0 到 k-1。
 *       此方式在每一步都整除，避免中間值溢位。
 *    c. 返回最終結果 result。
 * 5. 輸出 total。
 *
 * English:
 * 1. Read integers n and m.
 * 2. Initialize accumulator total = 0.
 * 3. Loop k from 0 to m, calling C(n, k) and adding the result to total.
 * 4. Implementation of C(n, k):
 *    a. Apply symmetry: if k > n-k, set k = n-k to minimize iterations.
 *    b. Compute iteratively: result = result * (n-i) / (i+1) for i = 0..k-1.
 *       This ensures integer division is exact at each step, preventing
 *       intermediate overflow.
 *    c. Return result.
 * 5. Print total.
 */
#include <stdio.h>

/* 計算二項式係數 C(n, k) / compute binomial coefficient C(n, k) */
int C(int n, int k) {
    int i;
    int result;

    /* 利用對稱性：C(n,k) = C(n, n-k) / use symmetry: C(n,k) = C(n, n-k) */
    if (k > n - k)
        k = n - k;

    result = 1;

    /* 逐步計算，避免中間值過大：result = n*(n-1)*...*(n-k+1) / k! / iterative computation to avoid large intermediate values */
    for (i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }

    return result;
}

int main(void) {
    int n, m;
    int k, total;

    /* 讀入 n 和 m / read n and m */
    scanf("%d %d", &n, &m);

    /* 累加 C(n,0) 到 C(n,m) / accumulate C(n,0) through C(n,m) */
    total = 0;
    for (k = 0; k <= m; k++)
        total += C(n, k);

    printf("%d\n", total);

    return 0;
}
