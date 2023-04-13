struct KMP {
	int n;
	string s;
	vector<int>fail; 

	// s: pattern, t: text => find s in t
	int match(string &t){
		int ans = 0, m = t.size(), j = -1;
		for(int i = 0; i < m; i++){
			while(j != -1 && t[i] != s[j + 1])
				j = fail[j];
			if(t[i] == s[j + 1])
				j++;
			if(j == n - 1){
				ans++;
				j = fail[j];
			}
		}
		return ans;
	}
	
	KMP(string &_s){
		s = _s;
		n = s.size();
		fail = vector<int>(n, -1);
		int j = -1;
		for(int i = 1; i < n; i++){
			while(j != -1 && s[i] != s[j + 1])
				j = fail[j];
			if(s[i] == s[j + 1])
				j++;
			fail[i] = j;
		}
	}
};

