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
const ll mod = 998244353;
const ll md = mod;
const ll gen = 3;
const int inf = 1 << 29;
const ll linf = 1LL << 60;
const double PI = 3.14159265358979323846;
///////////////////////////////////////////////////////////////////////////////////////////////////

int factor[3] = {2, 3, 7}; //mod_pow(gen, (mod - 1) / factor[i]) != 1 | i=0,1,2を満たすなら元になる

ll mod_pow(ll a, ll n) {
	if(n == 0) return 1;
	ll res = mod_pow(a, n / 2);
	if(n % 2 == 0) return res * res % mod;
	else return a * res % mod * res % mod;
}

ll pw(ll a, ll n) {
	if(n == 0) return 1;
	ll res = mod_pow(a, n / 2);
	if(n % 2 == 0) return res * res % mod;
	else return a * res % mod * res % mod;
}


struct FMT {
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

void fft(vector <int> &a) {
  int n = a.size();
  for (int i = 0; i < n; i++) {
    int j = 0;
    int x = i, y = n - 1;
    while (y > 0) {
      j = (j << 1) + (x & 1);
      x >>= 1;
      y >>= 1;
    }
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 1; len < n; len *= 2) {
    int root = pw(gen, (md - 1) / (2 * len));
    for (int i = 0; i < n; i += 2 * len) {
      int w = 1;
      for (int j = 0; j < len; j++) {
        int u = a[i + j];
        int v = (long long)a[i + j + len] * w % md;
        a[i + j] = u + v;
        if (a[i + j] >= md) a[i + j] -= md;
        a[i + j + len] = u - v;
        if (a[i + j + len] < 0) a[i + j + len] += md;
        w = (long long)w * root % md;
      }
    }
  }
}
 
vector <int> multiply(vector <int> a, vector <int> b) {
  int an = a.size();
  int bn = b.size();
  int need = an + bn - 1;
  int nn = 1;
  while (nn < 2 * an || nn < 2 * bn) nn <<= 1;
  a.resize(nn);
  b.resize(nn);
  fft(a);
  fft(b);
  for (int i = 0; i < nn; i++) a[i] = (long long)a[i] * b[i] % md;
  reverse(++a.begin(), a.end());
  fft(a);
  int inv = pw(nn, md - 2);
  for (int i = 0; i < nn; i++) a[i] = (long long)a[i] * inv % md;
  a.resize(need);
  return a;
}
 

int N;
FMT fmt;

void solve() {
	cin >> N;
	vector<ll> A, B;
	rep(i, 0, N) {
		int a, b;
		cin >> a >> b;
		A.pb(a); B.pb(b);
	}
	debug(A, B);
	debug(multiply(vi(all(A)), vi(all(B))));
	debug(fmt.get(A, B));
}

int main() {
#ifndef LOCAL
	ios::sync_with_stdio(false);
    cin.tie(0);
#endif
    cout << fixed;
	cout.precision(20);
	srand((unsigned int)time(NULL));
#ifdef LOCAL
	//freopen("in.txt", "wt", stdout); //for tester
    freopen("in.txt", "rt", stdin);
#endif	
	solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
	return 0;
}

