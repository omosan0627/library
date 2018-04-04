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
const ll mod = 998244353;
const int inf = 1 << 30;
const double PI = 3.14159265358979323846;
///////////////////////////////////////////////////////////////////////////////////////////////////

struct FFT {
	void fft(vector<comp>& v, bool rev = false) { //v.size() == (1 << x)
		int n = sz(v), i, j;
		for(i = 0, j = 1; j < n - 1; j++) {
			for(int k = n >> 1; k > (i ^= k); k /= 2);
			if(i > j) swap(v[i], v[j]);
		}
		for(int m = 2; m <= n; m *= 2) {
			comp wr = polar(1.0, (rev? -1 : 1) * 2.0 * PI / m);
			for(int i = 0; i < n; i += m) {
				comp w(1, 0);
				rep(j, 0, m / 2) {
					comp f0 = v[i + j], f1 = w * v[i + j + m / 2];
					v[i + j] = f0 + f1;
					v[i + j + m / 2] = f0 - f1;
					w *= wr;
				}
			}
		}
		if(rev) rep(i, 0, n) v[i] *= 1.0 / n;
	}
	vector<int> get(const vector<int>& A, const vector<int>& B) {
		int n = 1;
		int len = sz(A) + sz(B) - 1;
		while(n < sz(A) + sz(B)) n *= 2;
		vector<comp> a(n), b(n);
		rep(i, 0, sz(A)) a[i] = comp(A[i], 0);
		rep(i, 0, sz(B)) b[i] = comp(B[i], 0);
		fft(a); fft(b);
		rep(i, 0, n) a[i] *= b[i];
		fft(a, true);
		vector<int> res(len);
		rep(i, 0, len) res[i] = (int)(a[i].real() + 0.5);
		return res;
	}
};

struct FMT {
	const int num_factor = 3;
	ll factor[3] = {2, 3, 7};
	ll gen = 3;

	ll mod_pow(ll a, ll n) {
		if(n == 0) return 1;
		ll res = mod_pow(a, n / 2);
		if(n % 2 == 0) return res * res % mod;
		else return a * res % mod * res % mod;
	}

	bool check() {
		rep(i, 0, num_factor) {
			if(mod_pow(gen, (mod - 1) / factor[i]) == 1) {
				return false;
			}
		}
		return true;
	}
	void fmt(vector<ll>& v, bool rev = false) { //v.size() == (1 << x)
		int n = sz(v), i, j;
		for(i = 0, j = 1; j < n - 1; j++) {
			for(int k = n >> 1; k > (i ^= k); k /= 2);
			if(i > j) swap(v[i], v[j]);
		}
		for(int m = 2; m <= n; m *= 2) {
			ll root = mod_pow(gen, (mod - 1) / m);
			for(int i = 0; i < n; i += m) {
				ll w = 1;
				rep(j, 0, m / 2) {
					ll f0 = v[i + j], f1 = w * v[i + j + m / 2] % mod;
					v[i + j] = (f0 + f1) % mod;
					v[i + j + m / 2] = (mod + f0 - f1) % mod;
					MUL(w, root);
				}
			}
		}
		if(rev) rep(i, 0, n) MUL(v[i], mod_pow(n, mod - 2));
	}
	vector<ll> get(const vector<ll>& A, const vector<ll>& B) {
		int n = 1;
		int len = sz(A) + sz(B) - 1;
		while(n < len) n *= 2;
		vector<ll> a(n, 0), b(n, 0);
		rep(i, 0, sz(A)) a[i] = A[i];
		rep(i, 0, sz(B)) b[i] = B[i];
		fmt(a); fmt(b);
		rep(i, 0, n) MUL(a[i], b[i]);
		reverse(++a.begin(), a.end());
		fmt(a, true);
		vector<ll> res(len);
		rep(i, 0, len) res[i] = a[i];
		return res;
	}
};

void solve() {
	int N;
	cin >> N;
	vector<int> A(N), B(N);
	rep(i, 0, N) cin >> A[i] >> B[i];
	FFT f;
	vector<int> v = f.get(A, B);
	FMT fmt;
	vector<ll> vec = fmt.get(vector<ll>(all(A)), vector<ll>(all(B)));
	debug(v);
	debug(fmt.check());
	debug(vec);
}

int main() {
#ifndef LOCAL
	ios::sync_with_stdio(false);
    cin.tie(0);
#endif
    cout << fixed;
	cout.precision(5);
#ifdef LOCAL
    freopen("in.txt", "rt", stdin);
#endif	
	solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
	return 0;
}

