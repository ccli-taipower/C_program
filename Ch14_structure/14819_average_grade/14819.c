/*
 * NTHU EE2310 - 題目 14819: Average Grade
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 14 章（結構）
 *   如果不知道如何解題，請參考課本第 14 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14819/
 *
 * 【題目說明】
 * 定義一個 student 結構，包含成績數量（count）與成績陣列（grades）。
 * 實作函數 average_grade，計算並回傳該學生的平均成績（float）。
 * 若 count 為 0，回傳 0.0。
 *
 * 範例：
 *   count=3, grades=[80,90,100] → 90.000000
 *   count=5, grades=[60,75,80,90,100] → 81.000000
 *   count=0 → 0.000000
 *
 * 【解題策略】
 * 1. 在 main 中讀入 count 及各成績，填入 student 結構。
 * 2. average_grade 函數：
 *    - 若 count 為 0，直接回傳 0.0。
 *    - 否則對 grades 陣列加總，再除以 count 得浮點數平均。
 * 3. 輸出結果，保留 6 位小數。
 */
#include <stdio.h>

/* student 結構定義 */
struct student {
    int count;       /* 成績筆數 */
    int grades[100]; /* 成績陣列 */
};

/* 計算學生平均成績的函數 */
float average_grade(struct student *std_ptr) {
    int i;
    float sum;

    /* 若筆數為 0，回傳 0.0 */
    if (std_ptr->count == 0) {
        return 0.0f;
    }

    /* 累加所有成績 */
    sum = 0.0f;
    for (i = 0; i < std_ptr->count; i++) {
        sum += (float)std_ptr->grades[i];
    }

    /* 回傳平均值 */
    return sum / (float)std_ptr->count;
}

int main(void) {
    struct student s;  /* 學生結構 */
    int i;
    float avg;

    /* 讀入成績筆數 */
    scanf("%d", &s.count);

    /* 讀入各成績 */
    for (i = 0; i < s.count; i++) {
        scanf("%d", &s.grades[i]);
    }

    /* 計算並輸出平均成績，保留 6 位小數 */
    avg = average_grade(&s);
    printf("%f\n", avg);

    return 0;
}
