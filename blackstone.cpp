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
	int n, k; cin >> n >> k;
	vector<vector<int>> adj(n+1);
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	vector<int> A(k+1, 1);
	vector<int> on(n+1);
	for (int i = 1; i <= k; i++) cin >> A[i], on[A[i]]=1;

	vector<int> in(n+1), dep(n+1), sz(n+1);
	auto sp = V(20, n+1, 0);
	int cnt = 0;
	function<void(int, int)> dfs = [&](int cur, int prv) {
		in[cur] = ++cnt;
		sp[0][cur] = prv;
		sz[cur] += on[cur];
		for (auto nxt: adj[cur]) {
			if (nxt == prv) continue;
			dep[nxt] = dep[cur]+1;
			dfs(nxt, cur);
			sz[cur] += sz[nxt];
		}
	};

	dfs(1, 1);


	for (int i = 1; i < 20; i++) for (int j = 1; j <= n; j++) sp[i][j] = sp[i-1][sp[i-1][j]];

	auto lca = [&](int u, int v) {
		if (dep[u] > dep[v]) swap(u, v);
		for (int i = 0; i < 20; i++) if ((dep[v]-dep[u]>>i)&1) v = sp[i][v];
		if (u == v) return u;
		for (int i = 19; i >= 0; i--) if (sp[i][u]^sp[i][v]) u = sp[i][u], v = sp[i][v];
		return sp[0][u];
	};

	int t = A.size();
	sort(all(A), [&](int a, int b){return in[a] < in[b];});
	for (int i = 1; i < t; i++) A.push_back(lca(A[i-1], A[i]));
	sort(all(A), [&](int a, int b){return in[a] < in[b];});
	A.erase(unique(all(A)), A.end());


	vector<vector<pll>> G(n+1);
	cnt = 0;
	for (int i = 1; i < A.size(); i++) {
		int p = lca(A[i-1], A[i]);
		G[p].push_back({A[i], dep[A[i]]-dep[p]});
	}


	function<vector<pll>(int)> f = [&](int cur) -> vector<pll>{
		int ok = on[cur];
		sort(all(G[cur]), [&](auto a, auto b){return sz[a[0]] < sz[b[0]];});
		vector<pll> ret(ok+1);
		int ss = ok;
		for (auto [nxt, v]: G[cur]) {
			ret.resize(ss+1+sz[nxt], {LINF, LINF});
			auto z = f(nxt);
			for (int x = ss; x >= 0; x--) {
				for (int j = 0; j < z.size(); j++) {
					ret[x+j][0] = min(ret[x+j][0], ret[x][1]+z[j][0]+v);
					ret[x+j][0] = min(ret[x+j][0], ret[x][0]+z[j][1]+2*v);
					ret[x+j][1] = min(ret[x+j][1], ret[x][1]+z[j][1]+2*v);
				}
			}
			ss += sz[nxt];
		}
		return ret;
	};

	auto ans = f(A[0]);
	for (int i = 1; i <= k; i++) {
		ct(ans[i][0]);
	}







}


int main() {
	FASTIO
	int T = 1;
	for (int i = 1; i <= T; i++) {
		solve();
	}
}

















