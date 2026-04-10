/*
 * NTHU EE2310 - 題目 14744: Roots of a quadratic equation
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 2 章：基本運算
 *   如果不知道如何解題，請參考課本第 2 章的說明。
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
 */
#include <stdio.h>
#include <math.h>  /* 使用 sqrt() 函數需要此標頭檔 */

int main(void) {
    double a, b, c;   /* 二次方程式的係數 */
    double d;         /* 判別式 d = b² - 4ac */
    double root1;     /* 較大的根 */
    double root2;     /* 較小的根 */

    /* 讀入係數 a, b, c */
    scanf("%lf %lf %lf", &a, &b, &c);

    /* 計算判別式 */
    d = b * b - 4.0 * a * c;

    if (d > 0) {
        /* 判別式大於零：兩個不同實數根 */
        /* 較大的根：(-b + sqrt(d)) / (2a) */
        root1 = (-b + sqrt(d)) / (2.0 * a);
        /* 較小的根：(-b - sqrt(d)) / (2a) */
        root2 = (-b - sqrt(d)) / (2.0 * a);

        /* 確保 root1 >= root2（較大的先輸出） */
        if (root1 < root2) {
            double temp = root1;
            root1 = root2;
            root2 = temp;
        }

        /* 輸出兩個根，保留 4 位小數 */
        printf("%.4f\n", root1);
        printf("%.4f\n", root2);
    } else if (d == 0) {
        /* 判別式等於零：一個重根 */
        root1 = -b / (2.0 * a);
        printf("%.4f\n", root1);
    } else {
        /* 判別式小於零：無實數根 */
        printf("No real roots\n");
    }

    return 0;
}
