#include <bits/stdc++.h>
#define ADD(a, b) a = (a + (ll)b) % mod
#define MUL(a, b) a = (a * (ll)b) % mod
#define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define rer(i, a, b) for(int i = (a) - 1; i >= (b); i--)
#define all(a) (a).begin(), (a).end()
#define sz(v) (int)(v).size()
#define pb push_back
#define sec second
#define fst first
#define debug(fmt, ...) Debug(__LINE__, ":", fmt, ##__VA_ARGS__)
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<int, pi> ppi;
typedef vector<ll> vi;
typedef vector<vi> mat;
typedef complex<double> comp;
void Debug() {cout << '\n'; }
template<class FIRST, class... REST>void Debug(FIRST arg, REST... rest) { 
	cout << arg << " "; Debug(rest...); }
template<class T>ostream& operator<< (ostream& out, const vector<T>& v) {
	out << "[";if(!v.empty()){rep(i,0,sz(v)-1)out<<v[i]<< ", ";out<<v.back();}out << "]";return out;}
template<class S, class T>ostream& operator<< (ostream& out, const pair<S, T>& v) {
	out << "(" << v.first << ", " << v.second << ")";return out;}
const int MAX_N = 200010;
const int MAX_V = 100010;
const double eps = 1e-6;
const ll mod = 1000000007;
const int inf = 1 << 29;
const ll linf = 1LL << 60;
const double PI = 3.14159265358979323846;
///////////////////////////////////////////////////////////////////////////////////////////////////

//minimum cost circularation
namespace MCC { //init before you use it. //negative loops ok.

	struct edge { int to, cap, cost, rev; };

	int V; //num of vertex
	vector<edge> G[MAX_V];
	int h[MAX_V];
	int dist[MAX_V];
	int prevv[MAX_V], preve[MAX_V];
	int S[MAX_V];
	int off;

	void init(int v) {
		V = v;
		memset(S, 0, sizeof(S));
		rep(i, 0, V + 2) G[i].clear();
	}

	void add_edge(int from, int to, int cap, int cost) {
		if(cost >= 0) {
			G[from].push_back((edge){to, cap, cost, (int)G[to].size()});
			G[to].push_back((edge){from, 0, -cost, (int)G[from].size() - 1});
		}
		else {
			off += cap * cost;
			S[from] += cap; S[to] -= cap;
			G[to].push_back((edge){from, cap, -cost, (int)G[from].size()});
			G[from].push_back((edge){to, 0, cost, (int)G[to].size() - 1});
		}
	}

	void set_d(int v, int d) { S[v] += d; }

	int impl(int s, int t, int f) {
		int res = 0;
		memset(h, 0, sizeof(h));
		while(f > 0) {
			priority_queue<pi, vector<pi>, greater<pi> > que;
			fill(dist, dist + V, inf);
			dist[s] = 0;
			que.push(pi(0, s));
			while(!que.empty()) {
				pi p = que.top(); que.pop();
				int v = p.sec;
				if(dist[v] < p.fst) continue;
				rep(i, 0, (int)G[v].size()) {
					edge &e = G[v][i];
					if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
						dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
						prevv[e.to] = v;
						preve[e.to] = i;
						que.push(pi(dist[e.to], e.to));
					}
				}
			}
			if(dist[t] == inf) return -1;
			rep(v, 0, V) h[v] += dist[v];

			int d = f;
			for(int v = t; v != s; v = prevv[v]) {
				d = min(d, G[prevv[v]][preve[v]].cap);
			}
			f -= d;
			res += d * h[t];
			for(int v = t; v != s; v = prevv[v]) {
				edge &e = G[prevv[v]][preve[v]];
				e.cap -= d;
				G[v][e.rev].cap += d;
			}
		}
		return res;
	}

	int get() { //u,v,cap,cost
		int f = 0;
		int s = V, t = V + 1;
		rep(i, 0, V) {
			if(S[i] > 0) add_edge(i, t, S[i], 0);
			if(S[i] < 0) {
				add_edge(s, i, -S[i], 0);
				f += -S[i];
			}
		}
		V += 2;
		return impl(s, t, f) + off;
	}
}

int N, K;

int main() {
	scanf("%d%d", &N, &K);
	int s = 0, t = N * N * 2 - 1;
	MCC::init(N * N * 2);
	MCC::set_d(s, -K);
	MCC::set_d(t, K);

	rep(i, 0, N) {
		rep(j, 0, N) {
			int id = i * N + j;
			int a; scanf("%d", &a);
			MCC::add_edge(id, id + N * N, 1, -a);
			MCC::add_edge(id, id + N * N, K, 0);
			if(i != N - 1) {
				MCC::add_edge(id + N * N, id + N, K, 0);
			}
			if(j != N - 1) {
				MCC::add_edge(id + N * N, id + 1, K, 0);
			}
		}
	}
	printf("%d\n", -MCC::get());
	return 0;
}
