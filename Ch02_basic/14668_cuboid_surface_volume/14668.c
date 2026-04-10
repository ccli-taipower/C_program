/*
 * NTHU EE2310 - 題目 14668: Compute surface area and volume of a cuboid
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 2 章：基本運算
 *   如果不知道如何解題，請參考課本第 2 章的說明。
 *
 * 【題目說明】
 * 輸入長方體的長 l、寬 w、高 h，
 * 計算並輸出長方體的表面積和體積。
 *   表面積公式：2 * (l*w + w*h + l*h)
 *   體積公式：l * w * h
 *
 * 【解題策略】
 * 1. 讀入三個整數：長 l、寬 w、高 h
 * 2. 計算表面積：長方體有 6 個面，兩兩相對，
 *    共 3 組：底面(l*w)、側面(w*h)、正面(l*h)，各兩個
 * 3. 計算體積：三邊相乘
 * 4. 先輸出表面積，再輸出體積，各佔一行
 */
#include <stdio.h>

int main(void) {
    int l;            /* 長方體的長（length） */
    int w;            /* 長方體的寬（width） */
    int h;            /* 長方體的高（height） */
    int surface_area; /* 表面積 = 2*(l*w + w*h + l*h) */
    int volume;       /* 體積 = l * w * h */

    /* 讀入長、寬、高 */
    scanf("%d %d %d", &l, &w, &h);

    /* 計算表面積：6個面，3組相對面 */
    surface_area = 2 * (l * w + w * h + l * h);

    /* 計算體積 */
    volume = l * w * h;

    /* 輸出結果：先表面積後體積，各佔一行 */
    printf("%d\n", surface_area);
    printf("%d\n", volume);

    return 0;
}
