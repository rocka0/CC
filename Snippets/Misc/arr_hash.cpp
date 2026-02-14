#include <array>
#include <cassert>
#include <chrono>
#include <random>
#include <vector>

using mint = Z<1000000007>;

struct array_hash {
    int n;
    std::vector<mint> p, pref;

    array_hash() : n(0) {}

    array_hash(const std::vector<int>& arr, mint base) : n(arr.size()), p(n + 1, 1), pref(n + 1, 0) {
        for (int i = 0; i < n; ++i) p[i + 1] = p[i] * base;
        for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] * base + arr[i];
    }

    mint get(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        return pref[r + 1] - pref[l] * p[r - l + 1];
    }
};

template <int K = 3>
struct robust_array_hash {
    static inline std::array<mint, K> bases;
    static inline bool bases_init = false;
    std::array<array_hash, K> hashes;

    robust_array_hash(const std::vector<int>& arr) {
        if (!bases_init) {
            std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<int> dist(257, mint::mod() - 1);
            for (int i = 0; i < K; ++i) bases[i] = dist(rng);
            bases_init = true;
        }
        for (int i = 0; i < K; ++i) hashes[i] = array_hash(arr, bases[i]);
    }

    std::array<mint, K> get(int l, int r) const {
        std::array<mint, K> res;
        for (int i = 0; i < K; ++i) res[i] = hashes[i].get(l, r);
        return res;
    }
};
