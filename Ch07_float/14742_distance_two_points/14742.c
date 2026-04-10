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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入兩個極座標點的半徑和角度：(r1, theta1) 和 (r2, theta2)，角度單位為弧度。
 * 2. 將第一個點轉換為直角座標：x1 = r1*cos(theta1)，y1 = r1*sin(theta1)。
 * 3. 將第二個點轉換為直角座標：x2 = r2*cos(theta2)，y2 = r2*sin(theta2)。
 * 4. 計算兩點在 x 和 y 方向的差距：dx = x2-x1，dy = y2-y1。
 * 5. 利用畢氏定理計算歐幾里得距離：dist = sqrt(dx*dx + dy*dy)。
 * 6. 以 "%.6f" 格式輸出距離（保留 6 位小數）。
 *
 * English:
 * 1. Read two polar coordinate points: (r1, theta1) and (r2, theta2), with angles in radians.
 * 2. Convert the first point to Cartesian coordinates: x1 = r1*cos(theta1), y1 = r1*sin(theta1).
 * 3. Convert the second point to Cartesian coordinates: x2 = r2*cos(theta2), y2 = r2*sin(theta2).
 * 4. Compute the component differences: dx = x2-x1, dy = y2-y1.
 * 5. Apply the Pythagorean theorem to find the Euclidean distance: dist = sqrt(dx*dx + dy*dy).
 * 6. Print the distance formatted to 6 decimal places with "%.6f".
 */
#include <stdio.h>
#include <math.h>  /* 使用 sqrt(), cos(), sin() 函數需要此標頭檔 / required for sqrt(), cos(), sin() */

int main(void) {
    double r1, theta1;  /* 第一個點的極座標 / polar coordinates of the first point */
    double r2, theta2;  /* 第二個點的極座標 / polar coordinates of the second point */
    double x1, y1;      /* 第一個點的直角座標 / Cartesian coordinates of the first point */
    double x2, y2;      /* 第二個點的直角座標 / Cartesian coordinates of the second point */
    double dx;          /* x 方向的差距 / difference in the x direction */
    double dy;          /* y 方向的差距 / difference in the y direction */
    double dist;        /* 兩點之間的距離 / distance between the two points */

    /* 讀入兩個極座標點（浮點數用 %lf） / read two polar coordinate points (use %lf for double) */
    scanf("%lf %lf %lf %lf", &r1, &theta1, &r2, &theta2);

    /* 將極座標轉換為直角座標（theta 單位為弧度，直接使用） / convert polar to Cartesian (theta already in radians) */
    x1 = r1 * cos(theta1);
    y1 = r1 * sin(theta1);
    x2 = r2 * cos(theta2);
    y2 = r2 * sin(theta2);

    /* 計算 x 和 y 方向的差距 / compute differences in x and y */
    dx = x2 - x1;
    dy = y2 - y1;

    /* 利用畢氏定理計算距離 / compute Euclidean distance using the Pythagorean theorem */
    dist = sqrt(dx * dx + dy * dy);

    /* 輸出距離，保留 6 位小數 / print the distance with 6 decimal places */
    printf("%.6f\n", dist);

    return 0;
}
