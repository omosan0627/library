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
	out << "{";if(!v.empty()){rep(i,0,sz(v)-1)out<<v[i]<< ", ";out<<v.back();}out << "}";return out;}
template<class S, class T>ostream& operator<< (ostream& out, const pair<S, T>& v) {
	out << "(" << v.first << ", " << v.second << ")";return out;}
const int MAX_N = 200010;
const double eps = 1e-6;
const ll mod = 1000000007;
const int inf = 1 << 30;
const ll linf = 1LL << 60;
const double PI = 3.14159265358979323846;
///////////////////////////////////////////////////////////////////////////////////////////////////

int N = 4, M = 4;

vector<comp> conj(const vector<comp>& A) {
	vector<comp> res = A;
	int n = (int)A.size();
	rep(i, 0, n) {
		res[i] = conj(res[i]);
	}
	return res;
}


comp inpro(const vector<comp>& A, const vector<comp>& B) {
	assert((int)A.size() == (int)B.size());
	int n = (int)A.size();
	comp res;
	rep(i, 0, n) {
		res += A[i] * conj(B[i]);
	}
	return res;
}

vector<comp> norm(const vector<comp>& A) {
	comp a = sqrt(inpro(A, A));
	int n = (int)A.size();
	vector<comp> res(n);
	rep(i, 0, n) res[i] = A[i] / a;
	return res;
}

vector<vector<comp>> ortho(const vector<vector<comp>>& vec) {
	int n = (int)vec.size();
	vector<vector<comp>> res(n);

	res[0] = norm(vec[0]);

	rep(i, 1, N) {
		res[i] = vec[i];
		rep(j, 0, i) {
			comp a = inpro(vec[i], res[j]);
			rep(k, 0, M) {
				res[i][k] -= a * res[j][k];
			}
		}
		debug(i, res[i]);
		res[i] = norm(res[i]);
	}
	return res;
}

void solve() {
	vector<vector<comp>> vec(N, vector<comp>(M));
	vec[0][0] = comp(1, 0);
	vec[0][1] = comp(0, 1);
	vec[0][2] = comp(0, 0);
	vec[0][3] = comp(0, 1);
	vec[1][0] = comp(0, 1);
	vec[1][1] = comp(1, 0);
	vec[1][2] = comp(0, 0);
	vec[1][3] = comp(1, 0);
	vec[2][0] = comp(0, 0);
	vec[2][1] = comp(0, 1);
	vec[2][2] = comp(1, 1);
	vec[2][3] = comp(0, 0);
	vec[3][0] = comp(0, 0);
	vec[3][1] = comp(0, 0);
	vec[3][2] = comp(0, 0);
	vec[3][3] = comp(1, 0);
	
	vector<vector<comp>> vec2 = ortho(vec);

	debug(vec2);
	rep(i, 0, N) {
		rep(j, 0, N) {
			debug(inpro(vec2[i], vec2[j]));
		}
	}

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




