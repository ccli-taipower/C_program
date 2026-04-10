/*
 * NTHU EE2310 - 題目 14688: Determine the categories of triangles
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 4 章（判斷）
 *   如果不知道如何解題，請參考課本第 4 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14688/
 *
 * 【題目說明】
 * 輸入三角形三邊長 a, b, c，先判斷能否構成三角形，
 * 若可以，再判斷三角形的類型：
 *   - 等邊三角形（equilateral triangle）：三邊相等
 *   - 等腰三角形（isosceles triangle）：恰好兩邊相等
 *   - 不等邊三角形（scalene triangle）：三邊都不同
 *   - 同時判斷是否為直角三角形（right triangle）
 * 若不能構成三角形，輸出 "Not a triangle"
 *
 * 【解題策略】
 * 1. 讀入三邊長 a, b, c
 * 2. 判斷三角不等式：任意兩邊之和必須大於第三邊
 *    即：a+b>c 且 b+c>a 且 a+c>b
 * 3. 若能構成三角形：
 *    a. 判斷是否等邊：a==b 且 b==c
 *    b. 判斷是否等腰：a==b 或 b==c 或 a==c（但不全等）
 *    c. 否則為不等邊
 *    d. 再判斷是否直角：a²+b²==c² 或 其他排列
 */
#include <stdio.h>

int main(void) {
    int a, b, c;  /* 三角形的三邊長 */

    /* 讀入三邊長 */
    scanf("%d %d %d", &a, &b, &c);

    /* 先判斷能否構成三角形（三角不等式） */
    if (a + b <= c || b + c <= a || a + c <= b) {
        /* 不滿足三角不等式，不能構成三角形 */
        printf("Not a triangle\n");
    } else {
        /* 可以構成三角形，繼續判斷類型 */

        /* 判斷是否為直角三角形（畢氏定理：兩股平方和等於斜邊平方） */
        int is_right = 0;  /* 是否為直角三角形的旗標（0=否，1=是） */
        if (a * a + b * b == c * c ||
            b * b + c * c == a * a ||
            a * a + c * c == b * b) {
            is_right = 1;
        }

        /* 判斷三角形邊長類型 */
        if (a == b && b == c) {
            /* 三邊相等：等邊三角形 */
            printf("equilateral triangle\n");
        } else if (a == b || b == c || a == c) {
            /* 恰好兩邊相等：等腰三角形 */
            if (is_right) {
                printf("isosceles right triangle\n");
            } else {
                printf("isosceles triangle\n");
            }
        } else {
            /* 三邊都不同：不等邊三角形 */
            if (is_right) {
                printf("scalene right triangle\n");
            } else {
                printf("scalene triangle\n");
            }
        }
    }

    return 0;
}
