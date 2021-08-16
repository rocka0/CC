// https://github.com/tatyam-prime/kyopro_library/blob/master/Modint.cpp

const unsigned mod = 1000000007;

struct Modint
{
    unsigned num = 0;

    constexpr Modint() noexcept {}

    constexpr Modint(const Modint &x) noexcept : num(x.num) {}

    inline constexpr operator ll() const noexcept
    {
        return num;
    }

    inline constexpr Modint &operator+=(Modint x) noexcept
    {
        num += x.num;
        if (num >= mod)
            num -= mod;
        return *this;
    }

    inline constexpr Modint &operator++() noexcept
    {
        if (num == mod - 1)
            num = 0;
        else
            num++;
        return *this;
    }

    inline constexpr Modint operator++(int) noexcept
    {
        Modint ans(*this);
        operator++();
        return ans;
    }

    inline constexpr Modint operator-() const noexcept
    {
        return Modint(0) -= *this;
    }

    inline constexpr Modint operator-(Modint x) const noexcept
    {
        return Modint(*this) -= x;
    }

    inline constexpr Modint &operator-=(Modint x) noexcept
    {
        if (num < x.num)
            num += mod;
        num -= x.num;
        return *this;
    }

    inline constexpr Modint &operator--() noexcept
    {
        if (num == 0)
            num = mod - 1;
        else
            num--;
        return *this;
    }

    inline constexpr Modint operator--(int) noexcept
    {
        Modint ans(*this);
        operator--();
        return ans;
    }

    inline constexpr Modint &operator*=(Modint x) noexcept
    {
        num = ull(num) * x.num % mod;
        return *this;
    }

    inline constexpr Modint &operator/=(Modint x) noexcept
    {
        return operator*=(x.inv());
    }

    template <class T>
    constexpr Modint(T x) noexcept
    {
        using U = typename conditional<sizeof(T) >= 4, T, int >::type;
        U y = x;
        y %= U(mod);
        if (y < 0)
            y += mod;
        num = unsigned(y);
    }

    template <class T>
    inline constexpr Modint operator+(T x) const noexcept
    {
        return Modint(*this) += x;
    }

    template <class T>
    inline constexpr Modint &operator+=(T x) noexcept
    {
        return operator+=(Modint(x));
    }

    template <class T>
    inline constexpr Modint operator-(T x) const noexcept
    {
        return Modint(*this) -= x;
    }

    template <class T>
    inline constexpr Modint &operator-=(T x) noexcept
    {
        return operator-=(Modint(x));
    }

    template <class T>
    inline constexpr Modint operator*(T x) const noexcept
    {
        return Modint(*this) *= x;
    }

    template <class T>
    inline constexpr Modint &operator*=(T x) noexcept
    {
        return operator*=(Modint(x));
    }

    template <class T>
    inline constexpr Modint operator/(T x) const noexcept
    {
        return Modint(*this) /= x;
    }

    template <class T>
    inline constexpr Modint &operator/=(T x) noexcept
    {
        return operator/=(Modint(x));
    }

    inline constexpr Modint inv() const noexcept
    {
        ll x = 0, y = 0;
        extgcd(num, mod, x, y);
        return x;
    }

    static inline constexpr ll extgcd(ll a, ll b, ll &x, ll &y) noexcept
    {
        ll g = a;
        x = 1;
        y = 0;
        if (b)
        {
            g = extgcd(b, a % b, y, x);
            y -= a / b * x;
        }
        return g;
    }

    inline constexpr Modint pow(ull x) const noexcept
    {
        Modint ans = 1, cnt = *this;
        while (x)
        {
            if (x & 1)
                ans *= cnt;
            cnt *= cnt;
            x /= 2;
        }
        return ans;
    }
};

istream &operator>>(istream &is, Modint &x) noexcept
{
    ll a;
    cin >> a;
    x = a;
    return is;
}

inline constexpr Modint operator"" _M(ull x) noexcept
{
    return Modint(x);
}

vector<Modint> fac(1, 1), inv(1, 1);

void reserve(ll a)
{
    if (fac.size() >= a)
        return;
    if (a < fac.size() * 2)
        a = fac.size() * 2;
    if (a >= mod)
        a = mod;
    while (fac.size() < a)
        fac.push_back(fac.back() * Modint(fac.size()));
    inv.resize(fac.size());
    inv.back() = fac.back().inv();
    for (ll i = inv.size() - 1; !inv[i - 1]; i--)
        inv[i - 1] = inv[i] * i;
}

Modint fact(ll n)
{
    if (n < 0)
        return 0;
    reserve(n + 1);
    return fac[n];
}

Modint perm(ll n, ll r)
{
    if (r < 0 || n < r)
        return 0;
    if (n >> 24)
    {
        Modint ans = 1;
        for (ll i = 0; i < r; i++)
            ans *= n--;
        return ans;
    }
    reserve(n + 1);
    return fac[n] * inv[n - r];
}

Modint comb(ll n, ll r)
{
    if (r < 0 || n < r)
        return 0;
    reserve(r + 1);
    return perm(n, r) * inv[r];
}