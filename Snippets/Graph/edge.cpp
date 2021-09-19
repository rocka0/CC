// https://github.com/rocka0/CC

struct Edge {
    int from;
    int to;
    ll weight;

    bool operator<(const Edge& other) {
        return weight < other.weight;
    }

    friend ostream& operator<<(ostream& os, const Edge& E) {
        return os << '(' << E.from << "->" << E.to << ',' << E.weight << ')';
    }
};