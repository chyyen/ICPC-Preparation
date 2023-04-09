struct Disjoint_set{
	int n;
	vector<int>sz, p;

	int fp(int x){
		return (p[x] == -1 ? x : p[x] = fp(p[x]));
	}

	bool U(int x, int y){
		x = fp(x), y = fp(y);
		if(x == y)
			return false;
		if(sz[x] > sz[y])
			swap(x, y);
		p[x] = y;
		sz[y] += sz[x];
		return true;
	}

	Disjoint_set() {}
	Disjoint_set(int _n){
		n = _n;
		sz.resize(n, 1);
		p.resize(n, -1);
	}
};
