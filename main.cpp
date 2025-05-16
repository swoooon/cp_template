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



}


int main() {
	FASTIO
	int T = 1;
	for (int i = 1; i <= T; i++) {
		solve();
	}
}

















