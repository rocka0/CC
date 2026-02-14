#include <algorithm>
#include <cassert>
#include <climits>
#include <limits>
#include <vector>

template <typename T>
class disjoint_sparse_table {
    static constexpr T IDENTITY = std::numeric_limits<T>::max();
    T op(const T& lhs, const T& rhs) const { return std::min(lhs, rhs); }

public:
    explicit disjoint_sparse_table(std::vector<T> arr) {
        int N = 1;
        while (N < static_cast<int>(arr.size())) N <<= 1;

        int LG = (N == 0) ? 0 : 31 - __builtin_clz(N);
        arr.resize(N, IDENTITY);
        table.resize(LG, std::vector<T>(N));

        for (int level = 0; level < LG; ++level) {
            for (int block = 0; block < 1 << level; ++block) {
                const auto start = block << (LG - level);
                const auto end = (block + 1) << (LG - level);
                const auto middle = (end + start) / 2;

                auto val = arr[middle];
                table[level][middle] = val;
                for (int x = middle + 1; x < end; ++x) {
                    val = op(val, arr[x]);
                    table[level][x] = val;
                }

                val = arr[middle - 1];
                table[level][middle - 1] = val;
                for (int x = middle - 2; x >= start; --x) {
                    val = op(val, arr[x]);
                    table[level][x] = val;
                }
            }
        }
    }

    // Returns operation over range [l, r]
    T query(int l, int r) const {
        assert(0 <= l && l <= r);
        assert(r < static_cast<int>(table.back().size()));

        if (l == r) return table.back()[l];

        const auto pos_diff = (sizeof(int64_t) * CHAR_BIT) - 1 - __builtin_clzll(l ^ r);
        const auto level = static_cast<int>(table.size()) - 1 - pos_diff;
        return op(table[level][l], table[level][r]);
    }

private:
    std::vector<std::vector<T>> table;
};
