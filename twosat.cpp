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

struct twoSAT {
	vector<int> discovered, sccNumber;
	vector<vector<int> > adj;
	int cnt1, cnt2, n;

	twoSAT(int n) {
		this->n = n;
		discovered.resize(2*n);
		sccNumber.resize(2*n);
		adj.resize(2*n);
	}

	stack<int> S;
	int scc(int here) {
		discovered[here] = cnt1++;
		int ret = discovered[here];
		S.push(here);
		for (int &there : adj[here]) {
			if (discovered[there] == -1)
				ret = min(ret, scc(there));
			else if (sccNumber[there] == -1)
				ret = min(ret, discovered[there]);
		}
		if (ret == discovered[here]) {
			while (true) {
				int tmp = S.top();
				S.pop();
				sccNumber[tmp] = cnt2;
				if (tmp == here) break;
			}
			++cnt2;
		}
		return ret;
	}
	vector<int> solve() {
		int V = n;
		V *= 2;
		fill(all(discovered), -1);
		fill(all(sccNumber), -1);
		cnt1 = 0, cnt2 = 0;
		for (int i = 0; i < V; ++i)
			if (discovered[i] == -1)
				scc(i);
		for (int i = 0; i < V; i += 2)
			if (sccNumber[i] == sccNumber[i + 1])
				return vector<int>();
		vector<int> ans(V / 2, -1);
		vector<int> arr(2*n);
		for (int i = 0; i < V; ++i)
			arr[i] = i;
		sort(all(arr), [&](int &a, int &b) {
			if (sccNumber[a] != sccNumber[b])
				return sccNumber[a] > sccNumber[b];
			return a < b;
		});
		for (int i = 0; i < V; ++i)
			if (ans[arr[i] / 2] == -1)
				ans[arr[i] / 2] = !(arr[i] & 1);
		return ans;
	}
	void makeEdge(int X, bool XisTrue, int Y, bool YisTrue) {
		adj[2 * X + !XisTrue].push_back(2 * Y + YisTrue);
		adj[2 * Y + !YisTrue].push_back(2 * X + XisTrue);

	}


};


/*

 */


const int NMAX = 201010;
const int MOD = 998244353;
const ll LINF = 1e18;

int A[NMAX], B[NMAX];

void solve() {
	int n; cin >> n;
	vector<int> v;
	for (int i = 1; i <= n; i++) {
		int op; cin >> op;
		if (op == 1) {
			cin >> A[i] >> B[i];
		} else {
			v.push_back(i);
		}
	}
	int l = 1, r = n;
	int ans = 0;
	while (l <= r) {
		int mid = (l+r)/2;
		twoSAT TS(100001);
		for (int i = 1; i <= mid; i++) {
			if (A[i]) {
				TS.makeEdge(abs(A[i]), A[i] > 0, abs(B[i]), B[i] > 0);
			}
		}
		auto t = TS.solve();
		if (t.size() != 0) {
			ans = mid;
			l = mid+1;
		} else r = mid-1;
	}
	for (int i: v) {
		ct(i <= ans ? "YES DINNER": "NO DINNER");
	}

}


int main() {
	FASTIO
	int T = 1;
	for (int i = 1; i <= T; i++) {
		solve();
	}
}

















