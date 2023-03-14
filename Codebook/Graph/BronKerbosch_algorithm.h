vector<vector<int>>maximal_clique;
int cnt, G[N][N], all[N][N], some[N][N], none[N][N];

void dfs(int d, int an, int sn, int nn)
{
    if(sn == 0 && nn == 0){
		vector<int>v;
		for(int i = 0; i < an; i++)
			v.push_back(all[d][i]);
		maximal_clique.push_back(v);
		cnt++;
    }
	int u = sn > 0 ? some[d][0] : none[d][0];
    for(int i = 0; i < sn; i ++)
    {
        int v = some[d][i];
        if(G[u][v])
			continue;
        int tsn = 0, tnn = 0;
        for(int j = 0; j < an; j ++)
			all[d + 1][j] = all[d][j];
        all[d + 1][an] = v;
        for(int j = 0; j < sn; j ++)
            if(g[v][some[d][j]])
				some[d + 1][tsn ++] = some[d][j];
        for(int j = 0; j < nn; j ++)
            if(g[v][none[d][j]]) 
				none[d + 1][tnn ++] = none[d][j];
        dfs(d + 1, an + 1, tsn, tnn);
        some[d][i] = 0, none[d][nn ++] = v;
    }
}
void process(){
    cnt = 0;
    for(int i = 0; i < n; i ++)
		some[0][i] = i + 1;
    dfs(0, 0, n, 0);
}
