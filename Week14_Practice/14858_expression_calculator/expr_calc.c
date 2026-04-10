/*
 * NTHU ACM 14858 - Expression Calculator (HARD)
 * Tags: 11410EE 231002
 *
 * Evaluate a single-line arithmetic expression containing space-separated
 * integers (possibly negative) and the operators + - * /. Multiplication and
 * division bind tighter than addition and subtraction; within the same
 * precedence class operators are left-associative.
 *
 * Strategy: tokenize into parallel arrays nums[] and ops[], then
 *   pass 1: scan left-to-right, folding every * and / into its left operand.
 *   pass 2: do the same for + and -.
 * The final value is nums[0].
 *
 * Example:
 *   5 + 3 * 5 - 9 / 3 * -7
 * After pass 1: 5 + 15 - (-21)    (i.e. 5 + 15 - -21)
 * After pass 2: 41
 *
 * The final answer is guaranteed to be an integer, so plain int arithmetic
 * is fine for the intended inputs.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOK 1024

/* A token is an operator char iff its string length is 1 AND the single
 * character is one of + - * /. "-9" is a number because it has length 2. */
static int is_operator_token(const char *s) {
    if (s[0] == '\0' || s[1] != '\0') return 0;
    return s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/';
}

int main(void) {
    long long nums[MAXTOK];
    char      ops[MAXTOK];
    int       n_nums = 0, n_ops = 0;

    char tok[64];
    /* First token must be a number. */
    if (scanf("%63s", tok) != 1) return 0;
    nums[n_nums++] = strtoll(tok, NULL, 10);

    /* Subsequent tokens alternate: operator, number, operator, number, ... */
    while (scanf("%63s", tok) == 1) {
        if (is_operator_token(tok)) {
            ops[n_ops++] = tok[0];
        } else {
            nums[n_nums++] = strtoll(tok, NULL, 10);
        }
    }

    /* Pass 1: fold * and / left-to-right. */
    int i = 0;
    while (i < n_ops) {
        if (ops[i] == '*' || ops[i] == '/') {
            long long a = nums[i], b = nums[i + 1];
            long long r = (ops[i] == '*') ? (a * b) : (a / b);
            nums[i] = r;
            /* shift nums[i+2..] left by one */
            for (int k = i + 1; k < n_nums - 1; ++k) nums[k] = nums[k + 1];
            --n_nums;
            for (int k = i; k < n_ops - 1; ++k) ops[k] = ops[k + 1];
            --n_ops;
        } else {
            ++i;
        }
    }

    /* Pass 2: fold + and - left-to-right. */
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

    printf("%lld\n", nums[0]);
    return 0;
}
