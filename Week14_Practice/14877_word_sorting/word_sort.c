/*
 * NTHU ACM 14877 - Custom English Word Sorting
 * Contest: EE2310 Week 14 Practice
 * Tags: 11410EE 231002
 *
 * Sort n words (length <= m, 0 < n <= 1e5, 0 < m <= 80) using qsort()
 * under the following key order, from most to least significant:
 *   1. Shorter words come first.
 *   2. Fewer uppercase letters come first.
 *   3. Fewer vowels (a/e/i/o/u, either case) come first.
 *   4. strcmp() order.
 *
 * Because we must call qsort (not bubble sort) and stable ordering is not
 * required, the comparator fully encodes all four tiebreakers.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXLEN 128

static char words[MAXN][MAXLEN];

static int is_vowel(char c) {
    switch (c) {
        case 'a': case 'e': case 'i': case 'o': case 'u':
        case 'A': case 'E': case 'I': case 'O': case 'U':
            return 1;
        default:
            return 0;
    }
}

static int count_upper(const char *s) {
    int c = 0;
    for (; *s; ++s) if (*s >= 'A' && *s <= 'Z') ++c;
    return c;
}

static int count_vowels(const char *s) {
    int c = 0;
    for (; *s; ++s) if (is_vowel(*s)) ++c;
    return c;
}

static int cmp_word(const void *pa, const void *pb) {
    const char *a = (const char *)pa;
    const char *b = (const char *)pb;

    int la = (int)strlen(a);
    int lb = (int)strlen(b);
    if (la != lb) return la - lb;

    int ua = count_upper(a);
    int ub = count_upper(b);
    if (ua != ub) return ua - ub;

    int va = count_vowels(a);
    int vb = count_vowels(b);
    if (va != vb) return va - vb;

    return strcmp(a, b);
}

int main(void) {
    int n = 0;
    while (n < MAXN && scanf("%127s", words[n]) == 1) {
        ++n;
    }
    qsort(words, (size_t)n, sizeof(words[0]), cmp_word);
    for (int i = 0; i < n; ++i) {
        printf("%s\n", words[i]);
    }
    return 0;
}
