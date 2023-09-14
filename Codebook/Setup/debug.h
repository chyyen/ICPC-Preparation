namespace DEBUG{ 
	template <typename T, typename T2>
	ostream& operator<<(ostream& os, const pair<T, T2>& pr) {
		os << "( " << pr.first << ", " << pr.second << ")";
		return os;
	}

	template <typename T>
	inline void _printv(T l, T r){
		cerr << "DEBUG: [ ";
		for(; l != r; l++)
			cerr << *l << ", ";
		cerr << "]" << endl;
	}
	
	template <typename T>
	inline void _debug(const char* format, T t) {
		cerr << format << '=' << t << endl;
	}
	
	template <class First, class... Rest>
	inline void _debug(const char* format, First first, Rest... rest) {
		while (*format != ',')
			cerr << *format++;
		cerr << '=' << first << ",";
		_debug(format + 1, rest...);
	}

	#define TEST
	#ifdef TEST
	#define printv(x, y) _printv(x, y)
	#define debug(...) cerr << "DEBUG: ",_debug(#__VA_ARGS__, __VA_ARGS__)
	#else
	#define debug(...) void(0)
	#define printv(x, y) void(0)
	#endif
}  // namespace DEBUG

using namespace DEBUG;
