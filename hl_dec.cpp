#include <bits/stdc++.h>
#define ADD(a, b) a = (a + (ll)b) % mod
#define MUL(a, b) a = (a * (ll)b) % mod
#define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define rer(i, a, b) for(int i = (a) - 1; i >= (b); i--)
#define all(a) (a).begin(), (a).end()
#define sz(v) (int)(v).size()
#define pb push_back
#define sec second
#define fst first
#define debug(fmt, ...) Debug(__LINE__, ":", fmt, ##__VA_ARGS__)
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> ppi;
typedef vector<ll> vi;
void Debug() {cout << '\n'; }
template<class FIRST, class... REST>void Debug(FIRST arg, REST... rest) { 
	cout << arg << " "; Debug(rest...); }
template<class T>ostream& operator<< (ostream& out, const vector<T>& v) {
	out << "[";if(!v.empty()){rep(i,0,sz(v)-1)out<<v[i]<< ", ";out<<v.back();}out << "]";return out;}
template<class S, class T>ostream& operator<< (ostream& out, const pair<S, T>& v) {
	out << "(" << v.first << ", " << v.second << ")";return out;}
const int MAX_N = 200010;
const double eps = 1e-6;
const ll mod = 1000000007;
const int inf = 1 << 30;
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

struct T {
	ll v;
	T(ll v = -inf) : v(v) {}
	T operator+(const T& t) { return T(max(v, t.v)); } //when getting value
	void operator+=(const T& t) { v = max(v, t.v); } //when updating value
	friend ostream& operator<<(ostream& out, const T& t) {
		out << t.v; return out;
	}
};

