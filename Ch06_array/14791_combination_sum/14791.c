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
 */
#include <stdio.h>

/* 計算二項式係數 C(n, k) */
int C(int n, int k) {
    int i;
    int result;

    /* 利用對稱性：C(n,k) = C(n, n-k) */
    if (k > n - k)
        k = n - k;

    result = 1;

    /* 逐步計算，避免中間值過大：result = n*(n-1)*...*(n-k+1) / k! */
    for (i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }

    return result;
}

int main(void) {
    int n, m;
    int k, total;

    /* 讀入 n 和 m */
    scanf("%d %d", &n, &m);

    /* 累加 C(n,0) 到 C(n,m) */
    total = 0;
    for (k = 0; k <= m; k++)
        total += C(n, k);

    printf("%d\n", total);

    return 0;
}
