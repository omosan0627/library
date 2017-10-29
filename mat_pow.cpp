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
const double eps = 1e-6;
const ll mod = 1000000007;
const int inf = 1 << 30;
const ll linf = 1LL << 60;
const double PI = 3.14159265358979323846;
///////////////////////////////////////////////////////////////////////////////////////////////////


mat mat_mul(const mat &A, const mat &B) {//if invalid, assert. taking mod.
	assert((int)A[0].size() == (int)B.size());
	mat C(A.size(), vl(B[0].size()));
	rep(i, 0, (int)A.size()) {
		rep(k, 0, (int)B.size()) {
			rep(j, 0, (int)B[0].size()) {
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
			}
		}
	}
	return C;
}

mat mat_pow(mat A, ll n) {
	mat B((int)A.size(), vl((int)A.size()));
	rep(i, 0, (int)A.size()) {
		B[i][i] = 1;
	}
	while(n > 0) {
		if(n & 1) B = mat_mul(B, A);
		A = mat_mul(A, A);
		n >>= 1;
	}
	return B;
}

mat power_sum(const mat& A, ll m) { //1+A+A^2+...+A^(n-1)
	int n = (int)A.size();
	assert((int)A[0].size() == n);
	mat B(n * 2, vl(n * 2));
	rep(i, 0, n) {
		rep(j, 0, n) {
			B[i][j] = A[i][j];
		}
		B[n + i][i] = B[n + i][n + i] = 1;
	}
	B = mat_pow(B, m);
	mat C(n, vl(n));
	rep(i, 0, n) 
		rep(j, 0, n) C[i][j] = B[i + n][j];
	return C;
}

void solve() {
	mat A(2, vl(3));
	mat B(3, vl(2));
	A[0][0] = 1;
	B[0][0] = 1;
	mat C = mat_mul(A, B);
	debug(C);
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


