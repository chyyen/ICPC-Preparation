template<class T> struct Point {
	T x, y;
	
	Point(): x(0), y(0) {};
	Point(T a, T b): x(a), y(b) {};
	Point(pair<T, T>p): x(p.first), y(p.second) {};

	Point operator + (const Point& rhs){ return Point(x + rhs.x, y + rhs.y); }
	Point operator - (const Point& rhs){ return Point(x - rhs.x, y - rhs.y); }
	Point operator * (const int& rhs){ return Point(x * rhs, y * rhs); }
	Point operator / (const int& rhs){ return Point(x / rhs, y / rhs); }

	T cross(Point rhs){ return x * rhs.y - y * rhs.x; }
	T dot(Point rhs){ return x * rhs.x + y * rhs.y; }

	T cross2(Point a, Point b){ // (a - this) cross (b - this)
		return (a - *this).cross(b - *this);
	}
	T dot2(Point a, Point b){ // (a - this) dot (b - this)
		return (a - *this).dot(b - *this);
	}
};
