#include <bits/stdc++.h>
using namespace std;

/*
    Source: https://github.com/rocka0/CC

    Usage:  SegmentTree segt(vector<SegmentTree::Node> arr);
            segt.update(int index, SegmentTree::Node val)
            segt.query(int l, int r) -> returns SegmentTree::Node
            of (op) on range[l, r)
*/

class SegmentTree {
public:
    // Segment Tree Node
    struct Node {
        int64_t val;

        Node() : Node(0) {}
        Node(int64_t val) {
            this->val = val;
        }
    };

private:
    // Associative merge operation
    Node merge(const Node &left, const Node &right) {
        Node res(left.val + right.val);
        return res;
    }

    // Identity Node
    const Node ID;

public:
    SegmentTree() : SegmentTree(0) {}
    SegmentTree(int n) : SegmentTree(vector<Node>(n, ID)) {}
    SegmentTree(const vector<Node> &arr) {
        int _n = arr.size();
        int log = ceil_pow2(_n);
        n = 1 << log;
        tree.resize(n << 1, ID);
        for (int i = 0; i < _n; i++) {
            tree[n + i] = arr[i];
        }
        for (int i = n - 1; i >= 1; i--) {
            pull(i);
        }
    }

    void update(int index, Node val) {
        tree[index += n] = val;
        while (index > 1) {
            index >>= 1;
            pull(index);
        }
    }

    Node query(int l, int r, int at, int lo, int hi) {
        if (l <= lo and hi <= r) {
            return tree[at];
        } else if (hi <= l or r <= lo) {
            return ID;
        } else {
            int mi = (lo + hi) >> 1;
            Node left = query(l, r, at << 1, lo, mi);
            Node right = query(l, r, at << 1 | 1, mi, hi);
            return merge(left, right);
        }
    }

    Node query(int l, int r) {
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
