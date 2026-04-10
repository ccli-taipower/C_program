/*
 * NTHU EE2310 - 題目 14865: Employee Network Query System（員工網路查詢系統）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 12 章（資料結構）
 *   如果不知道如何解題，請參考課本第 12 章的說明。
 *
 * 【題目說明】
 * 員工資料包含：員工編號、姓名、直屬上司編號。
 * 若 boss_id == 自身 id，表示該員工為最高主管（頂層老闆）。
 * 支援三種查詢（查詢行末尾的整數 k 決定類型）：
 *   k = 1  同事（Colleagues）  ：與指定員工有相同直屬上司的人
 *                                （排除自身及頂層老闆）
 *   k = 2  上司鏈（Supervisors）：直屬上司、再上司……直到頂層老闆
 *   k = 3  下屬（Subordinates）  ：以 DFS 遞迴列出所有下屬
 *                                （按輸入順序走訪同層）
 *
 * 【解題策略】
 * 以陣列儲存所有員工，依題目需求實作三個查詢函式。
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

/* 依員工編號尋找陣列索引；找不到回傳 -1 */
static int find_by_id(int id) {
    for (int i = 0; i < n; ++i) {
        if (emp[i].id == id) return i;
    }
    return -1;
}

/* 查詢同事：與指定員工有相同直屬上司的人（排除自身及頂層老闆） */
static void query_colleagues(int idx) {
    int boss = emp[idx].boss_id;
    for (int i = 0; i < n; ++i) {
        if (i == idx) continue;                      /* 排除自身 */
        if (emp[i].id == emp[i].boss_id) continue;  /* 排除頂層老闆 */
        if (emp[i].boss_id == boss) {
            printf("%s %s\n", emp[i].firstname, emp[i].lastname);
        }
    }
}

/* 查詢上司鏈：從直屬上司往上，直到頂層老闆為止 */
static void query_supervisors(int idx) {
    int cur = idx;
    while (emp[cur].id != emp[cur].boss_id) {
        int boss_idx = find_by_id(emp[cur].boss_id);
        if (boss_idx < 0) break;
        printf("%s %s\n", emp[boss_idx].firstname, emp[boss_idx].lastname);
        cur = boss_idx;
    }
}

/* 查詢下屬：DFS 遞迴，按輸入順序走訪同層 */
static void query_subordinates(int boss_idx) {
    for (int i = 0; i < n; ++i) {
        if (emp[i].boss_id == emp[boss_idx].id &&
            emp[i].id != emp[i].boss_id) {
            printf("%s %s\n", emp[i].firstname, emp[i].lastname);
            query_subordinates(i);   /* 遞迴列出下屬的下屬 */
        }
    }
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
