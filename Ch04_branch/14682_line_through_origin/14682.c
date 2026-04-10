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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 宣告四個整數 a, b, c, d，分別對應兩點座標 (a,b) 和 (c,d)。
 * 2. 使用 scanf 讀入四個整數。
 * 3. 判斷三點 (a,b)、(c,d)、(0,0) 是否共線的數學核心是叉積。
 *    兩個向量 v1=(a,b) 和 v2=(c,d) 的叉積 = a*d - b*c。
 *    若叉積為零，表示 v1 和 v2 方向相同（或相反），即三點共線，
 *    也就是過兩點的直線通過原點。
 * 4. 使用 if 判斷 a*d - b*c == 0：
 *    - 為零：輸出 "Yes"，表示直線過原點。
 *    - 不為零：輸出 "No"，表示直線不過原點。
 * 5. 此方法避免了除法（可能除以零的風險），是更穩健的實作方式。
 * 6. 程式輸出後結束，回傳 0。
 *
 * English:
 * 1. Declare four integers a, b, c, d corresponding to two points (a,b) and (c,d).
 * 2. Use scanf to read all four integers.
 * 3. The mathematical core is the cross product of vectors v1=(a,b) and v2=(c,d):
 *    cross product = a*d - b*c.
 *    If the cross product is zero, v1 and v2 are parallel (or anti-parallel),
 *    meaning all three points (a,b), (c,d), and (0,0) are collinear —
 *    the line through the two points passes through the origin.
 * 4. Use an if statement to check a*d - b*c == 0:
 *    - Zero: print "Yes" (line passes through origin).
 *    - Non-zero: print "No" (line does not pass through origin).
 * 5. This avoids division (which risks divide-by-zero), making the solution more robust.
 * 6. Print the result, return 0, and exit.
 */
#include <stdio.h>

int main(void) {
    int a, b;  /* 第一個點的座標 (a, b) / coordinates of the first point (a, b) */
    int c, d;  /* 第二個點的座標 (c, d) / coordinates of the second point (c, d) */

    /* 讀入兩個點的座標 / read the coordinates of both points */
    scanf("%d %d %d %d", &a, &b, &c, &d);

    /* 使用叉積判斷三點是否共線：a*d - b*c == 0 / use cross product to check collinearity: a*d - b*c == 0 */
    if (a * d - b * c == 0) {
        /* 叉積為零，表示過原點 / cross product is zero, line passes through the origin */
        printf("Yes\n");
    } else {
        /* 叉積不為零，表示不過原點 / cross product is non-zero, line does not pass through the origin */
        printf("No\n");
    }

    return 0;
}
