/*
 * NTHU EE2310 - 題目 14683: Compute number of animals in a cage
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 4 章（判斷）
 *   如果不知道如何解題，請參考課本第 4 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14683/
 *
 * 【題目說明】
 * 籠中有雞和兔，已知：
 *   - 雞有 2 條腿，兔有 4 條腿
 *   - 共有 h 個頭（即 h 隻動物）
 *   - 共有 f 條腿
 * 計算雞有幾隻、兔有幾隻。
 * 若無解，輸出 "No solution"。
 *
 * 【解題策略】
 * 設雞有 chicken 隻，兔有 rabbit 隻：
 *   雞 + 兔 = h（頭數方程式）
 *   2*雞 + 4*兔 = f（腿數方程式）
 *
 * 由第一個方程式：雞 = h - 兔
 * 代入第二個方程式：2*(h - 兔) + 4*兔 = f
 *   2h - 2兔 + 4兔 = f
 *   2兔 = f - 2h
 *   兔 = (f - 2h) / 2
 *
 * 若兔的數量為非負整數，且不超過總頭數，則有解；否則無解。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 宣告 h（頭數）、f（腿數）、rabbit（兔子數）、chicken（雞數）。
 * 2. 使用 scanf 讀入 h 和 f。
 * 3. 建立方程組：設雞有 x 隻、兔有 y 隻，
 *    則 x + y = h（頭）；2x + 4y = f（腿）。
 *    由第一式代入第二式，消去 x，化簡得 y = (f - 2h) / 2。
 * 4. 驗證解的合法性（三個條件）：
 *    a. f - 2h >= 0：腿數不能少於每隻動物至少 2 條腿的下限。
 *    b. (f - 2h) % 2 == 0：結果必須整除，否則兔子數不是整數。
 *    c. chicken = h - rabbit >= 0：雞數也必須非負。
 * 5. 若三個條件都滿足，計算並輸出雞數和兔數（空格分隔）。
 * 6. 若任一條件不滿足，輸出 "No solution"。
 *
 * English:
 * 1. Declare h (head count), f (leg/feet count), rabbit, and chicken.
 * 2. Use scanf to read h and f.
 * 3. Set up a system of equations: let x = chickens, y = rabbits.
 *    x + y = h (heads); 2x + 4y = f (legs).
 *    Substituting from the first equation into the second and simplifying gives y = (f - 2h) / 2.
 * 4. Validate the solution with three checks:
 *    a. f - 2h >= 0: total legs must be at least 2 per animal.
 *    b. (f - 2h) % 2 == 0: the result must divide evenly; rabbits must be a whole number.
 *    c. chicken = h - rabbit >= 0: the chicken count must also be non-negative.
 * 5. If all checks pass, compute and print chicken count and rabbit count separated by a space.
 * 6. If any check fails, print "No solution".
 */
#include <stdio.h>

int main(void) {
    int h;        /* 總頭數（head count） / total number of heads */
    int f;        /* 總腿數（feet count） / total number of legs */
    int rabbit;   /* 兔子的數量 / number of rabbits */
    int chicken;  /* 雞的數量 / number of chickens */

    /* 讀入頭數和腿數 / read head count and leg count */
    scanf("%d %d", &h, &f);

    /* 計算兔子數量：rabbit = (f - 2*h) / 2 / compute rabbit count: rabbit = (f - 2*h) / 2 */
    /* 先判斷 (f - 2*h) 是否為非負偶數 / first check if (f - 2*h) is a non-negative even number */
    if ((f - 2 * h) >= 0 && (f - 2 * h) % 2 == 0) {
        rabbit = (f - 2 * h) / 2;
        chicken = h - rabbit;

        /* 再確認雞的數量也是非負整數 / also verify that the chicken count is non-negative */
        if (chicken >= 0) {
            /* 有解：輸出雞和兔的數量 / valid solution: print chicken and rabbit counts */
            printf("%d %d\n", chicken, rabbit);
        } else {
            /* 無解 / no valid solution */
            printf("No solution\n");
        }
    } else {
        /* (f - 2h) 為負數或奇數，無解 / (f - 2h) is negative or odd, no solution */
        printf("No solution\n");
    }

    return 0;
}
