#include <bits/stdc++.h>
#define ADD(a, b) a = (a + ll(b)) % mod
#define MUL(a, b) a = (a * ll(b)) % mod
#define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define rep(i, a, b) for(int i = int(a); i < int(b); i++)
#define rer(i, a, b) for(int i = int(a) - 1; i >= int(b); i--)
#define all(a) (a).begin(), (a).end()
#define sz(v) (int)(v).size()
#define pb push_back
#define sec second
#define fst first
#define debug(fmt, ...) Debug(__LINE__, ":", fmt, ##__VA_ARGS__)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<int, pi> ppi;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vl> mat;
typedef complex<double> comp;
void Debug() {cerr << '\n'; }
template<class FIRST, class... REST>void Debug(FIRST arg, REST... rest){
	cerr<<arg<<" ";Debug(rest...);}
template<class T>ostream& operator<<(ostream& out,const vector<T>& v) {
	out<<"[";if(!v.empty()){rep(i,0,sz(v)-1)out<<v[i]<<", ";out<<v.back();}out<<"]";return out;}
template<class S, class T>ostream& operator<<(ostream& out,const pair<S, T>& v){
	out<<"("<<v.first<<", "<<v.second<<")";return out;}
const int MAX_N = 500010;
const int MAX_V = 100010;
const double eps = 1e-6;
const ll mod = 1000000007;
const int inf = 1 << 30;
const ll linf = 1LL << 60;
const double PI = 3.14159265358979323846;
mt19937 rng; //use it by rng() % mod, shuffle(all(vec), rng)
///////////////////////////////////////////////////////////////////////////////////////////////////
 
struct Timer {
	const unsigned long long int cycle_per_sec = 2800000000;
	unsigned long long int begin_cycle;
 
	Timer() { reset(); }
	void reset() { begin_cycle = getCycle(); }
 
	unsigned long long int getCycle() {
		unsigned int low, high;
		__asm__ volatile ("rdtsc" : "=a" (low), "=d" (high));
		return ((unsigned long long int)low) | ((unsigned long long int)high << 32);
	}
	 
	double get() {
		return (double)(getCycle() - begin_cycle) / cycle_per_sec;
	}
} timer;
 
struct xorshift {
	unsigned int x, y, z, w;
	unsigned int t;
	xorshift() {
		x = rng(); y = rng(); z = rng(); w = rng();
		t = 0;
	}
	int rand() {
		t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
        return w & 0x7fffffff;
	}
	double drand() {
		return (double) rand() / 0x7fffffff;
	}
} gen;
 
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
 
int dx[4] = {1, -1, 0, 0}; //nothing, d, u, r, l
int dy[4] = {0, 0, 1, -1};
int inv[4] = {1, 0, 3, 2};
char C[4] = {'D', 'U', 'R', 'L'};
map<char, int> IC;
 
int N, M, B;
int gx, gy;
int board[40][40]; //-1 block 0 nothing 1 place
pi G[40][40][4];
pi pG[40][40][4];
pi hist[1600];
bool used[40][40];
int RX[100], RY[100], RC[100];
int bscore = 0;
 
struct SA {
	double looptime;
	SA() {
		looptime = 2.97;
		init();
	}
 
	void add_node(int i, int j) {
		bscore++;
		board[i][j] = 1;
		rep(k, 0, 4) {
			G[i][j][k] = pi(-1, -1);
			int x = i, y = j;
			rep(_, 0, N - 1) {
				x = (x + dx[k] + N) % N;
				y = (y + dy[k] + N) % N;
				if(board[x][y] == 1) {
					G[i][j][k] = pi(x, y);
					G[x][y][inv[k]] = pi(i, j);
					break;
				}
				else if(board[x][y] == -1) break;
			}
		}
	}
 
