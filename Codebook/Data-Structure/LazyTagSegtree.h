struct segment_tree{
	int seg[N << 2];
	int tag1[N << 2], tag2[N << 2];

	void down(int l, int r, int idx, int pidx){
		int v = tag1[pidx], vv = tag2[pidx];
		if(v)
			tag1[idx] = v, seg[idx] = v * (r - l + 1), tag2[idx] = 0;
		if(vv)
			tag2[idx] += vv, seg[idx] += vv * (r - l + 1);
	}
	void Set(int l, int r, int ql, int qr, int v, int idx = 1){
		if(ql == l && qr == r){
			tag1[idx] = v;
			tag2[idx] = 0;
			seg[idx] = v * (r - l + 1);
			return;
		}
		int mid = (l + r) >> 1;
		down(l, mid, idx << 1, idx);
		down(mid + 1, r, idx << 1 | 1, idx);
		tag1[idx] = tag2[idx] = 0;
		if(qr <= mid)
			Set(l, mid, ql, qr, v, idx << 1);
		else if(ql > mid)
			Set(mid + 1, r, ql, qr, v, idx << 1 | 1);
		else{
			Set(l, mid, ql, mid, v, idx << 1);
			Set(mid + 1, r, mid + 1, qr, v, idx << 1 | 1);
		}
		seg[idx] = seg[idx << 1] + seg[idx << 1 | 1];
	}
	void Increase(int l, int r, int ql, int qr, int v, int idx = 1){
		if(ql ==l && qr == r){
			tag2[idx] += v;
			seg[idx] +=  v * (r - l + 1);
			return;
		}
		int mid = (l + r) >> 1;
		down(l, mid, idx << 1, idx);
		down(mid + 1, r, idx << 1 | 1, idx);
		tag1[idx] = tag2[idx] = 0;
		if(qr <= mid)
			Increase(l, mid, ql, qr, v, idx << 1);
		else if(ql > mid)
			Increase(mid + 1, r, ql, qr, v, idx << 1 | 1);
		else{
			Increase(l, mid, ql, mid, v, idx << 1);
			Increase(mid + 1, r, mid + 1, qr, v, idx << 1 | 1);
		}
		seg[idx] = seg[idx << 1] + seg[idx << 1 | 1];
	}
	int query(int l, int r, int ql, int qr, int idx = 1){
		if(ql ==l && qr == r)
			return seg[idx];
		int mid = (l + r) >> 1;
		down(l, mid, idx << 1, idx);
		down(mid + 1, r, idx << 1 | 1, idx);
		tag1[idx] = tag2[idx] = 0;
		if(qr <= mid)
			return query(l, mid, ql, qr, idx << 1);
		else if(ql > mid)
			return query(mid + 1, r, ql, qr, idx << 1 | 1);
		return query(l, mid, ql, mid, idx << 1) + query(mid + 1, r, mid + 1, qr, idx << 1 | 1);
	}
	void modify(int l, int r, int ql, int qr, int v, int type){
		// type 1: increasement, type 2: set
		if(type == 2)
			Set(l, r, ql, qr, v); 
		else
			Increase(l, r, ql, qr, v);
	}
};