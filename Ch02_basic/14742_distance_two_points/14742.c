/*
 * NTHU EE2310 - 題目 14742: Calculate the distance between two points
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 2 章：基本運算
 *   如果不知道如何解題，請參考課本第 2 章的說明。
 *
 * 【題目說明】
 * 輸入兩個浮點數座標點 (x1, y1) 和 (x2, y2)，
 * 計算並輸出兩點之間的歐幾里得距離，結果保留 4 位小數。
 *   距離公式：sqrt((x2-x1)^2 + (y2-y1)^2)
 *
 * 【解題策略】
 * 1. 讀入兩個浮點數座標點
 * 2. 計算 x 方向的差距 dx = x2 - x1
 * 3. 計算 y 方向的差距 dy = y2 - y1
 * 4. 利用畢氏定理：distance = sqrt(dx*dx + dy*dy)
 * 5. 使用 sqrt() 函數需要引入 <math.h>
 * 6. 輸出保留 4 位小數
 */
#include <stdio.h>
#include <math.h>  /* 使用 sqrt() 函數需要此標頭檔 */

int main(void) {
    double x1, y1;  /* 第一個點的座標（浮點數） */
    double x2, y2;  /* 第二個點的座標（浮點數） */
    double dx;      /* x 方向的差距 */
    double dy;      /* y 方向的差距 */
    double dist;    /* 兩點之間的距離 */

    /* 讀入兩個座標點（浮點數用 %lf） */
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);

    /* 計算 x 和 y 方向的差距 */
    dx = x2 - x1;
    dy = y2 - y1;

    /* 利用畢氏定理計算距離 */
    dist = sqrt(dx * dx + dy * dy);

    /* 輸出距離，保留 4 位小數 */
    printf("%.4f\n", dist);

    return 0;
}
