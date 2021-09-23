#include <bits/stdc++.h>
using namespace std;

/*
    Source: https://codeforces.com/blog/entry/11080

    Usage:  ordered_set<int> oset;
            oset.insert(1);
            oset.insert(2);
            oset.insert(4);
            oset.insert(8);
            oset.insert(16);

            // oset = {1,2,4,8,16}
            // oset.find_by_order(x)	-> returns iterator to oset[x]
            *(oset.find_by_order(1))	-> returns oset[1] = 2
            *(oset.find_by_order(2))	-> returns oset[2] = 4
            *(oset.find_by_order(4))	-> returns oset[4] = 16
            oset.find_by_order(6)		-> returns oset.end()

            // oset = {1,2,4,8,16}
            // oset.order_of_key(x) -> returns number of elements strictly
            // less than x
            oset.order_of_key(-5)	-> 0
            oset.order_of_key(1)	-> 0
            oset.order_of_key(3)	-> 2
            oset.order_of_key(4)	-> 2
            oset.order_of_key(400)	-> 5

    Note:   If we want to get map but not a set,
            the second template argument type must be declared as mapped type,
            instead of null_type.
*/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
