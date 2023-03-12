// ax + by = c
// return (gcd(a, b), x, y)
tuple<long long, long long, long long>exgcd(long long a, long long b){
	if(b == 0)
		return make_tuple(a, 1, 0);
	auto[g, x, y] = exgcd(b, a % b);
	return make_tuple(g, y, x - (a / b) * y);
}