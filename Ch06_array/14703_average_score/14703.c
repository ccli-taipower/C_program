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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入學生數 s 與課程數 c，作為後續陣列的邊界。
 * 2. 用雙重迴圈（外層 i = 學生，內層 j = 課程）讀入所有成績，
 *    存入二維陣列 score[i][j]。
 * 3. 計算學生平均分：外層迴圈遍歷每位學生 i，
 *    內層迴圈將該學生所有課程成績加總至 sum，
 *    輸出 sum / c（整數除法）。
 * 4. 計算課程平均分：外層迴圈遍歷每門課程 j，
 *    內層迴圈將所有學生在課程 j 的成績加總至 sum，
 *    輸出 sum / s（整數除法）。
 * 5. 兩個輸出階段分開進行，確保先全部輸出學生平均，再輸出課程平均。
 *
 * English:
 * 1. Read s (number of students) and c (number of courses) as array bounds.
 * 2. Use nested loops (outer: student i, inner: course j) to fill the 2-D
 *    array score[i][j] with all grades.
 * 3. Compute per-student averages: for each student i, sum all c course
 *    scores and print sum / c (integer division).
 * 4. Compute per-course averages: for each course j, sum all s student
 *    scores for that course and print sum / s (integer division).
 * 5. The two output phases are kept separate so all student averages appear
 *    before any course averages, matching the required output order.
 */
#include <stdio.h>

int main(void) {
    int s, c;          /* 學生數、課程數 / number of students and courses */
    int score[100][100]; /* 成績矩陣 / grade matrix */
    int i, j;
    int sum;

    /* 讀入學生數和課程數 / read number of students and courses */
    scanf("%d %d", &s, &c);

    /* 讀入所有成績 / read all scores */
    for (i = 0; i < s; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &score[i][j]);
        }
    }

    /* 輸出每位學生的平均分 / print average score for each student */
    for (i = 0; i < s; i++) {
        sum = 0;
        for (j = 0; j < c; j++) {
            sum += score[i][j];
        }
        printf("%d\n", sum / c);
    }

    /* 輸出每門課程的平均分 / print average score for each course */
    for (j = 0; j < c; j++) {
        sum = 0;
        for (i = 0; i < s; i++) {
            sum += score[i][j];
        }
        printf("%d\n", sum / s);
    }

    return 0;
}
