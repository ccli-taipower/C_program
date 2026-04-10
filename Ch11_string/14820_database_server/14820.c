/*
 * NTHU EE2310 - 題目 14820: Database Server
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 11 章（字串）
 *   如果不知道如何解題，請參考課本第 11 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14820/
 *
 * 【題目說明】
 * 模擬資料庫伺服器。每筆記錄包含：
 *   lastname（姓）、firstname（名）、ID（字串）、salary（薪水，整數）、age（年齡，整數）
 * 讀入 n 筆記錄，再讀入 c 條查詢指令。
 *
 * 查詢格式：
 *   select f1 f2 ... fk where field op value
 *   - 字串欄位（lastname, firstname, ID）：支援 ==、!= 運算子
 *   - 數值欄位（salary, age）：支援 ==、>、< 運算子
 *
 * 對每條查詢，輸出所有符合條件的記錄，每筆顯示指定欄位，以空白分隔。
 *
 * 【解題策略】
 * 1. 讀入所有記錄存入陣列。
 * 2. 對每條查詢，解析出「select 欄位列表」與「where 條件」。
 * 3. 對每筆記錄套用條件，若符合則輸出指定欄位。
 *
 * 限制：n ≤ 50，字串 ≤ 80 字元，c ≤ 100。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入記錄筆數 n，逐一讀入每筆記錄的五個欄位（lastname、firstname、ID、salary、age）存入陣列。
 * 2. 讀入查詢數 c，消耗該行尾端換行符，以便後續用 fgets 讀取完整查詢行。
 * 3. 對每條查詢，以 fgets 讀入完整一行，去除結尾的 '\n'。
 * 4. 使用 strtok 將查詢行拆解成 token：跳過 "select"，
 *    依序收集欄位名稱直到遇到 "where"，再讀入 where_field、where_op、where_val。
 * 5. 對 records 陣列中每筆記錄呼叫 matches，判斷是否符合 where 條件：
 *    - 數值欄位（salary/age）：用 atoi 轉換後以 ==、>、< 比較。
 *    - 字串欄位（lastname/firstname/ID）：以 strcmp 進行 ==、!= 比較。
 * 6. 符合條件的記錄，依 select 欄位列表呼叫 get_field_str 取得值，以空白分隔輸出。
 *
 * English:
 * 1. Read n records, storing each record's five fields into the records array.
 * 2. Read the query count c, then consume the trailing newline so fgets works correctly.
 * 3. For each query, read a full line with fgets and strip the trailing '\n'.
 * 4. Tokenize the line with strtok: skip "select", collect field names until "where",
 *    then read where_field, where_op, and where_val.
 * 5. For each record, call matches to evaluate the WHERE condition:
 *    - Numeric fields (salary/age): convert value with atoi and compare with ==, >, <.
 *    - String fields (lastname/firstname/ID): use strcmp for == and != operators.
 * 6. For matching records, retrieve each SELECT field via get_field_str and print
 *    fields space-separated on one line.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN    55      /* 最大記錄筆數 / max number of records */
#define MAXC    105     /* 最大查詢數 / max number of queries */
#define SLEN    85      /* 字串欄位最大長度 / max string field length */
#define LINELEN 512     /* 查詢指令一行的最大長度 / max length of one query line */
#define MAXSEL  10      /* select 最多欄位數 / max number of SELECT fields */

/* 一筆記錄的結構 */
typedef struct {
    char lastname[SLEN];    /* 姓 / last name */
    char firstname[SLEN];   /* 名 / first name */
    char id[SLEN];          /* ID / employee ID */
    int  salary;            /* 薪水 / salary */
    int  age;               /* 年齡 / age */
} Record;

/*
 * get_field_str：取得記錄中指定欄位的字串表示
 * 回傳指向欄位值的指標（字串形式），或 NULL 若欄位不存在
 */
static const char *get_field_str(const Record *r, const char *field,
                                  char buf[SLEN]) {
    if (strcmp(field, "lastname") == 0)  return r->lastname;
    if (strcmp(field, "firstname") == 0) return r->firstname;
    if (strcmp(field, "ID") == 0)        return r->id;
    if (strcmp(field, "salary") == 0) {
        sprintf(buf, "%d", r->salary);
        return buf;
    }
    if (strcmp(field, "age") == 0) {
        sprintf(buf, "%d", r->age);
        return buf;
    }
    return NULL;
}

/*
 * is_numeric_field：判斷欄位是否為數值型別
 */
static int is_numeric_field(const char *field) {
    return (strcmp(field, "salary") == 0 || strcmp(field, "age") == 0);
}

