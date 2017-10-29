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

struct edge {
	int to, cost; 
};

int N;
vector<edge> E[1010];
int d[1010];

void dijkstra(int s) {
	//can be used as bfs.
	priority_queue<pi, vector<pi>, greater<pi> > que;
	fill(d, d + N, INF);
	d[s] = 0;
	que.push(pi(0, s));
	while(!que.empty()) {
		pi p = que.top(); que.pop();
		int v = p.second;
		if(d[v] < p.first) continue;
		for(int i = 0; i < E[v].size(); i++) {
			edge e = E[v][i];
			if(d[e.to] > d[v] + e.cost) {
				d[e.to] = d[v] + e.cost;
				que.push(pi(d[e.to], e.to));
			}
		}
	}

}

void add_edge(int s, int t, int cost) {//both direction
	E[s].push_back(edge{t, cost});
	E[t].push_back(edge{s, cost});
}

//d(dist) and E(edge) V(num of points)
//////////////////////////////////////////////////////////

int main() {
	N = 7;
	add_edge(0, 1, 2);
	add_edge(0, 2, 5);
	add_edge(1, 2, 4);
	add_edge(1, 3, 6);
	add_edge(1, 4, 10);
	add_edge(2, 3, 2);
	add_edge(3, 5, 1);
	add_edge(4, 5, 3);
	add_edge(4, 6, 5);
	add_edge(5, 6, 9);//arihon p96
	dijkstra(0);
	printf("%d\n", d[6]);
}

