/*
 * NTHU EE2310 - 題目 14683: Compute number of animals in a cage
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 3 章：條件判斷
 *   如果不知道如何解題，請參考課本第 3 章的說明。
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
 */
#include <stdio.h>

int main(void) {
    int h;        /* 總頭數（head count） */
    int f;        /* 總腿數（feet count） */
    int rabbit;   /* 兔子的數量 */
    int chicken;  /* 雞的數量 */

    /* 讀入頭數和腿數 */
    scanf("%d %d", &h, &f);

    /* 計算兔子數量：rabbit = (f - 2*h) / 2 */
    /* 先判斷 (f - 2*h) 是否為非負偶數 */
    if ((f - 2 * h) >= 0 && (f - 2 * h) % 2 == 0) {
        rabbit = (f - 2 * h) / 2;
        chicken = h - rabbit;

        /* 再確認雞的數量也是非負整數 */
        if (chicken >= 0) {
            /* 有解：輸出雞和兔的數量 */
            printf("%d %d\n", chicken, rabbit);
        } else {
            /* 無解 */
            printf("No solution\n");
        }
    } else {
        /* (f - 2h) 為負數或奇數，無解 */
        printf("No solution\n");
    }

    return 0;
}
