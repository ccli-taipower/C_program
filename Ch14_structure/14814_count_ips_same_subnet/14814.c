/*
 * NTHU EE2310 - 題目 14814: Count IPs in Same Subnet (Quiz)
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 14 章（結構）
 *   如果不知道如何解題，請參考課本第 14 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14814/
 *
 * 【題目說明】
 * 給定子網路遮罩（subnet mask）和參考 IP 位址 A，
 * 再讀入多個 IP 位址（直到 EOF），統計有幾個 IP 與 A 在相同子網路。（小考版）
 *
 * 兩個 IP 在相同子網路的條件：
 *   (IP1 & mask) == (IP2 & mask)
 * 即對每個 octet（4 個 8 位元組），分別做位元 AND 後比較。
 *
 * 【解題策略】
 * 使用結構體儲存 IP 位址（4 個 unsigned char）。
 * 先計算 A & mask 的結果（參考子網路），
 * 對每個輸入 IP 計算 IP & mask，若與參考子網路相同則計數加一。
 *
 * 範例：mask=255.255.255.0，A=140.112.28.28
 *   140.112.28.8  → (140,112,28,0) == (140,112,28,0) → 同一子網路 ✓
 *   140.112.28.88 → (140,112,28,0) == (140,112,28,0) → 同一子網路 ✓
 *   其餘皆不同
 *   答案：2
 *
 * 輸入格式：
 *   mask_o1 mask_o2 mask_o3 mask_o4
 *   A_o1 A_o2 A_o3 A_o4
 *   ip_o1 ip_o2 ip_o3 ip_o4  （重複直到 EOF）
 * 輸出：與 A 在同一子網路的 IP 數量。
 */
#include <stdio.h>

/* 儲存一個 IPv4 位址的結構體 */
typedef struct {
    unsigned char octet[4];   /* 4 個 8 位元組 */
} IPv4;

/*
 * read_ip：從標準輸入讀入一個 IPv4 位址
 * 回傳：1 表示成功，其他表示失敗（EOF）
 */
static int read_ip(IPv4 *ip) {
    unsigned int a, b, c, d;
    int ret = scanf("%u %u %u %u", &a, &b, &c, &d);
    if (ret == 4) {
        ip->octet[0] = (unsigned char)a;
        ip->octet[1] = (unsigned char)b;
        ip->octet[2] = (unsigned char)c;
        ip->octet[3] = (unsigned char)d;
        return 1;
    }
    return 0;
}

/*
 * same_subnet：判斷兩個 IP 是否在相同子網路
 * 回傳：1 表示相同，0 表示不同
 */
static int same_subnet(const IPv4 *ip1, const IPv4 *ip2, const IPv4 *mask) {
    for (int i = 0; i < 4; i++) {
        /* 分別對每個 octet 做位元 AND 後比較 */
        if ((ip1->octet[i] & mask->octet[i]) !=
            (ip2->octet[i] & mask->octet[i])) {
            return 0;   /* 某個 octet 的遮罩結果不同 */
        }
    }
    return 1;   /* 所有 octet 遮罩後相同，在同一子網路 */
}

int main(void) {
    IPv4 mask;       /* 子網路遮罩 */
    IPv4 ref;        /* 參考 IP 位址 A */
    IPv4 ip;         /* 待比較的 IP 位址 */
    int count = 0;   /* 在同一子網路的 IP 數量 */

    /* 讀入子網路遮罩 */
    read_ip(&mask);

    /* 讀入參考 IP 位址 A */
    read_ip(&ref);

    /* 逐一讀入 IP 位址，直到 EOF */
    while (read_ip(&ip)) {
        if (same_subnet(&ref, &ip, &mask)) {
            count++;   /* 與 A 在同一子網路，計數加一 */
        }
    }

    /* 輸出結果 */
    printf("%d\n", count);

    return 0;
}
