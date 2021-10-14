#include <bits/stdc++.h>
using namespace std;

/*
    Source: https://github.com/atcoder/ac-library

    Usage:  using mint = modint1000000007
*/

namespace atcoder::internal {

constexpr int64_t safe_mod(int64_t x, int64_t m) {
    x %= m;

    if (x < 0) {
        x += m;
    }

    return x;
}

struct barrett {
    uint32_t _m;
    uint64_t im;

    explicit barrett(uint32_t m) : _m(m), im((uint64_t) (-1) / m + 1) {}

    uint32_t umod() const {
        return _m;
    }

    uint32_t mul(uint32_t a, uint32_t b) const {
        uint64_t z = a;
        z *= b;
#ifdef _MSC_VER
        uint64_t x;
        _umul128(z, im, &x);
#else
        auto x = (uint64_t) (((unsigned __int128) (z) *im) >> 64);
#endif
        auto v = (uint32_t) (z - x * _m);

        if (_m <= v) {
            v += _m;
        }

        return v;
    }
};

constexpr int64_t pow_mod_constexpr(int64_t x, int64_t n, int m) {
    if (m == 1) {
        return 0;
    }

    auto _m = (uint32_t) (m);
    uint64_t r = 1;
    uint64_t y = safe_mod(x, m);

    while (n) {
        if (n & 1) {
            r = (r * y) % _m;
        }

        y = (y * y) % _m;
        n >>= 1;
    }

    return r;
}

constexpr bool is_prime_constexpr(int n) {
    if (n <= 1) {
        return false;
    }

    if (n == 2 || n == 7 || n == 61) {
        return true;
    }

    if (n % 2 == 0) {
        return false;
    }

    int64_t d = n - 1;

    while (d % 2 == 0) {
        d /= 2;
    }

    constexpr int64_t bases[3] = {2, 7, 61};

    for (int64_t a : bases) {
        int64_t t = d;
        int64_t y = pow_mod_constexpr(a, t, n);

        while (t != n - 1 && y != 1 && y != n - 1) {
            y = y * y % n;
            t <<= 1;
        }

        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }

    return true;
}
template <int n>
constexpr bool is_prime = is_prime_constexpr(n);

constexpr std::pair<int64_t, int64_t> inv_gcd(int64_t a, int64_t b) {
    a = safe_mod(a, b);

    if (a == 0) return {b, 0};

    int64_t s = b, t = a;

    int64_t m0 = 0, m1 = 1;

    while (t) {
        int64_t u = s / t;
        s -= t * u;
        m0 -= m1 * u;    // |m1 * u| <= |m1| * s <= b

        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }

    if (m0 < 0) {
        m0 += b / s;
    }

    return {s, m0};
}

constexpr int primitive_root_constexpr(int m) {
    if (m == 2) {
        return 1;
    }

    if (m == 167772161) {
        return 3;
    }

    if (m == 469762049) {
        return 3;
    }

    if (m == 754974721) {
        return 11;
    }

    if (m == 998244353) {
        return 3;
    }

    int divs[20] = {};
    divs[0] = 2;
    int cnt = 1;
    int x = (m - 1) / 2;

    while (x % 2 == 0) {
        x /= 2;
    }

    for (int i = 3; (int64_t) (i) *i <= x; i += 2) {
        if (x % i == 0) {
            divs[cnt++] = i;

            while (x % i == 0) {
                x /= i;
            }
        }
    }

    if (x > 1) {
        divs[cnt++] = x;
    }

    for (int g = 2;; g++) {
        bool ok = true;

        for (int i = 0; i < cnt; i++) {
            if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                ok = false;
                break;
            }
        }

        if (ok) {
            return g;
        }
    }
}
template <int m>
constexpr int primitive_root = primitive_root_constexpr(m);

uint64_t floor_sum_unsigned(uint64_t n, uint64_t m, uint64_t a, uint64_t b) {
    uint64_t ans = 0;

    while (true) {
        if (a >= m) {
            ans += n * (n - 1) / 2 * (a / m);
            a %= m;
        }

        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }

        uint64_t y_max = a * n + b;

        if (y_max < m) {
            break;
        }

        n = (uint64_t) (y_max / m);
        b = (uint64_t) (y_max % m);
        std::swap(m, a);
    }

    return ans;
}

}    // namespace atcoder::internal

