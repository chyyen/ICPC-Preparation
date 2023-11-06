template<class T, int SZ> struct LazySeg { // SZ must be power of 2
	// depends
	T tID, ID; 
	T seg[SZ * 2], lazy[SZ * 2];
	T cmb(T a, T b) {
		return max(a, b); 
	}

	LazySeg(T id, T tid): ID(id), tID(tid) { 
		for(int i = 0; i < SZ * 2; i++)
			seg[i] = ID, lazy[id] = tID;
	}

	void addtag(int l, int r, int ind, int v){
		if(lazy[ind] == tID)
			lazy[ind] = v;
		else
			lazy[ind] += v;
	}
	/// modify values for current node
	void push(int ind, int L, int R) { 
		// dependent on operation
		if(lazy[ind] == tID)
			return;
		seg[ind] += lazy[ind]; 
		if(L != R){
			int mid = (L + R) >> 1;
			addtag(L, mid, ind << 1, lazy[ind]);
			addtag(mid + 1, R, ind << 1 | 1, lazy[ind]);
		}
		lazy[ind] = tID; 
	}
	void pull(int ind){
		seg[ind] = cmb(seg[ind << 1], seg[ind << 1 | 1]);
	}
	void upd(int lo, int hi, T v, int ind = 1, int L = 0, int R = SZ - 1) {
		push(ind, L, R); 
		if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) { 
			addtag(L, R, ind, v);	
			push(ind, L, R); return;
		}
		int mid = (L + R) >> 1; 
		upd(lo, hi, v, ind << 1, L, mid); 
		upd(lo, hi, v, ind << 1 | 1, mid + 1, R); 
		pull(ind);
	}
	T query(int lo, int hi, int ind = 1, int L = 0, int R = SZ - 1) {
		push(ind, L, R);
		if (lo > R || L > hi) return ID;
		if (lo <= L && R <= hi) return seg[ind];
		int mid = (L + R) >> 1; 
		return cmb(query(lo, hi, ind << 1, L, mid),
			query(lo, hi, ind << 1 | 1, mid + 1, R));
	}
};
