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


const int NMAX = 606;
const int MOD = 998244353;
const ll LINF = 1e18;


struct MinCostMaxFlow{
	struct edg{ ll pos, cap, rev; ll cost; };
	vector<edg> adj[NMAX];
	void clear(){
		for(int i=0; i<NMAX; i++) adj[i].clear();
	}
	void add_edge(ll from, ll to, ll cap, ll cost){
		adj[from].push_back({to, cap, (int)adj[to].size(), cost});
		adj[to].push_back({from, 0, (int)adj[from].size()-1, -cost});
	}
	ll dist[NMAX];
	int pa[NMAX], pe[NMAX];
	bool inque[NMAX];
	bool spfa(int src, int sink){
		memset(dist, 0x3f, sizeof(dist));
		memset(inque, 0, sizeof(inque));
		queue<int> que;
		dist[src] = 0;
		inque[src] = 1;
		que.push(src);
		bool ok = 0;
		while(!que.empty()){
			int x = que.front();
			que.pop();
			if(x == sink) ok = 1;
			inque[x] = 0;
			for(int i=0; i<adj[x].size(); i++){
				edg e = adj[x][i];
				if(e.cap > 0 && dist[e.pos] > dist[x] + e.cost){
					dist[e.pos] = dist[x] + e.cost;
					pa[e.pos] = x;
					pe[e.pos] = i;
					if(!inque[e.pos]){
						inque[e.pos] = 1;
						que.push(e.pos);
					}
				}
			}
		}
		return ok;
	}
	pll match(int src, int sink){
		ll min_cost=0, max_flow=0;
		while(spfa(src, sink)){
			ll cap = LINF;
			for(int pos = sink; pos != src; pos = pa[pos]){
				cap = min(cap, adj[pa[pos]][pe[pos]].cap);
			}
			min_cost += dist[sink] * cap;
			max_flow += cap;
			for(int pos = sink; pos != src; pos = pa[pos]){
				int rev = adj[pa[pos]][pe[pos]].rev;
				adj[pa[pos]][pe[pos]].cap -= cap;
				adj[pos][rev].cap += cap;
			}
		}
		return {min_cost, max_flow};
	}
};


void solve() {
	int n; cin >> n;
	int S = 0, T = 601;
	MinCostMaxFlow flow;
	flow.clear();

	vector<array<ll, 3>> A(n+1);
	for (int j = 0; j < 3; j++) {
		for (int i= 1; i <= n; i++) cin >> A[i][j];
	}
	sort(all(A));
	for (int i = 1; i <= n; i++) {
		flow.add_edge(S, i, A[i][2]-(i != n), 0);
		for (int j = 1; j < i; j++) {
			flow.add_edge(i, j+300, 1, -(A[i][0]^A[j][0])+A[i][1]+A[j][1]);
		}
		flow.add_edge(i+300, T, 1, 0);
	}

	auto ans = flow.match(S, T);
	ct(-ans[0]);

}


int main() {
	FASTIO
	int T = 1;
	for (int i = 1; i <= T; i++) {
		solve();
	}
}

















