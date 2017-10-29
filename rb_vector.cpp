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

template<class T>
struct rbvector { //added insert O(logn), but random access is O(logn) too
	const bool black = false;
	const bool red = true;
	struct node {
		T t;
		bool color; int rnk, sz;
		node *nl, *nr;
	};
	typedef pair<node*, node*> np;

	node *root;
	inline int size() { return !root ? 0 : root->sz; }
	inline void update(node *a) {
		if(!a->nl) { a->rnk = 0; a->sz = 1; }
		else {
			a->rnk = a->nl->rnk + (a->nl->color == black);
			a->sz = a->nl->sz + a->nr->sz;
		}
	}
	node *new_node(bool color, T t, node *nl = NULL, node *nr = NULL) {
		node *nn = new node();
		nn->nl = nl; nn->nr = nr; nn->color = color; nn->t = t;
		update(nn);
		return nn;
	}
	node *merge_sub(node *a, node *b) {
		if(a->rnk < b->rnk) {
			node *c = merge_sub(a, b->nl);
			b->nl = c;
			if(b->color == black && c->color == red && c->nl->color == red) {
				if(b->nr->color == black) {
					node *y = c->nr;
					c->nr = b; b->nl = y;
					b->color = red; c->color = black;
					update(b); update(c);
					return c;
				}
				else {
					b->color = red;
					c->color = b->nr->color = black;
					update(c); update(b);
					return b;
				}
			}
			else { update(b); return b; };
		}
		else if(a->rnk > b->rnk) {
			node *c = merge_sub(a->nr, b);
			a->nr = c;
			if(a->color == black && c->color == red && c->nr->color == red) {
				if(a->nl->color == black) {
					node *y = c->nl;
					c->nl = a; a->nr = y;
					a->color = red; c->color = black;
					update(a); update(c);
					return c;
				}
				else {
					a->color = red;
					c->color = a->nl->color = black;
					update(c); update(a);
					return a;
				}
			}
			else { update(a); return a; }
		}
		else {
			node *c = new_node(red, T(), a, b);
			return c;
		}
	}
	node *merge(node *a, node *b) {
		if(!a) return b;
		if(!b) return a;
		a->color = black; update(a);
		b->color = black; update(b);
		node *c = merge_sub(a, b);
		c->color = black;
		return c;
	}
	np split(node *v, int k) {
		if(k <= 0) return np(NULL, v);
		if(k >= v->sz) return np(v, NULL);
		if(k < v->nl->sz) {
			np p = split(v->nl, k);
			return np(p.fst, merge(p.sec, v->nr));
		}
		else if(k > v->nl->sz) {
			np p = split(v->nr, k - v->nl->sz);
			return np(merge(v->nl, p.fst), p.sec);
		}
		else return np(v->nl, v->nr);
	}

	T& get_sub(node *a, int k, int l, int r) {
		if(r - l == 1) return a->t;
		if(k < a->nl->sz) return get_sub(a->nl, k, l, l + a->nl->sz);
		else return get_sub(a->nr, k - a->nl->sz, l + a->nl->sz, r);
	}
	void insert(const rbvector& sa, int k) { //after insert, sa is broken
		np p = split(root, k);
		root = merge(merge(p.fst, sa.root), p.sec);
	}
	void insert(T t, int k) {
		np p = split(root, k);
		root = merge(merge(p.fst, new_node(black, t)), p.sec);
	}
	T& get(int k) { return get_sub(root, k, 0, size()); }
	T& operator[](int k) { return get(k); }
	void push_back(const rbvector& sa) { insert(sa, size()); }
	void push_back(T t) { insert(t, size()); }

	friend ostream& operator<<(ostream& out, rbvector& sa){
		out << "[";
		rep(i, 0, sa.size() - 1) {
			out << sa.get(i) << ", ";
		}
		out << sa.get(sa.size() - 1) << "]";
		return out;
	}
};

rbvector<int> vec, vec2;

void solve() {
	vec.pb(0);
	vec.pb(1);
	vec.pb(2);
	vec.pb(3);
	vec.pb(4);
	vec2.pb(5);
	vec2.pb(6);
	vec2.pb(7);
	vec2.pb(8);
	vec2.pb(9);
	vec.insert(vec2, 3);
	debug(vec);
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

