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
typedef vector<ll> vi;
typedef vector<vi> mat;
typedef complex<double> comp;
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
const ll linf = 1LL << 60;
const double PI = 3.14159265358979323846;
///////////////////////////////////////////////////////////////////////////////////////////////////


int global_min_cut(vector<vector<int> > g) { //g: n*n matrix of graph. if no edge, the cost is zero
	int n = (int)g.size(), res = inf; 
	vector<int> redV(n); 
	rep(i, 0, n) redV[i] = i; 
	rer(rem, n + 1, 2) { //calc MA order 
		int u = 0, v = 0, cut = 0; 
		vector<int> w(rem,0); 
		rep(i, 0, rem){ 
			u = v; v = max_element(all(w)) - w.begin(); 
			cut = w[v]; w[v] = -1; 
			rep(p, 0, rem) {
				if(w[p] >= 0) w[p] += g[redV[v]][redV[p]]; 
			}
		}
		//merge graph 
		rep(i,0, rem) { 
			g[redV[u]][redV[i]] += g[redV[v]][redV[i]]; 
			g[redV[i]][redV[u]] += g[redV[i]][redV[v]]; 
		} 
		redV.erase(redV.begin() + v); 
		//update min_cut 
		res = min(res, cut); 
	} 
	return res; 
}

void solve() {
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



