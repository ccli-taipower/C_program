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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 宣告三個整數 a、b、c 儲存三邊長，以及旗標 is_right（0=非直角，1=直角）。
 * 2. 使用 scanf 讀入三邊長。
 * 3. 先判斷三角不等式：若任一邊不滿足（任意兩邊之和 <= 第三邊），
 *    直接輸出 "Not a triangle" 並結束，避免對無效輸入繼續判斷。
 * 4. 進入 else 分支後，先獨立計算 is_right：
 *    用畢氏定理的三種排列（哪一邊可能是斜邊）判斷是否為直角三角形。
 *    提前計算 is_right 是為了後續邊長類型判斷中能複用。
 * 5. 判斷邊長類型（由嚴格到寬鬆的順序）：
 *    - 等邊：a==b 且 b==c，三邊完全相等（等邊三角形不可能是直角三角形，故不需加 is_right）。
 *    - 等腰：a==b 或 b==c 或 a==c（但前提是不全等），再結合 is_right 決定輸出。
 *    - 不等邊：三邊皆不同，再結合 is_right 決定輸出。
 * 6. 結合邊長類型與直角旗標輸出對應字串，程式結束。
 *
 * English:
 * 1. Declare integers a, b, c for the three sides and flag is_right (0=no, 1=yes).
 * 2. Use scanf to read the three side lengths.
 * 3. Check the triangle inequality first: if any side violates it (sum of two sides <= third),
 *    immediately print "Not a triangle" and skip further checks to avoid processing invalid input.
 * 4. Inside the else branch, independently compute is_right using all three
 *    permutations of the Pythagorean theorem (any side could be the hypotenuse).
 *    Computing it up front allows reuse across all subsequent branch cases.
 * 5. Classify the triangle by side lengths from most to least restrictive:
 *    - Equilateral: a==b and b==c (all sides equal; equilateral triangles cannot be
 *      right triangles, so is_right is not combined here).
 *    - Isosceles: exactly two sides equal (the equilateral case is already handled above);
 *      combine with is_right to choose between "isosceles right triangle" and "isosceles triangle".
 *    - Scalene: all sides different; combine with is_right to choose the output string.
 * 6. Print the appropriate string based on the combined classification and return 0.
 */
#include <stdio.h>

int main(void) {
    int a, b, c;  /* 三角形的三邊長 / the three side lengths of the triangle */

    /* 讀入三邊長 / read the three side lengths */
    scanf("%d %d %d", &a, &b, &c);

    /* 先判斷能否構成三角形（三角不等式） / first check if the sides satisfy the triangle inequality */
    if (a + b <= c || b + c <= a || a + c <= b) {
        /* 不滿足三角不等式，不能構成三角形 / triangle inequality violated, cannot form a triangle */
        printf("Not a triangle\n");
    } else {
        /* 可以構成三角形，繼續判斷類型 / valid triangle, proceed to classify its type */

        /* 判斷是否為直角三角形（畢氏定理：兩股平方和等於斜邊平方） / check for right triangle using the Pythagorean theorem */
        int is_right = 0;  /* 是否為直角三角形的旗標（0=否，1=是） / right-triangle flag (0=no, 1=yes) */
        if (a * a + b * b == c * c ||
            b * b + c * c == a * a ||
            a * a + c * c == b * b) {
            is_right = 1;
        }

        /* 判斷三角形邊長類型 / classify the triangle by its side lengths */
        if (a == b && b == c) {
            /* 三邊相等：等邊三角形 / all three sides equal: equilateral triangle */
            printf("equilateral triangle\n");
        } else if (a == b || b == c || a == c) {
            /* 恰好兩邊相等：等腰三角形 / exactly two sides equal: isosceles triangle */
            if (is_right) {
                printf("isosceles right triangle\n");
            } else {
                printf("isosceles triangle\n");
            }
        } else {
            /* 三邊都不同：不等邊三角形 / all three sides different: scalene triangle */
            if (is_right) {
                printf("scalene right triangle\n");
            } else {
                printf("scalene triangle\n");
            }
        }
    }

    return 0;
}
