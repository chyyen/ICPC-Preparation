long long qpow(long long x, long long powcnt, long long tomod){
	long long res = 1;
	for(; powcnt ; powcnt >>= 1 , x = (x * x) % tomod)
		if(1 & powcnt)
			res = (res * x) % tomod;
	return (res % tomod);
}