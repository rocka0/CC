#include <cstdio>

/*
    Source: https://codeforces.com/blog/entry/62393

    Usage:  BigInt x; readBigInt(x); printBigInt(x);

    Note:   Change __int128_t to unsigned __int128 for unsigned 128-bit integer.
            __int128 can hold about max 1.7 * 10^38

    Note:   DO NOT use cin, cout or ios_base::sync_with_stdio(0), cin.tie(0) with this code.
            Use printf and scanf only without ios_base::sync_with_stdio(0), cin.tie(0).
*/

using BigInt = __int128;

void readBigInt(BigInt& num) {
    BigInt x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    num = x * f;
}

void printBigInt(BigInt x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) printBigInt(x / 10);
    putchar(x % 10 + '0');
}
