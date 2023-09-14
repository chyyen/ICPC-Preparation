void PollardRho(map<long long, int>& mp, long long n) {
	if(n == 1) return;
	if(is_prime(n)) return mp[n]++, void();
	if(n % 2 == 0) {
		mp[2] += 1;
		PollardRho(mp, n / 2);
		return;
	}
	ll x = 2, y = 2, d = 1, p = 1;
	#define f(x, n, p) ((__int128(x) * x % n + p) % n)
	while(1) {
		if(d != 1 && d != n) {
			PollardRho(mp, d);
			PollardRho(mp, n / d);
			return;
		}
		p += (d == n);
		x = f(x, n, p), y = f(f(y, n, p), n, p);
		d = __gcd(abs(x - y), n);
	}
	#undef f
}

vector<long long> get_divisors(long long n) {
	if(n == 0) return {};
	map<long long, int> mp;
	PollardRho(mp, n);
	vector<pair<long long, int>> v(mp.begin(), mp.end());
	vector<long long> res;
	auto f = [&](auto f, int i, long long x) -> void {
		if(i == (int)v.size()) {
			res.pb(x);
			return;
		}
		for(int j = v[i].second; ; j--) {
			f(f, i + 1, x);
			if(j == 0) break;
			x *= v[i].first;
		}
	};
	f(f, 0, 1);
	sort(res.begin(), res.end());
	return res;
}
