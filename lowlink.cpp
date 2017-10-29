#include <iostream>
#include <cmath>
#include <sstream>
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
#include <iomanip>
#define MAX_N 100010
#define BS 400
#define PI 3.141592653589
#define EPS 1e-6
#define MOD 1000000007
#define YJSNPI 810
#define INF (1 << 30)
#define ADD(a, b) a = (a + (b) % MOD) % MOD
#define SUB(a, b) a = (MOD + a - (b)) % MOD
#define MUL(a, b) a = (a * (ll)b) % MOD
#define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define x first
#define y second
#define REP(i, a, b) for(int i = a; i < (b); i++)
#define RER(i, a, b) for(int i = a - 1; i >= b; i--)

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vec;
typedef vector<vec> mat;

void debug() {cout << endl; }

template<class FIRST, class... REST>
void debug(FIRST arg, REST... rest) { cout << arg << " "; debug(rest...); }

template<class T>
void showary(T begin, T end) { while(begin != end) { cout << *begin << " "; begin++; } cout << endl; }

int N, M;
vector<int> G[100010];
bool used[100010];
int low[100010], ord[100010];


void lowlink(int at, int p, int &k) {
//int &k can be altered as int k
//used this as lowlink(0, -1, k). declare int k = 0
//if(ord[at] < low[n]) (n, at) is a bridge
//if(at == 0) if(nG[at].size() > 1) at  is an articulation point
//else if(ord[at] <= low[n]) at  is an articulation point
	used[at] = true;
	low[at] = ord[at] = k;
	k++;
	for(int i = 0; i < (int)G[at].size(); i++) {
		int n = G[at][i];
		if(!used[n]) {
			lowlink(n, at, k);
			low[at] = min(low[at], low[n]);
		}
		else if(n != p) low[at] = min(low[at], ord[n]); //if you set unreachable vertex, be careful here.
	}
}

/*
vector<pi> ans;

int dfs(int at) { //return num of bridges
	used[at] = true;
	int res = 0;
	for(int i = 0; i < G[at].size(); i++) {
		int n = G[at][i];
		if(used[n]) continue;
		if(ord[at] < low[n]) {
			ans.push_back(pi(at, n));
			res++;
		}
		res += dfs(n);
	}
	return res;
}
*/

vector<int> ans; 

int dfs(int at) { //return num of articulation points
	used[at] = true;
	bool tmp = false;
	int cnt = 0, res = 0;
	for(int i = 0; i < (int)G[at].size(); i++) {
		int n = G[at][i];
		if(used[n]) continue;
		if(at != 0 && ord[at] <= low[n] && !tmp) {
			ans.push_back(at);
			tmp = true;
			res++;
		}
		res += dfs(n);
		cnt++;
	}
	if(at == 0 && cnt > 1) {
		ans.push_back(0);
		res++;
	}
	return res;
}

int main() {
	scanf("%d%d", &N, &M);
	for(int i = 0; i < M; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	int k = 0;
	lowlink(0, -1, k);
	memset(used, 0, sizeof(used));
	dfs(0);
	sort(ans.begin(), ans.end());
	for(int i = 0; i < (int)ans.size(); i++) {
		printf("%d\n", ans[i]);
	}
}
