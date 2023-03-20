struct Suffix_Array{
	int n, m; // m is the range of s
	string s;
	vector<int>sa, rk, lcp;

	Suffix_Array(): Suffix_Array(0, 0, "") {};
	Suffix_Array(int _n, int _m, string _s): n(_n), m(_m), sa(_n), rk(_n), lcp(_n), s(_s) {}

	void Sort(int k, vector<int>&bucket, vector<int>&idx, vector<int>&lst){
		for(int i = 0; i < m; i++)
			bucket[i] = 0;
		for(int i = 0; i < n; i++)
			bucket[lst[i]]++;
		for(int i = 1; i < m; i++)
			bucket[i] += bucket[i-1];
		int p = 0;
		// update index
		for(int i = n - k; i < n; i++)
			idx[p++] = i;
		for(int i = 0; i < n; i++)
			if(sa[i] >= k)
				idx[p++] = sa[i] - k;
		for(int i = n - 1; i >= 0; i--)
			sa[--bucket[lst[idx[i]]]] = idx[i];
	}
	void build(){
		vector<int>idx(n), lst(n), bucket(max(n, m));
		for(int i = 0; i < n; i++)
			bucket[lst[i] = (s[i] - 'a')]++; 
		for(int i = 1; i < m; i++)
			bucket[i] += bucket[i - 1];
		for(int i = n - 1; i >= 0; i--)
			sa[--bucket[lst[i]]] = i;
		for(int k = 1; k < n; k <<= 1){
			Sort(k, bucket, idx, lst);
			// update rank
			int p = 0;
			idx[sa[0]] = 0;
			for(int i = 1; i < n; i++){
				int a = sa[i], b = sa[i - 1];
				if(lst[a] == lst[b] && a + k < n && b + k < n && lst[a + k] == lst[b + k]);
				else
					p++;
				idx[sa[i]] = p;
			}
			if(p == n - 1)
				break;
			for(int i = 0; i < n; i++)
				lst[i] = idx[i];
			m = p + 1;
		}
		for(int i = 0; i < n; i++)
			rk[sa[i]] = i;
		buildLCP();
	}
	void buildLCP(){
		// lcp[rk[i]] >= lcp[rk[i - 1]] - 1
		int v = 0;
		for(int i = 0; i < n; i++){
			if(!rk[i])
				lcp[rk[i]] = 0;
			else{
				if(v)
					v--;
				int p = sa[rk[i] - 1];
				while(i + v < n && p + v < n && s[i + v] == s[p + v])
					v++;
				lcp[rk[i]] = v;
			}
		}
	}
};
