int dep[N], low[N];
vector<int>G[N];
vector<pair<int, int>>bridge;

void init(){
	for(int i = 1; i <= n; i++){
		G[i].clear();
		dep[i] = low[i] = -1;
	}
	dep[1] = low[1] = 0;
}

void tarjan(int x, int px){
	for(auto i : G[x]){
		if(dep[i] == -1){
			dep[i] = low[i] = dep[x] + 1;
			tarjan(i, x);
			low[x] = min(low[x], low[i]);
			if(low[i] > dep[x])
				bridge.push_back(make_pair(i, x));
		}
		else if(i != px)
			low[x] = min(low[x], dep[i]);
	}
}
