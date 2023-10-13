struct line{
	int m, c;
	int val(int x){
		return m * x + c;
	}
	line(): m(_id), c(0) {} // _id is the identity element
	line(int _m, int _c): m(_m), c(_c) {}
};

struct Li_Chao_Tree{
	line seg[N << 2];
	void ins(int l, int r, int idx, line x){
		if(l == r){
			if(x.val(l) > seg[idx].val(l))
				seg[idx] = x; // change > to < when get min
			return;
		}
		int mid = (l + r) >> 1;
		if(x.m < seg[idx].m) // change < to > when get min
			swap(x, seg[idx]);
		if(seg[idx].val(mid) <= x.val(mid)){
			// change <= to >= when get min
			swap(x, seg[idx]);
			ins(l, mid, idx << 1, x);
		}
		else
			ins(mid + 1, r, idx << 1 | 1, x);
	}
	int query(int l, int r, int p, int idx){
		if(l == r)
			return seg[idx].val(l);
		int mid = (l + r) >> 1;
		// change max to min when get min
		if(p <= mid)
			return max(seg[idx].val(p), query(l, mid, p, idx << 1));
		else
			return max(seg[idx].val(p), query(mid + 1, r, p, idx << 1 | 1));
	}
}
