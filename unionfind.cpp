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
#define EPS 1e-6
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
typedef pair<int, pi> ppi;

void debug() {cout << endl; }

template<class FIRST, class... REST>
void debug(FIRST arg, REST... rest) { cout << arg << " "; debug(rest...); }

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

//unite, same, find, init
//don't forget to initialize it
//////////////////////////////////////////////////////////////


int main() {
	int N = 5;
	UF u(N);
	u.unite(0, 1); //unite node 0 and 1
	u.unite(2, 3);
	u.unite(2, 4); //unite node 2, 3, and 4
	cout << u.same(0, 1) << endl; //true
	cout << u.same(2, 4) << endl; //true
	cout << u.same(0, 2) << endl; //false
}

