int cnt;
int dep[N], low[N]; // dep == -1 -> unvisited
vector<int>G[N], rstree[2 * N]; // 1 ~ n: round, n + 1 ~ 2n: square
vector<int>stk;

void init(){
    cnt = n;
    for(int i = 1; i <= n; i++){
        G[i].clear();
        rstree[i].clear();
        rstree[i + n].clear();
        dep[i] = low[i] = -1;
    }
    dep[1] = low[1] = 0;
}

void tarjan(int x, int px){
    stk.push_back(x);
    for(auto i : G[x]){
        if(dep[i] == -1){
            dep[i] = low[i] = dep[x] + 1;
            tarjan(i, x);
            low[x] = min(low[x], low[i]);
            if(dep[x] <= low[i]){
                sz[++cnt] = 0;
                int z;
                do{
                    z = stk.back();
                    rstree[cnt].push_back(z);
                    rstree[z].push_back(cnt);
                    stk.pop_back();
                }while(z != i);
                rstree[cnt].push_back(x);
                rstree[x].push_back(cnt);
            }
        }
        else if(i != px)
            low[x] = min(low[x], dep[i]);
    }
}

