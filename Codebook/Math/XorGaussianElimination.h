pair<int, vector<bool>> GaussElimination(int n, int m)  {
	// m = # of variable, n = # of equation, return solution of system
	// X[0][0] + X[0][1] ... + X[0][m - 1] = X[0][m]
	// ... to X[n - 1]
	// has solution => return solution, no solution => return empty vector
	int sol_num = 1;
	vector<int>where(m, -1);

	for(int col = 0, row = 0; col < m && row < n; col++){
		for(int i = row; i < n; i++){
			if(X[i][col]){
				swap(X[i], X[row]);
				break;
			}
		}
		if(!X[row][col]){
			sol_num = 2;
			continue;
		}
		where[col] = row;
		for(int i = 0; i < n; i++){
			if(i != row && X[i][col])
				X[i] ^= X[row];	
		}
		row++;
	}
	vector<bool>ans(m, 0);
	for (int i = 0; i < m; i++){ //
        if (where[i] != -1)
            ans[i] = (X[where[i]][m] ? 1 : 0);
	}
    for (int i = 0; i < n; i++) {
		bool sum = X[i][m];
        for (int j = 0; j < m; j++)
			sum ^= (X[i][j] && ans[j]);
		if(sum)
            return make_pair(0, vector<bool>(0));
    }

    for (int i = 0; i < m; i++)
        if (where[i] == -1)
			sol_num = 2;
	return make_pair(sol_num, ans);
}
