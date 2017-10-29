#include <bits/stdc++.h>
#define ADD(a, b) a = (a + ll(b)) % mod
#define MUL(a, b) a = (a * ll(b)) % mod
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

namespace SCC {
	int n;
	vi G[MAX_N], rG[MAX_N];
	vi nG[MAX_N];//if you don't want to create a new graph, comment out
	vi vs;
	bool used[MAX_N];
	int cmp[MAX_N]; // cycle number that nodes are in, topological order
	//for scc:
	//cmp[i] == cmp[i + N] impossible
	//cmp[i] > cmp[i + N] vi is true
	//cmp[i] < cmp[i + N] vi is false
	vi C[MAX_N];//this too. all nodes in cycle

	void init(int N) {
		n = N;
		rep(i, 0, n) {
			G[i].clear();
			rG[i].clear();
			nG[i].clear();
			C[i].clear();
		}
	}

	void add_edge(int from, int to) {
		G[from].push_back(to);
		rG[to].push_back(from);
	}

	void dfs(int v) {
		used[v] = true;
		rep(i, 0, (int)G[v].size()) {
			int n = G[v][i];
			if(!used[n]) dfs(n);
		}
		vs.push_back(v);
	}

	void rdfs(int v, int k) {
		used[v] = true;
		cmp[v] = k;
		//* //C
		C[k].push_back(v);
		//*/
		rep(i, 0, (int)rG[v].size()) {
			int n = rG[v][i];
			if(!used[n]) rdfs(n, k);
			//* //nG
			if(used[n] && cmp[n] < k) nG[cmp[n]].push_back(k);
			//*/
		}
	}

	int get() {
		memset(used, 0, sizeof(used));
		vs.clear();
		rep(v, 0, n) {
			if(!used[v]) dfs(v);
		}
		memset(used, 0, sizeof(used));
		fill(cmp, cmp + n, n);
		int k = 0;
		rer(i, (int)vs.size(), 0) {
			if(!used[vs[i]]) rdfs(vs[i], k++);
		}
		//* //C
		rep(i, 0, k) reverse(all(C[i]));
		//*/
	
		//* //nG
		rep(i, 0, k) {
			sort(all(nG[i]));
			nG[i].erase(unique(all(nG[i])), nG[i].end());
		}
		//*/
		return k;
	}
}

void solve() {
	int N = 12;
	SCC::init(N);
	SCC::add_edge(0, 1);
	SCC::add_edge(1, 2);
	SCC::add_edge(1, 3);
	SCC::add_edge(3, 2);
	SCC::add_edge(4, 3);
	SCC::add_edge(2, 4);
	SCC::add_edge(4, 5);
	SCC::add_edge(5, 6);
	SCC::add_edge(6, 7);
	SCC::add_edge(7, 5);
	SCC::add_edge(6, 9);
	SCC::add_edge(6, 8);
	SCC::add_edge(8, 9);
	SCC::add_edge(9, 10);
	SCC::add_edge(10, 9);
	SCC::add_edge(8, 11);
	int k = SCC::get();
	debug(SCC::vs);
	rep(i, 0, k) debug(i, SCC::nG[i]);
	rep(i, 0, k) debug(i, SCC::C[i]);
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

