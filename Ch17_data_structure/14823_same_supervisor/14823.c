/*
 * NTHU EE2310 - 題目 14823: Same Supervisor（相同直屬上司）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 17 章（資料結構）
 *   如果不知道如何解題，請參考課本第 17 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14823/
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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀取 n 筆員工資料，將每筆資料（id、名、姓、boss_id）儲存於靜態陣列 emp[]。
 * 2. 讀取 m 筆查詢，每筆查詢包含兩位員工的名（firstname）和姓（lastname）。
 * 3. 對每筆查詢，呼叫 find_by_name() 以線性搜尋找到對應陣列索引。
 * 4. 若任一員工找不到（索引 < 0），直接輸出 "no"。
 * 5. 若任一員工的 boss_id 等於自身 id，代表是頂層老闆，輸出 "no"。
 * 6. 否則比較兩人的 boss_id：相等輸出 "yes"，不相等輸出 "no"。
 *
 * English:
 * 1. Read n employee records, storing each (id, firstname, lastname, boss_id) in static array emp[].
 * 2. Read m queries, each containing the first and last name of two employees.
 * 3. For each query, call find_by_name() to linearly search for each employee's array index.
 * 4. If either employee is not found (index < 0), output "no".
 * 5. If either employee's boss_id equals their own id, they are the top-level boss; output "no".
 * 6. Otherwise compare both boss_ids: if equal output "yes", otherwise output "no".
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

static Employee emp[MAXN];   /* 員工陣列 / employee array */
static int n;                /* 員工總數 / total number of employees */

/* 依姓名尋找員工的陣列索引；找不到回傳 -1 / find employee array index by name; return -1 if not found */
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
    /* 讀取所有員工資料 / read all employee records */
    for (int i = 0; i < n; ++i) {
        if (scanf("%d %31s %31s %d",
                  &emp[i].id, emp[i].firstname,
                  emp[i].lastname, &emp[i].boss_id) != 4) {
            return 0;
        }
    }

    int m;
    if (scanf("%d", &m) != 1) return 0;

    /* 依序處理每筆查詢 / process each query in order */
    for (int q = 0; q < m; ++q) {
        char fn1[NAMELEN], ln1[NAMELEN];
        char fn2[NAMELEN], ln2[NAMELEN];
        if (scanf("%31s %31s %31s %31s", fn1, ln1, fn2, ln2) != 4) return 0;

        int idx1 = find_by_name(fn1, ln1);
        int idx2 = find_by_name(fn2, ln2);

        /* 若找不到員工，輸出 "no" / if either employee is not found, output "no" */
        if (idx1 < 0 || idx2 < 0) {
            printf("no\n");
            continue;
        }

        /* 若任一員工是頂層老闆（boss_id == 自身 id），無有效上司，輸出 "no" / if either is a top-level boss (boss_id == own id), no valid supervisor, output "no" */
        if (emp[idx1].id == emp[idx1].boss_id ||
            emp[idx2].id == emp[idx2].boss_id) {
            printf("no\n");
            continue;
        }

        /* 比較兩人的直屬上司編號 / compare the direct boss IDs of both employees */
        if (emp[idx1].boss_id == emp[idx2].boss_id) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }
    return 0;
}
