/*
 * NTHU EE2310 - 題目 14878: Tiling an L-Shaped Board with L-Trominoes
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 15 章（遞迴）
 *   如果不知道如何解題，請參考課本第 15 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14878/
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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入 l 和 m；呼叫 tile_L(0, 0, l, m) 從左下角 (0,0) 開始鋪滿整個 L 型板。
 * 2. tile_L 在中心放一個類型 1 的骨牌（缺失格朝右上），保留右上角給缺口；
 *    此骨牌的三個格分別成為左下、右下、左上三個子象限的缺損格。
 * 3. 對左下、右下、左上三個子象限各呼叫 tile_deficient 遞迴鋪滿。
 * 4. 若 l > 2m，右上子象限為更小的 L 型板，遞迴呼叫 tile_L；若 l == 2m，右上為全缺口，跳過。
 * 5. tile_deficient(x, y, size, dx, dy)：基底情況 size==1 直接返回；size==2 直接輸出骨牌類型。
 * 6. 對更大的 size，計算四個子象限及中心位置，判斷缺損格在哪個子象限：
 *    在中心放骨牌類型（讓缺損格所在的子象限內角保持空白，其餘三個內角被骨牌佔用），
 *    再對四個子象限各自遞迴，各子象限的缺損格為中心骨牌佔用的對應內角。
 * 7. 每個骨牌輸出格式為「類型 中心x 中心y」。
 *
 * English:
 * 1. Read l and m; call tile_L(0, 0, l, m) to tile the entire L-shaped board starting
 *    from the lower-left corner (0, 0).
 * 2. tile_L places a type-1 tromino at the center (missing cell toward upper-right),
 *    reserving the upper-right corner for the cutout; the tromino's three cells become
 *    the deficient cells for the lower-left, lower-right, and upper-left sub-quadrants.
 * 3. Recursively call tile_deficient for the three non-cutout sub-quadrants.
 * 4. If l > 2m, the upper-right sub-quadrant is a smaller L-shaped board; recurse with
 *    tile_L. If l == 2m, the upper-right sub-quadrant is the full cutout; skip it.
 * 5. tile_deficient(x, y, size, dx, dy): base case size==1 returns immediately;
 *    size==2 directly prints the tromino type based on which cell is deficient.
 * 6. For larger size, compute four sub-quadrants and the center; identify which
 *    sub-quadrant contains the defect, place a center tromino leaving that sub-quadrant's
 *    inner corner free, then recurse on all four sub-quadrants with each sub-quadrant's
 *    deficient cell being the center tromino's corresponding covered corner.
 * 7. Each tromino is printed as "type centerX centerY".
 */
#include <stdio.h>

/* 鋪滿一個 size×size 的缺損正方形（左下角在 (x,y)，缺損格在 (dx,dy)） / tile a size×size deficient square (lower-left at (x,y), deficient cell at (dx,dy))
 * 共輸出 (size*size - 1) / 3 個 L 型骨牌 / outputs (size*size - 1)/3 L-trominoes in total */
