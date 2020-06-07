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
void Debug() {cerr << '\n'; }
template<class FIRST, class... REST>void Debug(FIRST arg, REST... rest){
	cerr<<arg<<" ";Debug(rest...);}
template<class T>ostream& operator<<(ostream& out,const vector<T>& v) {
	out<<"[";if(!v.empty()){rep(i,0,sz(v)-1)out<<v[i]<<", ";out<<v.back();}out<<"]";return out;}
template<class S, class T>ostream& operator<<(ostream& out,const pair<S, T>& v){
	out<<"("<<v.first<<", "<<v.second<<")";return out;}
const int MAX_N = (1 << 21);
const int MAX_V = 100010;
const double eps = 1e-6;
const ll mod = 1000000007;
const int inf = (1 << 30) - 1;
const ll linf = 1LL << 60;
const double PI = 3.14159265358979323846;
mt19937 rng; //use it by rng() % mod, shuffle(all(vec), rng)
///////////////////////////////////////////////////////////////////////////////////////////////////

int N, M;
int A[MAX_N], B[MAX_N];
int deg[MAX_N];


struct edge {
	int idxa, b, idxb, pbto, used;
};

vector<edge> g[MAX_N];


int dfs(int v, vector<int> &trail, bool add_trail) {
	int res = 0;
	while(!g[v].empty()) {
		auto pp = g[v].back();
		if(pp.used) {
			g[v].pop_back();
			continue;
		}
		int n = pp.b, idx = pp.pbto;
		g[v].pop_back();
		g[n][idx].used = 1;
		res += dfs(n, trail, add_trail);
		if(add_trail) {
			trail.pb(pp.idxb);
			trail.pb(pp.idxa);
		}
		res++;
	}
	//if you want vertices, not edges, then
	// trail.pb(v);
	return res;
}

void solve() {
	cin >> N;
	rep(i, 0, N) cin >> A[i] >> B[i];
	int pow2 = 2;
	int la = -1;
	int ok = 0, ng = 21;

	while(abs(ng - ok) > 1) {
		memset(deg, 0, sizeof(deg));
		
		int m = (ng + ok) / 2;
		pow2 = 1; rep(i, 0, m) pow2 *= 2;

		rep(i, 0, pow2) g[i].clear();

		rep(i, 0, N) {
			int a = A[i] & (pow2 - 1);
			int b = B[i] & (pow2 - 1);
			deg[a]++;
			deg[b]++;
			g[a].pb(edge{i * 2, b, i * 2 + 1, sz(g[b]) + (a == b), 0}); //(a,a)なら+1しないと。
			g[b].pb(edge{i * 2 + 1, a, i * 2, sz(g[a]) - 1, 0}); 
			la = a;
		}
		bool found = false;
		rep(i, 0, pow2) {
			if(deg[i] % 2) found = true;
		}
		vi emp;
		if(!found && dfs(la, emp, false) == N) ok = m;
		else ng = m;
	}

	pow2 = 1; rep(i, 0, ok) pow2 *= 2;

	rep(i, 0, pow2) g[i].clear();

	//from library
	rep(i, 0, N) {
		int a = A[i] & (pow2 - 1);
		int b = B[i] & (pow2 - 1);
		g[a].pb(edge{i * 2, b, i * 2 + 1, sz(g[b]) + (a == b), 0}); //(a,a)なら+1しないと。
		g[b].pb(edge{i * 2 + 1, a, i * 2, sz(g[a]) - 1, 0}); 
		la = a;
	}
	vi trail;
	dfs(la, trail, true);
	cout << ok << "\n";
	rep(i, 0, sz(trail)) {
		cout << trail[i] + 1 << " ";
	}
	cout << "\n";
}

uint32_t rd() {
	uint32_t res;
#ifdef __MINGW32__
	asm volatile("rdrand %0" :"=a"(res) ::"cc");
#else
	res = std::random_device()();
#endif
	return res;
}

int main() {
#ifndef LOCAL
	ios::sync_with_stdio(false);
    cin.tie(0);
#endif
    cout << fixed;
	cout.precision(20);
    cerr << fixed;
	cerr.precision(6);
	rng.seed(rd());
#ifdef LOCAL
	//freopen("in.txt", "wt", stdout); //for tester
	if(!freopen("in.txt", "rt", stdin)) return 1;
#endif	
	solve();
    cerr << "Time: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
	return 0;
}


