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
#include <ctime>
#define MAX_N 40100
#define BS 200
#define PI 3.141592653589
#define EPS 1e-6
#define MOD 1000000007
#define YJSPI 810
#define INF (1 << 28)
#define ADD(a, b) a = (a + (ll)b) % MOD
#define MUL(a, b) a = (a * (ll)b) % MOD
#define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define REP(i, a, b) for(int i = a; i < b; i++)
#define RER(i, a, b) for(int i = a - 1; i >= b; i--)

using namespace std;

typedef long long ll;
typedef vector<ll> vec;
typedef pair<int, int> pi;

void debug() {cout << endl; }

template<class FIRST, class... REST>
void debug(FIRST arg, REST... rest) { cout << arg << " "; debug(rest...); }

template<class T>
void showary(T begin, T end) { 
	while(begin != end) { cout << *begin << " "; begin++; } cout << endl; }

struct node_t { 
	int id;
	node_t *pp, *lp, *rp; 
	node_t(int id) : id(id), pp(NULL), lp(NULL), rp(NULL){}// 親，左の子，右の子// このノードは木の根？
	bool is_root() { 
		return !pp || (pp->lp != this && pp->rp != this);
	}
	void rotr() { // 右回転 
		node_t *q = pp, *r = q->pp;
		if ((q->lp = rp)) rp->pp = q; 
		rp = q; q->pp = this; 
		if ((pp = r)) { 
			if (r->lp == q) r->lp = this; 
			if (r->rp == q) r->rp = this;
		} 
	} 
	void rotl() { // 左回転 
		node_t *q = pp, *r = q->pp;
		if ((q->rp = lp)) lp->pp = q;
		lp = q; q->pp = this; 
		if ((pp = r)) {
			if (r->lp == q) r->lp = this; 
			if (r->rp == q) r->rp = this;
		}
	} 
	void splay() { // スプレー操作 
		while (!is_root()) { 
			node_t *q = pp; 
			if (q->is_root()) { 
				if (q->lp == this) rotr(); 
				else rotl(); 
			}
			else { 
				node_t *r = q->pp;
				if (r->lp == q) { 
					if (q->lp == this) { q->rotr(); rotr(); }
					else { rotl(); rotr(); }
				}
				else { 
					if (q->rp == this) { q->rotl(); rotl(); }
					else { rotr(); rotl(); } 
				}
			}
		}
	}
};

node_t* make_node(int id) {
	return new node_t(id);
}

node_t *expose(node_t *x) { 
	node_t *rp = NULL;
	for (node_t *p = x; p; p = p->pp) { 
		p->splay();
		p->rp = rp; 
		rp = p;
	} 
	x->splay();
	return x;
} 
void cut(node_t *c) { 
	expose(c); 
	node_t *p = c->lp; 
	c->lp = NULL; 
	p->pp = NULL;
}
void link(node_t *c, node_t *p) { 
	expose(c); 
	expose(p); 
	c->pp = p;
	p->rp = c;
}

int find_root(node_t *node){
    node_t *v = expose(node);
    while(v->lp) v = v->lp;
    v->splay();
    return v->id;
}


void show_node(node_t *node) {
	cout << "ID : " << node->id << "| ";
	cout << "PARENT : ";
	if(node->pp != NULL)cout << node->pp->id << "| ";
	else cout << ("ROOT| ");
	cout << "LEFT : ";
	if(node->lp != NULL)cout << node->lp->id << "| ";
	else cout << ("LEFF| ");
	cout << "RIGHT : ";
	if(node->rp != NULL)cout << node->rp->id << "| ";
	else cout << ("LEFF| ");
	if(node->is_root()) cout << "YES";
	cout << endl;
}

int main() {
	node_t *n1 = make_node(1);
	node_t *n2 = make_node(2);
	node_t *n3 = make_node(3);
	node_t *n4 = make_node(4);
	node_t *n5 = make_node(5);
	link(n5, n2); link(n4, n2); link(n2, n1); link(n3, n1);
	show_node(n1); show_node(n2); show_node(n3); show_node(n4); show_node(n5);
	expose(n5);
	show_node(n1); show_node(n2); show_node(n3); show_node(n4); show_node(n5);
	expose(n4);
	show_node(n1); show_node(n2); show_node(n3); show_node(n4); show_node(n5);
}
