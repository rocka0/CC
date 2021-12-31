#include <bits/stdc++.h>
using namespace std;

/*
    Source: https://codeforces.com/blog/entry/11080

    Ordered Set:
        Usage:  OrderedSet<int> oset;
                oset.insert(1);
                oset.insert(2);
                oset.insert(4);
                oset.insert(8);
                oset.insert(16);

                // oset = {1,2,4,8,16}
                // oset.find_by_order(x)    -> returns iterator to oset[x]
                *(oset.find_by_order(1))    -> returns oset[1] = 2
                *(oset.find_by_order(2))    -> returns oset[2] = 4
                *(oset.find_by_order(4))    -> returns oset[4] = 16
                oset.find_by_order(5)       -> returns oset.end()

                // oset = {1,2,4,8,16}
                // oset.order_of_key(x)     -> returns number of elements strictly less than x
                oset.order_of_key(-5)       -> 0
                oset.order_of_key(1)        -> 0
                oset.order_of_key(3)        -> 2
                oset.order_of_key(4)        -> 2
                oset.order_of_key(400)      -> 5

        Note:   If we want to get map but not a set,
                the second template argument type must be declared as mapped type,
                instead of null_type.

        Note:   One can achieve OrderedMultiset using ordered_set by changing
                less<T> to less_equal<T>.

                Usage:  template <typename T>
                        using OrderedMultiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

                        OrderedMultiset<int> omset;

                        There are some things to be noted about this OrderedMultiset:
                            1. OrderedMultiset::erase() method doesn't work
                            2. OrderedMultiset::lower_bound() behaves like upper_bound()
                            3. OrderedMultiset::upper_bound() behaves like lower_bound()
                            4. OrderedMultiset::find() always returns OrderedMultiset::end()
                            5. OrderedMultiset::find_by_order() and OrderedMultiset::order_of_key()
                            work normally

    Ordered Multiset [built using pair<T,int>]:
        Usage:  OrderedMultiset<int> omset;
                omset.insert(3);
                assert(omset.erase(3));
*/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
using OrderedSet = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T>
struct OrderedMultiset {
    OrderedSet<pair<T, int>> data;
    map<T, int> freq;

    void insert(T x) {
        data.insert({x, freq[x]});
        ++freq[x];
    };

    bool erase(T x) {
        if (freq.count(x) and freq[x] > 0) {
            --freq[x];
            auto it = data.find({x, freq[x]});
            data.erase(it);
            if (!freq[x]) {
                freq.erase(x);
            }
            return true;
        } else {
            return false;
        }
    }

    int strictlyLess(T x) {
        return data.order_of_key({x, 0});
    }

    int strictlyEqual(T x) {
        return freq[x];
    }

    int strictlyGreater(T x) {
        return (int) data.size() - strictlyLess(x) - strictlyEqual(x);
    }

    T getNthElement(int n) {
        assert(0 <= n and n < (int) data.size());
        return data.find_by_order(n)->first;
    }
};
