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

bool bellman_ford(int s) {
	//if a negative loop that can be reached from s exists, return true
	fill(d, d + N, INF);
	d[s] = 0;
	for(int k = 0; k < N; k++) {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < E[i].size(); j++) {
				edge e = E[i][j];
				if(d[i] != INF && d[e.to] > d[i] + e.cost) {
					d[e.to] = d[i] + e.cost;
					if(k == N - 1) return true;
				}
			}
		}
	}
	return false;
}

bool find_negative_loop() {//find all negative loop
	memset(d, 0, sizeof(d));
	for(int k = 0; k < N; k++) {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < E[i].size(); j++) {
				edge e = E[i][j];
				if(d[e.to] > d[i] + e.cost) {
					d[e.to] = d[i] + e.cost;
					if(k == N - 1) return true;
				}
			}
		}
	}
	return false;
}


void add_edge(int s, int t, int cost) {//one way path
	E[s].push_back(edge{t, cost});
}

//N = num of points, E edge, d distance
///////////////////////////////////////////



int main() {
	N = 3;
	add_edge(0, 1, 3);
	add_edge(1, 2, 3);
	add_edge(2, 0, -7);
	if(bellman_ford(0)) printf("YES\n");
	else printf("NO\n");
}
