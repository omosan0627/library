#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <string.h>
#include <map>
#include <fstream>
#include <functional>
#include <bitset>
#include <stack>
#include <set>
#include <climits>
#include <numeric>
#include <complex>
#include <cassert>
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
typedef vector<int> vl;
typedef vector<vl> mat;
typedef complex<double> comp;
void Debug() {cout << '\n'; }
template<class FIRST, class... REST>void Debug(FIRST arg, REST... rest) { 
	cout << arg << " "; Debug(rest...); }
template<class T>ostream& operator<< (ostream& out, const vector<T>& v) {
	out << "[";if(!v.empty()){rep(i,0,sz(v)-1)out<<v[i]<< ", ";out<<v.back();}out << "]";return out;}
template<class S, class T>ostream& operator<< (ostream& out, const pair<S, T>& v) {
	out << "(" << v.first << ", " << v.second << ")";return out;}
const int MAX_N = 500010;
const double eps = 1e-6;
const ll mod = 1000000007;
const int inf = 1 << 30;
const ll linf = 1LL << 60;
const double PI = 3.14159265358979323846;
///////////////////////////////////////////////////////////////////////////////////////////////////

struct BIT { //1-origin!!!
	int n, b; vl bit;
	void init(int mx) {
		n = mx;
		b = 1;
		while(b * 2 <= n) b *= 2;
		bit = vl(n + 1, 0);
	}
	BIT(int mx = 0) { init(mx); } 

	ll get(int i) {
		ll s = 0;
		while(i > 0) { s += bit[i]; i -= i & -i; }
		return s;
	}
	void update(int i, ll x) {
		while(i <= n) { bit[i] += x; i += i & -i; }
	}

	int get_index(ll x) { //something like lower_bound(all(sum), a). O(logn)
		x--;
		int r = b;
		int res = 0;
		while(r > 0) {
			if((r | res) <= n) {
				int rv = bit[r | res];
				if(x >= rv) {
					x -= rv;
					res += r;
				}
			}
			r >>= 1;
		}
		return res + 1;
	}

	int range_sum(int a, int b) { //[a, b]
		return get(b) - get(a - 1);
	}
};

int main() {
}
