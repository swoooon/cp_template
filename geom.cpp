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


pll operator- (const pll &a, const pll &b){ return {a[0]-b[0], a[1]-b[1]}; }
inline ll outer(const pll& a, const pll& b) { return a[0]*b[1] - a[1]*b[0]; }
inline ll ccw(const pll& a, const pll& b, const pll& c) {
    ll ret = outer(b - a, c - a); return (ret ? (ret > 0 ? 1 : -1) : 0);
}

vector<pll> convex_hull(vector<pll>& dat) {
    if (dat.size() <= 2) return dat;
    vector<pll> upper, lower;
    sort(dat.begin(), dat.end(), [](const pll& a, const pll& b) {
        return (a[0] == b[0]) ? a[1] < b[1] : a[0] < b[0];
    });
    for (const auto& p : dat) {
        while (upper.size() >= 2 && ccw(*++upper.rbegin(), *upper.rbegin(), p)
            >= 0) upper.pop_back();
        while (lower.size() >= 2 && ccw(*++lower.rbegin(), *lower.rbegin(), p)
            <= 0) lower.pop_back();
        upper.emplace_back(p);
        lower.emplace_back(p);
    }
    upper.insert(upper.end(), ++lower.rbegin(), --lower.rend());
    return upper;
}

int chk(pll a, pll b, pll c, pll d) {
    int l = ccw(a, b, c) * ccw(a, b, d);
    int r = ccw(c, d, a) * ccw(c, d, b);
    if (l == 0 && r == 0) {
        if (a > b) swap(a, b);
        if (c > d) swap(c, d);
        return c <= b && a <= d;
    }
    return l <= 0 && r <= 0;
}

int inchk(pll now, vector<pll> &v) {
    int cnt = 0;
    pll t = {now[0]+(ll)1e9, now[1]+1};
    for (int i = 0; i < v.size(); i++) {
        cnt ^= chk(now, t, v[i], v[(i+1)%v.size()]);
    }
    return cnt;
}


void solve() {
    int n, m; cin >> n >> m;
    vector<pll> A(n), B(m);
    for (int i = 0; i < n; i++) cin >> A[i][0] >> A[i][1];
    for (int i = 0; i < m; i++) cin >> B[i][0] >> B[i][1];
    auto x = convex_hull(A), y = convex_hull(B);

    int cnt = 0;
    for (auto i : A) cnt += inchk(i, y);
    for (auto i : B) cnt += inchk(i, x);
    if (cnt) {
        ct("NO");
        return;
    }

    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < y.size(); j++) {
            if (chk(x[i], x[(i+1)%x.size()], y[j], y[(j+1)%y.size()])) {
                ct("NO");
                return;
            }
        }
    }
    ct("YES");


}


int main() {
    FASTIO
    int T = 1; cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
}

















