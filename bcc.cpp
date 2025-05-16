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


struct BCC {
	int n;
	vector<pii> edges;
	vector<vector<pii>> adj;

	vector<int> is_bridge, is_cut;

	int bcc_cnt, vtime;
	vector<vector<int>> bcc_edges;

	vector<int> up, vis;
	vector<int> st;

	BCC(int n) {
		this->n = n;
		adj.resize(n+1);
		bcc_edges.resize(n+1);
		is_cut.resize(n+1);
		up.resize(n+1);
		vis.resize(n+1);
	}


	void dfs(int cur, int pe) {
		up[cur] = vis[cur] = ++vtime;
		int child = 0;
		for (auto [nxt, eid]: adj[cur]) {
			if (eid == pe) continue;
			if (vis[nxt] == 0) {
				st.push_back(eid);
				++child;
				dfs(nxt, eid);
				if (up[nxt] == vis[nxt]) is_bridge[eid] = 1;
				if (up[nxt] >= vis[cur]) {
					++bcc_cnt;
					do {
						auto lasteid = st.back();
						st.pop_back();
						bcc_edges[bcc_cnt].push_back(lasteid);
						if (lasteid == eid) break;
					} while (!st.empty());
					is_cut[cur]++;
				}
				up[cur] = min(up[cur], up[nxt]);
			} else if (vis[nxt] < vis[cur]) {
				st.push_back(eid);
				up[cur] = min(up[cur], vis[nxt]);
			}
		}

		if (pe == -1 && is_cut[cur] == 1) is_cut[cur] = 0;

	}

	void add_edge(int x, int y) {
		adj[x].push_back({y, edges.size()});
		adj[y].push_back({x, edges.size()});
		edges.push_back({x, y});
	}

	void get_bcc() {
		is_bridge.clear();
		is_bridge.resize(edges.size() + 1);
		for (int i = 0; i < n; ++i) bcc_edges[i].clear();
		bcc_cnt = 0;
		vtime = 0;
		for (int i = 1; i <= n; ++i) {
			if (vis[i] == 0)
				dfs(i, -1);
		}
	}
};

void solve() {
	int n, m; cin >> n >> m;
	BCC bcc(n);
	for (int i = 1; i <= m; i++) {
		int a, b; cin >> a >> b;
		bcc.add_edge(a, b);
	}

	bcc.get_bcc();


}


int main() {
	FASTIO
	int T = 1;
	for (int i = 1; i <= T; i++) {
		solve();
	}
}

















