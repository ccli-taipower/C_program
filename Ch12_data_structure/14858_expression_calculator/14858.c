/*
 * NTHU EE2310 - 題目 14858: Expression Calculator（運算式計算器）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 12 章（資料結構）
 *   如果不知道如何解題，請參考課本第 12 章的說明。
 *
 * 【題目說明】
 * 給定一行以空白分隔的算術運算式，其中包含整數（可為負數）
 * 以及運算子 + - * /。乘除法優先於加減法；同優先權的運算子
 * 由左至右結合。輸出運算式的整數結果。
 *
 * 【解題策略】
 * 將輸入 tokenize 成數字陣列 nums[] 與運算子陣列 ops[]，
 * 再進行兩次掃描：
 *   第一次：由左至右，將所有 * 和 / 折疊到左側運算元。
 *   第二次：由左至右，將所有 + 和 - 折疊到左側運算元。
 * 最終答案為 nums[0]。
 *
 * 範例：5 + 3 * 5 - 9 / 3 * -7
 *   第一次後：5 + 15 - -21
 *   第二次後：41
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOK 1024

/* 判斷 token 是否為運算子：長度為 1 且為 + - * / 之一。
 * 注意 "-9" 長度為 2，視為數字。 */
static int is_operator_token(const char *s) {
    if (s[0] == '\0' || s[1] != '\0') return 0;
    return s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/';
}

int main(void) {
    long long nums[MAXTOK];   /* 數字陣列 */
    char      ops[MAXTOK];    /* 運算子陣列 */
    int       n_nums = 0, n_ops = 0;

    char tok[64];
    /* 讀取第一個 token（必為數字） */
    if (scanf("%63s", tok) != 1) return 0;
    nums[n_nums++] = strtoll(tok, NULL, 10);

    /* 後續 token 交替出現：運算子、數字、運算子、數字…… */
    while (scanf("%63s", tok) == 1) {
        if (is_operator_token(tok)) {
            ops[n_ops++] = tok[0];
        } else {
            nums[n_nums++] = strtoll(tok, NULL, 10);
        }
    }

    /* 第一次掃描：由左至右，折疊所有 * 和 / */
    int i = 0;
    while (i < n_ops) {
        if (ops[i] == '*' || ops[i] == '/') {
            long long a = nums[i], b = nums[i + 1];
            long long r = (ops[i] == '*') ? (a * b) : (a / b);
            nums[i] = r;
            /* 將 nums[i+2..] 向左移動一格 */
            for (int k = i + 1; k < n_nums - 1; ++k) nums[k] = nums[k + 1];
            --n_nums;
            for (int k = i; k < n_ops - 1; ++k) ops[k] = ops[k + 1];
            --n_ops;
        } else {
            ++i;
        }
    }

    /* 第二次掃描：由左至右，折疊所有 + 和 - */
    i = 0;
    while (i < n_ops) {
        long long a = nums[i], b = nums[i + 1];
        long long r = (ops[i] == '+') ? (a + b) : (a - b);
        nums[i] = r;
        for (int k = i + 1; k < n_nums - 1; ++k) nums[k] = nums[k + 1];
        --n_nums;
        for (int k = i; k < n_ops - 1; ++k) ops[k] = ops[k + 1];
        --n_ops;
    }

    /* 輸出最終結果 */
    printf("%lld\n", nums[0]);
    return 0;
}
