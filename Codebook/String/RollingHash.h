struct Rolling_Hash{
	int n;
	const int P[5] = {146672737, 204924373, 585761567, 484547929, 116508269};
	const int M[5] = {922722049, 952311013, 955873937, 901981687, 993179543};
	vector<int>PW[5], pre[5], suf[5];
	
	Rolling_Hash(): Rolling_Hash("") {}
	Rolling_Hash(string s): n(s.size()){
		for(int i = 0; i < 5; i++){
			PW[i].resize(n), pre[i].resize(n), suf[i].resize(n);
			PW[i][0] = 1, pre[i][0] = s[0];
			suf[i][n - 1] = s[n - 1];
		}
		for(int i = 1; i < n; i++){
			for(int j = 0; j < 5; j++){
				PW[j][i] = PW[j][i - 1] * P[j] % M[j];
				pre[j][i] = (pre[j][i - 1] * P[j] + s[i]) % M[j];
			}
		}
		for(int i = n - 2; i >= 0; i--){
			for(int j = 0; j < 5; j++)
				suf[j][i] = (suf[j][i + 1] * P[j] + s[i]) % M[j];
		}
	}

	int _substr(int k, int l, int r) {
		int res = pre[k][r];
		if(l > 0) 
			res -= 1LL * pre[k][l - 1] * PW[k][r - l + 1] % M[k];
		if(res < 0) 
			res += M[k];
		return res;
	}

	vector<int>substr(int l, int r){
		vector<int>res(5);
		for(int i = 0; i < 5; ++i)
			res[i] = _substr(i, l, r);
		return res;
	}
};
