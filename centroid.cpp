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

template<typename T>
auto V(const int n, T&& val) {
	return vector(n, val);
}

template<typename... Ts>
auto V(const int n, Ts&&... args) {
	return vector(n, V(args...));
}



/*

 */


const int NMAX = 1001010;
const int MOD = 998244353;
const ll LINF = 1e18;




void solve() {
	int n, q; cin >> n >> q;
	vector<vector<pll>> adj(n+1);
	for (int i = 1; i < n; i++) {
		int a, b, c; cin >> a >> b >> c;
		a++, b++;
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}

	vector<ll> dist(n+1), dep(n+1);
	auto sp = V(20, n+1, 0);

	function<void(int, int)> dfs = [&](int cur, int prv) {
		sp[0][cur] = prv;
		for (auto [nxt, c] : adj[cur]) {
			if (nxt == prv) continue;
			dep[nxt] = dep[cur]+1;
			dist[nxt] = dist[cur] + c;
			dfs(nxt, cur);
		}
	};

	dfs(1, 1);
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j <= n; j++) {
			sp[i][j] = sp[i-1][sp[i-1][j]];
		}
	}


	auto lca = [&](int u, int v) {
		if (dep[u] > dep[v]) swap(u, v);
		int diff = dep[v]-dep[u];
		for (int i = 0; i < 20; i++) {
			if ((diff>>i)&1) v = sp[i][v];
		}
		if (u == v) return u;
		for (int i = 19; i >= 0; i--) {
			if (sp[i][u] != sp[i][v]) {
				u = sp[i][u];
				v = sp[i][v];
			}
		}
		return sp[0][u];
	};

	auto cal = [&](int u, int v) {
		return dist[u]+dist[v]-2*dist[lca(u, v)];
	};


	vector<int> vis(n+1), sz(n+1), cdtree(n+1);


	function<int(int, int)> get_size = [&](int cur, int prv) -> int {
		sz[cur] = 1;
		for (auto [nxt, c]: adj[cur]) {
			if (prv == nxt || vis[nxt]) continue;
			sz[cur] += get_size(nxt, cur);
		}
		return sz[cur];
	};

	function<int(int, int, int)> get_cen = [&](int cur, int prv, int cap) -> int{
		for (auto [nxt, c]: adj[cur]) {
			if (nxt == prv || vis[nxt] || sz[nxt] <= cap/2) continue;
			return get_cen(nxt, cur, cap);
		}
		return cur;
	};


	function<void(int, int)> cd = [&](int cur, int prv) {
		int cen = get_cen(cur, cur, get_size(cur, cur));
		vis[cen] = 1;
		if (prv == -1) cdtree[cen] = cen;
		else cdtree[cen] = prv;
		for (auto [nxt, c]: adj[cen]) {
			if (vis[nxt]) continue;
			cd(nxt, cen);
		}
	};

	cd(1, -1);


	vector<vector<pll>> cdpd(n+1);
	for (int i = 1; i <= n; i++) {
		ll now = i;
		while (now != cdtree[now]) {
			cdpd[i].push_back({now, cal(i, now)});
			now = cdtree[now];
		}
		cdpd[i].push_back({now, cal(i, now)});
	}

	vector<ll> buc(n+1, LINF);

	function<void(int)> upd = [&](int s) {
		for (auto [a, b]: cdpd[s]) {
			buc[a] = min(buc[a], b);
		}
	};

	function<ll(int)> query = [&](int s) -> ll{
		ll ret = LINF;
		for (auto [a, b]: cdpd[s]) {
			ret = min(ret, buc[a]+b);
		}
		return ret;
	};

	function<void(int)> recover = [&](int s) {
		for (auto [a, b]: cdpd[s]) {
			if (buc[a] == LINF) break;
			buc[a] = LINF;
		}
	};


	while (q--) {
		int a, b; cin >> a >> b;
		vector<int> A(a), B(b);
		for (int &i: A) cin >> i, i++;
		for (int &i: B) cin >> i, i++;
		ll ans = LINF;
		for (auto i: A) upd(i);
		for (auto i: B) ans = min(ans, query(i));
		for (auto i: A) recover(i);
		ct(ans);
	}




}


int main() {
	FASTIO
	int T = 1;
	for (int i = 1; i <= T; i++) {
		solve();
	}
}

















