#include <bits/stdc++.h>
using namespace std;

/*
    Source: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html

    Usage:  auto factorial = Y([&](auto F, int x) -> int {
                if (x == 0 or x == 1) {
                    return 1;
                }
                return x * F(x - 1);
            });
*/

template <class Fun>
class y_combinator_result {
    Fun fun_;

public:
    template <class T>
    explicit y_combinator_result(T&& fun) : fun_(forward<T>(fun)) {}
    template <class... Args>
    decltype(auto) operator()(Args&&... args) {
        return fun_(ref(*this), forward<Args>(args)...);
    }
};
template <class Fun>
decltype(auto) Y(Fun&& fun) {
    return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
}
