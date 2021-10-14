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

template <class T>
class Y {
    T f_;

public:
    template <class U>
    explicit Y(U&& f) : f_(forward<U>(f)) {}
    template <class... Args>
    decltype(auto) operator()(Args&&... args) {
        return f_(ref(*this), forward<Args>(args)...);
    }
};
template <class T>
Y(T) -> Y<T>;
