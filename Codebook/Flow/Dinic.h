struct Max_Flow{
	struct Edge{
		int cap, to, rev;
		Edge(){}
		Edge(int _to, int _cap, int _rev){
			to = _to, cap = _cap, rev = _rev;
		}
	};
	const int inf = 1e18+10;
	int s, t; // start node and end node
	vector<vector<Edge>>G;
	vector<int>dep;
	vector<int>iter;
	void addE(int u, int v, int cap){
		G[u].pb(Edge(v, cap, G[v].size()));
		// direct graph
    G[v].pb(Edge(u, 0, G[u].size() - 1));
    // undirect graph
    // G[v].pb(Edge(u, cap, G[u].size() - 1));
  }
	void bfs(){
		queue<int>q;
		q.push(s);
		dep[s] = 0;
		while(!q.empty()){
			int cur = q.front();
			q.pop();
			for(auto i : G[cur]){
				if(i.cap > 0 && dep[i.to] == -1){
					dep[i.to] = dep[cur] + 1;
					q.push(i.to);
				}
			}
		}
	}
	int dfs(int x, int fl){
		if(x == t)
			return fl;
		for(int _ = iter[x] ; _ < G[x].size() ; _++){
			auto &i = G[x][_];
			if(i.cap > 0 && dep[i.to] == dep[x] + 1){
				int res = dfs(i.to, min(fl, i.cap));
				if(res <= 0)
					continue;
				i.cap -= res;
				G[i.to][i.rev].cap += res;
				return res;
			}
			iter[x]++;
		}
		return 0;
	}
	int Dinic(){
		int res = 0;
		while(true){
			fill(all(dep), -1);
			fill(all(iter), 0);
			bfs();
			if(dep[t] == -1)
				break;
			int cur;
			while((cur = dfs(s, INF)) > 0)
				res += cur;
		}
		return res;
	}

	void init(int _n, int _s, int _t){
		s = _s, t = _t;
		G.resize(_n + 5);
		dep.resize(_n + 5);
		iter.resize(_n + 5);
	}
};
