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
#define mem(x,i) memset((x),(i),sizeof((x)))
 
using namespace std;
//using namespace __gnu_pbds;
using pii = pair<long long,long long>;
using ld = long double;
using ll = long long;
 
mt19937 mtrd(chrono::steady_clock::now().time_since_epoch().count());
 
const int mod = 1000000007;
const int mod2 = 998244353;
const ld PI = acos(-1);
 
#define Bint __int128
#define int long long

namespace DEBUG {
	template <typename T>
	ostream& operator<<(ostream& os, const vector<T>& V) {
		os << "[ ";
		for (const auto& vv : V)
			os << vv << ", ";
		os << "]";
		return os;
	}

	template <typename T>
	inline void _debug(const char* format, T t) {
		cerr << format << '=' << t << endl;
	}
	
	template <class First, class... Rest>
	inline void _debug(const int idx, const char* format, First first, Rest... rest) {
		if(idx == 1)
			cerr << "DEBUG: ";
		while (*format != ',')
			cerr << *format++;
		cerr << '=' << first << ",";
		_debug(idx + 1, format + 1, rest...);
	}

	#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

/* ----------------------------------------  */
 
 
void solve(){

}
 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t = 1; 
	//cin >> t;
	while(t--)
		solve();
}
