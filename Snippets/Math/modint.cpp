#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

template <int MOD>
struct Z {
    int v;
    Z() : v(0) {}

    Z(long long x) : v((x % MOD + MOD) % MOD) {}

    Z& operator+=(const Z& o) { return v += o.v, v -= (v >= MOD ? MOD : 0), *this; }
    Z& operator-=(const Z& o) { return v -= o.v, v += (v < 0 ? MOD : 0), *this; }
    Z& operator*=(const Z& o) { return v = 1LL * v * o.v % MOD, *this; }
    Z& operator/=(const Z& o) { return *this *= o.inv(); }

    friend Z operator+(Z a, const Z& b) { return a += b; }
    friend Z operator-(Z a, const Z& b) { return a -= b; }
    friend Z operator*(Z a, const Z& b) { return a *= b; }
    friend Z operator/(Z a, const Z& b) { return a /= b; }
    friend bool operator==(const Z& a, const Z& b) { return a.v == b.v; }
    friend bool operator!=(const Z& a, const Z& b) { return a.v != b.v; }

    Z operator-() const { return Z(-v); }
    Z& operator++() { return *this += 1; }
    Z& operator--() { return *this -= 1; }
    Z operator++(int) { return std::exchange(*this, *this + 1); }
    Z operator--(int) { return std::exchange(*this, *this - 1); }

    Z pow(long long k) const {
        Z res = 1, a = *this;
        while (k) {
            if (k & 1) res *= a;
            a *= a;
            k >>= 1;
        }
        return res;
    }

    Z inv() const { return pow(MOD - 2); }

    friend std::istream& operator>>(std::istream& is, Z& a) {
        return [&is, &a](long long x) -> std::istream& { return is >> x, a = Z(x), is; }(0);
    }
    friend std::ostream& operator<<(std::ostream& os, const Z& a) { return os << a.v; }
};

using mint = Z<1000000007>;

struct Combinatorics {
    int n;
    std::vector<mint> fact, inv_fact;

    Combinatorics(int _n) : n(_n), fact(_n + 1, 1), inv_fact(_n + 1, 1) {
        for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i;
        inv_fact[n] = fact[n].inv();
        for (int i = n; i >= 1; --i) inv_fact[i - 1] = inv_fact[i] * i;
    }

    mint F(int x) const { return (x < 0 || x > n) ? 0 : fact[x]; }
    mint invF(int x) const { return (x < 0 || x > n) ? 0 : inv_fact[x]; }

    mint nPr(int n, int r) const {
        if (r < 0 || n < r) return 0;
        assert(n <= this->n);
        return fact[n] * inv_fact[n - r];
    }

    mint nCr(int n, int r) const {
        if (r < 0 || n < r) return 0;
        assert(n <= this->n);
        return fact[n] * inv_fact[n - r] * inv_fact[r];
    }
};
