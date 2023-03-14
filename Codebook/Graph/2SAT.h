struct two_sat{
	int n;
	SCC G; // u: u, u + n: ~u
	vector<int>ans;

	two_sat(): two_sat(0) {}
	two_sat(int _n): n(_n), G(2 * _n), ans(_n + 1) {}

	void disjunction(int a, int b){
		G.addEdge((a > n ? a - n : a + n), b);
		G.addEdge((b > n ? b - n : b + n), a);
	}

	bool solve(){
		G.Kosaraju();
		for(int i = 1; i <= n; i++){
			if(G.sccid[i] == G.sccid[i + n])
				return false;
			ans[i] = (G.sccid[i] > G.sccid[i + n]);
		}
		return true;
	}
};
