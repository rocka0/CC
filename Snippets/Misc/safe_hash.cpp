#include <chrono>
#include <cstdint>
#include <utility>

/*
    Source: https://codeforces.com/blog/entry/62393
    Usage:  unordered_map <int, int, SafeHash>
            unordered_set<pair<int,int>, SafeHashPairInt>
    Note:   Sometimes causes slowdown of ~ (2-3)X
*/

uint64_t splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}

struct SafeHash {
    std::size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

struct SafeHashPairInt {
    std::size_t operator()(std::pair<int, int> p) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64((size_t)487631741 * (size_t)p.first + (size_t)436217543 * (size_t)p.second + FIXED_RANDOM);
    }
};
