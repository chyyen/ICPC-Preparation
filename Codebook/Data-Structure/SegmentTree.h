template <class T, T (*op)(T, T)> struct Segment_tree{
	int L, R;
	T id;
	vector<T>seg;

	void _modify(int p, T v, int l, int r, int idx = 1){
		assert(p <= r && p >= l);
		if(l == r){
			seg[idx] = v;
			return;
		}
		int mid = (l + r) >> 1;
		if(p <= mid)
			_modify(p, v, l, mid, idx << 1);
		else 
			_modify(p, v, mid + 1, r, idx << 1 | 1);
		seg[idx] = op(seg[idx << 1], seg[idx << 1 | 1]);
	}

	T _query(int ql, int qr, int l, int r, int idx = 1){
		if(ql == l && qr == r)
			return seg[idx];
		int mid = (l + r) >> 1;
		if(qr <= mid)
			return _query(ql, qr, l, mid, idx << 1);
		else if(ql > mid)
			return _query(ql, qr, mid + 1, r, idx << 1 | 1);
		return op(_query(ql, mid, l, mid, idx << 1), _query(mid + 1, qr, mid + 1, r, idx << 1 | 1));
	}

	void modify(int p, T v){ _modify(p, v, L, R, 1); }
	T query(int l, int r){ return _query(l, r, L, R, 1); }

	Segment_tree(): Segment_tree(0, 0, 0) {}
	Segment_tree(int l, int r, T _id): L(l), R(r) {
		id = _id;
		seg.resize(4 * (r - l + 10));
		fill(seg.begin(), seg.end(), id);
	}
};
