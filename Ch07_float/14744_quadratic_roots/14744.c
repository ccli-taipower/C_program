/*
 * NTHU EE2310 - 題目 14744: Roots of a quadratic equation
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 7 章（浮點數）
 *   如果不知道如何解題，請參考課本第 7 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14744/
 *
 * 【題目說明】
 * 輸入二次方程式 ax² + bx + c = 0 的係數 a, b, c（浮點數），
 * 計算方程式的根。判別式 d = b² - 4ac 決定根的情況：
 *   - 若 d > 0：有兩個不同實數根（較大的根先輸出）
 *   - 若 d = 0：有一個重根
 *   - 若 d < 0：無實數根，輸出 "No real roots"
 * 輸出保留 4 位小數。
 *
 * 【解題策略】
 * 1. 讀入係數 a, b, c
 * 2. 計算判別式 d = b*b - 4*a*c
 * 3. 根據 d 的正負零分三種情況處理：
 *    - d > 0：利用公式 root = (-b ± sqrt(d)) / (2a) 求兩根
 *    - d = 0：唯一根 root = -b / (2a)
 *    - d < 0：輸出無實數根
 * 4. 使用 sqrt() 需引入 <math.h>
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀入二次方程式的係數 a、b、c（double 型別）。
 * 2. 計算判別式 d = b*b - 4.0*a*c。
 * 3. 若 d > 0：計算兩根 root1 = (-b+sqrt(d))/(2a)，root2 = (-b-sqrt(d))/(2a)；
 *    若 root1 < root2 則交換，確保較大的根先輸出；輸出兩根（保留 4 位小數）。
 * 4. 若 d == 0：計算唯一重根 root1 = -b/(2a)，輸出一個根（保留 4 位小數）。
 * 5. 若 d < 0：方程式無實數根，輸出 "No real roots"。
 *
 * English:
 * 1. Read the quadratic equation coefficients a, b, c as doubles.
 * 2. Compute the discriminant d = b*b - 4.0*a*c.
 * 3. If d > 0: compute root1 = (-b+sqrt(d))/(2a) and root2 = (-b-sqrt(d))/(2a);
 *    swap them if root1 < root2 so the larger root is printed first; print both roots to 4 decimal places.
 * 4. If d == 0: compute the repeated root root1 = -b/(2a) and print it to 4 decimal places.
 * 5. If d < 0: the equation has no real roots; print "No real roots".
 */
#include <stdio.h>
#include <math.h>  /* 使用 sqrt() 函數需要此標頭檔 / required for sqrt() */

int main(void) {
    double a, b, c;   /* 二次方程式的係數 / coefficients of the quadratic equation */
    double d;         /* 判別式 d = b² - 4ac / discriminant d = b² - 4ac */
    double root1;     /* 較大的根 / the larger root */
    double root2;     /* 較小的根 / the smaller root */

    /* 讀入係數 a, b, c / read coefficients a, b, c */
    scanf("%lf %lf %lf", &a, &b, &c);

    /* 計算判別式 / compute the discriminant */
    d = b * b - 4.0 * a * c;

    if (d > 0) {
        /* 判別式大於零：兩個不同實數根 / discriminant > 0: two distinct real roots */
        /* 較大的根：(-b + sqrt(d)) / (2a) / larger root: (-b + sqrt(d)) / (2a) */
        root1 = (-b + sqrt(d)) / (2.0 * a);
        /* 較小的根：(-b - sqrt(d)) / (2a) / smaller root: (-b - sqrt(d)) / (2a) */
        root2 = (-b - sqrt(d)) / (2.0 * a);

        /* 確保 root1 >= root2（較大的先輸出） / ensure root1 >= root2 (larger root printed first) */
        if (root1 < root2) {
            double temp = root1;
            root1 = root2;
            root2 = temp;
        }

        /* 輸出兩個根，保留 4 位小數 / print both roots to 4 decimal places */
        printf("%.4f\n", root1);
        printf("%.4f\n", root2);
    } else if (d == 0) {
        /* 判別式等於零：一個重根 / discriminant == 0: one repeated root */
        root1 = -b / (2.0 * a);
        printf("%.4f\n", root1);
    } else {
        /* 判別式小於零：無實數根 / discriminant < 0: no real roots */
        printf("No real roots\n");
    }

    return 0;
}
