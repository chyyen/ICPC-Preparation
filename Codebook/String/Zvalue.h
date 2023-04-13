struct Zvalue {
	const string inf = "$"; // character that has never used
	vector<int>z; 

	// s: pattern, t: text => find s in t
	int match(string &s, string &t){
		string fin = s + inf + t;
		build(fin);
		int n = s.size(), m = t.size();
		int ans = 0;
		for(int i = n + 1; i < n + m + 1; i++)
			if(z[i] == n)
				ans++;
		return ans;
	}

	void build(string &s){
		int n = s.size();
		z = vector<int>(n, 0);
		int l = 0, r = 0;
		for(int i = 0; i < n; i++){
			z[i] = max(min(z[i - l], r - i), 0LL);
			while(i + z[i] < n && s[z[i]] == s[i + z[i]])
				l = i, r = i + z[i], z[i]++;
		}
	}
};

