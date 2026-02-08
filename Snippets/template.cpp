#include "bits/stdc++.h"
using namespace std;

#define int int64_t
#ifndef LOCAL
    #define dbg(...) 257
#endif

template <typename T>
bool chmax(T &x, T y) {
    return x < y && (x = y, true);
}

template <typename T>
bool chmin(T &x, T y) {
    return x > y && (x = y, true);
}

void solve() {
    //
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
}
