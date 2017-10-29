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
typedef pair<ll, ll> pl;
typedef pair<int, pi> ppi;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vl> mat;
typedef complex<double> comp;
void Debug() {cout << '\n'; }
template<class FIRST, class... REST>void Debug(FIRST arg, REST... rest) { 
	cout << arg << " "; Debug(rest...); }
template<class T>ostream& operator<< (ostream& out, const vector<T>& v) {
	out << "[";if(!v.empty()){rep(i,0,sz(v)-1)out<<v[i]<< ", ";out<<v.back();}out << "]";return out;}
template<class S, class T>ostream& operator<< (ostream& out, const pair<S, T>& v) {
	out << "(" << v.first << ", " << v.second << ")";return out;}
const int MAX_N = 200010;
const int MAX_V = 100010;
const double eps = 1e-6;
const ll mod = 1000000007;
const int inf = 1 << 29;
const ll linf = 1LL << 60;
const double PI = 3.14159265358979323846;
///////////////////////////////////////////////////////////////////////////////////////////////////

int N, K;
int ans; 

namespace CD { //centroid decomposition

	struct edge { int to, length; };

	vector<edge> G[MAX_N];
	bool centroid[MAX_N];
	int subtree_size[MAX_N];

	void init(int n) {
		rep(i, 0, n) G[i].clear();
	}
	void add_edge(int a, int b, int c) {
		G[a].push_back((edge){b, c});
		G[b].push_back((edge){a, c});
	}

	int compute_subtree_size(int v, int p) {
		int c = 1;
		rep(i, 0, (int)G[v].size()) {
			int w = G[v][i].to;
			if(w == p || centroid[w]) continue;
			c += compute_subtree_size(G[v][i].to, v);
		}
		subtree_size[v] = c;
		return c;
	}

	pi search_centroid(int v, int p, int t) { 
		pi res = pi(inf, -1);
		int s = 1, m = 0;
		rep(i, 0, (int)G[v].size()) {
			int w = G[v][i].to;
			if(w == p || centroid[w]) continue;

			MIN(res, search_centroid(w, v, t));

			MAX(m, subtree_size[w]);
			s += subtree_size[w];
		}
		MAX(m, t - s);
		MIN(res, pi(m, v));
		return res;
	}

	void update(int s, int n);

	void solve_subproblem(int v) {
		compute_subtree_size(v, -1);
		int s = search_centroid(v, -1, subtree_size[v]).sec;
		centroid[s] = true;

		int cnt = 0;
		rep(i, 0, (int)G[s].size()) {
			if(centroid[G[s][i].to]) continue;
			solve_subproblem(G[s][i].to);
			cnt++;
		}
		update(s, cnt);
		centroid[s] = false;
	}

	////////////////////////////////////////////// edit from here
	
	//distance from centroid
	void enumerate_pathes(int v, int p, int d, vi &ds) {
		ds.push_back(d);
		rep(i, 0, (int)G[v].size()) {
			int w = G[v][i].to;
			if(w == p || centroid[w]) continue;
			enumerate_pathes(w, v, d + G[v][i].length, ds);
		}
	}

	//num of pairs whose lengths is less than k
	int count_pairs(vi &ds) {
		int res = 0;
		sort(ds.begin(), ds.end());
		int j = ds.size();
		rep(i, 0, (int)ds.size()) {
			while(j > 0 && ds[i] + ds[j - 1] > K) j--;
			res += j - (j > i ? 1 : 0);
		}
		return res / 2;
	}

	void update(int s, int n) {
		static vi ds;
		ds.clear();
		ds.push_back(0);
		rep(i, 0, (int)G[s].size()) {
			if(centroid[G[s][i].to]) continue;

			static vi tds;
			tds.clear();
			enumerate_pathes(G[s][i].to, s, G[s][i].length, tds);

			ans -= count_pairs(tds);
			ds.insert(ds.end(), tds.begin(), tds.end());
		}
		ans += count_pairs(ds);
	}
}

void solve() {
	while(true) {
	cin >> N >> K;
	if(N == 0 && K == 0) break;
	CD::init(N);
	rep(i, 0, N - 1) {
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		CD::add_edge(a, b, c);
	}
	ans = 0;
	CD::solve_subproblem(0);
	cout << ans << "\n";
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