/*
 * get_field_int：取得記錄中指定數值欄位的整數值
 */
static int get_field_int(const Record *r, const char *field) {
    if (strcmp(field, "salary") == 0) return r->salary;
    if (strcmp(field, "age") == 0)    return r->age;
    return 0;
}

/*
 * matches：判斷記錄是否符合 where 條件
 */
static int matches(const Record *r, const char *field,
                   const char *op, const char *value) {
    if (is_numeric_field(field)) {
        /* 數值比較 */
        int rv  = get_field_int(r, field);   /* 記錄欄位值 / record field value */
        int val = atoi(value);               /* 查詢條件值 / query condition value */
        if (strcmp(op, "==") == 0) return rv == val;
        if (strcmp(op, ">")  == 0) return rv >  val;
        if (strcmp(op, "<")  == 0) return rv <  val;
    } else {
        /* 字串比較 */
        char buf[SLEN];
        const char *rv = get_field_str(r, field, buf);
        if (rv == NULL) return 0;
        if (strcmp(op, "==") == 0) return strcmp(rv, value) == 0;
        if (strcmp(op, "!=") == 0) return strcmp(rv, value) != 0;
    }
    return 0;
}

int main(void) {
    Record records[MAXN];   /* 所有記錄 / all records */
    int n;                  /* 記錄筆數 / number of records */

    /* 讀入記錄數量 / read the number of records */
    scanf("%d", &n);

    /* 讀入各筆記錄 / read each record */
    for (int i = 0; i < n; i++) {
        scanf("%s %s %s %d %d",
              records[i].lastname,
              records[i].firstname,
              records[i].id,
              &records[i].salary,
              &records[i].age);
    }

    int c;   /* 查詢數量 / number of queries */
    scanf("%d", &c);

    /* 消耗讀入數量後的換行符 / consume the newline after the query count */
    {
        char ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }

    /* 處理每條查詢 / process each query */
    for (int q = 0; q < c; q++) {
        char line[LINELEN];   /* 查詢指令整行 / full query line */

        /* 讀入一整行查詢指令 / read one full query line */
        if (fgets(line, sizeof(line), stdin) == NULL) break;
        /* 去掉結尾換行符 / strip trailing newline */
        int ll = (int)strlen(line);
        if (ll > 0 && line[ll - 1] == '\n') line[ll - 1] = '\0';

        /* 解析 select 欄位列表與 where 條件 / parse SELECT field list and WHERE condition */
        char sel_fields[MAXSEL][SLEN];   /* select 的欄位名稱列表 / list of SELECT field names */
        int  sel_count = 0;              /* select 的欄位數量 / count of SELECT fields */
        char where_field[SLEN];          /* where 條件欄位 / WHERE condition field */
        char where_op[5];               /* where 條件運算子 / WHERE operator */
        char where_val[SLEN];           /* where 條件值 / WHERE condition value */

        /* 使用 strtok 解析各 token / tokenize the line with strtok */
        char tmp[LINELEN];
        strcpy(tmp, line);

        char *tok = strtok(tmp, " ");   /* 第一個 token 應為 "select" / first token should be "select" */
        if (tok == NULL || strcmp(tok, "select") != 0) continue;

        /* 讀入欄位名稱，直到遇到 "where" / collect field names until "where" is encountered */
        while ((tok = strtok(NULL, " ")) != NULL) {
            if (strcmp(tok, "where") == 0) break;
            strcpy(sel_fields[sel_count++], tok);
        }

        /* 讀入 where 條件的三個部分：欄位、運算子、值 / read the three WHERE parts: field, operator, value */
        tok = strtok(NULL, " ");
        if (tok == NULL) continue;
        strcpy(where_field, tok);

        tok = strtok(NULL, " ");
        if (tok == NULL) continue;
        strcpy(where_op, tok);

        tok = strtok(NULL, " ");
        if (tok == NULL) continue;
        strcpy(where_val, tok);

        /* 對每筆記錄套用條件，輸出符合的記錄 / apply condition to each record and print matching ones */
        for (int i = 0; i < n; i++) {
            if (matches(&records[i], where_field, where_op, where_val)) {
                /* 輸出 select 指定的各欄位，以空白分隔 / print each SELECT field separated by spaces */
                char buf[SLEN];
                for (int j = 0; j < sel_count; j++) {
                    if (j > 0) printf(" ");
                    const char *val = get_field_str(&records[i],
                                                    sel_fields[j], buf);
                    if (val != NULL) printf("%s", val);
                }
                printf("\n");
            }
        }
    }

    return 0;
}
