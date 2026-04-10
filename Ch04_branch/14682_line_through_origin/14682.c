/*
 * NTHU EE2310 - 題目 14682: Check if line passes through the origin
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 4 章（判斷）
 *   如果不知道如何解題，請參考課本第 4 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14682/
 *
 * 【題目說明】
 * 輸入四個正整數 a, b, c, d 代表平面上兩點 (a, b) 和 (c, d)。
 * 判斷過這兩點的直線是否通過原點 (0, 0)。
 * 輸出 "Yes" 或 "No"。
 *
 * 【解題策略】
 * 判斷三點 (a,b)、(c,d)、(0,0) 是否共線，
 * 可以使用叉積（向量法）：
 *   若向量 (a,b) 和向量 (c,d) 平行（叉積為零），則三點共線。
 *   叉積公式：a * d - b * c == 0
 *   （即兩點連線的方向向量與原點到其中一點的向量平行）
 *
 * 原理：直線方程式為 (y - b) / (x - a) = (d - b) / (c - a)
 * 代入 (0, 0)：(-b) * (c - a) = (-a) * (d - b)
 * 化簡：b*(c-a) == a*(d-b)
 *       bc - ab == ad - ab
 *       bc == ad
 *       即 a*d - b*c == 0
 */
#include <stdio.h>

int main(void) {
    int a, b;  /* 第一個點的座標 (a, b) */
    int c, d;  /* 第二個點的座標 (c, d) */

    /* 讀入兩個點的座標 */
    scanf("%d %d %d %d", &a, &b, &c, &d);

    /* 使用叉積判斷三點是否共線：a*d - b*c == 0 */
    if (a * d - b * c == 0) {
        /* 叉積為零，表示過原點 */
        printf("Yes\n");
    } else {
        /* 叉積不為零，表示不過原點 */
        printf("No\n");
    }

    return 0;
}
