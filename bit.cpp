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


struct BIT { //0-origin!!! update and get just like lazy_segtree
	int n; vl bit0, bit1;
	void init(int mx) {
		n = mx;
		bit0 = vl(n + 1, 0); bit1 = vl(n + 1, 0);
	}
	BIT(int mx = 0) { init(mx); } 

	ll ga(vl& bit, int i) {
		ll s = 0;
		while(i > 0) { s += bit[i]; i -= i & -i; }
		return s;
	}
	void app(vl& bit, int i, ll x) {
		while(i <= n) { bit[i] += x; i += i & -i; }
	}
	void update(int a, int b, ll x) { //[a, b)
		a++;
		app(bit0, a, -x * (a - 1));
		app(bit1, a, x);
		app(bit0, b + 1, x * b);
		app(bit1, b + 1, -x);
	}
	ll get(int a, int b) { //[a, b)
		a++;
		return (ga(bit1, b) * b + ga(bit0, b)) 
			- (ga(bit1, a - 1) * (a - 1) + ga(bit0, a - 1));
	}
};

int N, M;
char s[2];

int main() {
	scanf("%d%d", &N, &M);
	BIT bit(N);
	for(int i = 0; i < N; i++) {
		int a;
		scanf("%d", &a);
		bit.add(i + 1, a);
	}
	while(M--) {
		scanf("%s", s);
		int a, b, v;
		if(s[0] == 'Q') {
			scanf("%d%d", &a, &b);
			printf("%lld\n", bit.range_sum(a, b));
		}
		else {
			scanf("%d%d%d", &a, &b, &v);
			bit.range_add(a, b, v);
		}
	}
}
