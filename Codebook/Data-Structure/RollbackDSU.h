struct Rollback_DSU{
	vector<int>p, sz;
	vector<pair<int, int>>history;

	int fp(int x){
		while(p[x] != -1)
			x = p[x];
		return x;
	}

	bool U(int x, int y){
		x = fp(x), y = fp(y);
		if(x == y){
			history.push_back(make_pair(-1, -1));
			return false;
		}
		if(sz[x] > sz[y])
			swap(x, y);
		p[x] = y;
		sz[y] += sz[x];
		history.push_back(make_pair(x, y));
		return true;
	}

	void undo(){
		if(his.empty() || history.back().F == -1)
			return;
		auto [x, y] = history.back();
		history.pop_back();
		p[x] = -1;
		sz[y] -= sz[x];
	}

	Rollback_DSU(): Rollback_DSU(0) {}

	Rollback_DSU(int n): p(n), sz(n) {
		fill(p.begin(), p.end(), -1);
		fill(sz.begin(), sz.end(), 1);
	}
};
