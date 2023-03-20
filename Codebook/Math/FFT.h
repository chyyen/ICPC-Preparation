struct Polynomial{
	int deg;
	vector<int>x;
	void FFT(vector<complex<double>>&a, bool invert){
		int a_sz = a.size();
		for(int len = 1; len < a_sz; len <<= 1){
			for(int st = 0; st < a_sz; st += 2 * len){
				double angle = PI / len * (invert ? -1 : 1);
				complex<double>wnow(1), w(cos(angle), sin(angle));
				for(int i = 0; i < len; i++){
					auto a0 = a[st + i], a1 = a[st + len + i];
					a[st + i] = a0 + wnow * a1;
					a[st + i + len] = a0 - wnow * a1;
					wnow *= w;
				}
			}
		}
		if(invert)
			for(auto &i : a)
				i /= a_sz;
	}
	void change(vector<complex<double>>&a){
		int a_sz = a.size();
		vector<int>rev(a_sz);
		for(int i = 1; i < a_sz; i++){
			rev[i] = rev[i / 2] / 2;
			if(i & 1)
				rev[i] += a_sz / 2;
		}
		for(int i = 0; i < a_sz; i++)
			if(i < rev[i])
				swap(a[i], a[rev[i]]);
	}
	Polynomial multiply(Polynomial const&b){
		vector<complex<double>>A(x.begin(), x.end()), B(b.x.begin(), b.x.end());
		int mx_sz = 1;
		while(mx_sz < A.size() + B.size())
			mx_sz <<= 1;
		A.resize(mx_sz);
		B.resize(mx_sz);
		change(A);
		change(B);
		FFT(A, 0);
		FFT(B, 0);
		for(int i = 0; i < mx_sz; i++)
			A[i] *= B[i];
		change(A);
		FFT(A, 1);
		Polynomial res(mx_sz);
		for(int i = 0; i < mx_sz; i++)
			res.x[i] = round(A[i].real());
		while(!res.x.empty() && res.x.back() == 0)
			res.x.pop_back();
		res.deg = res.x.size();
		return res;
	}
	Polynomial(): Polynomial(0) {}
	Polynomial(int Size): x(Size), deg(Size) {}
};
