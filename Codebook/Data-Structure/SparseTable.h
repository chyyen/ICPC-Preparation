template <class T, T (*op)(T, T)> struct SparseTable{
	// idx: [0, n - 1]
	int n;
	T id;
	vector<vector<T>>tbl;

	T query(int l, int r){
		int lg = __lg(r - l + 1);
		return op(tbl[lg][l], tbl[lg][r - (1 << lg) + 1]);
	}

	SparseTable (): n(0) {}
	SparseTable (int _n, vector<T>&arrr, T _id) {
		n = _n;
		id = _id;
		int lg = __lg(n) + 2;
		tbl.resize(lg, vector<T>(n + 5, id));
		for(int i = 0; i < n; i++)
			tbl[0][i] = arrr[i];
		for(int i = 1; i <= lg; i++)
			for(int j = 0; j + (1 << (i - 1)) < n; j++)
				tbl[i][j] = op(tbl[i - 1][j], tbl[i - 1][j + (1 << (i - 1))]);
	}
	SparseTable (int _n, T *arrr, T _id) {
		n = _n;
		id = _id;
		int lg = __lg(n) + 2;
		tbl.resize(lg, vector<T>(n + 5, id));
		for(int i = 0; i < n; i++)
			tbl[0][i] = arrr[i];
		for(int i = 1; i <= lg; i++)
			for(int j = 0; j + (1 << (i - 1)) < n; j++)
				tbl[i][j] = op(tbl[i - 1][j], tbl[i - 1][j + (1 << (i - 1))]);
	}
};
