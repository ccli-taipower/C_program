/*
 * NTHU EE2310 - 題目 14829: Max Profit Cutting
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 15 章（遞迴）
 *   如果不知道如何解題，請參考課本第 15 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14829/
 *
 * 【題目說明】
 * 將一塊 w×h 的木板切割成可販售的零件以最大化總利潤。
 *   - 共有 3 種可販售尺寸（不可旋轉，因紋理方向影響品質）。
 *   - 每種零件的售價 = 其寬 × 高。
 *   - 輸出最大利潤 = w*h - 最小廢料面積。
 *
 * 範例：5 7，可販售尺寸 [(2,3),(3,4),(5,2)] → 輸出 32
 *
 * 【解題策略（min_waste 遞迴）】
 * min_waste(w, h) 回傳切割 w×h 木板的最小廢料面積：
 *   - 若 w<=0 或 h<=0：回傳 0（無效尺寸，無廢料）
 *   - 若 (w,h) 恰好是某個可販售尺寸：回傳 0（整塊可賣，無廢料）
 *   - 對每種可販售尺寸 (wi, hi)（wi<=w 且 hi<=h）：
 *       切割方式 1：先水平切割（切掉高度 h-hi）
 *                   waste = min_waste(w, h-hi) + min_waste(w-wi, hi)
 *       切割方式 2：先垂直切割（切掉寬度 w-wi）
 *                   waste = min_waste(w-wi, h) + min_waste(wi, h-hi)
 *   - 若無任何可販售尺寸能放入，回傳 w*h（全部浪費）
 *   - 取所有切割方式中的最小廢料
 * 使用記憶化（memo[w][h]，0≤w,h≤32）避免重複計算。
 */
#include <stdio.h>
#include <string.h>

#define MAXDIM 33   /* 木板最大尺寸 + 1（0..32） */
#define NSIZES 3    /* 可販售尺寸的數量 */
#define INF 99999   /* 無窮大（代表尚未計算或極大廢料） */

static int sell_w[NSIZES];  /* 可販售尺寸的寬度 */
static int sell_h[NSIZES];  /* 可販售尺寸的高度 */
static int memo[MAXDIM][MAXDIM];  /* memo[w][h] = min_waste(w, h)，-1 表示未計算 */

/* 遞迴計算切割 w×h 木板的最小廢料面積 */
static int min_waste(int w, int h) {
    int i, best, w1, cut_style;

    /* 無效尺寸：無廢料 */
    if (w <= 0 || h <= 0) return 0;

    /* 若已計算過，直接回傳記憶的結果 */
    if (memo[w][h] != -1) return memo[w][h];

    /* 先假設找不到任何可販售尺寸，全部浪費 */
    best = INF;

    /* 嘗試每種可販售尺寸作為切割參考 */
    for (i = 0; i < NSIZES; i++) {
        int wi = sell_w[i];
        int hi = sell_h[i];

        /* 若 (w, h) 恰好等於此可販售尺寸：廢料為 0 */
        if (w == wi && h == hi) {
            memo[w][h] = 0;
            return 0;
        }

        /* 此可販售尺寸必須能放入 w×h 木板 */
        if (wi > w || hi > h) continue;

        /* 切割方式 1：先水平切割（高度方向），切掉上方 h-hi 部分
         *   左下 w×(h-hi) 的廢料 + 右上 (w-wi)×hi 的廢料 */
        w1 = min_waste(w, h - hi) + min_waste(w - wi, hi);
        if (w1 < best) best = w1;

        /* 切割方式 2：先垂直切割（寬度方向），切掉右方 w-wi 部分
         *   右邊 (w-wi)×h 的廢料 + 左下 wi×(h-hi) 的廢料 */
        w1 = min_waste(w - wi, h) + min_waste(wi, h - hi);
        if (w1 < best) best = w1;
    }

    /* 若無任何可販售尺寸能放入，整塊木板全部浪費 */
    if (best == INF) best = w * h;

    memo[w][h] = best;
    return best;
}

int main(void) {
    int W, H, i;

    /* 讀入木板尺寸 */
    if (scanf("%d %d", &W, &H) != 2) return 0;

    /* 讀入 3 種可販售尺寸 */
    for (i = 0; i < NSIZES; i++) {
        if (scanf("%d %d", &sell_w[i], &sell_h[i]) != 2) return 0;
    }

    /* 初始化記憶化陣列（-1 表示尚未計算） */
    memset(memo, -1, sizeof(memo));

    /* 輸出最大利潤 = 總面積 - 最小廢料 */
    printf("%d\n", W * H - min_waste(W, H));

    return 0;
}
