#include <bits/stdc++.h>
using namespace std;

/*
    Source: https://codeforces.com/blog/entry/79108

    Usage:  DisjointSparseTable ST(vector<int> arr, 0)

    Note:   Change operation in Monoid to any Associative Binary Operation
            In constructor, Identity is the identity element of the Monoid
            (e.g. 0 for addition/xor and inf for minimum)
*/

template <typename T>
class DisjointSparseTable {
    struct Monoid {
        constexpr T operator()(const T& lhs, const T& rhs) const {
            // TODO: Change this to any Associative Binary Operation
            return (lhs + rhs);
        }
    };
    vector<vector<T>> mat;
    T identity;

public:
    DisjointSparseTable(vector<T> arr, T Identity) {
        identity = Identity;
        int pow2 = 1, cnt = 0;
        int arrSize = static_cast<int>(arr.size());
        for (; pow2 < arrSize; pow2 <<= 1, ++cnt)
            ;
        if (arrSize == 1) {
            cnt = 1;
        }
        arr.resize(pow2, identity);
        mat.resize(cnt, vector<T>(pow2));
        int matSize = static_cast<int>(mat.size());
        for (int level = 0; level < matSize; ++level) {
            for (int block = 0; block < 1 << level; ++block) {
                const auto start = block << (matSize - level);
                const auto end = (block + 1) << (matSize - level);
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
        assert(l <= r);
        if (l == r) {
            return mat.back()[l];
        }
        const auto pos_diff = (sizeof(int64_t) * CHAR_BIT) - 1 - __builtin_clzll(l ^ r);
        const auto level = static_cast<int>(mat.size()) - 1 - pos_diff;
        return Monoid{}(mat[level][l], mat[level][r]);
    }
};
