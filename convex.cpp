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
typedef pair<double, double> pd;
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
const double eps = 1e-10;
const ll mod = 1000000007;
const int inf = 1 << 29;
const ll linf = 1LL << 60;
const double PI = 3.14159265358979323846;
///////////////////////////////////////////////////////////////////////////////////////////////////

struct P {
	double x, y;
	P() {}
	P(double x, double y) : x(x), y(y) {
	}
	P operator+(P p) { return P(x + p.x, y + p.y); }
	P operator-(P p) { return P(x - p.x, y - p.y); }
	double det(const P& p) { return x * p.y - y * p.x; }
	bool operator<(const P& p) { return y != p.y ? y < p.y : x < p.x; }
	friend ostream& operator<<(ostream& out, const P& p) {
		out << "(" << p.x << ", " << p.y << ")"; return out;
	}
};


vector<P> convex_hull(vector<P>& ps) {
	int n = sz(ps);
	sort(all(ps));
	int k = 0;
	vector<P> qs(n * 2);
	rep(i, 0, n) {
		while(k > 1 && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= -eps) k--;
		qs[k++] = ps[i];
	}

	for(int i = n - 2, t = k; i >= 0; i--) {
		while(k > t && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= -eps) k--;
		qs[k++] = ps[i];
	}
	qs.resize(k - 1);
	return qs;
}

int N;

void solve() {
	cin >> N;
	vector<P> vec;
	rep(i, 0, N) {
		int a, b;
		cin >> a >> b;
		vec.pb(P(a, b));
	}
	auto ans = convex_hull(vec);
	cout << sz(ans) << "\n";
	rep(i, 0, sz(ans)) {
		cout << (int)ans[i].x << " " << (int)ans[i].y << "\n";
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

