/*
 * NTHU EE2310 - 題目 14803: Subnet Determination
 *
 * 【課本參考】《由片語學習C程式設計（第二版）》
 *   第 14 章（結構）
 *   如果不知道如何解題，請參考課本第 14 章的說明。
 *
 * 【題目連結】https://acm.cs.nthu.edu.tw/problem/14803/
 *
 * 【題目說明】
 * 給定子網路遮罩（subnet mask）和參考 IP 位址 A，
 * 再讀入多個 IP 位址（直到 EOF），統計有幾個 IP 與 A 在相同子網路。
 *
 * 兩個 IP 在相同子網路的條件：
 *   (IP1 & mask) == (IP2 & mask)
 * 即對每個 octect（4 個 8 位元組），分別做位元 AND 後比較。
 *
 * 【解題策略】
 * 使用結構體儲存 IP 位址（4 個 unsigned char）。
 * 先計算 A & mask 的結果（參考子網路），
 * 對每個輸入 IP 計算 IP & mask，若與參考子網路相同則計數加一。
 *
 * 輸入格式：
 *   mask_o1 mask_o2 mask_o3 mask_o4
 *   A_o1 A_o2 A_o3 A_o4
 *   ip_o1 ip_o2 ip_o3 ip_o4  （重複直到 EOF）
 * 輸出：與 A 在同一子網路的 IP 數量。
 *
 * 【解題流程 / Solution Walkthrough】
 *
 * 中文說明：
 * 1. 定義 IPv4 結構體，以 4 個 unsigned char 分別儲存 IPv4 的 4 個 octet。
 * 2. 使用 read_ip 函式，以 scanf 讀入 4 個無號整數後轉型存入結構體。
 * 3. 先讀入子網路遮罩 mask，再讀入參考 IP 位址 ref。
 * 4. 持續以 read_ip 讀入待比較 IP，直到 EOF。
 * 5. 對每個讀入的 IP 呼叫 same_subnet(ref, ip, mask)：
 *    對 4 個 octet 分別計算 (ip1[i] & mask[i]) 與 (ip2[i] & mask[i])，
 *    若任一 octet 結果不同則回傳 0（不同子網路）。
 * 6. same_subnet 回傳 1 時，計數器 count 加一。
 * 7. 最後輸出 count。
 *
 * English:
 * 1. Define the IPv4 struct storing four unsigned chars for the four octets.
 * 2. The read_ip helper reads four unsigned ints via scanf and casts them into the struct.
 * 3. Read the subnet mask first, then the reference IP address ref.
 * 4. Loop with read_ip to read each candidate IP until EOF.
 * 5. For each candidate, call same_subnet(ref, ip, mask): for each of the 4 octets,
 *    compare (ip1[i] & mask[i]) with (ip2[i] & mask[i]); return 0 on any mismatch.
 * 6. Increment count whenever same_subnet returns 1.
 * 7. Print the final count.
 */
#include <stdio.h>

/* 儲存一個 IPv4 位址的結構體 */
typedef struct {
    unsigned char octet[4];   /* 4 個 8 位元組 / four 8-bit octets */
} IPv4;

/*
 * read_ip：從標準輸入讀入一個 IPv4 位址
 * 回傳：1 表示成功，0 或 EOF 表示失敗
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
 * same_subnet：判斷兩個 IP 在相同子網路
 * 回傳：1 表示相同，0 表示不同
 */
static int same_subnet(const IPv4 *ip1, const IPv4 *ip2, const IPv4 *mask) {
    for (int i = 0; i < 4; i++) {
        /* 分別對每個 octet 做 AND 後比較 / AND each octet and compare */
        if ((ip1->octet[i] & mask->octet[i]) !=
            (ip2->octet[i] & mask->octet[i])) {
            return 0;   /* 某個 octet 不同，不在同一子網路 / an octet differs, not in same subnet */
        }
    }
    return 1;   /* 所有 octet 都相同，在同一子網路 / all octets match, same subnet */
}

int main(void) {
    IPv4 mask;   /* 子網路遮罩 / subnet mask */
    IPv4 ref;    /* 參考 IP 位址 A / reference IP address A */
    IPv4 ip;     /* 待比較的 IP 位址 / candidate IP address to compare */
    int count = 0;   /* 在同一子網路的 IP 數量 / count of IPs in the same subnet */

    /* 讀入子網路遮罩 / read the subnet mask */
    read_ip(&mask);

    /* 讀入參考 IP 位址 A / read reference IP address A */
    read_ip(&ref);

    /* 逐一讀入 IP 位址，直到 EOF / read IP addresses one by one until EOF */
    while (read_ip(&ip)) {
        if (same_subnet(&ref, &ip, &mask)) {
            count++;   /* 與 A 在同一子網路，計數加一 / in same subnet as A, increment count */
        }
    }

    /* 輸出結果 / print the result */
    printf("%d\n", count);

    return 0;
}
