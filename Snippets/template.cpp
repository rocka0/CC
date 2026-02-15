#include "bits/stdc++.h"
using namespace std;

#ifdef LOCAL
#include "dbg.h"  // IWYU pragma: keep
#else
#define dbg(...) 257
#endif

template <typename T>
bool chmax(T& a, const T& b) { return a < b && (a = b, true); }
template <typename T>
bool chmin(T& a, const T& b) { return a > b && (a = b, true); }

void solve() {
    //
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T = 1;
    cin >> T;
    while (T--) solve();
}
