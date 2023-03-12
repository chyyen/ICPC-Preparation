struct line{
	int m, c;
	int val(int x){
		return m * x + c;
	}
	line(){}
	line(int _m, int _c){
		m = _m, c = _c;
	}
};

struct Li_Chao_Tree{
	line seg[N << 2];
	void ins(int l, int r, int idx, line x){
		if(l == r){
			if(x.val(l) > seg[idx].val(l))
				seg[idx] = x;
			return;
		}
		int mid = (l + r) >> 1;
		if(x.m < seg[idx].m)
			swap(x, seg[idx]);
		// ensure x.m > seg[idx].m
		if(seg[idx].val(mid) <= x.val(mid)){
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
		if(p <= mid)
			return max(seg[idx].val(p), query(l, mid, p, idx << 1));
		else
			return max(seg[idx].val(p), query(mid + 1, r, p, idx << 1 | 1));
	}
}