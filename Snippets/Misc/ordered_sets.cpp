#include <bits/stdc++.h>
using namespace std;

/*
    Source: https://codeforces.com/blog/entry/11080

    Ordered_Set:
        Usage:  ordered_set<int> oset;
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

    Ordered_Multiset:
        Usage:  ordered_multiset<int> omset;

        Note:   One can also achieve ordered_multiset using ordered_set and changing
                less<T> to less_equal<T>.
                // using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
                There are some things to be noted about this new ordered_multiset:
                    1. ordered_multiset::erase() method doesn't work
                    2. ordered_multiset::lower_bound() behaves like upper_bound()
                    3. ordered_multiset::upper_bound() behaves like lower_bound()
                    4. ordered_multiset::find() always returns ordered_multiset::end()
                    5. ordered_multiset::find_by_order() and ordered_multiset::order_of_key()
                    work normally

*/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T>
struct ordered_multiset {
    ordered_set<pair<T, int>> oset;
    map<T, int> freq;

    // NOTE: Stores size of entire multiset
    int size;

    ordered_multiset() {
        oset.clear();
        freq.clear();
        size = 0;
    }

    void add(T ele) {
        // NOTE: Adds an element into the multiset
        oset.insert({ele, freq[ele]});
        ++freq[ele];
        ++size;
    }

    void remove(T ele) {
        // NOTE: Removes an element from the multiset
        if (freq.find(ele) == freq.end()) return;
        --freq[ele];
        --size;
        oset.erase({ele, freq[ele]});
        if (!freq[ele]) {
            freq.erase(ele);
        }
    }

    int strictlyLess(T x) {
        // NOTE: Returns the number of elements < than x
        return oset.order_of_key({x, 0});
    }

    int strictlyEqual(T x) {
        // NOTE: Returns the number of elements == to x
        return freq[x];
    }

    int strictlyGreater(T ele) {
        // NOTE: Returns the number of elements > than x
        return size - strictlyLess(1 + ele);
    }
};
