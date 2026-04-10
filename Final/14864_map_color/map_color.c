/*
 * NTHU ACM 14864 - Map Color (20 points)
 * Contest: EE2310 Final
 *
 * Color n countries with c colors so that no two adjacent countries share
 * the same color. Output the lexicographically smallest valid coloring.
 * If no valid coloring exists, print "no solution".
 *
 * Approach: straightforward backtracking.
 *   - Visit countries in order 1..n.
 *   - For each country, try colors 1..c in increasing order.
 *   - A color is valid if it does not clash with any already-colored
 *     neighbour of the current country.
 *   - Because we pick colors in ascending order, the FIRST solution we find
 *     is automatically the lexicographically smallest one.
 *
 * The adjacency list is stored as a flat bitmap (adj[i][j] = 1 iff i~j)
 * which is simple and fast for n <= 100.
 */
#include <stdio.h>
#include <string.h>

#define MAXN 128

static int n, c;
static int adj[MAXN][MAXN];
static int color[MAXN];
static int solved;

static void backtrack(int v) {
    if (solved) return;
    if (v > n) {
        /* All countries colored successfully */
        for (int i = 1; i <= n; ++i) {
            printf("%d%s", color[i], i == n ? "\n" : " ");
        }
        solved = 1;
        return;
    }
    for (int k = 1; k <= c && !solved; ++k) {
        int ok = 1;
        for (int u = 1; u < v; ++u) {
            if (adj[v][u] && color[u] == k) { ok = 0; break; }
        }
        if (ok) {
            color[v] = k;
            backtrack(v + 1);
            color[v] = 0;
        }
    }
}

int main(void) {
    int p;
    if (scanf("%d %d %d", &n, &c, &p) != 3) return 0;

    for (int e = 0; e < p; ++e) {
        int i, j;
        if (scanf("%d %d", &i, &j) != 2) return 0;
        adj[i][j] = adj[j][i] = 1;
    }

    memset(color, 0, sizeof(color));
    solved = 0;
    backtrack(1);

    if (!solved) {
        printf("no solution\n");
    }
    return 0;
}
