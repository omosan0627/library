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
#include <cassert>
#define MAX_N 1002000
#define LOG 21
#define PI 3.141592653589
#define EPS 1e-9
#define MOD 1000000000
#define YJSNPI 810
#define INF (1 << 30)
#define ADD(a, b) a = (a + (ll)b) % MOD
#define MUL(a, b) a = (a * (ll)b) % MOD
#define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define REP(i, a, b) for(int i = a; i < b; i++)
#define RER(i, a, b) for(int i = a - 1; i >= b; i--)

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<double, double> pd;
typedef pair<int, pi> ppi;

void debug() {cout << endl; }

template<class FIRST, class... REST>
void debug(FIRST arg, REST... rest) { cout << arg << " "; debug(rest...); }

//////////////////////////////////////
#define T_ZERO 0
#define T_INF (1 << 30)


template <typename T>
struct fib_heap {//smaller first
	
	struct node {
		T v;
		int deg;
		bool mark;
		node *left, *right, *par, *child;
		node() : v(T_INF), deg(0), mark(false), left(this), right(this), par(NULL), child(NULL){}
	};
	node *n_top, *end;
	fib_heap() {
		end = new node();
		n_top = end;
	}

	~fib_heap() {
		del_heap(end);
	}

	//////////////////////////////////////
	node *remove(node *n) {
		node *l_n = n->left;
		node *r_n = n->right;
		l_n->right = n->right;
		r_n->left = n->left;
		n->right = n;
		n->left = n;
		//n->par = NULL;
		return n;
	}

	node *insert(node *pl, node *l, node *r, node *pr) {
		pl->right = l;
		l->left = pl;
		pr->left = r;
		r->right = pr;
		return pr;
	}

	node *insert_next(node *nex, node *n) {
		return insert(nex, n, n, nex->right);
	}
	/////////////////////////////////////////
	

	node *push(T v) {
		node *n = new node();
		n->v = v;
		insert_next(end, n);
		if(n_top == end) n_top = n;
		else if(n->v < n_top->v) n_top = n;
		return n;
	}

	T top() {
		return n_top->v;
	}

	node *merge(node *l, node *r) {
		assert(l->deg == r->deg);

		node *big, *small;
		if(l->v <= r->v) {
			small = l; big = r;
		}
		else {
			small = r; big = l;
		}

		small->deg++;
		big->par = small;
		remove(big);
		if(small->child == NULL) small->child = big;
		else insert_next(small->child, big);
		return small;
	}

	T pop() {
		assert(n_top != end);
		T res = n_top->v;
		if(n_top->child == NULL) remove(n_top);
		else insert(n_top->left, n_top->child, n_top->child->left, n_top->right);
		delete n_top;
		
		node *deg[50] = {NULL};

		node *t = end->right;
		do {
			int r = t->deg;
			node *tmp = t;
			t = t->right;
			while(deg[r] != NULL) {
				tmp = merge(deg[r], tmp);
				deg[r] = NULL;
				r++;
			}
			deg[r] = tmp;
			tmp->par = NULL;
		} while(t != end);

		t = end->right;
		n_top = t;
		do {
			if(t->v < n_top->v) n_top = t;
			t = t->right;
		} while(t != end);
		return res;
	}

	void decrease(node *n, T v) {
		n->v -= v;
		if(n->v < n_top->v) n_top = n;
		if(n->par == NULL) return;
		if(n->par->v > n->v) {
			if(n->par->deg == 1) n->par->child = NULL;
			else if(n->par->child == n) n->par->child = n->right;
			n->mark = false;
			remove(n);
			insert_next(end, n);
			if(n->par->mark && n->par->par != NULL) {
				decrease(n, T_ZERO);
			}
			else n->par->mark = true;
			n->par = NULL;
		}
	}

	void delete_n(node *n) {
		decrease(n, T_INF);
		pop();
	}

	bool empty() {
		return end->right == end;
	}

	/////////////////////////////////////////////////
	void show_heap(node *tp, int r) {
		node *t = tp;
		do {
			node *tmp = t;
			t = t->right;
			if(tmp == end) continue;
			debug("show", tmp->v, r, tmp->deg, tmp->par, tmp->mark);
			if(tmp->child != NULL) show_heap(tmp->child, r + 1);
		} while(t != tp);
		cout << endl;
	}

	void del_heap(node *tp) {
		node *t = tp;
		do {
			node *tmp = t;
			t = t->right;
			if(tmp->child != NULL) del_heap(tmp->child);
		} while(t != tp);
		while(tp->right != tp) {
			node *tmp = remove(tp->right);
			delete tmp;
		}
		delete tp;
	}

	void show() {
		debug("omoheap");
		show_heap(end, 0);
	}
};

int N;
int Q[MAX_N];
multiset<int> S;

node<int> buf[MAX_N];

int main() {
	N = 10;
	fib_heap<int> que;
	memset(Q, -1, sizeof(Q));
	int at = 0;
	while(N--) {
		int c, a, k;
		c = rand() % 5;
		if(0 <= c && c <= 2) {
			a = rand() % 10000;
			debug(c, a);
			S.insert(a);
			Q[at++] = a;
			que.push(&buf[at], que);
			debug("insert");
		}
		else if(c == 3) {
			debug(c);
			int res1 = INF;
			int res2 = INF;
			if(!S.empty()) {
				res1 = *min_element(S.begin(), S.end());
				S.erase(min_element(S.begin(), S.end()));
				res2 = que.pop();
				if(res1 != res2) {
					debug("FAIL", c, res1, res2);
				}
			}
			debug("pop", res1, res2);
		}
		else {
			k = rand() % 10000;
			debug(c, k);
			if(Q[k] != -1) {
				S.erase(S.find(Q[k]));
				Q[k] = -1;
			}
			if(!buf[k].remove && buf[k].v != INF) {
				que.delete_n(&buf[k]);
			}
			debug("delete");
		}
	}
}
