// ᕙ(⇀‸↼‶)ᕗ ~ TBC

// Libraries
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
#define all(x) (x).begin(), (x).end()
#define sz(x) static_cast<int>(x.size())
#define endl '\n'
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

// Typedefs
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using pi = pair<int, int>;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Debugging Template
string to_string(string s) { return '"' + s + '"'; }
string to_string(const char *s) { return to_string((string)s); }
string to_string(bool b) { return (b ? "true" : "false"); }
template <typename A, typename B> string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
template <typename A> string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

// Recursive Lambda Y Combinator
template <class Fun> class y_combinator_result {
    Fun fun_;

public:
    template <class T>
    explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

    template <class... Args> decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};
template <class Fun> decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

// Self max/min functions
template <typename T> bool chkmax(T &x, T y) {
    return x < y ? x = y, true : false;
}
template <typename T> bool chkmin(T &x, T y) {
    return x > y ? x = y, true : false;
}

// https://codeforces.com/blog/entry/62393
// struct safe_hash {
//     static uint64_t splitmix64(uint64_t x) {
//          // http://xorshift.di.unimi.it/splitmix64.c
//         x += 0x9e3779b97f4a7c15;
//         x = (x ^ (x >> 30)) *0xbf58476d1ce4e5b9;
//         x = (x ^ (x >> 27)) *0x94d049bb133111eb;
//         return x ^ (x >> 31);
//     }

//     size_t operator()(uint64_t x) const {
//         static const uint64_t FIXED_RANDOM =
//         chrono::steady_clock::now().time_since_epoch().count(); return
//         splitmix64(x + FIXED_RANDOM);
//     }
// };

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

void solve() {
    // Test Case code goes here

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // cout << fixed << setprecision(15);

    int t = 1;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}