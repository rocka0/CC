#include <cassert>
#include <vector>

using mint = atcoder::modint1000000007;

struct array_hash {
    array_hash()
        : n(0), base(0) {}

    array_hash(const std::vector<int>& arr, mint _b)
        : base(_b) {
        assert(base != 0);
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
