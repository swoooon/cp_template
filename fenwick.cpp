struct Fenwick {
    vector<ll> tree;
    int n;
    Fenwick(int n) {
        tree.resize(4 * n + 5);
        this->n = n;
    }
    ll get(int i) {
        ll ans = 0;
        while (i) {ans += tree[i], i -= (i&-i);}
        return ans;
    }
    ll q(int l, int r) {
        if (l > 0) return get(r)-get(l-1);
        return get(r);
    }
    void upd(int i, ll val) {
        for (;i <= n; i += i&-i) {tree[i] += val;}
    }
};
