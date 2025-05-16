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

쩌거를 구간쿼리로 변경??



 */


const int NMAX = 1001010;
const int MOD = 998244353;
const ll LINF = 1e18;




void solve() {
    int n; cin >> n;
    vector<int> A(n+1);
    for (int i = 1; i <= n; i++) cin >> A[i];
    vector<vector<int>> adj(n+1);
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> in(n+1),out(n+1), ett(2*n+1), dist(n+1);
    vector<vector<int>> dp(17, vector<int>(n+1));

    int cnt = 0;
    function<void(int, int)> dfs = [&](int cur, int prv) {
        in[cur] = ++cnt;
        ett[cnt] = cur;
        dp[0][cur] = prv;
        for (auto nxt: adj[cur]) {
            if (nxt == prv) continue;
            dist[nxt] = dist[cur]+1;
            dfs(nxt, cur);
        }
        out[cur] = ++cnt;
        ett[cnt] = cur;
    };

    dfs(1, 1);

    for (int i = 1; i < 17; i++) {
        for (int j = 1; j <= n; j++) dp[i][j] = dp[i-1][dp[i-1][j]];
    }

    function<int(int, int)> lca = [&](int u, int v) -> int {
        if (dist[u] > dist[v]) swap(u, v);
        int diff = dist[v]-dist[u];
        for (int i = 0; i < 17; i++) {
            if ((diff>>i)&1) v = dp[i][v];
        }
        if (u == v) return u;
        for (int i = 16; i >= 0; i--) {
            if (dp[i][u] != dp[i][v]) {
                u = dp[i][u];
                v = dp[i][v];
            }
        }
        return dp[0][u];
    };

    int q; cin >> q;
    vector<array<int, 4>> query;
    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        if (dist[a] > dist[b]) swap(a, b);
        int p = lca(a, b);
        if (a == p) {
            query.push_back({in[a], in[b], 0, i});
        } else {
            query.push_back({out[a], in[b], in[p], i});
        }
    }

    int rt = sqrt(2*n);
    sort(all(query), [rt](auto a, auto b) {
        int L = a[0]/rt, R = b[0]/rt;
        if (L ^ R) return L < R;
        if (L&1) return a[1] > b[1];
        return a[1] < b[1];
    });


    ll ans = 0;
    vector<int> vcnt(n+1), ccnt(NMAX);
    auto add = [&](int x) {
        int v = ett[x];
        int c = A[v];
        vcnt[v]++;
        if (vcnt[v]&1) {
            ccnt[c]++;
            if (ccnt[c] == 1) ans++;
        } else {
            ccnt[c]--;
            if (ccnt[c] == 0) ans--;
        }
    };


    auto pop = [&](int x) {
        int v = ett[x];
        int c = A[v];
        vcnt[v]--;
        if (vcnt[v]&1) {
            ccnt[c]++;
            if (ccnt[c] == 1) ans++;
        } else {
            ccnt[c]--;
            if (ccnt[c] == 0) ans--;
        }
    };

    /*
    for (int i = 1; i <= 2*n; i++) {
        cout << ett[i] << " ";
    }
    */

    int L = 1, R = 1; add(1);
    vector<int> ansv(q);
    for (auto [l, r, p, idx]: query) {
        while (l < L) add(--L);
        while (R < r) add(++R);
        while (r < R) pop(R--);
        while (L < l) pop(L++);
        ansv[idx] = ans + (p && ccnt[A[ett[p]]] == 0);
    }
    for (auto i: ansv) {
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

















