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
 */
#include <stdio.h>

int main(void) {
    int x1, y1;  /* 第一個對角頂點的座標 */
    int x2, y2;  /* 第二個對角頂點的座標 */
    int width;   /* 矩形的寬度（水平方向距離） */
    int height;  /* 矩形的高度（垂直方向距離） */
    int area;    /* 矩形面積 */

    /* 讀入兩個座標點 */
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    /* 計算寬度（取絕對值，避免負數） */
    width = x2 - x1;
    if (width < 0) {
        width = -width;
    }

    /* 計算高度（取絕對值，避免負數） */
    height = y2 - y1;
    if (height < 0) {
        height = -height;
    }

    /* 計算面積 */
    area = width * height;

    /* 輸出面積 */
    printf("%d\n", area);

    return 0;
}
