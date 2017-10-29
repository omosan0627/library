#include <bits/stdc++.h>
#define INF (1 << 30)

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<double, double> pd;
typedef pair<int, pi> ppi;

void debug() {cout << endl; }

template<class FIRST, class... REST>
void debug(FIRST arg, REST... rest) { cout << arg << " "; debug(rest...); }

struct node {
	node *pp, *rp, *lp;
	int sz, v, mv;
	bool rev;
	
	node() : pp(NULL), rp(NULL), lp(NULL), sz(1), v(INF), mv(INF), rev(false){}
};

struct splay_tree {

	typedef node* np;
	np root;

	splay_tree() : root(NULL) {}

	inline int size(np T) { return !T ? 0 : T->sz; }
	inline int value(np T) { return !T ? INF : T->v; }
	inline int mvalue(np T) { return !T ? INF : T->mv; }

	inline void update(np T) {
		if(!T) return;
		T->sz = size(T->rp) + size(T->lp) + 1;
		T->mv = min(value(T), min(mvalue(T->lp), mvalue(T->rp)));
	}

	inline void lazy_eval(np T) {
		if(!T) return;
		if(T->rev) {
			swap(T->lp, T->rp);
			if(T->lp) T->lp->rev ^= true;
			if(T->rp) T->rp->rev ^= true;
			T->rev = false;
		}
	}
	
	void r_rot(np P) {
		np D = P->pp, T = P->lp, B = T->rp;
		if(D) {
			if(D->rp == P) D->rp = T;
			else D->lp = T;
		}
		if(B) B->pp = P;
		T->pp = D; T->rp = P;
		P->pp = T; P->lp = B;
		update(P); update(T);
	}

	void l_rot(np P) {
		np D = P->pp, T = P->rp, B = T->lp;
		if(D) {
			if(D->rp == P) D->rp = T;
			else D->lp = T;
		}
		if(B) B->pp = P;
		T->pp = D; T->lp = P;
		P->pp = T; P->rp = B;
		update(P); update(T);
	}

	np splay(np T) {
		while(true) {
			np p = T->pp;
			if(!p) break;
			np pp = p->pp;
			if(!pp) {
				//lazy_eval(p);//if you use find before splay, you don't need this.
				if(p->lp == T) r_rot(p);
				else l_rot(p);
				break;
			}
			//lazy_eval(pp); //here too
			//lazy_eval(p);
			if(pp->lp == p) {
				if(p->lp == T) { r_rot(pp); r_rot(p); }
				else { l_rot(p); r_rot(pp); }
			}
			else {
				if(p->lp == T) { r_rot(p); l_rot(pp); }
				else { l_rot(pp); l_rot(p); }
			}
		}
		root = T;
		return T;
	}

	np find(int k, np T) {
		if(!T) return NULL;
		lazy_eval(T);
		if(k >= size(T)) return NULL;
		if(k == size(T->lp)) return T;
		if(k < size(T->lp)) return find(k, T->lp);
		else return find(k - size(T->lp) - 1, T->rp);
	}

	/////////////////////////////////////////////////
	
	np merge(np L, np R) {
		if(!L) return R;
		L = splay(find(size(L) - 1, L));
		L->rp = R;
		if(R) R->pp = L;
		update(L);
		root = L;
		return L;
	}

	pair<np, np> split(int k, np R) {//split before k
		if(k == size(R)) return make_pair(root, (np)(NULL));
		np T = find(k, R);
		if(!T) return make_pair((np)(NULL), (np)(NULL));
		splay(T);
		pair<np, np> tmp(T->lp, T);
		if(T->lp) T->lp->pp = NULL;
		T->lp = NULL;
		update(T);
		return tmp;
	}

	np insert(int k, np T) {//insert before k
		if(!T) return NULL;
		pair<np, np> p = split(k, root);
		T->lp = p.first;
		T->rp = p.second;
		if(p.first) p.first->pp = T;
		if(p.second) p.second->pp = T;
		update(T);
		root = T;
		return T;
	}

	void show_tree(np T) {
		if(!T) return;
		lazy_eval(T);
		debug(value(T), mvalue(T), value(T->lp), value(T->rp), value(T->pp));
		show_tree(T->lp);
		show_tree(T->rp);
	}
	
	void show() {
		show_tree(root);
	}

	/////////////////////////////////////
	

	void reverse(int l, int r) {//[ , ]
		pair<np, np> s1, s2;
		s2 = split(r + 1, root);
		s1 = split(l, s2.first);
		if(s1.second) s1.second->rev ^= true;
		np tmp;
		tmp = merge(s1.first, s1.second);
		tmp = merge(tmp, s2.second);
	}
	
	int query(int l, int r) {//[ , ]
		pair<np, np> s1, s2;
		s2 = split(r + 1, root);
		s1 = split(l, s2.first);
		int res = mvalue(s1.second);
		np tmp;
		tmp = merge(s1.first, s1.second);
		tmp = merge(tmp, s2.second);
		return res;
	}
};


int N, Q;
splay_tree s;
node buf[200010];
int A[200010];

void reverse(int l, int r) {
	reverse(A + l, A + r + 1);
}

int main() {
	N = 20;
	Q = 10000;
	for(int i = 0; i < N; i++) {
		buf[i].v = buf[i].mv = i;
		s.insert(i, &buf[i]);
		A[i] = i;
	}
	while(Q--) {
		int l = rand() % N, r = rand() % N;
		if(l > r) swap(l, r);
		s.reverse(l, r); reverse(l, r);
		for(int i = 0; i < N; i++) {
			cout << A[i] << " ";
		}
		cout << endl;
		for(int i = 0; i < N; i++) {
			cout << s.query(i, i) << " ";
		}
		cout << endl;
	}
}

