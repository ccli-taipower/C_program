/*
 * NTHU EE2310 - 題目 14684: Determine if line segments can form a triangle
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 4 章（判斷）
 *   如果不知道如何解題，請參考課本第 4 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14684/
 *
 * 【題目說明】
 * 輸入三個線段長度 a, b, c（正整數），判斷這三條線段是否能構成三角形。
 * 能構成三角形的條件（三角不等式）：任意兩邊之和必須大於第三邊
 *   a + b > c
 *   b + c > a
 *   a + c > b
 * 三個條件必須同時滿足才能構成三角形。
 * 輸出 "Yes" 或 "No"。
 *
 * 【解題策略】
 * 1. 讀入三邊長 a, b, c
 * 2. 同時驗證三個三角不等式
 * 3. 若三個條件都滿足，輸出 "Yes"；否則輸出 "No"
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 宣告三個整數 a、b、c 以儲存三條線段的長度。
 * 2. 使用 scanf 讀入三個整數。
 * 3. 三角形存在的充要條件是任意兩邊之和必須嚴格大於第三邊（三角不等式）：
 *    - a + b > c（a 和 b 的和必須大於 c）
 *    - b + c > a（b 和 c 的和必須大於 a）
 *    - a + c > b（a 和 c 的和必須大於 b）
 *    三個條件缺一不可，使用 && 連接確保同時成立。
 * 4. 若 if 條件為真，表示可以構成三角形，輸出 "Yes"。
 * 5. 否則進入 else 分支，輸出 "No"，表示不能構成三角形。
 * 6. 程式結束，回傳 0。
 *
 * English:
 * 1. Declare three integers a, b, c to store the lengths of the three line segments.
 * 2. Use scanf to read all three integers.
 * 3. A triangle exists if and only if all three triangle inequalities hold simultaneously:
 *    - a + b > c (sum of a and b must exceed c)
 *    - b + c > a (sum of b and c must exceed a)
 *    - a + c > b (sum of a and c must exceed b)
 *    All three must hold; they are combined with && to enforce this.
 * 4. If the if condition is true, the segments can form a triangle: print "Yes".
 * 5. Otherwise the else branch executes and prints "No".
 * 6. Return 0 to indicate successful completion.
 */
#include <stdio.h>

int main(void) {
    int a, b, c;  /* 三條線段的長度 / lengths of the three line segments */

    /* 讀入三條線段長度 / read the three segment lengths */
    scanf("%d %d %d", &a, &b, &c);

    /* 判斷三角不等式：三個條件必須同時成立 / check triangle inequality: all three conditions must hold */
    if (a + b > c && b + c > a && a + c > b) {
        /* 三個條件都滿足，可以構成三角形 / all conditions satisfied, segments form a triangle */
        printf("Yes\n");
    } else {
        /* 至少一個條件不滿足，不能構成三角形 / at least one condition fails, cannot form a triangle */
        printf("No\n");
    }

    return 0;
}
