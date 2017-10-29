#include <bits/stdc++.h>
#define ADD(a, b) a = (a + ll(b)) % mod
#define MUL(a, b) a = (a * ll(b)) % mod
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
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vl> mat;
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

struct T {
	ll v;
	T(ll v = inf) : v(v) {}
	T operator+(const T& t) { return T(min(v, t.v)); }
	friend ostream& operator<<(ostream& out, const T& t) {
		out << t.v; return out;
	}
};

struct segtree{
	int n; vector<T> seg;
	void init(int mx) {
		n = 1;
		while(n < mx) n *= 2;
		seg = vector<T>(n * 2);
	}
	segtree(int mx = 0) {
		init(mx);
	}
	void update(int i, T x) {
		i += n - 1;
		seg[i] = x;
		while(i > 0) {
			i = (i - 1) / 2;
			seg[i] = seg[i * 2 + 1] + seg[i * 2 + 2];
		}
	}
	T ga(int a, int b, int k, int l, int r) {
		if(b <= l || r <= a) return T();
		if(a <= l && r <= b) return seg[k];
		else {
			T lv = ga(a, b, k * 2 + 1, l, (l + r) / 2);
			T rv = ga(a, b, k * 2 + 2, (l + r) / 2, r);
			return lv + rv;
		}
	}
	void show() {
		vector<T> tmp;
		rep(i, 0, n) tmp.push_back(get(i, i + 1));
		debug(tmp);
	}
	//edit from here
	T get(int a, int b) { return ga(a, b, 0, 0, n); } //[a, b)
};

struct SA { //get_sa: don't forget to specify K. default:26
	int n;
	vi S, sa, rank, bkt; //i in S is rank[i] in sa
	vi lcp; segtree seg;
	void init(const vi& sin, int K = 26) {
		n = (int)sin.size();
		S.resize(n + 1); rank.resize(n + 1);
		rep(i, 0, n) S[i] = sin[i] + 1;
		bkt.resize(max(n + 1, K + 1));
		sa = get_sa(S, K + 1);
		rep(i, 0, n + 1) rank[sa[i]] = i;
		get_lcp(); //if you don't want lcp, comment out
		// seg.init(n); //if you don't want seg, comment out
		// rep(i, 0, n) seg.update(i, lcp[i]);
	}
	inline bool isLMS(const vi& t, int i) {
		if(i > 0 && t[i] && !t[i - 1]) return true;
		else return false;
	}
	void getBuckets(const vi& s, int K, bool end) {
		int sum = 0, n = (int)s.size();
		fill(bkt.begin(), bkt.begin() + K, 0);
		rep(i, 0, n) bkt[s[i]]++;
		rep(i, 0, K) {
			sum += bkt[i];
			bkt[i] = end ? sum : sum - bkt[i];
		}
	}
	void induceSAl(const vi& t, const vi& s, vi& SA, int K) {
		int n = (int)SA.size();
		getBuckets(s, K, false);
		rep(i, 0, n) {
			int j = SA[i] - 1;
			if(j >= 0 && !t[j]) SA[bkt[s[j]]++] = j;
		}
	}
	void induceSAs(const vi& t, const vi& s, vi& SA, int K) {
		int n = (int)SA.size();
		getBuckets(s, K, true);
		rer(i, n, 0) {
			int j = SA[i] - 1;
			if(j >= 0 && t[j]) SA[--bkt[s[j]]] = j;
		}
	}
	vi get_sa(const vi& s, int K) {
		int n = (int)s.size();
		vi t(n, 0);
		t[n - 1] = 1; t[n - 2] = 0;
		rer(i, n - 2, 0) 
			if(s[i] < s[i + 1] || (s[i] == s[i + 1] && t[i + 1] == 1)) t[i] = 1;
		getBuckets(s, K, true);
		vi SA(n, -1);
		rep(i, 1, n) if(isLMS(t, i)) SA[--bkt[s[i]]] = i;
		induceSAl(t, s, SA, K); induceSAs(t, s, SA, K);
		int n1 = 0;
		rep(i, 0, n) if(isLMS(t, SA[i])) SA[n1++] = SA[i];
		fill(SA.begin() + n1, SA.end(), -1);
		int name = 0, prev = -1;
		rep(i, 0, n1) {
			int pos = SA[i]; bool diff = false;
			rep(d, 0, n) {
				if(prev == -1 || s[pos + d] != s[prev + d] || t[pos + d] != t[prev + d]) {
					diff = true; break;
				}
				else if(d > 0 && (isLMS(t, pos + d) || isLMS(t, prev + d))) break;
			}
			if(diff) { name++; prev = pos; }
			pos = (pos % 2 == 0) ? pos / 2 : (pos - 1) / 2;
			SA[n1 + pos] = name - 1;
		}
		vi s1(n1, -1), SA1(n1, -1), p1(n1, -1);
		int at = 0;
		rep(i, n1, n) if(SA[i] >= 0) s1[at++] = SA[i];
		if(name < n1) SA1 = get_sa(s1, name);
		else rep(i, 0, n1) SA1[s1[i]] = i;
		getBuckets(s, K, true);
		at = 0;
		rep(i, 1, n) if(isLMS(t, i)) p1[at++] = i;
		fill(all(SA), -1);
		rer(i, n1, 0) {
			int j = p1[SA1[i]];
			SA[--bkt[s[j]]] = j;
		}
		induceSAl(t, s, SA, K); induceSAs(t, s, SA, K);
		return SA;
	}
	void get_lcp() {
		lcp.resize(n);
		int h = 0; lcp[0] = 0;
		rep(i, 0, n) {
			int j = sa[rank[i] - 1]; if(h > 0) h--;
			while(j + h < n && i + h < n && S[j + h] == S[i + h]) h++;
			lcp[rank[i] - 1] = h;
		}
	}
	int common(int i, int j) {
		if(i == j) return n - i;
		else {
			int a = rank[i], b = rank[j];
			if(a > b) swap(a, b);
			return seg.get(a, b).v;
		}
	}
};


vi str_to_vec(const string& s1) {
	int n = (int)s1.size();
	vi res(n, 0);
	rep(i, 0, n) res[i] = s1[i] - 'a';
	return res;
}

void solve() {
	string m = "abracadabra";
	vi vec = str_to_vec(m);
	SA sa; sa.init(vec, 26);
	debug(sa.S);
	debug(sa.sa);
	debug(sa.rank);
	debug(sa.lcp);
}

int main() {
#ifndef LOCAL
	ios::sync_with_stdio(false);
    cin.tie(0);
#endif
    cout << fixed;
	cout.precision(20);
#ifdef LOCAL
    freopen("in.txt", "rt", stdin);
#endif	
	solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
	return 0;
}