struct segtree {
	int n; vector<T> sum, lazy;
	void init(int mx) {
		n = 1;
		while(n < mx) n *= 2;
		sum = vector<T>(n * 2);
		lazy = vector<T>(n * 2);
	}
	segtree(int mx = 0) { init(mx); }
	inline void lazy_eval(int k, int l, int r) {
		if(lazy[k].v != T().v) {
			sum[k * 2 + 1] += lazy[k];
			lazy[k * 2 + 1] += lazy[k];
			sum[k * 2 + 2] += lazy[k];
			lazy[k * 2 + 2] += lazy[k];
			lazy[k] = T();
		}
	}
	void app(int a, int b, T s, int k, int l, int r) {
		if(b <= l || r <= a) return;
		if(a <= l && r <= b) {
			sum[k] += s; //here too
			lazy[k] += s;
		}
		else {
			lazy_eval(k, l, r);
			app(a, b, s, k * 2 + 1, l, (l + r) / 2);
			app(a, b, s, k * 2 + 2, (l + r) / 2, r);
			sum[k] = sum[k * 2 + 1] + sum[k * 2 + 2];
		}
	}
	T ga(int a, int b, int k, int l, int r) {
		if(b <= l || r <= a) return T();
		if(a <= l && r <= b) return sum[k];
		else {
			lazy_eval(k, l, r);
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
	T get(int a, int b) { return ga(a, b, 0, 0, n); } //[a, b)
	void update(int a, int b, T s) { app(a, b, s, 0, 0, n); } //[a, b)
};

//////////////////////////////////////////////////////////////////////////HL BEGIN

struct HL {
	int n;
	vector<vi> to, cost, D;//D:group
	vi vcost, vd, vk, pv, dep;//vcost:edge cost,vd:D at,vk:num from parent,pv:group par,dep:depth
	//edge starts from (e:v->p) where v is top of D
	vector<segtree> S; //change 
	vector<segtree> S2; //change
	int root;

	HL(int mx = 0): n(mx), to(mx), cost(mx), vcost(mx), vd(mx), vk(mx), dep(mx) {}
	void add_edge(int a, int b, int c = 1) {
		to[a].pb(b); cost[a].pb(c);
		to[b].pb(a); cost[b].pb(c);
	}

	int dfs(int v, int depth = 0, int p = -1) {
		dep[v] = depth;
		vector<pi> rs;
		rep(i, 0, sz(to[v])) {
			int u = to[v][i];
			if(u == p) continue;
			vcost[u] = cost[v][i];
			rs.pb(pi(dfs(u, depth + 1, v), u));
		}
		if(sz(rs)) {
			sort(all(rs));
			vd[v] = vd[rs[0].sec]; pv[vd[v]] = p;
			D[vd[v]].pb(v); vk[v] = -sz(D[vd[v]]);
			return rs[0].fst - (sz(rs) != 1 && rs[0].fst == rs[1].fst);
		}
		else {
			vd[v] = sz(D); vk[v] = -1; D.pb(vi(1, v)); pv.pb(p);
			return 1;
		}
	}
	void init(int v = 0) {
		root = v;
		dfs(root);
		rep(i, 0, sz(D)) reverse(all(D[i]));
		rep(i, 0, sz(vk)) vk[i] += sz(D[vd[i]]);
		rep(i, 0, sz(D)) {
			S.pb(segtree(sz(D[i])));      
			S2.pb(segtree(sz(D[i])));//change
			rep(j, 0, sz(D[i])) S[i].update(j, j + 1, vcost[D[i][j]]); //change
		}
	}
	int lca(int a, int b) {
		int p = vd[a]; vi ap(1, p);
		while(pv[p] != -1) ap.pb(p = vd[pv[p]]);
		reverse(all(ap)); ap.pb(-1);
		p = vd[b]; vi bp(1, p);
		while(pv[p] != -1) bp.pb(p = vd[pv[p]]);
		reverse(all(bp)); bp.pb(-2);
		int pi = 1; while(ap[pi] == bp[pi]) pi++;
		p = ap[pi - 1];
		int ai = vd[a] == p ? vk[a] : vk[pv[ap[pi]]];
		int bi = vd[b] == p ? vk[b] : vk[pv[bp[pi]]];
		return D[p][min(ai, bi)];
	}

	//////////////////////////////////////////////////////////////////////////////from here, change
	T ga(int par, int v) {
		T res;
		while(true) {
			int nd = vd[v], nk = vk[v];
			if(nd == vd[par]) {
				return res + S[nd].get(vk[par] + 1, nk + 1);
			}
			else {
				res = res + S[nd].get(0, nk + 1);
			}
			v = pv[nd];
		}
	}
	void app(int par, int v, ll x) {
		while(true) {
			int nd = vd[v], nk = vk[v];
			if(nd == vd[par]) {
				S2[nd].update(vk[par] + 1, nk + 1, T(-x));
				return;
			}
			else {
				S2[nd].update(0, nk + 1, T(-x));
			}
			v = pv[nd];
		}
	}
	int query(int a, int b, ll x) {
		int par = lca(a, b);
		T res = ga(par, a);
		res = res + ga(par, b);
		app(par, a, max(res.v, x));
		app(par, b, max(res.v, x));
		return res.v;
	}
	ll get(int a, int b) {
		if(dep[a] < dep[b]) a = b;
		return -S2[vd[a]].get(vk[a], vk[a] + 1).v;
	}
};


///////////////////////////////////////////////////////////////////////////HL END

struct edge {
	int a, b, c, i;
	bool operator<(const edge& e) {
		return c < e.c;
	}
};

int N, M;
edge es[MAX_N];
int ans[MAX_N];

void solve() {
	cin >> N >> M;
	rep(i, 0, M) {
		int a, b, c;
		cin >> a >> b >> c; a--; b--;
		es[i] = (edge){a, b, c, i};
	}
	UF uf(N);
	sort(es, es + M);
	HL g(N);
	rep(i, 0, M) {
		int a = es[i].a, b = es[i].b, c = es[i].c, at = es[i].i;
		if(!uf.same(a, b)) {
			uf.unite(a, b);
			ans[at] = -1;
			g.add_edge(a, b, c);
		}
	}
	g.init();
	rep(i, 0, M) {
		int a = es[i].a, b = es[i].b, c = es[i].c, at = es[i].i;
		if(ans[at] == -1) continue;
		ans[at] = g.query(a, b, c);
	}
	rep(i, 0, M) {
		int a = es[i].a, b = es[i].b, at = es[i].i;
		if(ans[at] != -1) continue;
		ans[at] = g.get(a, b);
	}
	rep(i, 0, M) {
		if(ans[i] == inf) {
			cout << -1 << "\n";
		}
		else {
			cout << ans[i] - 1 << "\n";
		}
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


