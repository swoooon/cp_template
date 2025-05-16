#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<int, int> pii;
typedef array<ll, 2> pll;
typedef long double ld;

#define xx first
#define yy second
#define FASTIO                   \
ios::sync_with_stdio(false); \
cin.tie(0);                  \
cout.tie(0);
#define debug(x) cout << (#x) << ": " << (x) << '\n'
#define all(x) begin(x), end(x)


template<class T>
void ct(T &&v) { cout << forward<T>(v) << '\n'; }

template<class T, class... Args>
void ct(T &&v, Args &&...args) {
	cout << forward<T>(v) << ' ';
	ct(forward<Args>(args)...);
};




/*

 */


const int NMAX = 500001;
const int MOD = 998244353;
const ll LINF = 1e18;
const ll bit = (1<<19)-1;

struct PersistentSegmentTree {
	struct Node {
		int value = 0; //반드시 항등원
		int lidx = 0, ridx = 0;
	};
	vector<int> root;
	vector<Node> seg;
	int n;

	void init(int n) {
		seg.clear();
		root.clear();
		seg.emplace_back(); //dummy
		seg.emplace_back(); //root
		root.emplace_back(1);
		this->n = n;
	}

	void update(int prv, int cur, int idx, int value, int nl, int nr) {
		if (idx < nl || nr < idx) return;
		if (nl == nr) {
			seg[cur].value += value;
			return;
		}
		int mid = (nl + nr) / 2;
		int nxt = seg.size();
		if (idx <= mid) {
			seg[cur].ridx = seg[prv].ridx;
			seg.emplace_back(seg[prv].lidx ? seg[seg[prv].lidx] : Node());
			seg[cur].lidx = nxt;
			update(seg[prv].lidx, seg[cur].lidx, idx, value, nl, mid);
		} else {
			seg[cur].lidx = seg[prv].lidx;
			seg.emplace_back(seg[prv].ridx ? seg[seg[prv].ridx] : Node());
			seg[cur].ridx = nxt;
			update(seg[prv].ridx, seg[cur].ridx, idx, value, mid+1, nr);
		}
		seg[cur].value = seg[seg[cur].lidx].value + seg[seg[cur].ridx].value;
	}

	int update(int idx, int value, int prv = -1) {
		int cur = seg.size();
		if (prv == -1) prv = root.back();
		else prv = root[prv];
		seg.emplace_back();
		root.push_back(cur);
		update(prv, cur, idx, value, 0, n);
		return root.size()-1;
	}

	int query(int idx, int l, int r, int nl, int nr) {
		if (!idx || nr < l || r < nl) return 0;
		if (l <= nl && nr <= r) return seg[idx].value;
		int mid = (nl + nr) / 2;
		return query(seg[idx].lidx, l, r, nl, mid) + query(seg[idx].ridx, l, r, mid + 1, nr);
	}

	int query(int root_idx, int l, int r) {
		return query(root[root_idx], l, r, 0, n);
	}


	int q2(int li, int ri, int x) {
		int l = 0, r = bit;
		for (int i = 18; i >= 0; i--) {
			int t;
			if ((x>>i)&1) {
				t = seg[seg[ri].lidx].value - seg[seg[li].lidx].value;
				if (t) {
					r -= (1<<i);
					li = seg[li].lidx;
					ri = seg[ri].lidx;
				} else {
					l += (1<<i);
					li = seg[li].ridx;
					ri = seg[ri].ridx;
				}
			} else {
				t = seg[seg[ri].ridx].value - seg[seg[li].ridx].value;
				if (t) {
					l += (1<<i);
					li = seg[li].ridx;
					ri = seg[ri].ridx;
				} else {
					r -= (1<<i);
					li = seg[li].lidx;
					ri = seg[ri].lidx;
				}
			}
		}
		return r;
	}

	int q5(int li, int ri, int x, int l, int r) {
		if (l == r) {return l;}
		int mid = (l+r)/2;
		int t = seg[seg[ri].lidx].value - seg[seg[li].lidx].value;
		if (x <= t) return q5(seg[li].lidx, seg[ri].lidx, x, l, mid);
		return q5(seg[li].ridx, seg[ri].ridx, x-t, mid+1, r);
	}

}pst;



void solve() {
	int q; cin >> q;
	pst.init(bit);
	while (q--) {
		int op, l, r, x; cin >> op;
		if (op == 1) {
			cin >> x;
			pst.update(x, 1);
		} else if (op == 2) {
			cin >> l >> r >> x;
			ct(pst.q2(pst.root[l-1], pst.root[r], x));
		} else if (op == 3) {
			cin >> x;
			for (int i = 0; i < x; i++) pst.root.pop_back();
		} else if (op == 4) {
			cin >> l >> r >> x;
			ct(pst.query(r, 0, x)-pst.query(l-1, 0, x));
		} else {
			cin >> l >> r >> x;
			ct(pst.q5(pst.root[l-1], pst.root[r], x, 0, bit));
		}
	}

}


int main() {
	FASTIO
	int T = 1;
	for (int i = 1; i <= T; i++) {
		solve();
	}
}

















