/*
 * NTHU EE2310 - 題目 14651: Compute rectangle perimeter and area
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 3 章（運算）
 *   如果不知道如何解題，請參考課本第 3 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14651/
 *
 * 【題目說明】
 * 輸入長方形的寬 w 和高 h（兩個正整數），
 * 計算並輸出長方形的周長和面積。
 *   周長公式：2 * (w + h)
 *   面積公式：w * h
 *
 * 【解題策略】
 * 1. 讀入兩個整數 w（寬）和 h（高）
 * 2. 利用公式計算周長 perimeter = 2 * (w + h)
 * 3. 利用公式計算面積 area = w * h
 * 4. 先輸出周長，再輸出面積，各佔一行
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 宣告四個整數變數：w（寬）、h（高）、perimeter（周長）、area（面積），
 *    以便儲存輸入值與計算結果。
 * 2. 使用 scanf 讀入兩個以空白分隔的整數，分別存入 w 和 h，
 *    這是程式的唯一輸入。
 * 3. 計算周長：長方形由兩條寬和兩條高組成，因此周長公式為 2 * (w + h)。
 *    先加再乘以 2，減少乘法次數。
 * 4. 計算面積：長方形面積等於寬乘以高，即 w * h。
 * 5. 先用 printf 輸出周長並換行，再輸出面積並換行，
 *    順序必須符合題目要求（先周長後面積）。
 * 6. 回傳 0 表示程式正常結束。
 *
 * English:
 * 1. Declare four integer variables: w (width), h (height), perimeter, and area
 *    to store the input values and computed results.
 * 2. Use scanf to read two space-separated integers into w and h;
 *    this is the only input the program receives.
 * 3. Compute the perimeter: a rectangle has two widths and two heights,
 *    so the formula is 2 * (w + h). Adding first then multiplying reduces operations.
 * 4. Compute the area: rectangle area equals width times height, i.e. w * h.
 * 5. Print the perimeter followed by a newline, then the area followed by a newline.
 *    The order must match the problem requirement (perimeter first, then area).
 * 6. Return 0 to indicate the program terminated successfully.
 */
#include <stdio.h>

int main(void) {
    int w;          /* 長方形的寬（width） / rectangle width */
    int h;          /* 長方形的高（height） / rectangle height */
    int perimeter;  /* 周長（perimeter = 2 * (w + h)） / perimeter = 2 * (w + h) */
    int area;       /* 面積（area = w * h） / area = w * h */

    /* 讀入寬和高 / read width and height */
    scanf("%d %d", &w, &h);

    /* 計算周長 / compute the perimeter */
    perimeter = 2 * (w + h);

    /* 計算面積 / compute the area */
    area = w * h;

    /* 輸出結果：先周長後面積，各佔一行 / print perimeter then area, each on its own line */
    printf("%d\n", perimeter);
    printf("%d\n", area);

    return 0;
}
