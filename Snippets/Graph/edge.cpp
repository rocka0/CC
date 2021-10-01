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

    bool operator<(const Edge& other) {
        // NOTE: Use > for descending order
        return weight < other.weight;
    }

    friend ostream& operator<<(ostream& os, const Edge& E) {
        return os << '(' << E.from << "->" << E.to << ',' << E.weight << ')';
    }
};
