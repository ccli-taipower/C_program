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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入木板尺寸 W×H 及 3 種可販售零件尺寸（sell_w[i], sell_h[i]）。
 * 2. 將記憶化陣列 memo[w][h] 全部初始化為 -1。
 * 3. 呼叫 min_waste(W, H)，以遞迴求切割 W×H 木板的最小廢料面積。
 * 4. 遞迴基底：若 w<=0 或 h<=0 回傳 0；若 memo[w][h] != -1 直接回傳快取值。
 * 5. 對每種可販售尺寸 (wi, hi)：若 w==wi 且 h==hi，直接回傳 0（整塊可賣）。
 * 6. 若 wi<=w 且 hi<=h，嘗試兩種切割方式：
 *    切法一：水平切割，廢料 = min_waste(w, h-hi) + min_waste(w-wi, hi)；
 *    切法二：垂直切割，廢料 = min_waste(w-wi, h) + min_waste(wi, h-hi)。
 * 7. 取所有切割方式中的最小廢料；若沒有任何可販售尺寸能放入，廢料為 w*h。
 * 8. 將結果存入 memo[w][h]；最終輸出 W*H - min_waste(W, H) 即最大利潤。
 *
 * English:
 * 1. Read board dimensions W×H and the 3 saleable piece sizes (sell_w[i], sell_h[i]).
 * 2. Initialize the memoization array memo[w][h] to -1.
 * 3. Call min_waste(W, H) to recursively compute the minimum waste for cutting W×H.
 * 4. Base cases: return 0 if w<=0 or h<=0; return cached value if memo[w][h] != -1.
 * 5. For each saleable size (wi, hi): if w==wi and h==hi, return 0 (entire board sold).
 * 6. If wi<=w and hi<=h, try two cut orientations:
 *    Cut 1 (horizontal): waste = min_waste(w, h-hi) + min_waste(w-wi, hi);
 *    Cut 2 (vertical):   waste = min_waste(w-wi, h) + min_waste(wi, h-hi).
 * 7. Take the minimum waste across all cuts; if no piece fits, waste equals w*h.
 * 8. Store result in memo[w][h]; output W*H - min_waste(W, H) as the maximum profit.
 */
#include <stdio.h>
#include <string.h>

#define MAXDIM 33   /* 木板最大尺寸 + 1（0..32） / max board dimension + 1 (0..32) */
#define NSIZES 3    /* 可販售尺寸的數量 / number of saleable sizes */
#define INF 99999   /* 無窮大（代表尚未計算或極大廢料） / infinity (placeholder for uncalculated or very large waste) */

static int sell_w[NSIZES];  /* 可販售尺寸的寬度 / width of each saleable piece */
static int sell_h[NSIZES];  /* 可販售尺寸的高度 / height of each saleable piece */
static int memo[MAXDIM][MAXDIM];  /* memo[w][h] = min_waste(w, h)，-1 表示未計算 / -1 means not yet computed */

/* 遞迴計算切割 w×h 木板的最小廢料面積 / recursively compute the minimum waste area for cutting a w×h board */
static int min_waste(int w, int h) {
    int i, best, w1, cut_style;

    /* 無效尺寸：無廢料 / invalid dimensions: no waste */
    if (w <= 0 || h <= 0) return 0;

    /* 若已計算過，直接回傳記憶的結果 / return cached result if already computed */
    if (memo[w][h] != -1) return memo[w][h];

    /* 先假設找不到任何可販售尺寸，全部浪費 / assume no piece fits; initialize best to INF */
    best = INF;

    /* 嘗試每種可販售尺寸作為切割參考 / try each saleable size as a cutting reference */
    for (i = 0; i < NSIZES; i++) {
        int wi = sell_w[i];
        int hi = sell_h[i];

        /* 若 (w, h) 恰好等於此可販售尺寸：廢料為 0 / if (w,h) exactly matches this piece: zero waste */
        if (w == wi && h == hi) {
            memo[w][h] = 0;
            return 0;
        }

        /* 此可販售尺寸必須能放入 w×h 木板 / skip if this piece doesn't fit in the w×h board */
        if (wi > w || hi > h) continue;

        /* 切割方式 1：先水平切割（高度方向），切掉上方 h-hi 部分 / cut 1: horizontal cut, remove top h-hi rows
         *   左下 w×(h-hi) 的廢料 + 右上 (w-wi)×hi 的廢料 / waste from bottom-left w×(h-hi) + top-right (w-wi)×hi */
        w1 = min_waste(w, h - hi) + min_waste(w - wi, hi);
        if (w1 < best) best = w1;

        /* 切割方式 2：先垂直切割（寬度方向），切掉右方 w-wi 部分 / cut 2: vertical cut, remove right w-wi columns
         *   右邊 (w-wi)×h 的廢料 + 左下 wi×(h-hi) 的廢料 / waste from right (w-wi)×h + bottom-left wi×(h-hi) */
        w1 = min_waste(w - wi, h) + min_waste(wi, h - hi);
        if (w1 < best) best = w1;
    }

    /* 若無任何可販售尺寸能放入，整塊木板全部浪費 / if no piece fits, the entire board is waste */
    if (best == INF) best = w * h;

    memo[w][h] = best;
    return best;
}

int main(void) {
    int W, H, i;

    /* 讀入木板尺寸 / read board dimensions */
    if (scanf("%d %d", &W, &H) != 2) return 0;

    /* 讀入 3 種可販售尺寸 / read 3 saleable piece sizes */
    for (i = 0; i < NSIZES; i++) {
        if (scanf("%d %d", &sell_w[i], &sell_h[i]) != 2) return 0;
    }

    /* 初始化記憶化陣列（-1 表示尚未計算） / initialize memoization array (-1 = not yet computed) */
    memset(memo, -1, sizeof(memo));

    /* 輸出最大利潤 = 總面積 - 最小廢料 / print max profit = total area - minimum waste */
    printf("%d\n", W * H - min_waste(W, H));

    return 0;
}
