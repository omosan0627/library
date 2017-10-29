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
const int MAX_N = 1010;
const int MAX_V = 1010;
const double eps = 1e-6;
const ll mod = 1000000007;
const int inf = 1 << 30;
const ll linf = 1LL << 60;
const double PI = 3.14159265358979323846;
///////////////////////////////////////////////////////////////////////////////////////////////////


namespace MCF { //init before you use it. O(|V|^2 + |F||E|log|V|), no negative loops allowed

	struct edge { int to, cap, cost, rev; };

	int V; //num of vertex
	vector<edge> G[MAX_V];
	int h[MAX_V];
	int dist[MAX_V];
	int prevv[MAX_V], preve[MAX_V];

	void init(int v) { //other things don't have to be inited.
		V = v;
		rep(i, 0, v) G[i].clear();
	}

	void add_edge(int from, int to, int cap, int cost) {
		G[from].push_back((edge){to, cap, cost, (int)G[to].size()});
		G[to].push_back((edge){from, 0, -cost, (int)G[from].size() - 1});
	}

	int get(int s, int t, int f) {
		int res = 0;
		memset(h, 0, sizeof(h));
		/* //add if the graph includes negative edges
		rep(k, 0, V) {
			rep(i, 0, V) {
				rep(j ,0, (int)G[i].size()) {
					edge &e = G[i][j];
					if(e.cap == 0) continue;
					MIN(h[e.to], h[i] + e.cost);
				}
			}
		}
		*/
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
}


int N, M;

void solve() {
	scanf("%d%d", &N, &M);
	int s = 0, t = N - 1;
	MCF::init(N);

	rep(i, 0, M) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c); a--; b--;
		MCF::add_edge(a, b, 1, c);
		MCF::add_edge(b, a, 1, c);
	}
	printf("%d\n", MCF::get(s, t, 2));
}

int main() {
	solve();
	return 0;
}
