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
#define MAX_N 100010
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


struct node {
	ll sum, lazy;
	bool t;
};

int N;
node seg[100000 * 4];

inline void lazy_eval(int k, int l, int r) {
	int m = (l + r) / 2;
	if(seg[k].lazy) {
		seg[k * 2 + 1].sum = (m - l) * seg[k].lazy;
		seg[k * 2 + 1].lazy = seg[k].lazy;
		seg[k * 2 + 1].t = true;
		seg[k * 2 + 2].sum = (r - m) * seg[k].lazy;
		seg[k * 2 + 2].lazy = seg[k].lazy;
		seg[k * 2 + 2].t = true;
		seg[k].lazy = 0;
	}
}

void update(int a, int b, ll s, int k = 0, int l = 0, int r = N) {
	if(b <= l || r <= a) return;
	if(a <= l && r <= b && seg[k].t) {
		seg[k].sum = (r - l) * s;
		seg[k].lazy = s;
		seg[k].t = true;
	}
	else if(r - l == 1) {
		seg[k].sum = s;
		seg[k].t = true;
	}
	else {
		int m = (l + r) / 2;
		lazy_eval(k, l, r);
		update(a, b, s, k * 2 + 1, l, m);
		update(a, b, s, k * 2 + 2, m, r);
		seg[k].sum = seg[k * 2 + 1].sum + seg[k * 2 + 2].sum;
		if(seg[k * 2 + 1].t && seg[k * 2 + 2].t) seg[k].t = true;
		else seg[k].t = false;
	}
}

ll get_sum(int a, int b, int k = 0, int l = 0, int r = N) {
	if(b <= l || r <= a) return 0;
	if(a <= l && r <= b && seg[k].t) return seg[k].sum;
	else if(r - l == 1) return seg[k].sum;
	else {
		int m = (l + r) / 2;
		lazy_eval(k, l, r);
		ll lsum = get_sum(a, b, k * 2 + 1, l, m);
		ll rsum = get_sum(a, b, k * 2 + 2, m, r);
		return lsum + rsum;
	}
}

ll A[100010];

void update_slow(int a, int b, int s) {
	for(int i = a; i < b; i++) A[i] = s;
}

ll get_sum_slow(int a, int b) {
	ll res = 0;
	for(int i = a; i < b; i++) res += A[i];
	return res;
}

int M;

int main() {
	N = 100000;
	//for(int i = 0; i < N * 4; i++) seg[i].t = true;
	scanf("%d", &M);
	srand(6);
	for(int i = 0; i < M; i++) {
		int s = rand() % 2;
		int a, b, v;
		a = rand() % N; b = rand() % N; v = rand() % N + 1;
		if(a > b) swap(a, b);
		if(s == 0) {
			//scanf("%d%d", &a, &b); a--;
			//ll rv = get_sum_slow(a, b);
			ll lv = get_sum(a, b);
			/*
			if(rv != lv) {
				cout << "OMO" << endl;
				break;
			}
			*/
		}
		else {
			//scanf("%d%d%d", &a, &b, &v); a--;
			//update_slow(a, b, v);
			update(a, b, v);
		}
	}
}
