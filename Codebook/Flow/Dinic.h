/**
* After computing flow, edges $\{u,v\}$ s.t
* $lev[u] \neq -1,$ $lev[v] = -1$ are part of min cut.
* Use \texttt{reset} and \texttt{rcap} for Gomory-Hu.
* Time: $O(N^2M)$ flow
* $O(M\sqrt N)$ bipartite matching
* $O(NM\sqrt N) or $O(NM\sqrtM) on unit graph.
 */

struct Dinic {
    using F = long long; // flow type
    struct Edge { int to; F flo, cap; };
    int N; 
	vector<Edge> eds; 
	vector<vector<int>> adj;
    void init(int _N) {
        N = _N; adj.resize(N), cur.resize(N);
    }
    void reset() {
        for (auto &e: eds) e.flo = 0;
    }
    void ae(int u, int v, F cap, F rcap = 0) { 
        assert(min(cap,rcap) >= 0);
        adj[u].pb((int)eds.size()); 
		eds.pb({v, 0, cap});
        adj[v].pb((int)eds.size()); 
		eds.pb({u, 0, rcap});
    }
    vector<int>lev;
	vector<vector<int>::iterator> cur;
    // level = shortest distance from source
    bool bfs(int s, int t) {
        lev = vector<int>(N,-1);
        for(int i = 0; i < N; i++) cur[i] = begin(adj[i]);
        queue<int> q({s}); lev[s] = 0;
        while (!q.empty()) { 
            int u = q.front(); q.pop();
            for (auto &e: adj[u]) { 
                const Edge& E = eds[e];
                int v = E.to; 
                if (lev[v] < 0 && E.flo < E.cap)
                    q.push(v), lev[v] = lev[u]+1;
            }
        }
        return lev[t] >= 0;
    }
    F dfs(int v, int t, F flo) {
        if (v == t) return flo;
        for (; cur[v] != end(adj[v]); cur[v]++) {
            Edge& E = eds[*cur[v]];
            if (lev[E.to]!=lev[v]+1||E.flo==E.cap) continue;
            F df = dfs(E.to,t,min(flo,E.cap-E.flo));
            if (df) {
                E.flo += df;
                eds[*cur[v]^1].flo -= df;
                return df;
            } // saturated >=1 one edge
        }
        return 0;
    }
    F maxFlow(int s, int t) {
        F tot = 0;
        while (bfs(s,t)) while (F df =
			dfs(s,t,numeric_limits<F>::max()))
				tot += df;
        return tot;
    }
    int fp(int u, int t,F f, vector<int> &path, vector<F> &flo, vector<int> &vis) {
        vis[u] = 1;
        if (u == t) {
            path.pb(u);
            return f;
        }
        for (auto eid: adj[u]) {
            auto &e = eds[eid];
            F w = e.flo - flo[eid];
            if (w <= 0 || vis[e.to]) continue;
            w = fp(e.to, t, 
				min(w, f), path, flo, vis);
            if (w) {
                flo[eid] += w, path.pb(u);
                return w;
            }
        }
        return 0;
    }
	// return collection of {bottleneck, path[]}
    vector<pair<F, vector<int>>> allPath(int s, int t) { 
        vector<pair<F, vector<int>>> res; vector<F> flo((int)eds.size());
		vector<int> vis;
        do res.pb(mp(0, vector<int>()));
        while (res.back().first = 
			fp(s, t, numeric_limits<F>::max(),
			res.back().second, flo, vis=vector<int>(N))
		);
        for (auto &p: res) reverse(all(p.second));
        return res.pop_back(), res;
    }
};