	void erase_node(int i, int j) {
		bscore--;
		board[i][j] = 0;
		//u and d
		rep(k, 0, 4) {
			if(G[i][j][k] != pi(-1, -1)) {
				G[G[i][j][k].fst][G[i][j][k].sec][inv[k]] = G[i][j][inv[k]];
			}
		}
		rep(k, 0, 4) G[i][j][k] = pi(-1, -1);
	}
	void check() {
		rep(i, 0, N) {
			rep(j, 0, N) {
				rep(k, 0, 4) {
					if(G[i][j][k] == pi(-1, -1)) continue;
					if(G[G[i][j][k].fst][G[i][j][k].sec][inv[k]] != pi(i, j)) {
						debug(i, j, k, G[i][j][k], G[G[i][j][k].fst][G[i][j][k].sec][inv[k]]);
					}
					assert(G[G[i][j][k].fst][G[i][j][k].sec][inv[k]] == pi(i, j));
				}
			}
		}
	}
	void init() {
		rep(i, 0, N) {
			rep(j, 0, N) {
				rep(k, 0, 4) {
					G[i][j][k] = pi(-1, -1);
				}
			}
		}
		rep(i, 0, N) {
			rep(j, 0, N) {
				if(i == gx && j == gy) board[i][j] = 1;
				else if(board[i][j] != -1) {
					// board[i][j] = rand() % 2;
					// board[i][j] = 1;
					board[i][j] = rand() % 10 > 0;
				}
			}
		}
		rep(i, 0, N) {
			rep(j, 0, N) {
				if(board[i][j] == 1) add_node(i, j);
			}
		}
	}
	int score() {
		// memset(used, 0, sizeof(used));
		queue<pi> que;
		que.push(pi(gx, gy));
		used[gx][gy] = 1;
		vector<pi> vec;
		int k = 0;
		while(!que.empty()) {
			pi p = que.front(); que.pop();
			rep(i, 0, 4) {
				int nx = G[p.fst][p.sec][i].fst, ny = G[p.fst][p.sec][i].sec;
				if(nx == -1) continue;
				if(!used[nx][ny]) {
					used[nx][ny] = 1;
					que.push(pi(nx, ny));
					hist[k++] = pi(nx, ny);
				}
			}
		}
		int ascore = 0;
		rep(i, 0, M) {
			int x = RX[i], y = RY[i], c = RC[i];
			rep(_, 0, N) {
				if(board[x][y] == -1) break;
				if(board[x][y] == 1) {
					ascore += used[x][y];
					break;
				}
				else {
					x = (x + dx[c] + N) % N;
					y = (y + dy[c] + N) % N;
				}
			}
		}
		rep(i, 0, k) used[hist[i].fst][hist[i].sec] = 0;
		return ascore * 1000 - bscore * 10;
	}
	double temp(double t) {
		double start_temp = 4.0;
		double end_temp = 0.2;
		return start_temp + (end_temp - start_temp) * t / looptime;
	}
	void iterate() {
		timer.reset();
		int current_score = score();
		int cnt = 0;
		while(true) {
			double t = timer.get();
			if(t > looptime) break;
			int x = gen.rand() % N, y = gen.rand() % N;
			if(board[x][y] == -1 || (gx == x && gy == y)) continue;
 
			int p = board[x][y];
 
			if(p == 0) add_node(x, y);
			else erase_node(x, y);
 
			int diff = score() - current_score;
			double curr_temp = temp(t);
 
			if(diff > 0 || exp(diff / curr_temp) > gen.drand()) {
				current_score += diff;
			}
			else {
				if(p == 0) erase_node(x, y);
				else add_node(x, y);
			}
			
			// debug(x, y, p, score(), current_score, diff);
			if(score() != current_score) break;
			// check();
			cnt++;
		}
		debug(score(), current_score, cnt);
	}
 
};
 
void show_board() {
	rep(i, 0, N) {
		rep(j, 0, N) {
			cout << board[i][j] + 1 << " ";
		}
		cout << "\n";
	}
}
 
void solve() {
	IC['D'] = 0; IC['U'] = 1; IC['R'] = 2; IC['L'] = 3;
	cin >> N >> M >> B;
	cin >> gx >> gy;
	rep(i, 0, M) {
		cin >> RX[i] >> RY[i];
		char c; cin >> c;
		RC[i] = IC[c];
	}
	rep(i, 0, B) {
		int x, y;
		cin >> x >> y;
		board[x][y] = -1;
	}
	SA sa;
	sa.iterate();
	vector<pair<pi, int>> ans;
 
	memset(used, 0, sizeof(used));
	queue<pi> que;
	que.push(pi(gx, gy));
	used[gx][gy] = 1;
 
	while(!que.empty()) {
		pi p = que.front(); que.pop();
		rep(i, 0, 4) {
			int nx = G[p.fst][p.sec][i].fst, ny = G[p.fst][p.sec][i].sec;
			if(nx == -1) continue;
			if(!used[nx][ny]) {
				used[nx][ny] = 1;
				ans.pb(make_pair(pi(nx, ny), inv[i]));
				que.push(pi(nx, ny));
			}
		}
	}
	cout << sz(ans) << "\n";
	rep(i, 0, sz(ans)) {
		cout << ans[i].fst.fst << " " << ans[i].fst.sec << " " << C[ans[i].sec] << "\n";
	}
	debug(sa.score(), bscore);
}
 
 
uint32_t rd() {
	uint32_t res;
#ifdef __MINGW32__
	asm volatile("rdrand %0" :"=a"(res) ::"cc");
#else
	res = std::random_device()();
#endif
	return res;
}
 
int main() {
#ifndef LOCAL
	ios::sync_with_stdio(false);
    cin.tie(0);
#endif
    cout << fixed;
	cout.precision(20);
    cerr << fixed;
	cerr.precision(6);
	rng.seed(rd());
#ifdef LOCAL
	// //freopen("in.txt", "wt", stdout); //for tester
	if(!freopen("input/example_02.txt", "rt", stdin)) return 1;
	// if(!freopen("in.txt", "rt", stdin)) return 1;
#endif	
	solve();
    cerr << "Time: " << timer.get() << " s.\n";
	return 0;
}


