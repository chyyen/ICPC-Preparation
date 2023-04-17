template<class T> vector<Point<T>> convex_hull(vector<Point<T>>&a){
	int n  = a.size();
	sort(a.begin(), a.end(), [](Point<T>p1, Point<T>p2){
		if(p1.x == p2.x)
			return p1.y < p2.y;
		return p1.x < p2.x;
	});
	int m = 0, t = 1;
	vector<Point<T>>ans;
	auto addPoint = [&](const Point<T>p) {
		while(m > t && ans[m - 2].cross2(ans[m - 1], p) <= 0)
			ans.pop_back(), m--;
		ans.push_back(p);
		m++;
	};
	for(int i = 0; i < n; i++)
		addPoint(a[i]);
	t = m;
	for(int i = n - 2; ~i; i--)
		addPoint(a[i]);
	if(a.size() > 1)
		ans.pop_back();
	return ans;
}