static void tile_deficient(int x, int y, int size, int dx, int dy) {
    int half, cx, cy;
    int mid, mjd;
    int in_LL, in_LR, in_UL, in_UR;
    int type;
    int LLx, LLy, LRx, LRy, ULx, ULy, URx, URy;

    if (size <= 1) return;  /* 大小為 1 時無需鋪設 / size 1 needs no tiling */

    if (size == 2) {
        /* 基底情況：2×2 正方形，直接輸出一個 L 型骨牌 / base case: 2×2 square, print one L-tromino directly */
        cx = x + 1;
        cy = y + 1;
        if      (dx == x     && dy == y    ) type = 3; /* 缺失格在左下 / missing cell at lower-left */
        else if (dx == x + 1 && dy == y    ) type = 4; /* 缺失格在右下 / missing cell at lower-right */
        else if (dx == x     && dy == y + 1) type = 2; /* 缺失格在左上 / missing cell at upper-left */
        else                                  type = 1; /* 缺失格在右上 / missing cell at upper-right */
        printf("%d %d %d\n", type, cx, cy);
        return;
    }

    /* 計算子象限分割點與中心格 / compute sub-quadrant split point and center cell */
    half = size / 2;
    cx = x + half;
    cy = y + half;
    mid = x + half;
    mjd = y + half;

    /* 判斷缺損格位於哪個子象限 / determine which sub-quadrant contains the deficient cell */
    in_LL = (dx <  mid && dy <  mjd);  /* 左下子象限 / lower-left sub-quadrant */
    in_LR = (dx >= mid && dy <  mjd);  /* 右下子象限 / lower-right sub-quadrant */
    in_UL = (dx <  mid && dy >= mjd);  /* 左上子象限 / upper-left sub-quadrant */
    in_UR = (dx >= mid && dy >= mjd);  /* 右上子象限 / upper-right sub-quadrant */

    /* 在中心放置 L 型骨牌，讓含有缺損格的子象限的內角保持空白 / place center tromino, leaving the inner corner of the deficient sub-quadrant free */
    if      (in_LL) type = 3; /* 左下已有缺損，骨牌覆蓋其他三個內角 / LL has defect; tromino covers the other three inner corners */
    else if (in_LR) type = 4; /* 右下已有缺損 / LR has defect */
    else if (in_UL) type = 2; /* 左上已有缺損 / UL has defect */
    else            type = 1; /* 右上已有缺損 / UR has defect */
    printf("%d %d %d\n", type, cx, cy);

    /* 決定各子象限的缺損格位置 / determine the deficient cell for each sub-quadrant
     * 含原始缺損格的子象限：使用原始 (dx, dy) / sub-quadrant with original defect: use (dx, dy)
     * 其他子象限：使用中心骨牌所覆蓋的內角格 / other sub-quadrants: use the inner corner covered by the center tromino */
    LLx = in_LL ? dx : cx - 1;  LLy = in_LL ? dy : cy - 1;
    LRx = in_LR ? dx : cx;      LRy = in_LR ? dy : cy - 1;
    ULx = in_UL ? dx : cx - 1;  ULy = in_UL ? dy : cy;
    URx = in_UR ? dx : cx;      URy = in_UR ? dy : cy;

    /* 遞迴鋪滿四個子象限 / recursively tile all four sub-quadrants */
    tile_deficient(x,        y,        half, LLx, LLy);  /* 左下 / lower-left */
    tile_deficient(x + half, y,        half, LRx, LRy);  /* 右下 / lower-right */
    tile_deficient(x,        y + half, half, ULx, ULy);  /* 左上 / upper-left */
    tile_deficient(x + half, y + half, half, URx, URy);  /* 右上 / upper-right */
}

/* 鋪滿 L 型板（l×l 正方形去掉右上角 m×m 缺口），左下角在 (x,y) / tile the L-shaped board (l×l minus upper-right m×m cutout), lower-left at (x,y) */
static void tile_L(int x, int y, int l, int m) {
    int half = l / 2;
    int cx = x + half;
    int cy = y + half;

    /* 在中心放置類型 1 骨牌（缺失格在右上，即保留 (cx, cy) 給右上子象限） / place type-1 tromino at center (missing cell at upper-right, reserving (cx,cy) for the upper-right sub-quadrant)
     * 此骨牌覆蓋左下、右下、左上三個子象限各自的右上內角格 / this tromino covers the upper-right inner corner of the LL, LR, and UL sub-quadrants */
    printf("1 %d %d\n", cx, cy);

    /* 遞迴鋪滿左下、右下、左上三個子象限（各為缺損正方形） / recursively tile the LL, LR, UL sub-quadrants (each is a deficient square) */
    tile_deficient(x,        y,        half, cx - 1, cy - 1);  /* 左下象限，缺損在右上內角 / LL sub-quadrant, defect at upper-right inner corner */
    tile_deficient(x + half, y,        half, cx,     cy - 1);  /* 右下象限，缺損在左上內角 / LR sub-quadrant, defect at upper-left inner corner */
    tile_deficient(x,        y + half, half, cx - 1, cy);      /* 左上象限，缺損在右下內角 / UL sub-quadrant, defect at lower-right inner corner */

    /* 處理右上子象限 / handle the upper-right sub-quadrant */
    if (l > 2 * m) {
        /* 右上子象限為更小的 L 型板 L(half, m)，遞迴鋪滿 / upper-right sub-quadrant is a smaller L-board L(half, m); recurse */
        tile_L(x + half, y + half, half, m);
    }
    /* 若 l == 2m，右上子象限完全是缺口，不需鋪設 / if l == 2m, upper-right sub-quadrant is entirely the cutout; skip */
}

int main(void) {
    int l, m;  /* L 型板的尺寸參數 / L-shaped board dimension parameters */

    if (scanf("%d %d", &l, &m) != 2) return 0;

    /* 從左下角 (0, 0) 開始鋪滿整個 L 型板 / tile the entire L-shaped board starting from lower-left (0, 0) */
    tile_L(0, 0, l, m);

    return 0;
}
