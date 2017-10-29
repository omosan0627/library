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

struct T {
	pi v;
	T(pi v = pi(inf, -1)) : v(v) {}
	T operator+(const T& t) { return T(min(v, t.v)); }
	friend ostream& operator<<(ostream& out, const T& t) {
		out << t.v; return out;
	}
};

struct segtree{
	int n; vector<T> seg;
	void init(int mx) {
		n = 1;
		while(n < mx) n *= 2;
		seg = vector<T>(n * 2);
	}
	segtree(int mx = 0) {
		init(mx);
	}
	void update(int i, T x) {
		i += n - 1;
		seg[i] = x;
		while(i > 0) {
			i = (i - 1) / 2;
			seg[i] = seg[i * 2 + 1] + seg[i * 2 + 2];
		}
	}
	T ga(int a, int b, int k, int l, int r) {
		if(b <= l || r <= a) return T();
		if(a <= l && r <= b) return seg[k];
		else {
			T lv = ga(a, b, k * 2 + 1, l, (l + r) / 2);
			T rv = ga(a, b, k * 2 + 2, (l + r) / 2, r);
			return lv + rv;
		}
	}
	void show() {
		vector<T> tmp;
		rep(i, 0, n) tmp.push_back(get(i, i + 1));
		debug(tmp);
	}
	//edit from here
	T get(int a, int b) { return ga(a, b, 0, 0, n); } //[a, b)
};

struct BIT { //0-origin!!!
	int n; vl bit0, bit1;
	void init(int mx) {
		n = mx;
		bit0 = vl(n + 1, 0); bit1 = vl(n + 1, 0);
	}
	BIT(int mx = 0) { init(mx); } 

	ll ga(vl& bit, int i) {
		ll s = 0;
		while(i > 0) { s += bit[i]; i -= i & -i; }
		return s;
	}
	void app(vl& bit, int i, ll x) {
		while(i <= n) { bit[i] += x; i += i & -i; }
	}
	void update(int a, int b, ll x) { //[a, b)
		a++;
		app(bit0, a, -x * (a - 1));
		app(bit1, a, x);
		app(bit0, b + 1, x * b);
		app(bit1, b + 1, -x);
	}
	ll get(int a, int b) { //[a, b)
		a++;
		return (ga(bit1, b) * b + ga(bit0, b)) 
			- (ga(bit1, a - 1) * (a - 1) + ga(bit0, a - 1));
	}
};

namespace ET {
	struct edge { int to, cost; };
	int n;
	vector<edge> G[MAX_N];
	int root;
	int cost[MAX_N * 2]; //2 * n - 2
	int vs[MAX_N * 2]; //2 * n - 1
	int depth[MAX_N * 2]; //2 * n - 1
	int idb[MAX_N], ide[MAX_N]; //(e:v->p)'s cost: cost[idb[v] - 1](>0) or cost[ide[v]](<0)
	segtree seg;
	BIT bit;

	void add_edge(int a, int b, int cost) {
		G[a].pb(edge{b, cost});
		G[b].pb(edge{a, cost});
	}
	void dfs(int v, int p, int d, int pc, int &k) {
		idb[v] = k;
		vs[k] = v;
		depth[k++] = d;
		rep(i, 0, G[v].size()) {
			edge& e = G[v][i];
			if(e.to == p) continue;
			cost[k - 1] = e.cost;
			dfs(e.to, v, d + 1, e.cost, k);
			vs[k] = v;
			depth[k++] = d;
		}
		if(pc != -1) cost[k - 1] = -pc;
		ide[v] = k - 1;
	}
	void init(int nn, int nroot = 0) {
		n = nn; root = nroot;
		int k = 0; dfs(root, -1, 0, -1, k);
		seg.init(2 * n - 1); rep(i, 0, 2 * n - 1) seg.update(i, T(pi(depth[i], i)));
		bit.init(2 * n - 2); rep(i, 0, 2 * n - 2) bit.update(i, i + 1, cost[i]);
	}

	int lca(int u, int v) {
		int a = idb[u], b = idb[v];
		if(a > b) swap(a, b);
		return vs[seg.get(a, b + 1).v.sec];
	}
	ll path_cost(int u, int v) {
		int p = lca(u, v);
		int a = idb[u], b = idb[p], c = idb[v];
		return bit.get(min(a, b), max(a, b)) + bit.get(min(b, c), max(b, c));
	}
	void change_cost(int v, int c) {
		int a = cost[idb[v] - 1];
		cost[idb[v] - 1] = c; cost[ide[v]] = -c;
		bit.update(idb[v] - 1, idb[v], c - a);
		bit.update(ide[v], ide[v] + 1, a - c);
	}
	void show() {
		debug("cost", vi(cost, cost + n * 2 - 2));
		debug("vs", vi(vs, vs + n * 2 - 1));
		debug("depth", vi(depth, depth + n * 2 - 1));
		debug("idb", vi(idb, idb + n));
		debug("ide", vi(ide, ide + n));
	}
};

void solve() {
	int N = 8;
	ET::add_edge(0, 1, 1);
	ET::add_edge(1, 3, 2);
	ET::add_edge(1, 4, 3);
	ET::add_edge(4, 6, 4);
	ET::add_edge(4, 7, 5);
	ET::add_edge(0, 2, 6);
	ET::add_edge(2, 5, 7);
	ET::init(N);
	ET::show();
	rep(i, 1, N) debug(i, ET::cost[ET::idb[i] - 1], ET::cost[ET::ide[i]]);
	rep(i, 0, N) 
		rep(j, 0, N) debug(i, j, ET::lca(i, j), ET::path_cost(i, j));
	ET::change_cost(1, 8);
	rep(i, 0, N) 
		rep(j, 0, N) debug(i, j, ET::lca(i, j), ET::path_cost(i, j));
	ET::show();
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

