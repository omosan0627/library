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
	ll v;
	T(ll v = inf) : v(v) {}
	T operator+(const T& t) { return T(min(v, t.v)); } //when getting value
	void operator+=(const T& t) { v = min(v, t.v); } //when updating value
	friend ostream& operator<<(ostream& out, const T& t) {
		out << t.v; return out;
	}
};

struct LCA { //set N for constructer

	const int LOG = 20; //par_next <= 2^(LOG - 1)
	int n, root;
	vector<vi> G, cost;
	vector<vi> par;
	vector<vector<T>> vcost;
	vector<int> depth;
	vector<vector<T>> S;

	LCA(int mx = 0): n(mx), G(mx), cost(mx), par(mx, vi(LOG)), vcost(mx, vector<T>(LOG, T())), depth(mx), S(mx, vector<T>(LOG, T())){}

	void add_edge(int a, int b, int c = 1) {
		G[a].pb(b); cost[a].pb(c);
		G[b].pb(a); cost[b].pb(c);
	}
	void dfs(int v, int p, int d) {
		par[v][0] = p;
		depth[v] = d;
		rep(i, 0, sz(G[v])) {
			int n = G[v][i];
			if(n != p) {
				vcost[n][0] = T(cost[v][i]);
				dfs(n, v, d + 1);
			}
		}
	}

	void init(int root = 0) {
		dfs(root, -1, 0);
		vcost[root][0] = T();
		rep(k, 0, LOG - 1) {
			rep(v, 0, n) {
				if(par[v][k] == -1) {
					par[v][k + 1] = -1;
					vcost[v][k + 1] = T();
				}
				else {
					par[v][k + 1] = par[par[v][k]][k];
					vcost[v][k + 1] = vcost[par[v][k]][k] + vcost[v][k];
				}
			}
		}
	}

	int lca(int u, int v) {
		if(depth[u] > depth[v]) swap(u, v);
		rep(k, 0, LOG) {
			if((depth[v] - depth[u]) >> k & 1) {
				v = par[v][k];
			}
		}
		if(u == v) return u;
		rer(k, LOG, 0)  {
			if(par[u][k] != par[v][k]) {
				u = par[u][k];
				v = par[v][k];
			}
		}
		return par[u][0];
	}

	T ga(int p, int v) {
		int d = depth[v] - depth[p];
		T res = T();
		rep(k, 0, LOG) {
			if(d & (1 << k)) {
				res += vcost[v][k];
				v = par[v][k];
			}
		}
		return res;
	}

	void app(int p, int v, T x) {
		int d = depth[v] - depth[p];
		rep(k, 0, LOG) {
			if(d & (1 << k)) {
				debug(p, v, x);
				S[v][k] += x;
				v = par[v][k];
			}
		}
	}

	ll query(int u, int v) {
		int p = lca(u, v);
		return (ga(p, u) + ga(p, v)).v;
	}
	void update(int u, int v, ll x) {
		int p = lca(u, v);
		debug(u, v, p, x);
		app(p, u, T(x));
		app(p, v, T(x));
	}

	void sweep() {
		rer(k, LOG, 1) {
			rep(v, 0, n) {
				S[v][k - 1] += S[v][k];
				if(par[v][k - 1] != -1) S[par[v][k - 1]][k - 1] += S[v][k];
			}
		}
	}
};

void solve() {
	int N = 9;
	LCA lca(N);
	lca.add_edge(0, 1, 8);
	lca.add_edge(0, 2, 7);
	lca.add_edge(1, 3, 6);
	lca.add_edge(1, 4, 4);
	lca.add_edge(2, 7, 5);
	lca.add_edge(4, 5, 3);
	lca.add_edge(4, 6, 2);
	lca.add_edge(5, 8, 1);
	lca.init(0);
	lca.update(8, 7, 3);
	lca.update(6, 2, 1);
	lca.update(8, 3, -1);
	lca.sweep();
	rep(i, 0, N) {
		rep(j, i + 1, N) {
			debug(i, j, lca.query(i, j));
		}
	}
	rep(i, 0, N) {
		debug(i, lca.S[i][0]);
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
