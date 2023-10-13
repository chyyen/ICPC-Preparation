template <class T> struct SparseTable{
	// idx: [0, n - 1]
	int n;
	T id;
	vector<vector<T>>tbl;

	T op(T lhs, T rhs){
		// write your mege function	
	}

	T query(int l, int r){
		int lg = __lg(r - l + 1);
		return op(tbl[lg][l], tbl[lg][r - (1 << lg) + 1]);
	}

	SparseTable (): n(0) {}
	template<typename iter_t>	
	SparseTable (int _n, iter_t l, iter_t r, T _id) {
		n = _n;
		id = _id;
		int lg = __lg(n) + 2;
		tbl.resize(lg, vector<T>(n + 5, id));
		iter_t ptr = l;
		for(int i = 0; i < n; i++, ptr++){
			assert(ptr != r);
			tbl[0][i] = *ptr;
		}
		for(int i = 1; i <= lg; i++)
			for(int j = 0; j + (1 << (i - 1)) < n; j++)
				tbl[i][j] = op(tbl[i - 1][j], tbl[i - 1][j + (1 << (i - 1))]);
	}
};
