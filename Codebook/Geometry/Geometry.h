template<class T> int ori(Point<T>a, Point<T>b, Point<T>c){
	// sign of (b - a) cross(c - a)
	auto res = a.cross2(b, c);
	// if type if double
	// if(abs(res) <= eps)
	if(res == 0) 
		return 0;
	return res > 0 ? 1 : -1;
}

template<class T> bool collinearity(Point<T>a, Point<T>b, Point<T>c){
	// if type is double
	// return abs(c.cross2(a,b)) <= eps;
	return c.cross2(a, b) == 0;
}

template<class T> bool between(Point<T>a, Point<T>b, Point<T>c){
	// check if c is between a, b
	return collinearity(a, b, c) && c.dot2(a, b) <= 0;
}

template<class T> bool seg_intersect(Point<T>p1, Point<T>p2, Point<T>p3, Point<T>p4){
	// seg (p1, p2), seg(p3, p4)
	int a123 = ori(p1, p2, p3);
	int a124 = ori(p1, p2, p4);
	int a341 = ori(p3, p4, p1);
	int a342 = ori(p3, p4, p2);
	if(a123 == 0 && a124 == 0)
		return between(p1, p2, p3) || between(p1, p2, p4) || between(p3, p4, p1) || between(p3, p4, p2);
	return a123 * a124 <= 0 && a341 * a342 <= 0;
}

template<class T> Point<T> point2point_intersect_at(Point<T> a, Point<T> b, Point<T> c, Point<T> d) {
	// line(a, b), line(c, d)
	T a123 = a.cross(b, c);
	T a124 = a.cross(b, d);
	return (d * a123 - c * a124) / (a123 - a124);
}

bool circle2circle_intersect_at(Circle c1, Circle c2, Point<double>&p1, Point<double>&p2){
	// return 1 if has intersect points
	Point<double>o1 = c1.O, o2 = c2.O; 
	Point<double>od = o1 - o2;
    double r1 = a.R, r2 = b.R, d2 = od.dot(od), d = sqrt(d2);
	if(d < max(r1, r2) - min(r1, r2) || d > r1 + r2) return 0;
	Point<double> u = (o1 + o2) * 0.5 + (o1 - o2) * ((r2 * r2 - r1 * r1) / (2 * d2));
	double A = sqrt((r1 + r2 + d) * (r1 - r2 + d) * (r1 + r2 - d) * (-r1 + r2 + d));
	Point<double> v = Point(o1.y - o2.y, -o1.x + o2.x) * A / (2 * d2);
	p1 = u + v, p2 = u - v;
	return 1;	
}

template<class T> int point_in_convex_polygon(vector<Point<T>>& a, Point<T>p){
	// 1: IN
	// 0: OUT
	// -1: ON
	// the points of convex polygon must sort in counter-clockwise order
	int n = a.size();
	if(between(a[0], a[1], p) || between(a[0], a[n - 1], p))
		return -1;
	int l = 0, r = n - 1;
	while(l <= r){
		int mid = (l + r) >> 1;
		auto a1 = a[0].cross2(a[mid], p);
		auto a2 = a[0].cross2(a[(mid + 1) % n], p);
		if(a1 >= 0 && a2 <= 0){
			auto res = a[mid].cross2(a[(mid + 1) % n], p);
			return res > 0 ? 1 : (res >= 0 ? -1 : 0);
		}
		else if(a1 < 0)
			r = mid - 1;
		else
			l = mid + 1;
	}
	return 0;
}

template<class T> int point_in_simple_polygon(vector<Point<T>>&a, Point<T>p, Point<T>INF_point){
	// 1: IN
	// 0: ON
	// -1: OUT

	// a[i] must adjacent to a[(i + 1) % n] for all i
	// collinearity(a[i], p, INF_point) must be false for all i
	// we can let the slope of line(p, INF_point) be irrational (e.g. PI)
	int ans = -1;
	for(auto l = prev(a.end()), r = a.begin(); r != a.end(); l = r++){
		if(between(*l, *r, p))
			return 0;
		if(seg_intersect(*l, *r, p, INF_point)){
			ans *= -1;
			if(collinearity(*l, p, INF_point))
				assert(0);
		}
	}
	return ans;
}

template<class T> T area(vector<Point<T>>&a){
	// remember to divide 2 after calling this function
	if(a.size() <= 1)
		return 0;
	T ans = 0;
	for(auto  l = prev(a.end()), r = a.begin(); r != a.end(); l = r++)
		ans += l->cross(*r);
	return abs(ans);
}
