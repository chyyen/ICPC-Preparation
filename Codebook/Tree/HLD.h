struct Heavy_light_decomposition{
	int n;
	int cnt;
	vector<int>dep, sz, mx_son, fa, top;
	vector<int>id, inv_id;
	vector<vector<pii>>G;

	void addEdge(int u, int v, int c){
		G[u].push_back(make_pair(v, c));
		G[v].push_back(make_pair(u, c));
	}

	void dfs1(int x, int px){
		dep[x] = dep[px] + 1;
		sz[x] = 1;
		fa[x] = px;
		for(auto [i, c] : G[x])if(i != px){
			dfs1(i, x);
			sz[x] += sz[i];
			mx_son[x] = (sz[i] > sz[mx_son[x]] ? i : mx_son[x]);
		}
	}
	 
	void dfs2(int x, int root){
		top[x] = root;
		id[x] = ++cnt;
		inv_id[cnt] = x;
		if(mx_son[x])
			dfs2(mx_son[x], root);
		for(auto [i, c] : G[x]){
			if(i != fa[x] && i != mx_son[x])
				dfs2(i, i);
		}
	}
	 
	void decompose(){
		dfs1(1, 0);
		dfs2(1, 1);
		// initialize data structure
	}
	 
	int lca(int u, int v){
		int mx = 0;
		while(top[u] != top[v]){
			if(dep[top[u]] < dep[top[v]])
				swap(u, v);
			u = fa[top[u]];
		}
		if(dep[u]>dep[v])
			swap(u, v);
		return u;
	}

	Heavy_light_decomposition(): Heavy_light_decomposition(0) {}
	Heavy_light_decomposition(int _n): n(_n), cnt(0) {
		dep.resize(_n + 1, 0);
		sz.resize(_n + 1, 0);
		mx_son.resize(_n + 1, 0);
		fa.resize(_n + 1);
		top.resize(_n + 1);
		id.resize(_n + 1);
		inv_id.resize(_n + 1);
		G.resize(_n + 1, vector<pii>(0));
	}
};
