#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Fast modular exponentiation evaluated at compile time.
 * @complexity O(log(exp))
 */
[[nodiscard]] constexpr int64_t pow_mod_constexpr(int64_t base, int64_t exp, int64_t mod) noexcept {
    int64_t res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

/**
 * @brief Deterministic Miller-Rabin Primality Test for 32-bit integers.
 * Reference: M. Forisek and J. Jancina.
 * @param n Integer to check (0 <= n < 2^31)
 * @complexity O(log n) Time | O(1) Space
 */
[[nodiscard]] constexpr bool is_prime_constexpr(int32_t n) noexcept {
    if (n <= 1) return false;
    if (n == 2 || n == 7 || n == 61) return true;
    if (n % 2 == 0) return false;

    int64_t d = n - 1;
    while (d % 2 == 0) d /= 2;

    constexpr int64_t bases[3] = {2, 7, 61};
    for (int64_t a : bases) {
        int64_t t = d;
        int64_t y = pow_mod_constexpr(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = (y * y) % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Fast Modular Integer for fixed compile-time constants.
 * @usage using mint = modint<998244353>; mint a = 10;
 */
template <uint32_t MOD>
struct modint {
    static_assert(MOD > 0 && MOD < 0x7FFFFFFF, "MOD must be valid and prevent overflow");
    static_assert(is_prime_constexpr(MOD), "MOD must be strictly prime for modular inverse to work");

    uint32_t value;

    constexpr modint() noexcept : value(0) {}

    [[nodiscard]] static constexpr modint raw(uint32_t v) noexcept {
        modint m;
        m.value = v;
        return m;
    }

    template <typename T, enable_if_t<is_integral_v<T>, bool> = true>
    constexpr modint(T x) noexcept {
        if constexpr (is_signed_v<T>) {
            int64_t y = int64_t(x % MOD);
            if (y < 0) y += MOD;
            value = uint32_t(y);
        } else {
            value = uint32_t(x % MOD);
        }
    }

    [[nodiscard]] static constexpr uint32_t get_mod() noexcept { return MOD; }

    explicit constexpr operator uint32_t() const noexcept { return value; }
    explicit constexpr operator int32_t() const noexcept { return int32_t(value); }

    constexpr modint& operator+=(modint other) noexcept {
        value += other.value;
        if (value >= MOD) value -= MOD;
        return *this;
    }
    constexpr modint& operator-=(modint other) noexcept {
        if (value < other.value) value += MOD;
        value -= other.value;
        return *this;
    }
    constexpr modint& operator*=(modint other) noexcept {
        value = uint32_t(uint64_t(value) * other.value % MOD);
        return *this;
    }
    constexpr modint& operator/=(modint other) noexcept {
        return *this *= other.inv();
    }

    constexpr modint& operator++() noexcept { return *this += 1; }
    constexpr modint operator++(int) noexcept {
        modint t = *this;
        ++*this;
        return t;
    }
    constexpr modint& operator--() noexcept { return *this -= 1; }
    constexpr modint operator--(int) noexcept {
        modint t = *this;
        --*this;
        return t;
    }

    [[nodiscard]] constexpr modint operator+(modint other) const noexcept { return modint(*this) += other; }
    [[nodiscard]] constexpr modint operator-(modint other) const noexcept { return modint(*this) -= other; }
    [[nodiscard]] constexpr modint operator*(modint other) const noexcept { return modint(*this) *= other; }
    [[nodiscard]] constexpr modint operator/(modint other) const noexcept { return modint(*this) /= other; }
    [[nodiscard]] constexpr modint operator-() const noexcept { return modint::raw(value == 0 ? 0 : MOD - value); }

    [[nodiscard]] constexpr bool operator==(modint other) const noexcept { return value == other.value; }
    [[nodiscard]] constexpr bool operator!=(modint other) const noexcept { return value != other.value; }

    [[nodiscard]] constexpr modint pow(uint64_t exponent) const noexcept {
        modint base = *this, res = raw(1);
        while (exponent > 0) {
            if (exponent & 1) res *= base;
            base *= base;
            exponent >>= 1;
        }
        return res;
    }

    [[nodiscard]] constexpr modint inv() const noexcept {
        assert(value != 0 && "Division by zero in modular inverse");
        return pow(MOD - 2);
    }

    friend ostream& operator<<(ostream& os, const modint& m) { return os << m.value; }
    friend istream& operator>>(istream& is, modint& m) {
        int64_t x;
        is >> x;
        m = modint(x);
        return is;
    }
};

/**
 * @brief Auto-resizing combinatorics struct.
 * @usage cout << combinatorics<mint>::nCr(10, 3);
 * @complexity Amortized build: O(N) | Queries: O(1)
 */
template <typename MintType>
struct combinatorics {
    static inline vector<MintType> fact{1, 1};
    static inline vector<MintType> inv_fact{1, 1};

    static void ensure(int32_t n) {
        assert(uint32_t(n) < MintType::get_mod() && "n must be strictly less than MOD");

        int32_t curr_size = int32_t(fact.size());
        if (n < curr_size) return;

        fact.resize(n + 1);
        inv_fact.resize(n + 1);

        for (int32_t i = curr_size; i <= n; ++i) {
            fact[i] = fact[i - 1] * MintType::raw(uint32_t(i));
        }

        inv_fact[n] = fact[n].inv();
        for (int32_t i = n - 1; i >= curr_size; --i) {
            inv_fact[i] = inv_fact[i + 1] * MintType::raw(uint32_t(i + 1));
        }
    }

    [[nodiscard]] static MintType factorial(int32_t n) {
        if (n < 0) return 0;
        ensure(n);
        return fact[n];
    }

    [[nodiscard]] static MintType inv_factorial(int32_t n) {
        if (n < 0) return 0;
        ensure(n);
        return inv_fact[n];
    }

    [[nodiscard]] static MintType nPr(int32_t n, int32_t r) {
        if (r < 0 || n < r) return 0;
        ensure(n);
        return fact[n] * inv_fact[n - r];
    }

    [[nodiscard]] static MintType nCr(int32_t n, int32_t r) {
        if (r < 0 || n < r) return 0;
        ensure(n);
        return fact[n] * inv_fact[n - r] * inv_fact[r];
    }
};
