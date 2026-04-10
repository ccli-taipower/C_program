/*
 * NTHU ACM 14850 - The Skyline Problem (30 points, HARD)
 *
 * Given n axis-aligned rectangular buildings [L, R, H] sitting on the ground,
 * print the key points of the outer skyline. A key point [x, y] is a location
 * where the skyline height changes; redundant collinear points must not be
 * emitted.
 *
 * Sweep-line approach:
 *   - Each building generates two edges: a "start" edge (x = L, h = H) and
 *     an "end" edge (x = R, h = H).
 *   - Sort edges by x.
 *   - Sweep left-to-right. At every distinct x, first apply ALL edges at
 *     that x to the active-height multiset (start -> add, end -> remove),
 *     THEN compute the new maximum height. If the max changed from the
 *     previous one, output (x, new_max).
 *
 * The active-height multiset is an unsorted array: add/remove are O(n),
 * max is O(n). Total O(n^2), well within the judge's limits.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXBLDG 10005
#define MAXEDGE (2 * MAXBLDG)

typedef struct {
    int x;
    int height;
    int type; /* 1 = start, 0 = end */
} Edge;

static int compareEdges(const void *pa, const void *pb) {
    const Edge *a = (const Edge *)pa;
    const Edge *b = (const Edge *)pb;
    return a->x - b->x;
}

/* ---- multiset of active heights ---------------------------------------- */
static int active[MAXEDGE];
static int active_n;

static void add_height(int h) {
    active[active_n++] = h;
}

static void remove_height(int h) {
    for (int i = 0; i < active_n; ++i) {
        if (active[i] == h) {
            active[i] = active[--active_n];
            return;
        }
    }
}

static int max_height(void) {
    int m = 0;
    for (int i = 0; i < active_n; ++i) {
        if (active[i] > m) m = active[i];
    }
    return m;
}
/* ------------------------------------------------------------------------ */

static void getSkyline(Edge *edges, int e_count) {
    qsort(edges, (size_t)e_count, sizeof(Edge), compareEdges);

    int prev = 0;
    int i = 0;
    while (i < e_count) {
        int cur_x = edges[i].x;
        /* process every edge with this x in one batch */
        while (i < e_count && edges[i].x == cur_x) {
            if (edges[i].type == 1) add_height(edges[i].height);
            else                    remove_height(edges[i].height);
            ++i;
        }
        int cur = max_height();
        if (cur != prev) {
            printf("%d %d\n", cur_x, cur);
            prev = cur;
        }
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    static Edge edges[MAXEDGE];
    int e_count = 0;
    for (int i = 0; i < n; ++i) {
        int L, R, H;
        if (scanf("%d %d %d", &L, &R, &H) != 3) return 0;
        edges[e_count].x = L; edges[e_count].height = H; edges[e_count].type = 1; ++e_count;
        edges[e_count].x = R; edges[e_count].height = H; edges[e_count].type = 0; ++e_count;
    }

    active_n = 0;
    getSkyline(edges, e_count);
    return 0;
}