namespace atcoder::internal {

#ifndef _MSC_VER
template <class T>
using is_signed_int128 = typename std::conditional<std::is_same<T, __int128_t>::value || std::is_same<T, __int128>::value, std::true_type, std::false_type>::type;

template <class T>
using is_unsigned_int128 = typename std::conditional<std::is_same<T, __uint128_t>::value || std::is_same<T, unsigned __int128>::value, std::true_type, std::false_type>::type;

template <class T>
using make_unsigned_int128 = typename std::conditional<std::is_same<T, __int128_t>::value, __uint128_t, unsigned __int128>;

template <class T>
using is_integral = typename std::conditional<std::is_integral<T>::value || is_signed_int128<T>::value || is_unsigned_int128<T>::value, std::true_type, std::false_type>::type;

template <class T>
using is_signed_int = typename std::conditional<(is_integral<T>::value && std::is_signed<T>::value) || is_signed_int128<T>::value, std::true_type, std::false_type>::type;

template <class T>
using is_unsigned_int = typename std::conditional<(is_integral<T>::value && std::is_unsigned<T>::value) || is_unsigned_int128<T>::value, std::true_type, std::false_type>::type;

template <class T>
using to_unsigned = typename std::conditional<is_signed_int128<T>::value, make_unsigned_int128<T>, typename std::conditional<std::is_signed<T>::value, std::make_unsigned<T>, std::common_type<T>>::type>::type;

#else

template <class T>
using is_integral = typename std::is_integral<T>;

template <class T>
using is_signed_int = typename std::conditional<is_integral<T>::value && std::is_signed<T>::value, std::true_type, std::false_type>::type;

template <class T>
using is_unsigned_int = typename std::conditional<is_integral<T>::value && std::is_unsigned<T>::value, std::true_type, std::false_type>::type;

template <class T>
using to_unsigned = typename std::conditional<is_signed_int<T>::value, std::make_unsigned<T>, std::common_type<T>>::type;

#endif

template <class T>
using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

template <class T>
using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

template <class T>
using to_unsigned_t = typename to_unsigned<T>::type;

}    // namespace atcoder::internal

namespace atcoder {

namespace internal {

struct modint_base {};
struct static_modint_base : modint_base {};

template <class T>
using is_modint = std::is_base_of<modint_base, T>;
template <class T>
using is_modint_t = std::enable_if_t<is_modint<T>::value>;

}    // namespace internal

template <int m, std::enable_if_t<(1 <= m)>* = nullptr>
struct static_modint : internal::static_modint_base {
    using mint = static_modint;

public:
    static constexpr int mod() {
        return m;
    }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    static_modint() : _v(0) {}
    template <class T, internal::is_signed_int_t<T>* = nullptr>
    static_modint(T v) {
        auto x = (int64_t) (v % (int64_t) (umod()));

        if (x < 0) {
            x += umod();
        }

        _v = (uint32_t) (x);
    }
    template <class T, internal::is_unsigned_int_t<T>* = nullptr>
    static_modint(T v) {
        _v = (uint32_t) (v % umod());
    }

    uint32_t val() const {
        return _v;
    }

    mint& operator++() {
        _v++;

        if (_v == umod()) {
            _v = 0;
        }

        return *this;
    }
    mint& operator--() {
        if (_v == 0) {
            _v = umod();
        }

        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }

    mint& operator+=(const mint& rhs) {
        _v += rhs._v;

        if (_v >= umod()) {
            _v -= umod();
        }

        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v -= rhs._v;

        if (_v >= umod()) {
            _v += umod();
        }

        return *this;
    }
    mint& operator*=(const mint& rhs) {
        uint64_t z = _v;
        z *= rhs._v;
        _v = (uint32_t) (z % umod());
        return *this;
    }
    mint& operator/=(const mint& rhs) {
        return *this = *this * rhs.inv();
    }

    mint operator+() const {
        return *this;
    }
    mint operator-() const {
        return mint() - *this;
    }

