class LazySegmentTree {
public:
    vector<ll> seg;
    vector<ll> lazy;
    int n;
    LazySegmentTree(int n) {
        seg.resize(4 * n + 5);
        lazy.resize(4 * n + 5);
        this->n = n;
    }
    void prop(int node, int l, int r) {
        if (lazy[node] == 0) return;
        if (l != r) {
            lazy[node*2] += lazy[node]; //
            lazy[node*2+1] += lazy[node]; //
        }
        seg[node] += lazy[node];
        lazy[node] = 0;
    }

    void upd(int node, int l, int r, int wl, int wr, ll val) {
        prop(node, l, r);
        if (wr < l || wl > r) return;
        if (wl <= l && r <= wr) {
            lazy[node] += val;
            prop(node, l, r);
            return;
        }
        int mid = (l + r) / 2;
        upd(node * 2, l, mid, wl, wr, val);
        upd(node * 2 + 1, mid + 1, r, wl, wr, val);
        seg[node] = max(
            seg[node*2], //
            seg[node*2+1]
        );
    }

    ll query(int node, int l, int r, int wl, int wr) {
        prop(node, l, r);
        if (l > wr || r < wl) return 0;
        if (wl <= l && r <= wr) return seg[node];
        int mid = (l + r) / 2;
        return max(
            query(node * 2, l, mid, wl, wr), //
            query(node * 2 + 1, mid + 1, r, wl, wr)
        );
    }

    ll query(int wl, int wr) {return query(1, 1, n, wl, wr);}
    void upd(int wl, int wr, ll val) {upd(1, 1, n, wl, wr, val);}

};
