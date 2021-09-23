#include <bits/stdc++.h>
using namespace std;

/*
    Source: https://codeforces.com/blog/entry/79108

    Usage:  disjointSparseTable(vector<int> arr, 0)
            T is the type of the element
            Monoid is the Associative Binary Operation
            Identity is the identity element of the Monoid
            (e.g. 0 for addition/xor and inf for minimum)
*/

template <typename T>
class disjointSparseTable {
public:
    disjointSparseTable(vector<T> arr, T Identity) {
        identity = Identity;
        int pow2 = 1, cnt = 0;
        for (; pow2 < int(arr.size()); pow2 <<= 1, ++cnt)
            ;
        if (int(arr.size()) == 1) {
            cnt = 1;
        }
        arr.resize(pow2, identity);
        mat.resize(cnt, vector<T>(pow2));
        for (int level = 0; level < int(mat.size()); ++level) {
            for (int block = 0; block < 1 << level; ++block) {
                const auto start = block << (int(mat.size()) - level);
                const auto end = (block + 1) << (int(mat.size()) - level);
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
        const auto level = int(mat.size()) - 1 - pos_diff;
        return Monoid{}(mat[level][l], mat[level][r]);
    }

private:
    struct Monoid {
        constexpr T operator()(const T& lhs, const T& rhs) const {
            // NOTE: Change this to any Associative Binary Operation
            return (lhs ^ rhs);
        }
    };
    vector<vector<T>> mat;
    T identity;
};
