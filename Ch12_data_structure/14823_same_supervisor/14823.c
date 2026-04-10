/*
 * NTHU EE2310 - 題目 14823: Same Supervisor（相同直屬上司）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 12 章（資料結構）
 *   如果不知道如何解題，請參考課本第 12 章的說明。
 *
 * 【題目說明】
 * 給定 n 筆員工資料，每筆包含員工編號、姓名（名、姓）、上司編號。
 * 若某員工的 boss_id == 自身 id，表示該員工為頂層老闆（無實際上司）。
 * 給定 m 筆查詢，每筆查詢兩位員工的姓名，判斷他們是否有相同的直屬上司。
 * 輸出 "yes" 或 "no"。
 *
 * 【解題策略】
 * 判斷規則：
 *   - 若其中一人是頂層老闆（boss_id == 自身 id），則沒有有效的直屬上司，
 *     不可能與任何人共享上司，輸出 "no"。
 *   - 否則，比較兩人的 boss_id：相同則輸出 "yes"，不同則輸出 "no"。
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

static Employee emp[MAXN];   /* 員工陣列 */
static int n;                /* 員工總數 */

/* 依姓名尋找員工的陣列索引；找不到回傳 -1 */
static int find_by_name(const char *fn, const char *ln) {
    for (int i = 0; i < n; ++i) {
        if (strcmp(emp[i].firstname, fn) == 0 &&
            strcmp(emp[i].lastname, ln) == 0) {
            return i;
        }
    }
    return -1;
}

int main(void) {
    if (scanf("%d", &n) != 1) return 0;
    /* 讀取所有員工資料 */
    for (int i = 0; i < n; ++i) {
        if (scanf("%d %31s %31s %d",
                  &emp[i].id, emp[i].firstname,
                  emp[i].lastname, &emp[i].boss_id) != 4) {
            return 0;
        }
    }

    int m;
    if (scanf("%d", &m) != 1) return 0;

    /* 依序處理每筆查詢 */
    for (int q = 0; q < m; ++q) {
        char fn1[NAMELEN], ln1[NAMELEN];
        char fn2[NAMELEN], ln2[NAMELEN];
        if (scanf("%31s %31s %31s %31s", fn1, ln1, fn2, ln2) != 4) return 0;

        int idx1 = find_by_name(fn1, ln1);
        int idx2 = find_by_name(fn2, ln2);

        /* 若找不到員工，輸出 "no" */
        if (idx1 < 0 || idx2 < 0) {
            printf("no\n");
            continue;
        }

        /* 若任一員工是頂層老闆（boss_id == 自身 id），無有效上司，輸出 "no" */
        if (emp[idx1].id == emp[idx1].boss_id ||
            emp[idx2].id == emp[idx2].boss_id) {
            printf("no\n");
            continue;
        }

        /* 比較兩人的直屬上司編號 */
        if (emp[idx1].boss_id == emp[idx2].boss_id) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }
    return 0;
}
