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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 定義 student 結構體，包含整數 count（成績筆數）與整數陣列 grades[100]。
 * 2. 在 main 中以 scanf 讀入 count，再以迴圈讀入 count 個成績到 grades 陣列。
 * 3. 呼叫 average_grade 函式，傳入學生結構體指標。
 * 4. average_grade 函式首先檢查 count 是否為 0，若是直接回傳 0.0f。
 * 5. 否則用 for 迴圈對 grades[0..count-1] 累加（轉型為 float），
 *    最後除以 (float)count 得到平均值並回傳。
 * 6. 在 main 中以 %f 格式（預設保留 6 位小數）輸出平均值。
 *
 * English:
 * 1. Define the student struct with an int count and an int array grades[100].
 * 2. In main, read count with scanf, then loop to read count grades into grades[].
 * 3. Call average_grade, passing a pointer to the student struct.
 * 4. average_grade first checks if count == 0 and returns 0.0f immediately if so.
 * 5. Otherwise, accumulate grades[0..count-1] cast to float in a for loop,
 *    divide by (float)count, and return the result.
 * 6. Print the returned average with %f (6 decimal places by default) in main.
 */
#include <stdio.h>

/* student 結構定義 */
struct student {
    int count;       /* 成績筆數 / number of grades */
    int grades[100]; /* 成績陣列 / array of grades */
};

/* 計算學生平均成績的函數 */
float average_grade(struct student *std_ptr) {
    int i;
    float sum;

    /* 若筆數為 0，回傳 0.0 / if count is 0, return 0.0 */
    if (std_ptr->count == 0) {
        return 0.0f;
    }

    /* 累加所有成績 / accumulate all grades */
    sum = 0.0f;
    for (i = 0; i < std_ptr->count; i++) {
        sum += (float)std_ptr->grades[i];
    }

    /* 回傳平均值 / return the average */
    return sum / (float)std_ptr->count;
}

int main(void) {
    struct student s;  /* 學生結構 / student struct */
    int i;
    float avg;

    /* 讀入成績筆數 / read the number of grades */
    scanf("%d", &s.count);

    /* 讀入各成績 / read each grade */
    for (i = 0; i < s.count; i++) {
        scanf("%d", &s.grades[i]);
    }

    /* 計算並輸出平均成績，保留 6 位小數 / compute and print average grade with 6 decimal places */
    avg = average_grade(&s);
    printf("%f\n", avg);

    return 0;
}
