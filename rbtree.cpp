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
	T(ll v = -inf) : v(v) {}
	T operator+(const T& t) { return T(max(v, t.v)); } //when getting value
	void operator+=(const T& t) { v = max(v, t.v); } //when updating value
	friend ostream& operator<<(ostream& out, const T& t) {
		out << t.v; return out;
	}
};

struct rbtree {
	const bool black = false;
	const bool red = true;
	struct node {
		T t;
		bool color; int rnk, sz;
		node *nl, *nr;
	};
	typedef pair<node*, node*> np;

	node *root;
	rbtree() {}
	rbtree(node *root) : root(root) {}
	rbtree(T t) { root = new_node(black, t); }
	inline void update(node *a) {
		if(!a->nl) { a->rnk = 0; a->sz = 1; }
		else {
			a->rnk = a->nl->rnk + (a->nl->color == black);
			a->sz = a->nl->sz + a->nr->sz;
			a->t = a->nl->t + a->nr->t;
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
	node *insert(node *a, node *b, int k) {
		np p = split(a, k);
		debug("omo");
		node *c = merge(p.fst, b);
		show_sub(c);
		debug("omoend");
		return merge(c, p.sec);
	}
	T get_sub(node *a, int k, int l, int r) {
		if(r - l == 1) return a->t;
		if(k < a->nl->sz) return get_sub(a->nl, k, l, l + a->nl->sz);
		else return get_sub(a->nr, k - a->nl->sz, l + a->nl->sz, r);
	}


	void merge(const rbtree& sa, const rbtree& sb) {
		root = merge(sa.root, sb.root);
	}
	pair<rbtree, rbtree> split(int k) {
		np p = split(root, k);
		return make_pair(rbtree(p.fst), rbtree(p.sec));
	}
	void insert(const rbtree& sa, int k) {
		root = insert(root, sa.root, k);
	}
	void insert(T t, int k) {
		insert(rbtree(t), k);
	}
	T get(int k) {
		return get_sub(root, k, 0, root->sz);
	}

	void show_sub(node *a) {
		if(!a) return;
		debug(a, a->t, a->nl, a->nr, a->color ? "red" : "black", a->rnk, a->sz);
		if(a->nl) show_sub(a->nl);
		if(a->nr) show_sub(a->nr);
	}
	void show() { show_sub(root); }
	void show2() {
		vector<T> vec;
		rep(i, 0, root->sz) {
			vec.pb(get(i));
		}
		debug(vec);
	}
};

rbtree s;
rbtree sd;

void solve() {
	s.insert(T(0), 0);
	s.insert(T(1), 1);
	s.insert(T(2), 2);
	s.insert(T(3), 3);
	s.insert(T(4), 4);
	sd.insert(T(5), 0);
	sd.insert(T(6), 1);
	sd.insert(T(7), 2);
	sd.insert(T(8), 3);
	sd.insert(T(9), 4);
	s.insert(sd, 3);
	s.show();
	s.show2();
	pair<rbtree, rbtree> p = s.split(4);
	p.fst.show2();
	p.fst.show();
	p.sec.show2();
	p.sec.show();
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

