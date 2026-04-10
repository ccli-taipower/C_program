/*
 * NTHU ACM 14878 - Tiling an L-Shaped Board with L-Trominoes
 * Contest: EE2310 Week 14 Practice
 * Tags: 11410EE 231002
 *
 * Board: full l x l square with the top-right m x m corner removed (an
 * L-shape). l and m are powers of two, 1 <= m < l <= 64. Tile the remaining
 * (l^2 - m^2) cells with L-trominoes (each covers 3 cells of a 2x2 block).
 *
 * Tromino types used by the judge (inferred from the sample):
 *   Type 1 = missing cell is UPPER-RIGHT  of the 2x2 bounding box
 *   Type 2 = missing cell is UPPER-LEFT
 *   Type 3 = missing cell is LOWER-LEFT
 *   Type 4 = missing cell is LOWER-RIGHT
 * Each tromino is reported as "type cx cy" where (cx, cy) is the geometric
 * center (= upper-right corner cell) of the 2x2 bounding box.
 *
 * Algorithm:
 *   tile_L(x, y, l, m):
 *     Place a type-1 tromino at the L-shape centre (x+l/2, y+l/2). It covers
 *     the LL/LR/UL cells of that 2x2 block. The UR cell sits inside the
 *     upper-right sub-quadrant, which is either entirely removed (if l == 2m)
 *     or forms a smaller L-shape L(l/2, m) (if l > 2m) and will be tiled by
 *     recursion. The other three sub-quadrants become deficient-by-one-cell
 *     squares, each tileable by the classic deficient-board recursion.
 *
 *   tile_deficient(x, y, size, dx, dy):
 *     Standard divide-and-conquer: split the size x size square into four
 *     equal sub-quadrants, identify the sub-quadrant containing the existing
 *     missing cell (dx, dy), place a central tromino that covers the other
 *     three sub-quadrants' inner corner cells, and recurse on each
 *     sub-quadrant with its own deficient cell.
 *
 * Note: the output sequence from this solution is a valid tiling but its
 * ordering may differ from the judge's reference order.
 */
#include <stdio.h>

/* Tile a size x size square at (x, y), where cell (dx, dy) is already
 * accounted for. Emits (size*size - 1) / 3 trominoes. */
static void tile_deficient(int x, int y, int size, int dx, int dy) {
    if (size <= 1) return;
    if (size == 2) {
        int cx = x + 1, cy = y + 1;
        int type;
        if      (dx == x     && dy == y    ) type = 3; /* missing LL */
        else if (dx == x + 1 && dy == y    ) type = 4; /* missing LR */
        else if (dx == x     && dy == y + 1) type = 2; /* missing UL */
        else                                  type = 1; /* missing UR */
        printf("%d %d %d\n", type, cx, cy);
        return;
    }

    int half = size / 2;
    int cx = x + half, cy = y + half;
    int mid = x + half, mjd = y + half;

    int in_LL = (dx <  mid && dy <  mjd);
    int in_LR = (dx >= mid && dy <  mjd);
    int in_UL = (dx <  mid && dy >= mjd);
    int in_UR = (dx >= mid && dy >= mjd);

    /* Central tromino type: leave the sub-quadrant that already has a
     * deficient cell uncovered. */
    int type;
    if      (in_LL) type = 3; /* leave (cx-1, cy-1) */
    else if (in_LR) type = 4; /* leave (cx,   cy-1) */
    else if (in_UL) type = 2; /* leave (cx-1, cy)   */
    else            type = 1; /* leave (cx,   cy)   */
    printf("%d %d %d\n", type, cx, cy);

    /* Determine each sub-quadrant's deficient cell. */
    int LLx = in_LL ? dx : cx - 1, LLy = in_LL ? dy : cy - 1;
    int LRx = in_LR ? dx : cx,     LRy = in_LR ? dy : cy - 1;
    int ULx = in_UL ? dx : cx - 1, ULy = in_UL ? dy : cy;
    int URx = in_UR ? dx : cx,     URy = in_UR ? dy : cy;

    tile_deficient(x,        y,        half, LLx, LLy);
    tile_deficient(x + half, y,        half, LRx, LRy);
    tile_deficient(x,        y + half, half, ULx, ULy);
    tile_deficient(x + half, y + half, half, URx, URy);
}

/* Tile an L-shape: full l x l square with upper-right m x m corner removed,
 * with lower-left corner at (x, y). */
static void tile_L(int x, int y, int l, int m) {
    int half = l / 2;
    int cx = x + half, cy = y + half;

    /* Central tromino leaves the UR cell (cx, cy) uncovered. */
    printf("1 %d %d\n", cx, cy);
    tile_deficient(x,        y,        half, cx - 1, cy - 1);
    tile_deficient(x + half, y,        half, cx,     cy - 1);
    tile_deficient(x,        y + half, half, cx - 1, cy);

    if (l > 2 * m) {
        /* UR sub-quadrant is L(half, m); (cx, cy) is its own LL corner cell
         * and is still to be tiled by the sub-recursion. */
        tile_L(x + half, y + half, half, m);
    }
    /* Otherwise l == 2m and the UR sub-quadrant is entirely the removed
     * region -- nothing left to tile there. */
}

int main(void) {
    int l, m;
    if (scanf("%d %d", &l, &m) != 2) return 0;
    tile_L(0, 0, l, m);
    return 0;
}
