long long inv(long long x){ return qpow(x, mod - 2, mod); }

long long mul(long long x, long long y, long long m){
 	x = ((x % m) + m) % m, y = ((y % m) + m) % m;
	long long ans = 0;
	while(y){
		if(y & 1)
			ans = (ans + x) % m;
		x = x * 2 % m;
		y >>= 1; 
	}
	return ans;
}

pii ExCRT(long long r1, long long m1, long long r2, long long m2){
	long long g, x, y;
	tie(g, x, y) = exgcd(m1, m2);
	if((r1 - r2) % g)
		return {-1, -1};
	long long lcm = (m1 / g) * m2;
	long long res = (mul(mul(m1, x, lcm), ((r2 - r1) / g), lcm) + r1) % lcm;
	res = (res + lcm) % lcm;
	return {res, lcm};
}

void solve(){
	long long n, r, m;
	cin >> n;
	cin >> m >> r; // x == r (mod m)
	for(long long i = 1 ; i < n ; i++){
		long long r1, m1;
		cin >> m1 >> r1;
		if(r != -1 && m != -1)
			tie(r, m) = ExCRT(r m, r1, m1);
	}
	if(r == -1 && m == -1)
		cout << "no solution\n";
	else
		cout << r << '\n';
}

