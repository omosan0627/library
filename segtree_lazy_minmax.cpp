#include <bits/stdc++.h>
#define ADD(a, b) a = (a + (ll)b) % mod
#define MUL(a, b) a = (a * (ll)b) % mod
#define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define rer(i, a, b) for(int i = (a) - 1; i >= (b); i--)
#define all(a) (a).begin(), (a).end()
#define sz(v) (int)(v).size()
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
	out << "[";if(!v.empty()){rep(i,0,sz(v))out<<v[i]<< ", ";out<<v.back();}out << "]";return out;}
template<class S, class T>ostream& operator<< (ostream& out, const pair<S, T>& v) {
	out << "(" << v.first << ", " << v.second << ")";return out;}
const int MAX_N = 200010;
const double eps = 1e-6;
const ll mod = 1000000007;
const int inf = 1 << 30;
///g++ -g3 -std=c++0x -DLOCAL -Wall -ftrapv -D_GLIBCXX_DEBUG -Wl,-stack,268435456 -o
///g++ -O2 -std=c++0x -DLOCAL -Wall -Wl,-stack,268435456 -o
////////////////////////////////////////////////////////////////////////


struct T {
	ll v;
	T(ll v = 0) : v(v) {}
	T operator+(const T& t) { return T(max(v, t.v)); } //when getting value
	void operator+=(const T& t) { v = max(v, t.v); } //when updating value
	friend ostream& operator<<(ostream& out, const T& t) {
		out << t.v; return out;
	}
};

struct segtree { //use BIT if you can
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

segtree seg;
int A[MAX_N] = {5, 3, 7, 9, 6, 4, 1, 2, 10};

void solve() {
	int N = 9;
	seg.init(N);
	rep(i, 0, N) seg.update(i, i + 1, T(A[i]));
	rep(i, 0, N + 1) {
		rep(j, i + 1, N + 1) {
			debug(i, j, seg.get(i, j));
		}
	}
	seg.update(0, 5, -1);
	rep(i, 0, N + 1) {
		rep(j, i + 1, N + 1) {
			debug(i, j, seg.get(i, j));
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

