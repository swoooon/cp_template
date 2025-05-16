#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef long double ld;

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


struct SCC {
	int vstn, sccn;
	vector<int> vst;
	vector<vector<int>> adj;
	stack<int> s;

	vector<int> scci; // i in scc[i]
	vector<vector<int>> scc;
	int n;

	SCC(int n) {
		n++;
		this->n = n;
		vst.resize(n);
		vst.resize(n);
		adj.resize(n);
	}

	int DFS(int here) {
		vst[here] = vstn++;
		int ret = vst[here];
		s.push(here);
		for (int &there : adj[here]) {
			if (vst[there] == -1)
				ret = min(ret, DFS(there));
			else if (scci[there] == -1)
				ret = min(ret, vst[there]);
		}
		if (ret == vst[here]) {
			scc.emplace_back(vector<int>());
			auto &V = scc.back();
			while (true) {
				int tmp = s.top();
				s.pop();
				scci[tmp] = sccn;
				V.push_back(tmp);
				if (tmp == here) break;
			}
			++sccn;
		}
		return ret;
	}

	void make_scc() {
		scc.clear();
		vst.assign(n, -1);
		scci.assign(n, -1);
		vstn = 0, sccn = 0;
		for (int i = 1; i <= n; ++i)
			if (vst[i] == -1)
				DFS(i);
	}

	vector<vector<int>> make_scc_adj() {
		vector<vector<int>> sadj(scc.size());
		for(int i=0; i<scc.size(); ++i) {
			auto &A = sadj[i];
			for(int x : scc[i])
				for(int y : adj[x])
					if(scci[x] != scci[y])
						A.emplace_back(scci[y]);
			sort(all(A));
			A.erase(unique(all(A)), A.end());
		}
		return sadj;
	}
};


/*

 */


const int NMAX = 201010;
const int MOD = 998244353;
const ll LINF = 1e18;


void solve() {
	int n, m; cin >> n >> m;
	SCC scc(n);
	for (int i = 1; i <= m; i++) {
		int a, b; cin >> a >> b;
		scc.adj[a].push_back(b);
	}

	scc.make_scc();
	vector<vector<int>> ans;
	for (auto i : scc.scc) {
		sort(all(i));
		ans.push_back(i);
	}
	sort(all(ans));
	ct(ans.size());
	for (auto i: ans) {
		for (auto j: i) cout << j << " ";
		ct("-1");
	}

}


int main() {
	FASTIO
	int T = 1;
	for (int i = 1; i <= T; i++) {
		solve();
	}
}

















