
struct SegmentTree {
    vector<ll> seg;
    int n;
    SegmentTree(int n) {
        seg.resize(4 * n + 5);
        this->n = n;
    }
    void upd(int node, int l, int r, int target, ll val) {
        if (target < l || target > r) return;
        if (target == l && target == r) {
            seg[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        upd(node*2, l, mid, target, val);
        upd(node*2+1, mid+1, r, target, val);
        seg[node] = (seg[node*2] + seg[node*2+1]);
        return;
    }
    ll query(int node, int l, int r, int wl, int wr) {
        if (l > wr || r < wl) return 0;
        if (wl <= l && r <= wr) return seg[node];
        int mid = (l + r) / 2;
        return (
            query(node * 2, l, mid, wl, wr) +
            query(node * 2 + 1, mid + 1, r, wl, wr)
        );
    }

    void upd(int idx, ll val) {
        upd(1, 1, n, idx, val);
    }
    ll query(int wl, int wr) {
        return query(1, 1, n, wl, wr);
    }
};
