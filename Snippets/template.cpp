/*
No one,
can construct for you,
the bridge,
upon which precisely,
you must cross,
the stream of life,
no one,
but you yourself alone.
    - Friedrich Wilhelm Nietzsche
*/

// Header Files
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// Namespaces
using namespace std;
using namespace __gnu_pbds;

// Macros
#define pb push_back
#define ff first
#define ss second
#define all(x) ((x)).begin(), ((x)).end()
#define sz(x) static_cast<int>((x).size())
#define endl '\n'
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

// Typedefs
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using pi = pair<int, int>;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Debugging
template <typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}
template < typename T_container, typename T = typename enable_if < !is_same<T_container, string>::value, typename T_container::value_type >::type >
ostream & operator<<(ostream& os, const T_container& v)
{
    os << '{';
    string sep;
    for (const T& x : v) {
        os << sep << x, sep = ", ";
    }
    return os << '}';
}
void debug_out()
{
    cerr << endl;
}
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    debug_out(T...);
}

// Recursive Lambda
template <class Fun>
class y_combinator_result {
    public:
        template <class T>
        explicit y_combinator_result(T&& fun): fun_(forward<T>(fun)) {}
        template <class... Args>
        decltype(auto) operator()(Args&& ... args) {
            return fun_(ref(*this), forward<Args>(args)...);
        }
    private:
        Fun fun_;
};
template <class Fun>
decltype(auto) y_combinator(Fun&& fun)
{
    return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
}

// Change max/min functions
template <typename T>
bool chmax(T& x, T y)
{
    return x < y ? x = y, true : false;
}
template <typename T>
bool chmin(T& x, T y)
{
    return x > y ? x = y, true : false;
}

// Safe Hash: https://codeforces.com/blog/entry/62393
struct safe_hash {
    static ull splitmix64(ull x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(ull x) const {
        static const ull FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void solve()
{
    // TODO: Reset variables between tests

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout << fixed << setprecision(15);

    int tc = 1;
    cin >> tc;

    while (tc--) {
        solve();
    }

    return 0;
}