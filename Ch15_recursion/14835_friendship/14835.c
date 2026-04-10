/*
 * NTHU EE2310 - 題目 14835: Friendship
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 15 章（遞迴）
 *   如果不知道如何解題，請參考課本第 10、11 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14835/
 *
 * 【題目說明】
 * 從二進位檔案 "friends" 讀取人員與好友關係資料，
 * 針對標準輸入的每對姓名查詢，判斷兩人是否為直接好友。
 *
 * 【二進位檔案格式】
 *   - 4 bytes：int n（人員總數）
 *   - n × sizeof(struct person)：人員資料
 *   - 4 bytes：int f（好友關係對數）
 *   - f × sizeof(struct friends_pair)：好友關係對
 *
 * struct person { int id; char firstname[32]; char lastname[32]; };
 * struct friends_pair { int id1; int id2; };
 *   （sizeof(struct person) = 68 bytes；sizeof(struct friends_pair) = 8 bytes）
 *
 * 【解題策略】
 * 1. 以 "rb" 模式開啟 "friends" 二進位檔。
 * 2. 讀入人員總數 n，再讀入 n 筆人員資料。
 * 3. 讀入好友關係對數 f，再讀入 f 對好友關係。
 * 4. 對標準輸入的每對姓名：
 *    a. 依姓名查找兩人的 id。
 *    b. 查找好友關係陣列中是否存在此對 (id1, id2) 或 (id2, id1)。
 *    c. 輸出 "yes" 或 "no"。
 */
#include <stdio.h>
#include <string.h>

#define MAXPEOPLE 1005  /* 人員數量上限 */
#define MAXPAIRS  5005  /* 好友關係對上限 */

/* 人員資料結構（共 68 bytes） */
struct person {
    int id;             /* 人員 ID（4 bytes） */
    char firstname[32]; /* 名字（32 bytes） */
    char lastname[32];  /* 姓氏（32 bytes） */
};

/* 好友關係對資料結構（共 8 bytes） */
struct friends_pair {
    int id1;  /* 第一人的 ID */
    int id2;  /* 第二人的 ID */
};

static struct person     people[MAXPEOPLE];  /* 人員資料陣列 */
static struct friends_pair pairs[MAXPAIRS];  /* 好友關係對陣列 */
static int n;  /* 人員總數 */
static int f;  /* 好友關係對數 */

/* 依姓名查找人員 ID，若找不到回傳 -1 */
static int find_id(const char *first, const char *last) {
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(people[i].firstname, first) == 0 &&
            strcmp(people[i].lastname,  last)  == 0) {
            return people[i].id;
        }
    }
    return -1;
}

/* 判斷兩個 ID 是否為直接好友 */
static int are_friends(int ida, int idb) {
    int i;
    for (i = 0; i < f; i++) {
        if ((pairs[i].id1 == ida && pairs[i].id2 == idb) ||
            (pairs[i].id1 == idb && pairs[i].id2 == ida)) {
            return 1;  /* 是好友 */
        }
    }
    return 0;  /* 不是好友 */
}

int main(void) {
    int i;

    /* 開啟二進位好友資料檔 */
    FILE *fp = fopen("friends", "rb");
    if (fp == NULL) return 1;

    /* 讀入人員總數 */
    if (fread(&n, sizeof(int), 1, fp) != 1) {
        fclose(fp);
        return 1;
    }

    /* 讀入 n 筆人員資料 */
    for (i = 0; i < n; i++) {
        if (fread(&people[i], sizeof(struct person), 1, fp) != 1) {
            fclose(fp);
            return 1;
        }
    }

    /* 讀入好友關係對數 */
    if (fread(&f, sizeof(int), 1, fp) != 1) {
        fclose(fp);
        return 1;
    }

    /* 讀入 f 對好友關係 */
    for (i = 0; i < f; i++) {
        if (fread(&pairs[i], sizeof(struct friends_pair), 1, fp) != 1) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    /* 從標準輸入讀取查詢，每次讀入兩人的名字 */
    char fn1[32], ln1[32];  /* 第一人的名與姓 */
    char fn2[32], ln2[32];  /* 第二人的名與姓 */

    while (scanf("%31s %31s %31s %31s", fn1, ln1, fn2, ln2) == 4) {
        /* 查找兩人的 ID */
        int id1 = find_id(fn1, ln1);
        int id2 = find_id(fn2, ln2);

        /* 若任一人不存在或兩人不是好友，輸出 "no" */
        if (id1 == -1 || id2 == -1 || !are_friends(id1, id2)) {
            printf("no\n");
        } else {
            printf("yes\n");
        }
    }

    return 0;
}
