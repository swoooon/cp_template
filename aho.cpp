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


f(i) = i번째 idx까지 만들수있는가??

f(i) = (j < i && s[j+1:i] 존재) f(i) = max(f(j))

일단 아 이거 아호코라식인데




 */


const int NMAX = 1001010;
const int MOD = 998244353;
const ll LINF = 1e18;

const int MAXN = 100*1000 +1, MAXC = 26; // 트라이 노드 개수, 알파벳 개수

struct Aho {
	int piv, trie[MAXN][MAXC], fail[MAXN]; //트라이 번호 매기기, 트라이, 실패 함수 링크
	bool term[MAXN]; //N번째 트라이가 종말 노드인가?
	void init(vector<string> &v){
		memset(trie, 0, sizeof(trie));
		memset(fail, 0, sizeof(fail));
		memset(term, 0, sizeof(term));
		piv = 0;
		for(string &i : v){
			int p = 0;
			for(char &j : i){
				if(!trie[p][j-'a']) trie[p][j-'a'] = ++piv;
				p = trie[p][j-'a'];
			}
			term[p] = 1;
		}
		queue<int> que;
		for(int i=0; i<MAXC; i++){
			if(trie[0][i]) que.push(trie[0][i]);
		}
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(int i=0; i<MAXC; i++){
				if(trie[x][i]){
					int p = fail[x];
					while(p && !trie[p][i]) p = fail[p];
					p = trie[p][i];
					fail[trie[x][i]] = p;
					if(term[p]) term[trie[x][i]] = 1;
					que.push(trie[x][i]);
				}
			}
		}
	}


	bool query(string &s){
		int p = 0;
		for(char &i : s){
			while(p && !trie[p][i-'a']) p = fail[p];
			p = trie[p][i-'a'];
			if(term[p]) return 1;
		}
		return 0;
	}
} aho;





void solve() {
	int n; cin >> n;
	vector<string> A(n);
	for (int i = 0;i < n; i++) cin >> A[i];
	aho.init(A);
	int q; cin >> q;
	while (q--) {
		string s; cin >> s;
		ct(aho.query(s) ? "YES" : "NO");
	}



}


int main() {
	FASTIO
	int T = 1;
	for (int i = 1; i <= T; i++) {
		solve();
	}
}

















