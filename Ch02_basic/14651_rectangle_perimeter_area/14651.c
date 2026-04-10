/*
 * NTHU EE2310 - 題目 14651: Compute rectangle perimeter and area
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 2 章：基本運算
 *   如果不知道如何解題，請參考課本第 2 章的說明。
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
 */
#include <stdio.h>

int main(void) {
    int w;          /* 長方形的寬（width） */
    int h;          /* 長方形的高（height） */
    int perimeter;  /* 周長（perimeter = 2 * (w + h)） */
    int area;       /* 面積（area = w * h） */

    /* 讀入寬和高 */
    scanf("%d %d", &w, &h);

    /* 計算周長 */
    perimeter = 2 * (w + h);

    /* 計算面積 */
    area = w * h;

    /* 輸出結果：先周長後面積，各佔一行 */
    printf("%d\n", perimeter);
    printf("%d\n", area);

    return 0;
}
