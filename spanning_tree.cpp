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

int N, E; //erase this

//////////////////////////////////
//prim O(|V|^2)

//int N; add this///////////////////////////////////
int cost[1010][1010];
int mincost[1010];
bool used[1010];

int prim() {
	for(int i = 0; i < N; i++) {
		mincost[i] = INF;
		used[i] = false;
	}
	mincost[0] = 0;
	int res = 0;

	while(true) {
		int v = -1;

		for(int u = 0; u < N; u++) {
			if(!used[u] && (v == -1 || mincost[u] < mincost[v])) v = u;
		}
		if(v == -1) break;
		used[v] = true;
		res += mincost[v];

		for(int u = 0; u < N; u++) {
			mincost[u] = min(mincost[u], cost[v][u]);
		}
	}
	return res;
}


/////////////////////////////////////////////////////



/////////////////////////////////////////////////////
//kruskal O(|E| log |V|)

//////////////
//unionfind

struct UF {
	vector<int> par, ran;
	void init(int n) {
		par.resize(n); ran.resize(n);
		for(int i = 0; i < n; i++) {
			par[i] = i;
			ran[i] = 0;
		}
	}
	UF(int mx = 0) { init(mx); }

	int find(int x) {
		if(par[x] == x) return x;
		else return par[x] = find(par[x]);
	}
	void unite(int x, int y) {
		x = find(x);
		y = find(y);
		if(x == y) return;
		if(ran[x] < ran[y]) {
			par[x] = y;
		}
		else {
			par[y] = x;
			if(ran[x] == ran[y]) ran[x]++;
		}
	}
	bool same(int x, int y) { return find(x) == find(y); }
};

//////////////


struct edge { int u, v, cost; };

bool comp(const edge& e1, const edge& e2) {
	return e1.cost < e2.cost;
}

//int N, E; add this////////////////////////////
edge es[100010];

int kruskal() {
	sort(es, es + E, comp);
	UF uf(N);//init union_find
	int res = 0;
	for(int i = 0; i < E; i++) {
		edge e = es[i];
		if(!uf.same(e.u, e.v)) {
			uf.unite(e.u, e.v);
			res += e.cost;
		}
	}
	return res;
}

void add_edge(int s, int t, int cost) {
	es[E++] = edge{s, t, cost};
}

/////////////////////////////////////////////////////

int main() {
	N = 7;
	add_edge(0, 1, 1);
	add_edge(1, 2, 2);
	add_edge(1, 4, 7);
	add_edge(1, 6, 3);
	add_edge(2, 3, 10);
	add_edge(3, 4, 5);
	add_edge(4, 5, 8);
	add_edge(4, 6, 1);
	add_edge(5, 6, 5);
	for(int i = 0; i < N; i++) {
		fill(cost[i], cost[i] + N, INF);
		cost[i][i] = 0;
	}
	for(int i = 0; i < E; i++) {
		edge e = es[i];
		cost[e.u][e.v] = e.cost;
		cost[e.v][e.u] = e.cost;
	}
	debug("prim", prim());
	debug("kruskal", kruskal());
}

