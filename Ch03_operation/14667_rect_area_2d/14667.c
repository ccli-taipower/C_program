/*
 * NTHU EE2310 - 題目 14667: Compute area of a rectangle in 2D space
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 3 章（運算）
 *   如果不知道如何解題，請參考課本第 3 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14667/
 *
 * 【題目說明】
 * 在二維平面上，輸入矩形兩個對角的座標點 (x1, y1) 和 (x2, y2)，
 * 計算並輸出矩形的面積。
 *   面積公式：|x2 - x1| * |y2 - y1|
 * （使用絕對值，避免座標順序造成負數）
 *
 * 【解題策略】
 * 1. 讀入兩個整數座標點 (x1, y1) 和 (x2, y2)
 * 2. 計算寬度 = |x2 - x1|（使用條件判斷取絕對值）
 * 3. 計算高度 = |y2 - y1|（使用條件判斷取絕對值）
 * 4. 面積 = 寬度 * 高度
 * 5. 輸出面積
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 宣告四個整數 x1, y1, x2, y2 以儲存兩個對角頂點座標，
 *    再宣告 width、height、area 以存放計算過程的中間值。
 * 2. 使用 scanf 一次讀入四個整數，依序對應 x1, y1, x2, y2。
 * 3. 計算水平距離（寬度）：先做 x2 - x1，若結果為負數則取其相反數，
 *    這樣無論哪個 x 較大都能得到正確的距離（即絕對值）。
 * 4. 以相同方式計算垂直距離（高度）：先做 y2 - y1，若為負則取負。
 *    不使用 abs() 是為了強調基本的條件判斷概念。
 * 5. 面積 = 寬度 × 高度，兩個正值相乘即為正確面積。
 * 6. 使用 printf 輸出面積並換行，程式結束。
 *
 * English:
 * 1. Declare four integers x1, y1, x2, y2 for the two diagonal corner coordinates,
 *    plus width, height, and area for intermediate calculations.
 * 2. Use scanf to read all four integers at once into x1, y1, x2, y2 in order.
 * 3. Compute horizontal distance (width): calculate x2 - x1; if the result is
 *    negative, negate it to get the absolute value regardless of coordinate order.
 * 4. Compute vertical distance (height) the same way: calculate y2 - y1 and
 *    negate if negative. Avoiding abs() reinforces basic conditional logic.
 * 5. Area = width * height; multiplying two non-negative values gives the correct area.
 * 6. Print the area with a newline and return 0.
 */
#include <stdio.h>

int main(void) {
    int x1, y1;  /* 第一個對角頂點的座標 / coordinates of the first diagonal corner */
    int x2, y2;  /* 第二個對角頂點的座標 / coordinates of the second diagonal corner */
    int width;   /* 矩形的寬度（水平方向距離） / rectangle width (horizontal distance) */
    int height;  /* 矩形的高度（垂直方向距離） / rectangle height (vertical distance) */
    int area;    /* 矩形面積 / rectangle area */

    /* 讀入兩個座標點 / read the two corner coordinate points */
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    /* 計算寬度（取絕對值，避免負數） / compute width (take absolute value to avoid negatives) */
    width = x2 - x1;
    if (width < 0) {
        width = -width;
    }

    /* 計算高度（取絕對值，避免負數） / compute height (take absolute value to avoid negatives) */
    height = y2 - y1;
    if (height < 0) {
        height = -height;
    }

    /* 計算面積 / compute the area */
    area = width * height;

    /* 輸出面積 / print the area */
    printf("%d\n", area);

    return 0;
}
