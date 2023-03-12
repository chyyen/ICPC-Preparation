mt19937 mtrd(chrono::steady_clock::now().time_since_epoch().count());

struct Treap{
	Treap *l, *r;
	int pri, key, sz;
	Treap(){}
	Treap(int _v){
		l = r = NULL;
		pri = mtrd();
		key = _v;
		sz = 1;
	}
	~Treap(){
        if ( l )
            delete l;
        if ( r )
            delete r;
    }	
	void push(){
		for(auto ch : {l, r}){
			if(ch){
				// do something
			}
		}
	}
};

int getSize(Treap *t){
	return t ? t->sz : 0;
}

void pull(Treap *t){
	t->sz = getSize(t->l) + getSize(t->r) + 1;
}

Treap* merge(Treap* a, Treap* b){
	if(!a || !b)
		return a ? a : b;
	if(a->pri > b->pri){
		a->push();
		a->r = merge(a->r, b);
		pull(a);
		return a;
	}
	else{
		b->push();
		b->l = merge(a, b->l);
		pull(b);
		return b;
	}
}

void splitBySize(Treap *t, Treap *&a, Treap *&b, int k){
	if(!t)
		a = b = NULL;
	else if(getSize(t->l) + 1 <= k){
		a = t;
		a->push();
		splitBySize(t->r, a->r, b, k - getSize(t->l) - 1);
		pull(a);
	}
	else{
		b = t;
		b->push();
		splitBySize(t->l, a, b->l, k);
		pull(b);
	}
}

void splitByKey(Treap *t, Treap *&a, Treap *&b, int k){
    if(!t)
        a = b = NULL;
    else if(t->key <= k){
        a = t;
        a->push();
        splitByKey(t->r, a->r, b, k);
        pull(a);
    }
    else{
        b = t;
        b->push();
        splitByKey(t->l, a, b->l, k);
        pull(b);
    }
}


// O(n) build treap with sorted key nodes
void traverse(Treap *t){
	if(t->l)
		traverse(t->l);
	if(t->r)
		traverse(t->r);
	pull(t);
}

Treap *build(int n){
	vector<Treap*>st(n);
	int tp = 0;
	for(int i = 0, x; i < n; i++){
		cin >> x;
		Treap *nd = new Treap(x);
		while(tp && st[tp - 1]->pri < nd->pri)
			nd->l = st[tp - 1], tp--;
		if(tp)
			st[tp - 1]->r = nd;
		st[tp++] = nd;
	}
	if(!tp){
		st[0] = NULL;
		return st[0];
	}
	traverse(st[0]);
	return st[0];
}
