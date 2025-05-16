mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
ll generaterandomprime(){
    uniform_int_distribution<ll> dist((ll)1e9, 2e9);
    ll randnum=dist(mt);
    while(1){
        int flag=0;
        for(ll i=2; i*i<randnum; i++){
            if(randnum%i==0){
                flag=1;
                break;
            }
        }
        if(flag==0) return randnum;
        randnum++;
    }
}//랜덤한 소수 생성
struct Hashing {
    ll P, M;
    vector<ll> h, p;
    Hashing(ll P, ll M) : P(P), M(M){}
    void build(const string &s){
        int n = s.size();
        h = p = vector<long long>(n+1); p[0] = 1;
        for(int i=1; i<=n; i++) h[i] = (h[i-1] * P + s[i-1]) % M;
        for(int i=1; i<=n; i++) p[i] = p[i-1] * P % M;
    }
    ll get_hash(int s, int e) const {
        ll res = (h[e] - h[s-1] * p[e-s+1]) % M;
        return (res + M) % M;
    }
};//build(문자열)로 빌드, get_hash(시작 위치, 끝 위치)로 해당 부분 문자열의 해시값을 계산
ll mod1=generaterandomprime();
ll mod2=generaterandomprime();
uniform_int_distribution<ll> small(1000, 10000);
ll key=small(mt);


struct hash_string{
    vector<ll> v;
    vector<ll> pw;
    int sz;
    void init(string s){
        sz=s.length();
        v.resize(s.length()+1);
        pw.resize(s.length()+1);
        pw[0]=1;
        for(int i=1;i<=s.length();i++){
            pw[i]=pw[i-1]*p1;
            v[i]=v[i-1]*p1+s[i-1];
        }
    }ll get(int l,int r){///////1-base
        return v[r]-v[l-1]*pw[r-l+1];
    }
}tree;
