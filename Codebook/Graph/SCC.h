struct SCC{
	int n;
	int cnt;
	vector<vector<int>>G, revG;
	vector<int>stk, sccid;
	vector<bool>vis;

	SCC(): SCC(0) {}
	SCC(int _n): n(_n), G(_n + 1), revG(_n + 1), sccid(_n + 1), vis(_n + 1), cnt(0) {}

	void addEdge(int u, int v){
		// u -> v
		assert(u > 0 && u <= n);
		assert(v > 0 && v <= n);
		G[u].push_back(v);
		revG[v].push_back(u);
	}

	void dfs1(int u){
		vis[u] = 1;
		for(int v : G[u]){
			if(!vis[v])
				dfs1(v);
		}
		stk.push_back(u);
	}

	void dfs2(int u, int k){
		vis[u] = 1;
		sccid[u] = k;
		for(int v : revG[u]){
			if(!vis[v])
				dfs2(v, k);
		}
	}

	void Kosaraju(){
		for(int i = 1; i <= n; i++)
			if(!vis[i])
				dfs1(i);
		fill(vis.begin(), vis.end(), 0);
		while(!stk.empty()){
			if(!vis[stk.back()])
				dfs2(stk.back(), ++cnt);
			stk.pop_back();
		}
	}
};
