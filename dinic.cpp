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


const int NMAX = 410;
const int MOD = 998244353;
const ll LINF = 1e18;

struct Dinic {
    struct edg {int pos, cap, rev;};
    vector<edg> adj[NMAX];
    int check[NMAX];
    void clear() { for (int i = 0; i < NMAX; i++) adj[i].clear(); }
    void make_edge(int s, int e, int x) {
        adj[s].push_back({e, x, (int) adj[e].size()});
        adj[e].push_back({s, 0, (int) adj[s].size() - 1});
    }
    int dis[NMAX], pnt[NMAX];
    bool bfs(int src, int sink) {
        memset(dis, 0, sizeof(dis));
        memset(pnt, 0, sizeof(pnt));
        queue<int> que;
        que.push(src);
        dis[src] = 1;
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            for (auto &e : adj[x]) {
                if (e.cap > 0 && !dis[e.pos]) {
                    dis[e.pos] = dis[x] + 1;
                    que.push(e.pos);
                }
            }
        }
        return dis[sink] > 0;
    }
    int dfs(int x, int sink, int f) {
        if (x == sink) return f;
        for (; pnt[x] < adj[x].size(); pnt[x]++) {
            edg e = adj[x][pnt[x]];
            if (e.cap > 0 && dis[e.pos] == dis[x] + 1) {
                int w = dfs(e.pos, sink, min(f, e.cap));
                if (w) {
                    adj[x][pnt[x]].cap -= w;
                    adj[e.pos][e.rev].cap += w;
                    return w;
                }
            }
        }
        return 0;
    }
    void decom(int s) {
        memset(check, 0, sizeof(check));
        queue<int> q; q.push(s);
        check[s] = 1;
        while(!q.empty()) {
            int now = q.front(); q.pop();
            for (auto nxt : adj[now]) {
                if (!check[nxt.pos] && nxt.cap > 0) {
                    check[nxt.pos] = 1;
                    q.push(nxt.pos);
                }
            }
        }
    }
    ll solve(int src, int sink) {
        ll ret = 0;
        while (bfs(src, sink)) {
            int r;
            while ((r = dfs(src, sink, 2e9))) ret += r;
        }
        return ret;
    }
}f;



void solve() {
    int n, m; cin >> n >> m;
    int S, T; cin >> S >> T;
    vector<int> A(n+1);
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i <= n; i++) f.make_edge(i*2, i*2+1, A[i]);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        f.make_edge(a*2+1, b*2, 2e9);
        f.make_edge(b*2+1, a*2, 2e9);
    }

    f.solve(2*S, 2*T+1);
    f.decom(2*S);
    for (int i = 1; i <= n; i++) {
        if (f.check[i*2] && !f.check[i*2+1]) cout << i << " ";
    }


}


int main() {
    FASTIO
    int T = 1;
    for (int i = 1; i <= T; i++) {
        solve();
    }
}

