    mint pow(int64_t n) const {
        assert(0 <= n);
        mint x = *this, r = 1;

        while (n) {
            if (n & 1) {
                r *= x;
            }

            x *= x;
            n >>= 1;
        }

        return r;
    }
    mint inv() const {
        if (prime) {
            assert(_v);
            return pow(umod() - 2);
        } else {
            auto eg = internal::inv_gcd(_v, m);
            assert(eg.first == 1);
            return eg.second;
        }
    }

    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }

private:
    uint32_t _v;
    static constexpr uint32_t umod() {
        return m;
    }
    static constexpr bool prime = internal::is_prime<m>;
};

template <int id>
struct dynamic_modint : internal::modint_base {
    using mint = dynamic_modint;

public:
    static int mod() {
        return (int) (bt.umod());
    }
    static void set_mod(int m) {
        assert(1 <= m);
        bt = internal::barrett(m);
    }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    dynamic_modint() : _v(0) {}
    template <class T, internal::is_signed_int_t<T>* = nullptr>
    dynamic_modint(T v) {
        auto x = (int64_t) (v % (int64_t) (mod()));

        if (x < 0) {
            x += mod();
        }

        _v = (uint32_t) (x);
    }
    template <class T, internal::is_unsigned_int_t<T>* = nullptr>
    dynamic_modint(T v) {
        _v = (uint32_t) (v % mod());
    }

    uint32_t val() const {
        return _v;
    }

    mint& operator++() {
        _v++;

        if (_v == umod()) {
            _v = 0;
        }

        return *this;
    }
    mint& operator--() {
        if (_v == 0) {
            _v = umod();
        }

        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }

    mint& operator+=(const mint& rhs) {
        _v += rhs._v;

        if (_v >= umod()) {
            _v -= umod();
        }

        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v += mod() - rhs._v;

        if (_v >= umod()) {
            _v -= umod();
        }

        return *this;
    }
    mint& operator*=(const mint& rhs) {
        _v = bt.mul(_v, rhs._v);
        return *this;
    }
    mint& operator/=(const mint& rhs) {
        return *this = *this * rhs.inv();
    }

    mint operator+() const {
        return *this;
    }
    mint operator-() const {
        return mint() - *this;
    }

    mint pow(int64_t n) const {
        assert(0 <= n);
        mint x = *this, r = 1;

        while (n) {
            if (n & 1) {
                r *= x;
            }

            x *= x;
            n >>= 1;
        }

        return r;
    }
    mint inv() const {
        auto eg = internal::inv_gcd(_v, mod());
        assert(eg.first == 1);
        return eg.second;
    }

    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }

private:
    uint32_t _v;
    static internal::barrett bt;
    static uint32_t umod() {
        return bt.umod();
    }
};
template <int id>
internal::barrett dynamic_modint<id>::bt(998244353);

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;
using modint = dynamic_modint<-1>;

namespace internal {

template <class T>
using is_static_modint = std::is_base_of<internal::static_modint_base, T>;

template <class T>
using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;

template <class>
struct is_dynamic_modint : public std::false_type {};
template <int id>
struct is_dynamic_modint<dynamic_modint<id>> : public std::true_type {};

template <class T>
using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;

}    // namespace internal

}    // namespace atcoder

using namespace atcoder;
using mint = modint1000000007;

const int factorialLimit = 1e6;
array<mint, factorialLimit + 1> fact;
array<mint, factorialLimit + 1> invFact;
bool setupDone = false;

void setupModint() {
    fact[0] = 1;
    for (int i = 1; i <= factorialLimit; ++i) {
        fact[i] = fact[i - 1] * i;
    }
    invFact[factorialLimit] = fact[factorialLimit].inv();
    for (int i = factorialLimit; i >= 1; --i) {
        invFact[i - 1] = invFact[i] * i;
    }
    setupDone = true;
}

mint factorial(int x) {
    assert(setupDone);
    assert(x <= factorialLimit);
    if (x < 0) {
        return 0;
    }
    return fact[x];
}

mint inverseFactorial(int x) {
    assert(setupDone);
    assert(x <= factorialLimit);
    if (x < 0) {
        return 0;
    }
    return invFact[x];
}

mint nPr(int n, int r) {
    assert(setupDone);
    if (r < 0 or n < r) {
        return 0;
    }
    return factorial(n) * inverseFactorial(n - r);
}

mint nCr(int n, int r) {
    assert(setupDone);
    if (r < 0 or n < r) {
        return 0;
    }
    return nPr(n, r) * inverseFactorial(r);
}
