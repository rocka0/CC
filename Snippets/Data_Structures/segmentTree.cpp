#include <bits/stdc++.h>
using namespace std;

/*
    Source: https://github.com/rocka0/CC

    Usage:  SegmentTree seg(vector<int> arr);
            seg.update(int index, int val)
            seg.query(int l, int r) -> returns associative op on range[l, r)
*/

// TODO: Change Node of SegmentTree
struct Node {
    using T = int64_t;

    T val;

    // TODO: Change default constructor to reflect Identity Node
    Node() : Node(INT_MAX) {}

    Node(T val) {
        this->val = val;
    }

    operator T() const {
        return val;
    }
};

const Node IdentityNode;

// TODO: Change Associative Merge Operation of SegmentTree
Node merge(const Node &left, const Node &right) {
    return Node(min(left.val, right.val));
}

class SegmentTree {
public:
    SegmentTree() : SegmentTree(0) {}
    SegmentTree(int n) : SegmentTree(vector<int>(n, 0)) {}

    SegmentTree(const vector<int> &arr) {
        int _n = arr.size();
        int log = ceil_pow2(_n);
        n = 1 << log;
        tree.resize(n << 1, IdentityNode);
        for (int i = 0; i < _n; i++) {
            // TODO: Set leaf nodes of SegmentTree from arr
            tree[n + i] = Node(arr[i]);
        }
        for (int i = n - 1; i >= 1; i--) {
            pull(i);
        }
    }

    void update(int index, int val) {
        tree[index += n] = Node(val);
        while (index > 1) {
            index >>= 1;
            pull(index);
        }
    }

    Node query(int l, int r, int at, int lo, int hi) const {
        if (l <= lo and hi <= r) {
            return tree[at];
        } else if (hi <= l or r <= lo) {
            return IdentityNode;
        } else {
            int mi = (lo + hi) >> 1;
            Node left = query(l, r, at << 1, lo, mi);
            Node right = query(l, r, at << 1 | 1, mi, hi);
            return merge(left, right);
        }
    }

    Node query(int l, int r) const {
        return query(l, r, 1, 0, n);
    }

private:
    int n;
    vector<Node> tree;

    void pull(int x) {
        tree[x] = merge(tree[x << 1], tree[x << 1 | 1]);
    }

    int ceil_pow2(int t) {
        int x = 0;
        while ((1u << x) < (uint32_t) (t)) x++;
        return x;
    }
};
