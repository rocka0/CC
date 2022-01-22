#include <bits/stdc++.h>
using namespace std;

/*
    Source: https://github.com/rocka0/CC

    Usage:  Edge E; cin >> E.from >> E.to >> E.weight;
*/

struct Edge {
    int from;
    int to;
    int64_t weight;

    bool operator<(const Edge& other) const {
        // NOTE: Use > for descending order
        return weight < other.weight;
    }
};

inline string to_string(Edge E) {
    return '{' + to_string(E.from) + " -> " + to_string(E.to) + ", " + to_string(E.weight) + '}';
}
