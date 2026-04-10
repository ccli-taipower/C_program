/*
 * NTHU EE2310 - 題目 14878: Tiling an L-Shaped Board with L-Trominoes
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 11 章（遞迴）
 *   如果不知道如何解題，請參考課本第 11 章的說明。
 *
 * 【題目說明】
 * 給定一個 l×l 的正方形，右上角有一個 m×m 的缺口（L 型板）。
 * l 和 m 均為 2 的冪次方，1 ≤ m < l ≤ 64。
 * 用 L 型三格骨牌（L-tromino）鋪滿整塊 L 型板。
 *
 * 【L 型三格骨牌的類型】（依 2×2 邊界框中缺失格的位置）
 *   類型 1：缺失格在右上 (UPPER-RIGHT)
 *   類型 2：缺失格在左上 (UPPER-LEFT)
 *   類型 3：缺失格在左下 (LOWER-LEFT)
 *   類型 4：缺失格在右下 (LOWER-RIGHT)
 * 每個骨牌輸出格式：「類型 中心x 中心y」
 * 其中 (中心x, 中心y) 是 2×2 邊界框的右上角格座標。
 *
 * 【遞迴演算法】
 *
 * tile_deficient(x, y, size, dx, dy)：
 *   鋪滿一個左下角在 (x,y)、大小為 size×size 的正方形，
 *   其中格 (dx, dy) 已被佔用（缺損格）。
 *   做法：將正方形分成四個子象限，在中心放置一個 L 型骨牌
 *   覆蓋不含缺損格的三個子象限的內角，再對四個子象限各自遞迴。
 *
 * tile_L(x, y, l, m)：
 *   鋪滿 L 型板（l×l 正方形去掉右上角 m×m 缺口），左下角在 (x,y)。
 *   在中心放置類型 1 骨牌，覆蓋左下、右下、左上三個子象限的內角，
 *   右上子象限若 l == 2m 則完全是缺口（不鋪），
 *   若 l > 2m 則為更小的 L 型板，遞迴呼叫 tile_L 處理。
 */
#include <stdio.h>

/* 鋪滿一個 size×size 的缺損正方形（左下角在 (x,y)，缺損格在 (dx,dy)）
 * 共輸出 (size*size - 1) / 3 個 L 型骨牌 */
static void tile_deficient(int x, int y, int size, int dx, int dy) {
    int half, cx, cy;
    int mid, mjd;
    int in_LL, in_LR, in_UL, in_UR;
    int type;
    int LLx, LLy, LRx, LRy, ULx, ULy, URx, URy;

    if (size <= 1) return;  /* 大小為 1 時無需鋪設 */

    if (size == 2) {
        /* 基底情況：2×2 正方形，直接輸出一個 L 型骨牌 */
        cx = x + 1;
        cy = y + 1;
        if      (dx == x     && dy == y    ) type = 3; /* 缺失格在左下 */
        else if (dx == x + 1 && dy == y    ) type = 4; /* 缺失格在右下 */
        else if (dx == x     && dy == y + 1) type = 2; /* 缺失格在左上 */
        else                                  type = 1; /* 缺失格在右上 */
        printf("%d %d %d\n", type, cx, cy);
        return;
    }

    /* 計算子象限分割點與中心格 */
    half = size / 2;
    cx = x + half;
    cy = y + half;
    mid = x + half;
    mjd = y + half;

    /* 判斷缺損格位於哪個子象限 */
    in_LL = (dx <  mid && dy <  mjd);  /* 左下子象限 */
    in_LR = (dx >= mid && dy <  mjd);  /* 右下子象限 */
    in_UL = (dx <  mid && dy >= mjd);  /* 左上子象限 */
    in_UR = (dx >= mid && dy >= mjd);  /* 右上子象限 */

    /* 在中心放置 L 型骨牌，讓含有缺損格的子象限的內角保持空白 */
    if      (in_LL) type = 3; /* 左下已有缺損，骨牌覆蓋其他三個內角 */
    else if (in_LR) type = 4; /* 右下已有缺損 */
    else if (in_UL) type = 2; /* 左上已有缺損 */
    else            type = 1; /* 右上已有缺損 */
    printf("%d %d %d\n", type, cx, cy);

    /* 決定各子象限的缺損格位置
     * 含原始缺損格的子象限：使用原始 (dx, dy)
     * 其他子象限：使用中心骨牌所覆蓋的內角格 */
    LLx = in_LL ? dx : cx - 1;  LLy = in_LL ? dy : cy - 1;
    LRx = in_LR ? dx : cx;      LRy = in_LR ? dy : cy - 1;
    ULx = in_UL ? dx : cx - 1;  ULy = in_UL ? dy : cy;
    URx = in_UR ? dx : cx;      URy = in_UR ? dy : cy;

    /* 遞迴鋪滿四個子象限 */
    tile_deficient(x,        y,        half, LLx, LLy);  /* 左下 */
    tile_deficient(x + half, y,        half, LRx, LRy);  /* 右下 */
    tile_deficient(x,        y + half, half, ULx, ULy);  /* 左上 */
    tile_deficient(x + half, y + half, half, URx, URy);  /* 右上 */
}

/* 鋪滿 L 型板（l×l 正方形去掉右上角 m×m 缺口），左下角在 (x,y) */
static void tile_L(int x, int y, int l, int m) {
    int half = l / 2;
    int cx = x + half;
    int cy = y + half;

    /* 在中心放置類型 1 骨牌（缺失格在右上，即保留 (cx, cy) 給右上子象限）
     * 此骨牌覆蓋左下、右下、左上三個子象限各自的右上內角格 */
    printf("1 %d %d\n", cx, cy);

    /* 遞迴鋪滿左下、右下、左上三個子象限（各為缺損正方形） */
    tile_deficient(x,        y,        half, cx - 1, cy - 1);  /* 左下象限，缺損在右上內角 */
    tile_deficient(x + half, y,        half, cx,     cy - 1);  /* 右下象限，缺損在左上內角 */
    tile_deficient(x,        y + half, half, cx - 1, cy);      /* 左上象限，缺損在右下內角 */

    /* 處理右上子象限 */
    if (l > 2 * m) {
        /* 右上子象限為更小的 L 型板 L(half, m)，遞迴鋪滿 */
        tile_L(x + half, y + half, half, m);
    }
    /* 若 l == 2m，右上子象限完全是缺口，不需鋪設 */
}

int main(void) {
    int l, m;  /* L 型板的尺寸參數 */

    if (scanf("%d %d", &l, &m) != 2) return 0;

    /* 從左下角 (0, 0) 開始鋪滿整個 L 型板 */
    tile_L(0, 0, l, m);

    return 0;
}
