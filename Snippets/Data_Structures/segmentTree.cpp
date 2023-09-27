#include <vector>

/*
    Source: https://github.com/rocka0/CC

    Usage:  segtree st(n);
*/

struct segtree {
    struct node_t {
        int m_sum;

        explicit node_t() {
            m_sum = 0;
        }

        explicit node_t(int sum) {
            m_sum = sum;
        }

        explicit node_t(const node_t &l, const node_t &r) {
            m_sum = l.m_sum + r.m_sum;
        }
    };

    explicit segtree(int n) {
        m_n = 1;
        while (m_n < n) m_n <<= 1;
        m_tree.resize(2 * m_n);
    }

    void update(int idx, int val) {
        idx += m_n;
        m_tree[idx] = node_t(val);
        while (idx >>= 1) {
            m_tree[idx] = node_t(m_tree[idx << 1], m_tree[idx << 1 | 1]);
        }
    }

    node_t query(int l, int r) {
        return query(l, r, 1, 0, m_n);
    }

    node_t query(int l, int r, int at, int at_l, int at_r) {
        if (at_r <= l or r <= at_l) {
            return node_t();
        } else if (l <= at_l and at_r <= r) {
            return m_tree[at];
        } else {
            int at_m = (at_l + at_r) >> 1;
            return node_t(query(l, r, at << 1, at_l, at_m), query(l, r, at << 1 | 1, at_m, at_r));
        }
    }

    int m_n;
    std::vector<node_t> m_tree;
};
