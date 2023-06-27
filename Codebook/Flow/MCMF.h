struct MCMF{
	struct Edge{
		int from, to;
		int cap, cost;
		Edge(int f, int t, int ca, int co): from(f), to(t), cap(ca), cost(co) {}
	};	

	int n, s, t;
	vector<Edge>edges;
	vector<vector<int>>G;
	vector<int>d;
	vector<int>in_queue, prev_edge;

	MCMF(){}
	MCMF(int _n, int _s, int _t): n(_n), G(_n + 1), d(_n + 1), in_queue(_n + 1), prev_edge(_n + 1), s(_s), t(_t) {}

	void addEdge(int u, int v, int cap, int cost){
		G[u].push_back(edges.size());
		edges.push_back(Edge(u, v, cap, cost));
		G[v].push_back(edges.size());
		edges.push_back(Edge(v, u, 0, -cost));
	}

	bool bfs(){
		bool found = false;
		fill(d.begin(), d.end(), (int)1e18+10);
		fill(in_queue.begin(), in_queue.end(), false);
		d[s] = 0;
		in_queue[s] = true;
		queue<int>q;
		q.push(s);
		while(!q.empty()){
			int u = q.front();
			q.pop();
			if(u == t)
				found = true;
			in_queue[u] = false;
			for(auto &id : G[u]){
				Edge e = edges[id];
				if(e.cap > 0 && d[u] + e.cost < d[e.to]){
					d[e.to] = d[u] + e.cost;
					prev_edge[e.to] = id;
					if(!in_queue[e.to]){
						in_queue[e.to] = true;
						q.push(e.to);
					}
				}
			}
		}
		return found;
	}
	
	pair<int, int>flow(){ 
		// return (cap, cost)
		int cap = 0, cost = 0;
		while(bfs()){
			int send = (int)1e18 + 10;
			int u = t;
			while(u != s){
				Edge e = edges[prev_edge[u]];
				send = min(send, e.cap);
				u = e.from;
			}
			u = t;
			while(u != s){
				Edge &e = edges[prev_edge[u]];
				e.cap -= send;
				Edge &e2 = edges[prev_edge[u] ^ 1];
				e2.cap += send;
				u = e.from;
			}
			cap += send;
			cost += send * d[t];
		}
		return make_pair(cap, cost);
	}
};
