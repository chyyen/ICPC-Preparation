int anc[20][N];
int dis[20][N];
int dep[N];
vector<pair<int, int>>G[N]; // weighted(edge) tree
 
void dfs(int u, int pu = 0){
	for(int i = 1; i < 20; i++){
		anc[i][u] = anc[i - 1][anc[i - 1][u]];
		dis[i][u] = dis[i - 1][u] + dis[i - 1][anc[i - 1][u]];
	}
	for(auto [v, c] : G[u]){
		if(v == pu)
			continue;
		dep[v] = dep[u] + 1;
		anc[0][v] = u;
		dis[0][v] = c;
		dfs(v, u);
	}
}
 
int LCA(int x, int y){
	if(dep[x] < dep[y])
		swap(x, y);
	int diff = dep[x] - dep[y];
	for(int i = 19; i >= 0; i--){
		if(diff - (1 << i) >= 0)
			x = anc[i][x], diff -= (1 << i);
	}
	if(x == y)
		return x;
	for(int i = 19; i >= 0; i--){
		if(anc[i][x] != anc[i][y]){
			x = anc[i][x];
			y = anc[i][y];
		}
	}
	return anc[0][x];
}
