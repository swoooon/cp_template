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


const int NMAX = 1001010;
const int MOD = 998244353;
const ll LINF = 1e18;






void solve() {
	int n, k; cin >> n >> k;
	vector<int> A(n+1);
	for (int i = 1; i <= n; i++) cin >> A[i];
	vector<array<int, 3>> query;
	int q; cin >> q;
	for (int i = 0; i < q; i++) {
		int l, r; cin >> l >> r;
		query.push_back({l, r, i});
	}

	const int rt = sqrt(n);
	sort(all(query), [rt](auto &a, auto &b) {
		int L = a[0]/rt, R = b[0]/rt;
		if (L ^ R) return L < R; // 부등호 반대로 바꿔볼수도있음
		if (L&1) return a[1] > b[1];
		return a[1] < b[1];
	});

	vector<int> ans(n+1);
	vector<int> buc(rt+1);
	vector<pll> lr(k+1, {0, -1});
	vector<vector<int>> B(k+1);
	for (int i = 1; i <= n; i++) B[A[i]].push_back(i);

	auto addR = [&](int x) {
		auto [l, r] = lr[A[x]];
		int t;
		if (l <= r) {
			t = B[A[x]][r] - B[A[x]][l];
			ans[t]--;
			buc[t/rt]--;
		}
		r++;
		t = B[A[x]][r] - B[A[x]][l];
		ans[t]++;
		buc[t/rt]++;
		lr[A[x]][1]++;
	};

	auto popR = [&](int x) {
		auto [l, r] = lr[A[x]];
		int t;
		if (l <= r-1) {
			t = B[A[x]][r-1] - B[A[x]][l];
			ans[t]++;
			buc[t/rt]++;
		}
		t = B[A[x]][r] - B[A[x]][l];
		ans[t]--;
		buc[t/rt]--;
		lr[A[x]][1]--;
	};

	auto addL = [&](int x) {
		auto [l, r] = lr[A[x]];
		int t;
		if (l <= r) {
			t = B[A[x]][r] - B[A[x]][l];
			ans[t]--;
			buc[t/rt]--;
		}
		l--;
		t = B[A[x]][r] - B[A[x]][l];
		ans[t]++;
		buc[t/rt]++;
		lr[A[x]][0]--;
	};

	auto popL = [&](int x) {
		auto [l, r] = lr[A[x]];
		int t;
		if (l+1 <= r) {
			t = B[A[x]][r] - B[A[x]][l+1];
			ans[t]++;
			buc[t/rt]++;
		}
		t = B[A[x]][r] - B[A[x]][l];
		ans[t]--;
		buc[t/rt]--;
		lr[A[x]][0]++;
	};

	auto f = [&]() {
		for (int i = n/rt; i >= 0; i--) {
			if (buc[i]) {
				for (int j = min(n, (i+1)*rt-1); j >= i*rt; j--) {
					if (ans[j]) return j;
				}
			}
		}
		return 0;
	};


	vector<int> qans(q);
	int L = 1, R = 1; addR(1);
	for (auto [l, r, idx]: query) {
		while (l < L) addL(--L);
		while (R < r) addR(++R);
		while (L < l) popL(L++);
		while (r < R) popR(R--);
		qans[idx] = f();
	}

	for (auto i: qans) {
		ct(i);
	}



}


int main() {
	FASTIO
	int T = 1;
	for (int i = 1; i <= T; i++) {
		solve();
	}
}

















