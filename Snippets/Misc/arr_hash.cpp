#include <array>
#include <cassert>
#include <chrono>
#include <random>
#include <vector>

using mint = atcoder::modint1000000007;

struct array_hash {
    array_hash()
        : n(0), base(0) {}

    array_hash(const std::vector<int>& arr, mint _b) {
        assert(_b != 0);
        base = _b;
        n = static_cast<int>(arr.size());

        powers.resize(n, 1);
        for (int i = 1; i < n; ++i) {
            powers[i] = powers[i - 1] * base;
        }

        invPowers.resize(n, 1);
        mint inv = base.inv();
        for (int i = 1; i < n; ++i) {
            invPowers[i] = invPowers[i - 1] * inv;
        }

        prefHash.resize(n + 1);
        for (int i = 0; i < n; ++i) {
            prefHash[i + 1] = prefHash[i] + powers[i] * arr[i];
        }
    }

    mint get(int l, int r) {
        assert(0 <= l and l <= r and r < n);
        return (prefHash[r + 1] - prefHash[l]) * invPowers[l];
    }

    int n;
    mint base;
    std::vector<mint> powers;
    std::vector<mint> invPowers;
    std::vector<mint> prefHash;
};

constexpr int K = 3;
std::array<mint, K> bases;
struct robust_array_hash {
    robust_array_hash(const std::vector<int>& arr) {
        static bool bases_initialized = false;
        if (!bases_initialized) {
            std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<int> dist(257, mint::mod() - 1);
            for (int i = 0; i < K; ++i) {
                bases[i] = dist(rng);
            }
            bases_initialized = true;
        }

        hashes.resize(K);
        for (int i = 0; i < K; ++i) {
            hashes[i] = array_hash(arr, bases[i]);
        }
    }

    std::array<mint, K> get(int l, int r) {
        std::array<mint, K> res;
        for (int i = 0; i < K; ++i) {
            res[i] = hashes[i].get(l, r);
        }
        return res;
    }

    std::vector<array_hash> hashes;
};
