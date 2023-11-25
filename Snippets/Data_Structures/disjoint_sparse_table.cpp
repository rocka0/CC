#include <algorithm>
#include <cassert>
#include <climits>
#include <limits>
#include <vector>

/*
    Source: https://codeforces.com/blog/entry/79108
    Usage:  DisjointSparseTable<int> ST(vector<int> arr)
    Note:   Change operation in Monoid to any Associative Binary Operation
            In class, identity is the identity element of the Monoid
            (e.g. 0 for addition/xor and inf for minimum)
*/

template <typename T>
class DisjointSparseTable {
    struct Monoid {
        static constexpr T identity = std::numeric_limits<T>::max();
        constexpr T operator()(const T& lhs, const T& rhs) const {
            return std::min(lhs, rhs);
        }
    };

public:
    explicit DisjointSparseTable(std::vector<T> arr) {
        int N = 1;
        while (N < arr.size())
            N <<= 1;
        int LG = std::max(1, std::__lg(N));
        arr.resize(N, Monoid::identity);
        mat.resize(LG, std::vector<T>(N));
        for (int level = 0; level < LG; ++level) {
            for (int block = 0; block < 1 << level; ++block) {
                const auto start = block << (LG - level);
                const auto end = (block + 1) << (LG - level);
                const auto middle = (end + start) / 2;
                auto val = arr[middle];
                mat[level][middle] = val;
                for (int x = middle + 1; x < end; ++x) {
                    val = Monoid{}(val, arr[x]);
                    mat[level][x] = val;
                }
                val = arr[middle - 1];
                mat[level][middle - 1] = val;
                for (int x = middle - 2; x >= start; --x) {
                    val = Monoid{}(val, arr[x]);
                    mat[level][x] = val;
                }
            }
        }
    }

    // Returns operation over range [l, r]
    T query(int l, int r) const {
        assert(0 <= l and l <= r and r < static_cast<int>(mat.back().size()));
        if (l == r) {
            return mat.back()[l];
        } else {
            const auto pos_diff = (sizeof(int64_t) * CHAR_BIT) - 1 - __builtin_clzll(l ^ r);
            const auto level = static_cast<int>(mat.size()) - 1 - pos_diff;
            return Monoid{}(mat[level][l], mat[level][r]);
        }
    }

private:
    std::vector<std::vector<T>> mat;
};
