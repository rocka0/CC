#include <cassert>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>

using namespace __gnu_pbds;

template <typename T>
using pbds_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using pbds_multiset = tree<T, null_type, std::less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T>
struct ordered_set {
    pbds_set<T> data;

    int size() const { return data.size(); }
    bool insert(T val) { return data.insert(val).second; }
    bool erase(T val) { return data.erase(val); }
    int strictlyLess(T val) const { return data.order_of_key(val); }
    int strictlyGreater(T val) const { return size() - data.order_of_key(val + 1); }
    int strictlyEqual(T val) const { return data.find(val) != data.end(); }
    int inBetween(T l, T r) const { return data.order_of_key(r + 1) - data.order_of_key(l); }
    T get(int idx) const { return *data.find_by_order(idx); }

    friend std::ostream& operator<<(std::ostream& os, const ordered_set<T>& s) {
        os << "{";
        for (auto it = s.data.begin(); it != s.data.end(); ++it) os << (it == s.data.begin() ? "" : ", ") << *it;
        return os << "}";
    }
};

template <typename T>
struct ordered_multiset {
    pbds_multiset<T> data;

    int size() const { return data.size(); }
    bool insert(T val) { return data.insert(val).second; }

    bool erase(T val) {
        int idx = strictlyLess(val);
        if (idx < size() && get(idx) == val) {
            data.erase(data.find_by_order(idx));
            return true;
        }
        return false;
    }

    int strictlyLess(T val) const { return data.order_of_key(val); }
    int strictlyGreater(T val) const { return size() - data.order_of_key(val + 1); }
    int strictlyEqual(T val) const { return data.order_of_key(val + 1) - data.order_of_key(val); }
    int inBetween(T l, T r) const { return data.order_of_key(r + 1) - data.order_of_key(l); }
    T get(int idx) const { return *data.find_by_order(idx); }

    friend std::ostream& operator<<(std::ostream& os, const ordered_multiset<T>& s) {
        os << "{";
        for (auto it = s.data.begin(); it != s.data.end(); ++it) os << (it == s.data.begin() ? "" : ", ") << *it;
        return os << "}";
    }
};
