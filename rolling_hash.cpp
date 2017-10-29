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
	cout<<arg<<" ";Debug(rest...);}
template<class T>ostream& operator<< (ostream& out, const vector<T>& v) {
	out<<"[";if(!v.empty()){rep(i,0,sz(v)-1)out<<v[i]<<", ";out<<v.back();}out<<"]";return out;}
template<class S, class T>ostream& operator<< (ostream& out, const pair<S, T>& v) {
	out<<"("<<v.first<<", "<<v.second<<")";return out;}
const int MAX_N = 200010;
const int MAX_V = 100010;
const double eps = 1e-6;
//const ll mod = 1000000007;
const int inf = 1 << 29;
const ll linf = 1LL << 60;
const double PI = 3.14159265358979323846;
///////////////////////////////////////////////////////////////////////////////////////////////////

struct ll3 {
	ll v[3];
	ll3(ll a,ll b,ll c){v[0]=a;v[1]=b;v[2]=c;}
	ll3(ll a){v[0]=a;v[1]=a;v[2]=a;}
	ll3(){v[0]=0;v[1]=0;v[2]=0;}
	inline void operator=(const ll3& vs){rep(i,0,3)v[i]=vs.v[i];}
	inline void operator=(ll a){rep(i,0,3)v[i]=a;}
	inline ll3 operator+(const ll3& vs){ll3 res;rep(i,0,3)res.v[i]=v[i]+vs.v[i];return res;}
	inline ll3 operator-(const ll3& vs){ll3 res;rep(i,0,3)res.v[i]=v[i]-vs.v[i];return res;}
	inline ll3 operator*(const ll3& vs){ll3 res;rep(i,0,3)res.v[i]=v[i]*vs.v[i];return res;}
	inline ll3 operator%(const ll3& vs){ll3 res;rep(i,0,3)res.v[i]=v[i]%vs.v[i];return res;}
	inline void operator+=(const ll3& vs){rep(i,0,3)v[i]+=vs.v[i];}
	inline void operator-=(const ll3& vs){rep(i,0,3)v[i]-=vs.v[i];}
	inline void operator*=(const ll3& vs){rep(i,0,3)v[i]*=vs.v[i];}
	inline void operator%=(const ll3& vs){rep(i,0,3)v[i]%=vs.v[i];}
	inline ll3 operator+(ll a){ll3 res;rep(i,0,3)res.v[i]=v[i]+a;return res;}
	inline ll3 operator-(ll a){ll3 res;rep(i,0,3)res.v[i]=v[i]-a;return res;}
	inline ll3 operator*(ll a){ll3 res;rep(i,0,3)res.v[i]=v[i]*a;return res;}
	inline ll3 operator%(ll a){ll3 res;rep(i,0,3)res.v[i]=v[i]%a;return res;}
	inline void operator+=(ll a){rep(i,0,3)v[i]+=a;}
	inline void operator-=(ll a){rep(i,0,3)v[i]-=a;}
	inline void operator*=(ll a){rep(i,0,3)v[i]*=a;}
	inline void operator%=(ll a){rep(i,0,3)v[i]%=a;}
	inline bool operator==(const ll3& vs){int cnt=0;rep(i,0,3)cnt+=v[i]==vs.v[i];return cnt==3;}
	inline bool operator!=(const ll3& vs){int cnt=0;rep(i,0,3)cnt+=v[i]==vs.v[i];return cnt<=2;}
	friend ostream& operator<<(ostream& out,const ll3& vs){out<<"("<<vs.v[0]<<" "<<vs.v[1]<<" "<<vs.v[2]<<")";return out;}
};
bool operator<=(const ll3& vs1,const ll3& vs2){rep(i,0,3)if(vs1.v[i]!=vs2.v[i])return vs1.v[i]<=vs2.v[i];return true;}
bool operator<(const ll3& vs1,const ll3& vs2){rep(i,0,3)if(vs1.v[i]!=vs2.v[i])return vs1.v[i]<vs2.v[i];return false;}
const ll3 mod = ll3{1000000007, 1000000009, 1000000021};

struct ll2 {
	ll v[2];
	ll2(ll a,ll b){v[0]=a;v[1]=1;}
	ll2(ll a){v[0]=a;v[1]=a;}
	ll2(){v[0]=0;v[1]=0;}
	inline void operator=(const ll2& vs){rep(i,0,2)v[i]=vs.v[i];}
	inline void operator=(ll a){rep(i,0,2)v[i]=a;}
	inline ll2 operator+(const ll2& vs){ll2 res;rep(i,0,2)res.v[i]=v[i]+vs.v[i];return res;}
	inline ll2 operator-(const ll2& vs){ll2 res;rep(i,0,2)res.v[i]=v[i]-vs.v[i];return res;}
	inline ll2 operator*(const ll2& vs){ll2 res;rep(i,0,2)res.v[i]=v[i]*vs.v[i];return res;}
	inline ll2 operator/(const ll2& vs){ll2 res;rep(i,0,2)res.v[i]=v[i]/vs.v[i];return res;}
	inline ll2 operator%(const ll2& vs){ll2 res;rep(i,0,2)res.v[i]=v[i]%vs.v[i];return res;}
	inline void operator+=(const ll2& vs){rep(i,0,2)v[i]+=vs.v[i];}
	inline void operator-=(const ll2& vs){rep(i,0,2)v[i]-=vs.v[i];}
	inline void operator*=(const ll2& vs){rep(i,0,2)v[i]*=vs.v[i];}
	inline void operator/=(const ll2& vs){rep(i,0,2)v[i]/=vs.v[i];}
	inline void operator%=(const ll2& vs){rep(i,0,2)v[i]%=vs.v[i];}
	inline ll2 operator+(ll a){ll2 res;rep(i,0,2)res.v[i]=v[i]+a;return res;}
	inline ll2 operator-(ll a){ll2 res;rep(i,0,2)res.v[i]=v[i]-a;return res;}
	inline ll2 operator*(ll a){ll2 res;rep(i,0,2)res.v[i]=v[i]*a;return res;}
	inline ll2 operator/(ll a){ll2 res;rep(i,0,2)res.v[i]=v[i]/a;return res;}
	inline ll2 operator%(ll a){ll2 res;rep(i,0,2)res.v[i]=v[i]%a;return res;}
	inline void operator+=(ll a){rep(i,0,2)v[i]+=a;}
	inline void operator-=(ll a){rep(i,0,2)v[i]-=a;}
	inline void operator*=(ll a){rep(i,0,2)v[i]*=a;}
	inline void operator/=(ll a){rep(i,0,2)v[i]/=a;}
	inline void operator%=(ll a){rep(i,0,2)v[i]%=a;}
	inline bool operator==(const ll2& vs){int cnt=0;rep(i,0,2)cnt+=v[i]==vs.v[i];return cnt==2;}
	inline bool operator!=(const ll2& vs){int cnt=0;rep(i,0,2)cnt+=v[i]==vs.v[i];return cnt<=1;}
	friend ostream& operator<<(ostream& out,const ll2& vs){out<<"("<<vs.v[0]<<" "<<vs.v[1]<<" "<<vs.v[2]<<")";return out;}
};

bool operator<=(const ll2& vs1,const ll2& vs2){rep(i,0,2)if(vs1.v[i]!=vs2.v[i])return vs1.v[i]<=vs2.v[i];return true;}
bool operator<(const ll2& vs1,const ll2& vs2){rep(i,0,2)if(vs1.v[i]!=vs2.v[i])return vs1.v[i]<vs2.v[i];return false;}
//const ll2 mod = ll2{1000000007, 1000000009};
void solve() {

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

