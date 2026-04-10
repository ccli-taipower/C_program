/*
 * NTHU EE2310 - 題目 14668: Compute surface area and volume of a cuboid
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 3 章（運算）
 *   如果不知道如何解題，請參考課本第 3 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14668/
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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 宣告 l（長）、w（寬）、h（高）三個整數變數來儲存輸入，
 *    另宣告 surface_area 和 volume 儲存計算結果。
 * 2. 使用 scanf 讀入三個整數，依序對應長、寬、高。
 * 3. 計算表面積：長方體共有 6 個矩形面，形成 3 對相對面：
 *    - 底面與頂面：各面積為 l*w，兩片共 2*l*w
 *    - 前面與後面：各面積為 l*h，兩片共 2*l*h
 *    - 左面與右面：各面積為 w*h，兩片共 2*w*h
 *    總表面積 = 2*(l*w + w*h + l*h)，提出公因數 2 可簡化運算。
 * 4. 計算體積：長方體體積等於三邊相乘，即 l * w * h。
 * 5. 先輸出表面積後輸出體積，兩者各佔一行，順序不可顛倒。
 * 6. 回傳 0 表示程式正常結束。
 *
 * English:
 * 1. Declare integers l (length), w (width), h (height) for input,
 *    and surface_area and volume for computed results.
 * 2. Use scanf to read three integers in order: l, w, h.
 * 3. Compute surface area: a cuboid has 6 rectangular faces forming 3 pairs:
 *    - Bottom and top: area l*w each, total 2*l*w
 *    - Front and back: area l*h each, total 2*l*h
 *    - Left and right: area w*h each, total 2*w*h
 *    Total surface area = 2*(l*w + w*h + l*h); factoring out 2 simplifies the expression.
 * 4. Compute volume: multiply all three dimensions, i.e. l * w * h.
 * 5. Print surface area then volume, each on its own line, in the required order.
 * 6. Return 0 to indicate successful termination.
 */
#include <stdio.h>

int main(void) {
    int l;            /* 長方體的長（length） / cuboid length */
    int w;            /* 長方體的寬（width） / cuboid width */
    int h;            /* 長方體的高（height） / cuboid height */
    int surface_area; /* 表面積 = 2*(l*w + w*h + l*h) / surface area = 2*(l*w + w*h + l*h) */
    int volume;       /* 體積 = l * w * h / volume = l * w * h */

    /* 讀入長、寬、高 / read length, width, and height */
    scanf("%d %d %d", &l, &w, &h);

    /* 計算表面積：6個面，3組相對面 / compute surface area: 6 faces forming 3 opposite pairs */
    surface_area = 2 * (l * w + w * h + l * h);

    /* 計算體積 / compute the volume */
    volume = l * w * h;

    /* 輸出結果：先表面積後體積，各佔一行 / print surface area then volume, each on its own line */
    printf("%d\n", surface_area);
    printf("%d\n", volume);

    return 0;
}
