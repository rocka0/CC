#include <bits/stdc++.h>
using namespace std;

/*
    Source: https://codeforces.com/blog/entry/62393

    Usage:  Use as unordered_map <int, int, safe_hash>

    Note:   Worst case, causes considerable slowdown of ~ (2-3)X
*/

struct safe_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
