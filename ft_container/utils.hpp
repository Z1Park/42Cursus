#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {
	template< bool B, class T = void >
	struct enable_if {
	};

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

	template <class Tp, Tp v>
	struct integral_constant {
		typedef Tp					value_type;
		typedef integral_constant	type;

		static const Tp				value = v;

		operator value_type() const {
			return value;
		}
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	template <class Tp>
	struct is_integral : public false_type {};

	template <>
	struct is_integral<bool> : public true_type {};

	template <>
	struct is_integral<signed char> : public true_type {};

	template <>
	struct is_integral<unsigned char> : public true_type {};

	template <>
	struct is_integral<char> : public true_type {};

	template <>
	struct is_integral<char16_t> : public true_type {};

	template <>
	struct is_integral<char32_t> : public true_type {};

	template <>
	struct is_integral<wchar_t> : public true_type {};

	template <>
	struct is_integral<short> : public true_type {};

	template <>
	struct is_integral<unsigned short> : public true_type {};

	template <>
	struct is_integral<int> : public true_type {};

	template <>
	struct is_integral<unsigned int> : public true_type {};

	template <>
	struct is_integral<long> : public true_type {};

	template <>
	struct is_integral<unsigned long> : public true_type {};

	template <>
	struct is_integral<long long> : public true_type {};

	template <>
	struct is_integral<unsigned long long> : public true_type {};


	template< class InputIt1, class InputIt2 >
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		for (; first1 != last1; ++first1, ++first2)
			if (!(*first1 == *first2))
				return false;
		return true;
	}

	template< class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p) {
		for (; first1 != last1; ++first1, ++first2)
			if (!p(*first1, *first2))
				return false;
		return true;
	}


	template< class InputIt1, class InputIt2 >
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <class T1, class T2>
	struct pair {
		public:
			typedef T1	first_type;
			typedef T2	second_type;

			T1 first;
			T2 second;

			pair() : first(), second() {
			}

			pair(const T1& x, const T2& y) : first(x), second(y) {
			}

			template<class U1, class U2>
			pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {
			}

			pair& operator=(const pair& other) {
				first = other.first;
				second = other.second;
				return *this;
			}
	};

	template<class T1, class T2>
	pair<T1, T2> make_pair(T1 t, T2 u) {
		return pair<T1, T2>(t, u);
	};

	template<class T1, class T2, class U1, class U2>
	bool operator==(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template<class T1, class T2, class U1, class U2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs) {
		return !(lhs == rhs);
	}

	template<class T1, class T2, class U1, class U2>
	bool operator<(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs) {
		if (lhs.first < rhs.first)
			return true;
		if (rhs.first < lhs.first)
			return false;
		if (lhs.second < rhs.second)
			return true;
		if (rhs.second < lhs.second)
			return false;
		return false;
	}

	template<class T1, class T2, class U1, class U2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs) {
		return !(rhs < lhs);
	}

	template<class T1, class T2, class U1, class U2>
	bool operator>(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs) {
		return rhs < lhs;
	}

	template<class T1, class T2, class U1, class U2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs) {
		return !(lhs < rhs);
	}

	template<typename T>
	void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}
}

#endif
