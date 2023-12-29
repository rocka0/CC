#include <iostream>

// Source: https://codeforces.com/blog/entry/11080

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template <typename T>
struct ordered_set {
    int size() const {
        return data.size();
    }

    bool insert(T element) {
        return data.insert(element).second;
    }

    bool erase(T element) {
        return data.erase(element);
    }

    int strictlyLess(T val) const {
        return static_cast<int>(data.order_of_key(val));
    }

    int strictlyGreater(T val) const {
        return static_cast<int>(data.size() - data.order_of_key(val + 1));
    }

    int strictlyEqual(T val) const {
        return data.find(val) != data.end();
    }

    // Returns the number of elements in the inclusive range [l,r] present in the set
    int inBetween(T l, T r) const {
        assert(l <= r);
        return static_cast<int>(data.order_of_key(r + 1) - data.order_of_key(l));
    }

    // Returns the element present at position "index" in the < order of elements in the set
    T get(int index) const {
        assert(0 <= index && index < size());
        return *data.find_by_order(index);
    }

    __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> data;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const ordered_set<T>& s) {
    os << "{";
    for (auto it = s.data.begin(); it != s.data.end(); it++) {
        if (it != s.data.begin())
            os << ", ";
        os << *it;
    }
    os << "}";
    return os;
}

/*
 * Since we use less_equal<T> instead of less<T>, some functions of ordered_multiset are changed with respect to normal std::set:
 * 1. insert() works normally
 * 2. erase() doesn't work at all
 * 3. lower_bound() works like upper_bound()
 * 4. upper_bound() works like lower_bound()
 */
template <typename T>
struct ordered_multiset {
    int size() const {
        return data.size();
    }

    bool insert(T element) {
        return data.insert(element).second;
    }

    bool erase(T element) {
        auto it = data.upper_bound(element);
        if (it != data.end() && *it == element) {
            data.erase(it);
            return true;
        }
        return false;
    }

    int strictlyLess(T val) const {
        return static_cast<int>(data.order_of_key(val));
    }

    int strictlyGreater(T val) const {
        return static_cast<int>(data.size() - data.order_of_key(val + 1));
    }

    int strictlyEqual(T val) const {
        return static_cast<int>(data.order_of_key(val + 1) - data.order_of_key(val));
    }

    // Returns the number of elements in the range [l, r] in the multiset
    int inBetween(T l, T r) const {
        assert(l <= r);
        return static_cast<int>(data.order_of_key(r + 1) - data.order_of_key(l));
    }

    // Returns the element at position "index" in the sorted < order of elements in the multiset
    T get(int index) const {
        assert(0 <= index && index < size());
        return *data.find_by_order(index);
    }

    __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less_equal<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> data;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const ordered_multiset<T>& s) {
    os << "{";
    for (auto it = s.data.begin(); it != s.data.end(); it++) {
        if (it != s.data.begin())
            os << ", ";
        os << *it;
    }
    return os << "}";
}
