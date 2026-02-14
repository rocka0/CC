#include <cassert>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

template <int MOD>
struct Z;

constexpr int MOD1 = 1000000007;
constexpr int MOD2 = 1000000009;

using Z1 = Z<MOD1>;
using Z2 = Z<MOD2>;

template <typename mint>
struct array_hash {
    int n;
    std::vector<mint> p, pref;

    array_hash() : n(0) {}

    array_hash(const std::vector<int>& arr, mint base) : n(arr.size()), p(n + 1, 1), pref(n + 1, 0) {
        for (int i = 0; i < n; ++i) p[i + 1] = p[i] * base;
        for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] * base + mint(arr[i]);
    }

    mint get(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        return pref[r + 1] - pref[l] * p[r - l + 1];
    }
};

struct robust_array_hash {
    static inline Z1 base1;
    static inline Z2 base2;
    static inline bool bases_init = false;

    array_hash<Z1> hash1;
    array_hash<Z2> hash2;

    explicit robust_array_hash(const std::vector<int>& arr) {
        if (!bases_init) {
            std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<int> dist1(257, MOD1 - 2);
            std::uniform_int_distribution<int> dist2(257, MOD2 - 2);
            base1 = Z1(dist1(rng));
            base2 = Z2(dist2(rng));
            bases_init = true;
        }
        hash1 = array_hash<Z1>(arr, base1);
        hash2 = array_hash<Z2>(arr, base2);
    }

    std::pair<Z1, Z2> get(int l, int r) const { return {hash1.get(l, r), hash2.get(l, r)}; }
};
