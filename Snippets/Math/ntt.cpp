#include <array>
#include <vector>
using namespace std;

namespace internal {

    [[nodiscard]] constexpr uint32_t bit_ceil(uint32_t n) noexcept {
        return n <= 1 ? 1 : 1u << (32 - __builtin_clz(n - 1));
    }

    [[nodiscard]] constexpr int32_t primitive_root(int32_t m) noexcept {
        if (m == 998244353) return 3;
        int32_t divs[20] = {2}, cnt = 1, x = (m - 1) / 2;
        while (x % 2 == 0) x /= 2;
        for (int32_t i = 3; int64_t(i) * i <= x; i += 2) {
            if (x % i == 0) {
                divs[cnt++] = i;
                while (x % i == 0) x /= i;
            }
        }
        if (x > 1) divs[cnt++] = x;
        for (int32_t g = 2;; g++) {
            bool ok = true;
            for (int32_t i = 0; i < cnt; i++) {
                int32_t p = (m - 1) / divs[i];
                int64_t res = 1, y = g;
                while (p) {
                    if (p & 1) res = (res * y) % m;
                    y = (y * y) % m;
                    p >>= 1;
                }
                if (res == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) return g;
        }
    }

    template <typename MintType>
    struct fft_info {
        static constexpr uint32_t mod_val = MintType::get_mod();
        static constexpr int32_t rank2 = __builtin_ctz(mod_val - 1);

        array<MintType, rank2 + 1> root, iroot;
        array<MintType, max(0, rank2 - 1)> rate2, irate2;
        array<MintType, max(0, rank2 - 2)> rate3, irate3;

        fft_info() {
            root[rank2] = MintType(primitive_root(mod_val)).pow((mod_val - 1) >> rank2);
            iroot[rank2] = root[rank2].inv();
            for (int32_t i = rank2 - 1; i >= 0; i--) {
                root[i] = root[i + 1] * root[i + 1];
                iroot[i] = iroot[i + 1] * iroot[i + 1];
            }
            MintType prod = 1, iprod = 1;
            for (int32_t i = 0; i <= rank2 - 2; i++) {
                rate2[i] = root[i + 2] * prod;
                irate2[i] = iroot[i + 2] * iprod;
                prod *= iroot[i + 2];
                iprod *= root[i + 2];
            }
            prod = 1;
            iprod = 1;
            for (int32_t i = 0; i <= rank2 - 3; i++) {
                rate3[i] = root[i + 3] * prod;
                irate3[i] = iroot[i + 3] * iprod;
                prod *= iroot[i + 3];
                iprod *= root[i + 3];
            }
        }
    };

    template <typename MintType>
    void butterfly(vector<MintType>& a) {
        int32_t n = int32_t(a.size()), h = __builtin_ctz(uint32_t(n));
        static const fft_info<MintType> info;
        for (int32_t len = 0; len < h;) {
            if (h - len == 1) {
                int32_t p = 1 << (h - len - 1);
                MintType rot = 1;
                for (int32_t s = 0; s < (1 << len); s++) {
                    int32_t offset = s << (h - len);
                    for (int32_t i = 0; i < p; i++) {
                        auto l = a[i + offset];
                        auto r = a[i + offset + p] * rot;
                        a[i + offset] = l + r;
                        a[i + offset + p] = l - r;
                    }
                    if (s + 1 != (1 << len)) rot *= info.rate2[__builtin_ctz(~(uint32_t)s)];
                }
                len++;
            } else {
                int32_t p = 1 << (h - len - 2);
                MintType rot = 1, imag = info.root[2];
                for (int32_t s = 0; s < (1 << len); s++) {
                    MintType rot2 = rot * rot, rot3 = rot2 * rot;
                    int32_t offset = s << (h - len);
                    for (int32_t i = 0; i < p; i++) {
                        uint64_t mod2 = uint64_t(MintType::get_mod()) * MintType::get_mod();
                        uint64_t a0 = a[i + offset].value;
                        uint64_t a1 = uint64_t(a[i + offset + p].value) * rot.value;
                        uint64_t a2 = uint64_t(a[i + offset + 2 * p].value) * rot2.value;
                        uint64_t a3 = uint64_t(a[i + offset + 3 * p].value) * rot3.value;

                        uint64_t a1_minus_a3_imag = MintType(a1 + mod2 - a3).value * uint64_t(imag.value);
                        uint64_t neg_a2 = mod2 - a2;

                        a[i + offset] = a0 + a2 + a1 + a3;
                        a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
                        a[i + offset + 2 * p] = a0 + neg_a2 + a1_minus_a3_imag;
                        a[i + offset + 3 * p] = a0 + neg_a2 + (mod2 - a1_minus_a3_imag);
                    }
                    if (s + 1 != (1 << len)) rot *= info.rate3[__builtin_ctz(~(uint32_t)s)];
                }
                len += 2;
            }
        }
    }

    template <typename MintType>
    void butterfly_inv(vector<MintType>& a) {
        int32_t n = int32_t(a.size()), h = __builtin_ctz(uint32_t(n));
        static const fft_info<MintType> info;
        for (int32_t len = h; len;) {
            if (len == 1) {
                int32_t p = 1 << (h - len);
                MintType irot = 1;
                for (int32_t s = 0; s < (1 << (len - 1)); s++) {
                    int32_t offset = s << (h - len + 1);
                    for (int32_t i = 0; i < p; i++) {
                        auto l = a[i + offset], r = a[i + offset + p];
                        a[i + offset] = l + r;
                        a[i + offset + p] = (uint64_t(l.value + MintType::get_mod() - r.value) * irot.value);
                    }
                    if (s + 1 != (1 << (len - 1))) irot *= info.irate2[__builtin_ctz(~(uint32_t)s)];
                }
                len--;
            } else {
                int32_t p = 1 << (h - len);
                MintType irot = 1, iimag = info.iroot[2];
                for (int32_t s = 0; s < (1 << (len - 2)); s++) {
                    MintType irot2 = irot * irot, irot3 = irot2 * irot;
                    int32_t offset = s << (h - len + 2);
                    for (int32_t i = 0; i < p; i++) {
                        uint64_t a0 = a[i + offset + 0 * p].value, a1 = a[i + offset + 1 * p].value;
                        uint64_t a2 = a[i + offset + 2 * p].value, a3 = a[i + offset + 3 * p].value;

                        uint64_t a2_minus_a3_iimag = MintType((MintType::get_mod() + a2 - a3) * iimag.value).value;

                        a[i + offset] = a0 + a1 + a2 + a3;
                        a[i + offset + 1 * p] = (a0 + (MintType::get_mod() - a1) + a2_minus_a3_iimag) * irot.value;
                        a[i + offset + 2 * p] = (a0 + a1 + (MintType::get_mod() - a2) + (MintType::get_mod() - a3)) * irot2.value;
                        a[i + offset + 3 * p] = (a0 + (MintType::get_mod() - a1) + (MintType::get_mod() - a2_minus_a3_iimag)) * irot3.value;
                    }
                    if (s + 1 != (1 << (len - 2))) irot *= info.irate3[__builtin_ctz(~(uint32_t)s)];
                }
                len -= 2;
            }
        }
    }

}  // namespace internal

/**
 * @brief Extremely fast polynomial multiplication (NTT).
 * @usage auto C = convolution(A, B);
 * @complexity O(N \log N)
 * @note Output size is |A| + |B| - 1.
 */
template <typename MintType>
[[nodiscard]] vector<MintType> convolution(vector<MintType> a, vector<MintType> b) {
    int32_t n = int32_t(a.size()), m = int32_t(b.size());
    if (!n || !m) return {};

    // Naive fallback for very small polynomials
    if (min(n, m) <= 60) {
        vector<MintType> ans(n + m - 1);
        for (int32_t i = 0; i < n; i++) {
            for (int32_t j = 0; j < m; j++) {
                ans[i + j] += a[i] * b[j];
            }
        }
        return ans;
    }

    int32_t z = internal::bit_ceil(uint32_t(n + m - 1));
    assert((MintType::get_mod() - 1) % z == 0 && "Modulo must support this transform size");

    a.resize(z);
    internal::butterfly(a);

    b.resize(z);
    internal::butterfly(b);

    for (int32_t i = 0; i < z; i++) {
        a[i] *= b[i];
    }

    internal::butterfly_inv(a);
    a.resize(n + m - 1);

    MintType inv_z = MintType(z).inv();
    for (int32_t i = 0; i < n + m - 1; i++) {
        a[i] *= inv_z;
    }

    return a;
}
