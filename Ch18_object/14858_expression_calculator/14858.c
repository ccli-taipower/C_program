/*
 * NTHU EE2310 - 題目 14858: Expression Calculator（運算式計算器）
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 18 章（物件）
 *   如果不知道如何解題，請參考課本第 18 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14858/
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
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 讀取第一個 token 並以 strtoll() 轉為整數，存入 nums[0]，作為運算式的起始數字。
 * 2. 迴圈讀取後續 token：呼叫 is_operator_token() 判斷是否為單字元運算子（長度 1 且為 +-*/）；是則存入 ops[]，否則轉換後存入 nums[]。
 * 3. 第一次掃描：以索引 i 由左至右遍歷 ops[]，遇到 * 或 / 時計算 nums[i] op nums[i+1] 並覆寫 nums[i]，再將 nums[i+2..] 和 ops[i+1..] 左移一格，縮短陣列長度。
 * 4. 第二次掃描：對剩餘的 + 和 - 做同樣的折疊操作，所有運算子處理完後 nums[0] 即為最終結果。
 * 5. 輸出 nums[0] 為 64 位元整數（%lld），確保不因中間乘法溢位而出錯。
 * 6. is_operator_token() 以長度判斷區分負數（如 "-9" 長度 2）和減法運算子（"-" 長度 1），正確處理負數 token。
 *
 * English:
 * 1. Read the first token and convert it to a 64-bit integer with strtoll(), storing it in nums[0] as the starting operand.
 * 2. Loop to read subsequent tokens: call is_operator_token() to detect single-character operators (length 1, one of +-*/); store operators in ops[] and numeric tokens in nums[].
 * 3. First pass: iterate ops[] left-to-right with index i; when ops[i] is * or /, compute nums[i] op nums[i+1], overwrite nums[i], and left-shift nums[i+2..] and ops[i+1..] to shrink the arrays.
 * 4. Second pass: apply the same folding for remaining + and - operators; after all operators are processed, nums[0] holds the final result.
 * 5. Print nums[0] as a 64-bit integer (%lld) to avoid overflow from intermediate multiplications.
 * 6. is_operator_token() uses string length to distinguish negative numbers (e.g., "-9" has length 2) from the subtraction operator ("-" has length 1), correctly handling negative operands.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOK 1024

/* 判斷 token 是否為運算子：長度為 1 且為 + - * / 之一。注意 "-9" 長度為 2，視為數字。
 * / check if token is an operator: length 1 and one of + - * /; note "-9" has length 2 and is treated as a number. */
static int is_operator_token(const char *s) {
    if (s[0] == '\0' || s[1] != '\0') return 0;
    return s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/';
}

int main(void) {
    long long nums[MAXTOK];   /* 數字陣列 / operand array */
    char      ops[MAXTOK];    /* 運算子陣列 / operator array */
    int       n_nums = 0, n_ops = 0;

    char tok[64];
    /* 讀取第一個 token（必為數字） / read the first token (must be a number) */
    if (scanf("%63s", tok) != 1) return 0;
    nums[n_nums++] = strtoll(tok, NULL, 10);

    /* 後續 token 交替出現：運算子、數字、運算子、數字…… / subsequent tokens alternate: operator, number, operator, number... */
    while (scanf("%63s", tok) == 1) {
        if (is_operator_token(tok)) {
            ops[n_ops++] = tok[0];
        } else {
            nums[n_nums++] = strtoll(tok, NULL, 10);
        }
    }

    /* 第一次掃描：由左至右，折疊所有 * 和 / / first pass: left-to-right, fold all * and / operators */
    int i = 0;
    while (i < n_ops) {
        if (ops[i] == '*' || ops[i] == '/') {
            long long a = nums[i], b = nums[i + 1];
            long long r = (ops[i] == '*') ? (a * b) : (a / b);
            nums[i] = r;
            /* 將 nums[i+2..] 向左移動一格 / shift nums[i+2..] one slot to the left */
            for (int k = i + 1; k < n_nums - 1; ++k) nums[k] = nums[k + 1];
            --n_nums;
            for (int k = i; k < n_ops - 1; ++k) ops[k] = ops[k + 1];
            --n_ops;
        } else {
            ++i;
        }
    }

    /* 第二次掃描：由左至右，折疊所有 + 和 - / second pass: left-to-right, fold all + and - operators */
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

    /* 輸出最終結果 / print the final result */
    printf("%lld\n", nums[0]);
    return 0;
}
