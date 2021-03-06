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


struct UF {
	vector<int> par, ran;
	void init(int n) {
		par.resize(n); ran.resize(n);
		for(int i = 0; i < n; i++) {
			par[i] = i;
			ran[i] = 0;
		}
	}
	UF(int mx = 0) { init(mx); }

	int find(int x) {
		if(par[x] == x) return x;
		else return par[x] = find(par[x]);
	}
	void unite(int x, int y) {
		x = find(x);
		y = find(y);
		if(x == y) return;
		if(ran[x] < ran[y]) {
			par[x] = y;
		}
		else {
			par[y] = x;
			if(ran[x] == ran[y]) ran[x]++;
		}
	}
	bool same(int x, int y) { return find(x) == find(y); }
};


struct mergeUF { //O((logn)^2)
	int n;
	vector<set<int>> g;
	vector<int> gat;
	void init(int mx) {
		n = mx;
		g.resize(n); gat.resize(n);
		rep(i, 0, n) {
			g[i].insert(i);
			gat[i] = i;
		}
	}

	mergeUF(int mx = 0) { init(mx); }

	void unite(int x, int y) {
		int a = gat[x], b = gat[y];
		if(a == b) return;
		if(sz(g[a]) > sz(g[b])) swap(a, b);

		for(int s : g[a]) {
			gat[s] = b;
			g[b].insert(s);
		}
		g[a].clear();
	}

	bool same(int x, int y) { return gat[x] == gat[y]; }
	void show() {
		rep(i, 0, n) debug(i, vi(all(g[i])));
		debug(gat);
	}
};

//unite, same, find, init
//don't forget to initialize it
//////////////////////////////////////////////////////////////


void solve() {
	int N = 5;
	mergeUF u(N);
	u.unite(0, 1); //unite node 0 and 1
	u.show();
	u.unite(2, 3);
	u.show();
	u.unite(2, 4); //unite node 2, 3, and 4
	u.show();
	cout << u.same(0, 1) << endl; //true
	cout << u.same(2, 4) << endl; //true
	cout << u.same(0, 2) << endl; //false
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
