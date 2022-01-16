#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#include "debug.h"
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

template <class T>
class Y {
    T f_;

public:
    template <class U>
    explicit Y(U &&f) : f_(forward<U>(f)) {}
    template <class... Args>
    decltype(auto) operator()(Args &&...args) {
        return f_(ref(*this), forward<Args>(args)...);
    }
};
template <class T>
Y(T) -> Y<T>;

template <typename T>
bool chmax(T &x, T y) {
    return x < y and (x = y, true);
}
template <typename T>
bool chmin(T &x, T y) {
    return x > y and (x = y, true);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Code goes here
}
