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

vector<int> zeta(vector<int> f) { //get F(S)=Σ(T⊂S)G(T)
	int n = sz(f);
	for(int i = 0; (1 << i) < n; i++) {
		rep(j, 0, n) if(j & (1 << i)) f[j] += f[j ^ (1 << i)];
	}
	return f;
}
/*
vector<int> zeta(vector<int> f) { //get F(S)=Σ(S⊂T)G(T)
	int n = sz(f);
	for(int i = 0; (1 << i) < n; i++) {
		rep(j, 0, n) if(!(j & (1 << i))) f[j] += f[j | (1 << i)];
	}
	return f;
}
*/
vector<int> moebius(vector<int> f) { //inverse of the first zeta
	int n = sz(f);
	for(int i = 0; (1 << i) < n; i++) {
		rep(j, 0, n) if(j & (1 << i)) f[j] -= f[j ^ (1 << i)];
	}
	return f;
}

int N;
int d[4] = {2, 3, 7, 11};
int cnt[110];

void solve() {
	N = 4;
	int res = 0;
	rep(i, 1, 100 + 1) {
		rep(j, 0, N) {
			if(i % d[j] == 0) {
				res++;
				break;
			}
		}
	}
	debug(res);
	rep(bit, 0, (1 << N)) {
		int a = 1;
		rep(i, 0, N) {
			if(bit & (1 << i)) {
				a *= d[i];
			}
		}
		cnt[bit] = 100 / a;
	}
	cnt[0] = 0;
	debug(vi(cnt, cnt + (1 << N)));
	vi vec = moebius(vi(cnt, cnt + (1 << N)));
	vi vec2 = zeta(vec);
	rep(bit, 0, (1 << N)) {
		debug(bitset<4>(bit), vec[bit], vec2[bit]);
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

