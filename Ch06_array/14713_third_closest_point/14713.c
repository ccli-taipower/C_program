/*
 * NTHU EE2310 - 題目 14713: Third Closest Point
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14713/
 *
 * 【題目說明】
 * 給定 n 個三維點（n 最多 1,000,000），以串流方式讀入，
 * 找出距原點第三近的點的 1-based 索引。
 *
 * 【解題策略】
 * 由於 n 可能極大，不儲存所有點，只保留最近的前三名。
 * 維護三個變數：(top1_dist, top1_idx)、(top2_dist, top2_idx)、(top3_dist, top3_idx)。
 * 每讀入一個點，計算其距離平方（避免開平方），與前三名比較並更新。
 * 距離相同時，索引較小者優先（索引越小排越前面）。
 * 最後輸出 top3_idx。
 *
 * 注意：使用距離平方比較，避免浮點開方的精度問題，
 * 但輸入為 double，所以距離平方也用 double。
 */
#include <stdio.h>
#include <float.h>

int main(void) {
    int n, i;
    double x, y, z, d;

    double top1_dist, top2_dist, top3_dist; /* 前三名的距離平方 */
    int    top1_idx,  top2_idx,  top3_idx;  /* 前三名的 1-based 索引 */

    /* 初始化：距離設為最大值，索引設為 0（尚未有點） */
    top1_dist = DBL_MAX; top1_idx = 0;
    top2_dist = DBL_MAX; top2_idx = 0;
    top3_dist = DBL_MAX; top3_idx = 0;

    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        scanf("%lf %lf %lf", &x, &y, &z);
        d = x * x + y * y + z * z; /* 距離平方 */

        /* 判斷是否擠進前三名 */
        if (d < top1_dist || (d == top1_dist && i < top1_idx)) {
            /* 新點成為第一名，第一名降為第二，第二名降為第三 */
            top3_dist = top2_dist; top3_idx = top2_idx;
            top2_dist = top1_dist; top2_idx = top1_idx;
            top1_dist = d;         top1_idx = i;
        } else if (d < top2_dist || (d == top2_dist && i < top2_idx)) {
            /* 新點成為第二名，第二名降為第三 */
            top3_dist = top2_dist; top3_idx = top2_idx;
            top2_dist = d;         top2_idx = i;
        } else if (d < top3_dist || (d == top3_dist && i < top3_idx)) {
            /* 新點成為第三名 */
            top3_dist = d;         top3_idx = i;
        }
    }

    printf("%d\n", top3_idx);

    return 0;
}
