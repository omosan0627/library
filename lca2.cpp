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
#define MAX_N 100100
#define LOG 21
#define PI 3.141592653589
#define EPS 1e-6
#define MOD 1000000007
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
typedef pair<int, pi> ppi;

void debug() {cout << endl; }

template<class FIRST, class... REST>
void debug(FIRST arg, REST... rest) { cout << arg << " "; debug(rest...); }

template<class T>
void showary(T begin, T end) { 
	while(begin != end) { cout << *begin << " "; begin++; } cout << endl; }

struct RMQ {
	int n;
	int seg[MAX_N * 4];
	int* A;

	void init(int* ary, int N) {
		A = ary;
		n = 1; while(n < N) n *= 2;
		REP(i, 0, n) seg[i + n - 1] = i;
		RER(i, n - 1, 0) {
			if(A[seg[i * 2 + 1]] < A[seg[i * 2 + 2]]) seg[i] = seg[i * 2 + 1];
			else seg[i] = seg[i * 2 + 2];
		}
	}

	int get_min(int a, int b, int k, int l, int r) {
		if(b <= l || r <= a) return -1;
		if(a <= l && r <= b) return seg[k];
		int lv = get_min(a, b, k * 2 + 1, l, (l + r) / 2);
		int rv = get_min(a, b, k * 2 + 2, (l + r) / 2, r);
		if(lv == -1) return rv;
		if(rv == -1) return lv;
		if(A[lv] < A[rv]) return lv;
		else return rv;
	}

	int get(int a, int b) {
		return get_min(a, b, 0, 0, n);
	}
};

struct LCA {
	RMQ rmq;
	int vs[MAX_N * 2];
	int depth[MAX_N * 2];
	int id[MAX_N];

	void dfs(int v, int p, int d, int &k, vector<int> *G) {
		id[v] = k;
		vs[k] = v;
		depth[k++] = d;
		REP(i, 0, G[v].size()) {
			if(G[v][i] != p) {
				dfs(G[v][i], v, d + 1, k, G);
				vs[k] = v;
				depth[k++] = d;
			}
		}
	}

	void init(vector<int>* G, int root = 0) {
		int k = 0;
		dfs(root, -1, 0, k, G);
		rmq.init(depth, k);
	}

	int get(int u, int v) {
		return vs[rmq.get(min(id[u], id[v]), max(id[u], id[v]) + 1)];
	}
};

LCA lca;
vector<int> G[MAX_N];

void add_edge(int a, int b) {
	G[a].push_back(b);
	G[b].push_back(a);
}

int main() {
	add_edge(0, 1);
	add_edge(0, 2);
	add_edge(1, 3);
	add_edge(1, 4);
	add_edge(2, 7);
	add_edge(4, 5);
	add_edge(4, 6);
	lca.init(G);
	debug(lca.get(6, 5));
}

