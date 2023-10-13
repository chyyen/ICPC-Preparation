#include<bits/stdc++.h>
#include<bits/extc++.h>
 
#define F first
#define S second
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof pop_front
#define mp make_pair
#define mt make_tuple
#define all(x) (x).begin(),(x).end()
 
using namespace std;
//using namespace __gnu_pbds;
using pii = pair<long long,long long>;
using ld = long double;
using ll = long long;
 
mt19937 mtrd(chrono::steady_clock::now() \
.time_since_epoch().count());
 
const int mod = 1000000007;
const int mod2 = 998244353;
const ld PI = acos(-1);
 
#define Bint __int128
#define int long long

template <typename T>
inline void printv(T l, T r){
	cerr << "[ ";
	for(; l != r; l++)
		cerr << *l << ", ";
	cerr << "]" << endl;
}

#define TEST
#ifdef TEST
#define de(x) cerr << #x << '=' << x << ", "
#define ed cerr << '\n';
#else
#define de(x) void(0)
#define ed void(0)
#define printv(...) void(0)
#endif


/* ----------------------------------------  */
 

void solve(){

}
 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t = 1; 
	// cin >> t;
	while(t--)
		solve();
}

