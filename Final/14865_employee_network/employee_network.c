/*
 * NTHU ACM 14865 - Employee Network Query System (20 points)
 * Contest: EE2310 Final
 *
 * Data: an array of employees, each with a unique id, first/last name and a
 * direct supervisor (boss_id). The top-level boss satisfies boss_id == id.
 *
 * Three query types (keyed by trailing integer k on the query line):
 *   k = 1  Colleagues  : employees sharing the same direct supervisor as the
 *                        queried person, excluding the queried person and the
 *                        top-level boss.
 *   k = 2  Supervisors : direct boss, then boss's boss, ... up to and
 *                        including the top-level boss, in that order.
 *   k = 3  Subordinates: DFS of the subordinate tree rooted at the queried
 *                        person, visiting siblings in their original input
 *                        order (pseudocode given in the problem statement).
 *
 * All outputs are "firstname lastname" per line. If no match is found the
 * query prints nothing.
 */
#include <stdio.h>
#include <string.h>

#define MAXN 256
#define NAMELEN 32

typedef struct {
    int id;
    char firstname[NAMELEN];
    char lastname[NAMELEN];
    int boss_id;
} Employee;

static Employee emp[MAXN];
static int n;

/* Find the array index of the employee matching firstname + lastname.
 * Returns -1 if not found. */
static int find_by_name(const char *fn, const char *ln) {
    for (int i = 0; i < n; ++i) {
        if (strcmp(emp[i].firstname, fn) == 0 &&
            strcmp(emp[i].lastname, ln) == 0) {
            return i;
        }
    }
    return -1;
}

/* Find the array index of the employee with the given id. -1 if missing. */
static int find_by_id(int id) {
    for (int i = 0; i < n; ++i) {
        if (emp[i].id == id) return i;
    }
    return -1;
}

static void query_colleagues(int idx) {
    int boss = emp[idx].boss_id;
    for (int i = 0; i < n; ++i) {
        if (i == idx) continue;                 /* exclude self */
        if (emp[i].id == emp[i].boss_id) continue; /* exclude top-level boss */
        if (emp[i].boss_id == boss) {
            printf("%s %s\n", emp[i].firstname, emp[i].lastname);
        }
    }
}

static void query_supervisors(int idx) {
    int cur = idx;
    while (emp[cur].id != emp[cur].boss_id) {
        int boss_idx = find_by_id(emp[cur].boss_id);
        if (boss_idx < 0) break;
        printf("%s %s\n", emp[boss_idx].firstname, emp[boss_idx].lastname);
        cur = boss_idx;
    }
}

static void query_subordinates(int boss_idx) {
    for (int i = 0; i < n; ++i) {
        if (emp[i].boss_id == emp[boss_idx].id &&
            emp[i].id != emp[i].boss_id) {
            printf("%s %s\n", emp[i].firstname, emp[i].lastname);
            query_subordinates(i);
        }
    }
}

int main(void) {
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; ++i) {
        if (scanf("%d %31s %31s %d",
                  &emp[i].id, emp[i].firstname,
                  emp[i].lastname, &emp[i].boss_id) != 4) {
            return 0;
        }
    }

    int m;
    if (scanf("%d", &m) != 1) return 0;
    for (int q = 0; q < m; ++q) {
        char fn[NAMELEN], ln[NAMELEN];
        int k;
        if (scanf("%31s %31s %d", fn, ln, &k) != 3) return 0;
        int idx = find_by_name(fn, ln);
        if (idx < 0) continue;
        if      (k == 1) query_colleagues(idx);
        else if (k == 2) query_supervisors(idx);
        else if (k == 3) query_subordinates(idx);
    }
    return 0;
}
