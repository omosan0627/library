#include <bits/stdc++.h>
#define ADD(a, b) a = (a + ll(b)) % mod
#define MUL(a, b) a = (a * ll(b)) % mod
#define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define rep(i, a, b) for(int i = int(a); i < int(b); i++)
#define rer(i, a, b) for(int i = int(a) - 1; i >= int(b); i--)
#define all(a) (a).begin(), (a).end()
#define sz(v) (int)(v).size()
#define pb push_back
#define sec second
#define fst first
#define debug(fmt, ...) Debug(__LINE__, ":", fmt, ##__VA_ARGS__)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<int, pi> ppi;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vl> mat;
typedef complex<double> comp;
void Debug() {cout << '\n'; }
template<class FIRST, class... REST>void Debug(FIRST arg, REST... rest){
	cout<<arg<<" ";Debug(rest...);}
template<class T>ostream& operator<<(ostream& out,const vector<T>& v) {
	out<<"[";if(!v.empty()){rep(i,0,sz(v)-1)out<<v[i]<<", ";out<<v.back();}out<<"]";return out;}
template<class S, class T>ostream& operator<<(ostream& out,const pair<S, T>& v){
	out<<"("<<v.first<<", "<<v.second<<")";return out;}
const int MAX_N = 200010;
const int MAX_V = 100010;
const double eps = 1e-6;
const ll mod = 1000000007;
const int inf = 1 << 29;
const ll linf = 1LL << 60;
const double PI = 3.14159265358979323846;
///////////////////////////////////////////////////////////////////////////////////////////////////

struct slidemax {
	ll que[MAX_N];
	int s, e;
	void init() {
		s = 0; e = 0;
	}
	void add(ll x) {
		while(s < e && que[e - 1] < x) e--;
		que[e++] = x;
	}
	void remove(ll x) {
		if(s < e && que[s] == x) s++;
	}
	bool empty() {
		return s == e;
	}
	ll get() {
		if(s == e) return -linf;
		else return que[s];
	}
	void show() {
		debug(vi(que + s, que + e));
	}
};

struct slidemin {
	ll que[MAX_N];
	int s, e;
	void init() {
		s = 0; e = 0;
	}
	void add(ll x) {
		while(s < e && que[e - 1] > x) e--;
		que[e++] = x;
	}
	void remove(ll x) {
		if(s < e && que[s] == x) s++;
	}
	bool empty() {
		return s == e;
	}
	ll get() {
		if(s == e) return -linf;
		else return que[s];
	}
	void show() {
		debug(vi(que + s, que + e));
	}
};

int N, X;
int T[5010];
ll dp[2][5010];

void solve() {
	cin >> N >> X;
	rep(i, 0, N) cin >> T[i];
	rep(i, 0, N) dp[0][i] = X;
	cout << X << "\n";
	int now = 0, next = 1;
	rep(k, 2, N + 1) {
		ll ans = 0;
		slidemax que;
		que.init();
		memset(dp[next], 0, sizeof(dp[next]));
		int lv = -1;
		rep(i, 0, N) {
			while(lv + 1 < N && T[i] - T[lv + 1] > X) {
				lv++;
				que.remove(dp[now][lv] - T[lv]);
			}
			MAX(dp[next][i], que.get() + T[i]);
			if(lv >= 0) MAX(dp[next][i], dp[now][lv] + X);
			MAX(ans, dp[next][i]);

			que.add(dp[now][i] - T[i]);
		}
		cout << ans << "\n";
		swap(now, next);
	}
}

int main() {
#ifndef LOCAL
	ios::sync_with_stdio(false);
    cin.tie(0);
#endif
    cout << fixed;
	cout.precision(20);
#ifdef LOCAL
    freopen("in.txt", "rt", stdin);
#endif	
	solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
	return 0;
}


