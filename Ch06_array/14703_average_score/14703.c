/*
 * NTHU EE2310 - 題目 14703: Average Score
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 6 章（陣列）
 *   如果不知道如何解題，請參考課本第 6 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14703/
 *
 * 【題目說明】
 * 有 s 位學生、c 門課程，輸入每位學生各科成績（s 行，每行 c 個整數）。
 * 先輸出每位學生的平均分（s 行），再輸出每門課程的平均分（c 行）。
 * 平均分使用整數除法（截斷小數）。
 *
 * 【解題策略】
 * 1. 讀入 s 和 c。
 * 2. 用二維陣列儲存所有成績。
 * 3. 對每位學生（每行）加總後除以 c，輸出結果。
 * 4. 對每門課（每列）加總後除以 s，輸出結果。
 */
#include <stdio.h>

int main(void) {
    int s, c;          /* 學生數、課程數 */
    int score[100][100]; /* 成績矩陣 */
    int i, j;
    int sum;

    /* 讀入學生數和課程數 */
    scanf("%d %d", &s, &c);

    /* 讀入所有成績 */
    for (i = 0; i < s; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &score[i][j]);
        }
    }

    /* 輸出每位學生的平均分 */
    for (i = 0; i < s; i++) {
        sum = 0;
        for (j = 0; j < c; j++) {
            sum += score[i][j];
        }
        printf("%d\n", sum / c);
    }

    /* 輸出每門課程的平均分 */
    for (j = 0; j < c; j++) {
        sum = 0;
        for (i = 0; i < s; i++) {
            sum += score[i][j];
        }
        printf("%d\n", sum / s);
    }

    return 0;
}
