/*
 * NTHU EE2310 - 題目 14742: Calculate the distance between two points
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 7 章（浮點數）
 *   如果不知道如何解題，請參考課本第 7 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14742/
 *
 * 【題目說明】
 * 輸入兩個以極座標表示的點 (r1, theta1) 和 (r2, theta2)（theta 單位為弧度），
 * 計算並輸出兩點之間的歐幾里得距離，結果保留 6 位小數。
 *
 * 【解題策略】
 * 1. 讀入兩個極座標點 (r1, theta1) 和 (r2, theta2)
 * 2. 將極座標轉換為直角座標（theta 已是弧度，直接使用）：
 *    x = r * cos(theta)
 *    y = r * sin(theta)
 * 3. 利用畢氏定理：distance = sqrt((x2-x1)^2 + (y2-y1)^2)
 * 4. 使用 sqrt()、cos()、sin() 函數需要引入 <math.h>
 * 5. 輸出保留 6 位小數
 */
#include <stdio.h>
#include <math.h>  /* 使用 sqrt(), cos(), sin() 函數需要此標頭檔 */

int main(void) {
    double r1, theta1;  /* 第一個點的極座標 */
    double r2, theta2;  /* 第二個點的極座標 */
    double x1, y1;      /* 第一個點的直角座標 */
    double x2, y2;      /* 第二個點的直角座標 */
    double dx;          /* x 方向的差距 */
    double dy;          /* y 方向的差距 */
    double dist;        /* 兩點之間的距離 */

    /* 讀入兩個極座標點（浮點數用 %lf） */
    scanf("%lf %lf %lf %lf", &r1, &theta1, &r2, &theta2);

    /* 將極座標轉換為直角座標（theta 單位為弧度，直接使用） */
    x1 = r1 * cos(theta1);
    y1 = r1 * sin(theta1);
    x2 = r2 * cos(theta2);
    y2 = r2 * sin(theta2);

    /* 計算 x 和 y 方向的差距 */
    dx = x2 - x1;
    dy = y2 - y1;

    /* 利用畢氏定理計算距離 */
    dist = sqrt(dx * dx + dy * dy);

    /* 輸出距離，保留 6 位小數 */
    printf("%.6f\n", dist);

    return 0;
}
