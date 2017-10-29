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

struct T {
	ll v;
	T(ll v = 0) : v(v) {}
	T operator+(const T& t) { return T(v + t.v); }
	friend ostream& operator<<(ostream& out, const T& t) {
		out << t.v; return out;
	}
};

struct p_segtree {
	struct node { T t; node *ln, *rn; };
	int n;
	vector<node*> roots;
	inline int latest(int k) { return k == -1 ? (int)roots.size() - 1 : k; }
	void init(int mx) {
		n = 1;
		while(n < mx) n *= 2;
		vector<node*> nodes(2 * n - 1);
		rep(i, 0, 2 * n - 1) {
			node* nn = new node();
			nodes[i] = nn;
		}
		rep(i, 0, n - 1) {
			nodes[i]->ln = nodes[i * 2 + 1];
			nodes[i]->rn = nodes[i * 2 + 2];
		}
		roots.pb(nodes[0]);
	}
	p_segtree(int mx = -1) {
		if(mx != -1) init(mx);
	}
	void app(int a, T x, node* root, int l, int r) {
		int b = a + 1;
		if(b <= l || r <= a) return;
		if(a <= l && r <= b) root->t = x;
		else {
			node* nln = new node(*(root->ln));
			node* nrn = new node(*(root->rn));
			root->ln = nln; root->rn = nrn;
			app(a, x, nln, l, (l + r) / 2);
			app(a, x, nrn, (l + r) / 2, r);
			root->t = root->ln->t + root->rn->t;
		}
	}

	T ga(int a, int b, node* root, int l, int r) {
		if(b <= l || r <= a) return T();
		if(a <= l && r <= b) return root->t;
		else {
			T lv = ga(a, b, root->ln, l, (l + r) / 2);
			T rv = ga(a, b, root->rn, (l + r) / 2, r);
			return lv + rv;
		}
	}
	void update(int a, T t, int k = -1) {
		k = latest(k);
		node* nroot = new node(*roots[k]);
		roots.pb(nroot);
		app(a, t, nroot, 0, n);
	}
	T get(int a, int b, int k = -1) {
		k = latest(k);
		return ga(a, b, roots[k], 0, n);
	}
	void show(int k = -1) {
		vector<T> tmp;
		rep(i, 0, n) tmp.pb(get(i, i + 1, k));
		debug(tmp);
	}
};

int N, M;
p_segtree seg;
pi A[MAX_N];

bool ok(int a, int b, int t, int m) {
	return seg.get(a, b, m + 1).v >= t;
}

int main() {
	scanf("%d%d", &N, &M);
	seg.init(N);
	rep(i, 0, N) {
		scanf("%d", &A[i].fst);
		A[i].sec = i;
	}
	sort(A, A + N);
	rep(i, 0, N) {
		seg.update(A[i].sec, T(1));
	}
	while(M--) {
		int a, b, t;
		scanf("%d%d%d", &a, &b, &t); a--;
		int lv = -1, rv = N;
		while(rv - lv > 1) {
			int m = (lv + rv) / 2;
			if(ok(a, b, t, m)) rv = m;
			else lv = m;
		}
		printf("%d\n", A[rv].fst);
	}
}
