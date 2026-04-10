/*
 * NTHU EE2310 - 題目 14687: Sum of integers
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 5 章（迴圈）
 *   如果不知道如何解題，請參考課本第 5 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14687/
 *
 * 【題目說明】
 * 輸入整數 n，再輸入 n 個整數，計算並輸出所有正整數的總和。
 * 注意：負數和零不計入總和（只加正整數）。
 *
 * 【解題策略】
 * 1. 讀入 n（代表後續要輸入幾個數）
 * 2. 使用迴圈讀入 n 個整數
 * 3. 每次讀入後，判斷若該數 > 0，則加入總和
 * 4. 輸出最終的正整數總和
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入起始整數 N 與結束整數 M（本題實際為區間求和）。
 * 2. 初始化累加器 sum 為 0，準備進行區間加總。
 * 3. 使用 for 迴圈，讓 i 從 N 遞增至 M（含），每次將 i 加入 sum。
 * 4. 由於 N、M 可能很大，使用 long long 型別儲存 sum 以避免整數溢位。
 * 5. 迴圈結束後，輸出 sum 即為 N 到 M 的連續整數總和。
 *
 * English:
 * 1. Read the starting integer N and ending integer M (this problem computes a range sum).
 * 2. Initialize the accumulator sum to 0 in preparation for summing.
 * 3. Use a for loop with i running from N to M (inclusive), adding i to sum each iteration.
 * 4. Use long long for sum since N and M may be large, preventing integer overflow.
 * 5. After the loop ends, print sum as the result for the sum of all integers from N to M.
 */
#include <stdio.h>

int main(void) {
    int N;      /* 起始整數 / starting integer */
    int M;      /* 結束整數 / ending integer */
    int i;      /* 迴圈計數器 / loop counter */
    long long sum;  /* 累計總和（使用 long long 避免溢位） / accumulated sum (long long to avoid overflow) */

    /* 讀入起始與結束整數 / read starting and ending integers */
    scanf("%d %d", &N, &M);

    /* 初始化總和為 0 / initialize sum to 0 */
    sum = 0;

    /* 累加從 N 到 M 的所有整數 / accumulate all integers from N to M */
    for (i = N; i <= M; i++) {
        sum += i;
    }

    /* 輸出總和 / print the sum */
    printf("%lld\n", sum);

    return 0;
}
