#ifndef STACK_HPP
#define STACK_HPP
#include "vector.hpp"

namespace ft {
	template<class T, class Container = vector<T> >
	class stack {
		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

		protected:
			Container c;

		public:
			explicit stack(const Container& cont = Container()) : c(cont) {
			}

			stack(const stack& other) : c(other.c) {
			}

			~stack() {
			}

			stack& operator=(const stack& other) {
				c = other.c;
			}


			reference top() {
				return c.back();
			}


			bool empty() const {
				return c.size() == 0;
			}

			size_type size() const {
				return c.size();
			}


			void push(const value_type& value) {
				c.push_back(value);
			}

			void pop() {
				c.pop_back();
			}


			template<class U, class C>
			friend bool operator==(const stack<U, C>& lhs, const stack<U, C>& rhs);

			template<class U, class C>
			friend bool operator< (const stack<U, C>& lhs, const stack<U, C>& rhs);
	};

	template<class T, class Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.c == rhs.c;
	}

	template<class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return !(lhs == rhs);
	}

	template<class T, class Container>
	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.c < rhs.c;
	}

	template<class T, class Container>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return !(rhs < lhs);
	}

	template<class T, class Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return rhs < lhs;
	}

	template<class T, class Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return !(lhs < rhs);
	}
}

#endif
