/*

p = r * 2^k + 1

p					r	k	root

998244353			119	23	3
2013265921			15	27	31
2061584302081		15	37	7

*/

template<int MOD, int RT>
struct NTT {
    #define OP(op) static int op(int x, int y)
    OP(add) { return (x += y) >= MOD ? x - MOD : x; }
    OP(sub) { return (x -= y) < 0 ? x + MOD : x; }
    OP(mul) { return ll(x) * y % MOD; } // multiply by bit if p * p > 9e18
    static int mpow(int a, int n) {
        int r = 1;
        while (n) {
            if (n % 2) r = mul(r, a);
            n /= 2, a = mul(a, a);
        }
        return r;
    }
	static const int MAXN = 1 << 21;
    static int minv(int a) { return mpow(a, MOD - 2); }
    int w[MAXN];
    NTT() {
        int s = MAXN / 2, dw = mpow(RT, (MOD - 1) / MAXN);
        for (; s; s >>= 1, dw = mul(dw, dw)) {
            w[s] = 1;
            for (int j = 1; j < s; ++j) 
                w[s + j] = mul(w[s + j - 1], dw);
        }
    }
    void apply(vector<int>&a, int n, bool inv = 0) { 
        for (int i = 0, j = 1; j < n - 1; ++j) {
            for (int k = n >> 1; (i ^= k) < k; k >>= 1);
            if (j < i) swap(a[i], a[j]);
        }
        for (int s = 1; s < n; s <<= 1) {
            for (int i = 0; i < n; i += s * 2) {
                for (int j = 0; j < s; ++j) {
                    int tmp = mul(a[i + s + j], w[s + j]);
                    a[i + s + j] = sub(a[i + j], tmp);
                    a[i + j] = add(a[i + j], tmp);
                }
            }
        }
        if(!inv)
			return;
        int iv = minv(n); 
		if(n > 1)
			reverse(next(a.begin()), a.end());
        for (int i = 0; i < n; ++i)
			a[i] = mul(a[i], iv);
    }
	vector<int>convolution(vector<int>&a, vector<int>&b){
		int sz = a.size() + b.size() - 1, n = 1;
		while(n <= sz)
			n <<= 1; // check n <= MAXN
		vector<int>res(n);
		a.resize(n), b.resize(n);
		apply(a, n);
		apply(b, n);
		for(int i = 0; i < n; i++)
			res[i] = mul(a[i], b[i]);
		apply(res, n, 1);
		return res;
	}
};
