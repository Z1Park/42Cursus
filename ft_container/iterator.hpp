#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <cstddef>
#include "TreeNode.hpp"

namespace ft {
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template <class Iter>
	struct iterator_traits {
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template<class T>
	struct iterator_traits<T*> {
		typedef std::ptrdiff_t								difference_type;
		typedef T											value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};

	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef	T			value_type;
		typedef	Distance	difference_type;
		typedef	Pointer		pointer;
		typedef	Reference	reference;
		typedef	Category	iterator_category;
	};

	template<class Iter>
	class reverse_iterator {
		public:
			typedef Iter													iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef typename ft::iterator_traits<Iter>::reference			reference;

		protected:
			iterator_type current;

		public:
			reverse_iterator() {
			}

			~reverse_iterator() {
			}

			explicit reverse_iterator(iterator_type x) : current(x) {
			}

			template<class U>
			reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {
			}

			iterator_type base() const {
				return current;
			}

			template<class U>
			reverse_iterator& operator=(const reverse_iterator<U>& other) {
				current = other.base();
				return *this;
			}

			reference operator*() const {
				iterator_type temp = current;
				return *(--temp);
			}

			pointer operator->() const {
				iterator_type temp = current;
				return &*(--temp);
			}

			reference operator[](difference_type n) const {
				return *(current - 1 - n);
			}

			reverse_iterator& operator++() {
				current--;
				return *this;
			}

			reverse_iterator& operator--() {
				current++;
				return *this;
			}

			reverse_iterator operator++(int) {
				reverse_iterator it(*this);
				current--;
				return it;
			}

			reverse_iterator operator--(int) {
				reverse_iterator it(*this);
				current++;
				return it;
			}

			reverse_iterator operator+(difference_type n) const {
				reverse_iterator it(*this);
				it.current -= n;
				return it;
			}

			reverse_iterator operator-(difference_type n) const {
				reverse_iterator it(*this);
				it.current += n;
				return it;
			}

			reverse_iterator& operator+=(difference_type n) {
				current -= n;
				return *this;
			}

			reverse_iterator& operator-=(difference_type n) {
				current += n;
				return *this;
			}
	};

	template<class Iterator1, class Iterator2>
	bool operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return rhs.base() < lhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return !(rhs.base() > lhs.base());
	}

	template<class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return rhs.base() > lhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return !(rhs.base() < lhs.base());
	}

	template<class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it) {
		reverse_iterator<Iter> nit(it + n);
		return nit;
	}

	template<class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return rhs.base() - lhs.base();
	}

	template <class T>
	class random_access_iterator : public ft::iterator<ft::input_iterator_tag, T, long, const T*, T&> {
		public:
			typedef typename iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename iterator<random_access_iterator_tag, T>::value_type		value_type;
			typedef typename iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename iterator<random_access_iterator_tag, T>::pointer			pointer;
			typedef typename iterator<random_access_iterator_tag, T>::reference			reference;

		protected:
			pointer current;

		public:
			random_access_iterator() {
			}

			~random_access_iterator() {
			}

			explicit random_access_iterator(pointer x) : current(x) {
			}

			template<class U>
			random_access_iterator(const random_access_iterator<U>& other) : current(other.base()) {
			}

			pointer base() const {
				return current;
			}

			template<class U>
			random_access_iterator& operator=(const random_access_iterator<U>& other) {
				current = other.base();
				return *this;
			}

			reference operator*() const {
				return *current;
			}

			pointer operator->() const {
				return &*current;
			}

			reference operator[](difference_type n) const {
				return *(current + n);
			}

			random_access_iterator& operator++() {
				current++;
				return *this;
			}

			random_access_iterator& operator--() {
				current--;
				return *this;
			}

			random_access_iterator operator++(int) {
				random_access_iterator it(*this);
				current++;
				return it;
			}

			random_access_iterator operator--(int) {
				random_access_iterator it(*this);
				current--;
				return it;
			}

			random_access_iterator operator+(difference_type n) const {
				random_access_iterator it(*this);
				it.current += n;
				return it;
			}

			random_access_iterator operator-(difference_type n) const {
				random_access_iterator it(*this);
				it.current -= n;
				return it;
			}

			random_access_iterator& operator+=(difference_type n) {
				current += n;
				return *this;
			}

			random_access_iterator& operator-=(difference_type n) {
				current -= n;
				return *this;
			}
	};

	template<class Iterator1, class Iterator2>
	bool operator==(const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator!=(const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator<(const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs) {
		return lhs.base() < rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator<=(const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator>(const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs) {
		return lhs.base() > rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator>=(const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template<class Iter>
	random_access_iterator<Iter> operator+(typename random_access_iterator<Iter>::difference_type n, const random_access_iterator<Iter>& it) {
		random_access_iterator<Iter> nit = it + n;
		return nit;
	}

	template<class Iterator1, class Iterator2>
	typename random_access_iterator<Iterator1>::difference_type operator-(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
		return lhs.base() - rhs.base();
	}

	template <class T>
	class tree_iterator : public ft::iterator<ft::input_iterator_tag, T, long, const T*, T&> {
		public:
			typedef typename T::value_type															value_type;
			typedef typename iterator<bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename iterator<bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename iterator<bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename iterator<bidirectional_iterator_tag, value_type>::reference			reference;

		protected:
			T *current;
			T *end_node;

		private:
			T *tree_next_iter(T *n) {
				if (n->right() != NULL)
					return min_node(n->right());
				while (is_right_child(n))
					n = n->parent();
				if (n->parent() != NULL)
					return n->parent();
				else
					return end_node;
			}

			T *tree_prev_iter(T *n) {
				if (n->left() != NULL)
					return max_node(n->left());
				T *temp = n;
				while (is_left_child(temp))
					temp = temp->parent();
				return temp->parent();
			}

		public:
			tree_iterator() : current(NULL), end_node(NULL) {
			}

			~tree_iterator() {
			}

			explicit tree_iterator(T *node, T *end) : current(node), end_node(end) {
			}

			template<class U>
			tree_iterator(const tree_iterator<U>& other)
					: current(other.base()), end_node(other.end()) {
			}

			T *base() const {
				return current;
			}

			T* end() const {
				return end_node;
			}

			template<class U>
			tree_iterator& operator=(const tree_iterator<U>& other) {
				current = other.base();
				end_node = other.end();
				return *this;
			}

			reference operator*() const {
				return current->getValue();
			}

			pointer operator->() const {
				return &(current->getValue());
			}

			tree_iterator& operator++() {
				current = tree_next_iter(current);
				return *this;
			}

			tree_iterator& operator--() {
				current = tree_prev_iter(current);
				return *this;
			}

			tree_iterator operator++(int) {
				tree_iterator it(*this);
				current = tree_next_iter(current);
				return it;
			}

			tree_iterator operator--(int) {
				tree_iterator it(*this);
				current = tree_prev_iter(current);
				return it;
			}
	};

	template<class Iterator1, class Iterator2>
	bool operator==(const ft::tree_iterator<Iterator1>& lhs, const ft::tree_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator!=(const ft::tree_iterator<Iterator1>& lhs, const ft::tree_iterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}

	template <class T>
	class tree_const_iterator : public ft::iterator<ft::input_iterator_tag, const T, long, const T*, const T&> {
		public:
			typedef const typename T::value_type													value_type;
			typedef typename iterator<bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename iterator<bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename iterator<bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename iterator<bidirectional_iterator_tag, value_type>::reference			reference;

		protected:
			T *current;
			T *end_node;

		private:
			T *tree_next_iter(T *n) {
				if (n->right() != NULL)
					return min_node(n->right());
				while (is_right_child(n))
					n = n->parent();
				if (n->parent() != NULL)
					return n->parent();
				else
					return end_node;
			}

			T *tree_prev_iter(T *n) {
				if (n->left() != NULL)
					return max_node(n->left());
				T *temp = n;
				while (is_left_child(temp))
					temp = temp->parent();
				return temp->parent();
			}

		public:
			tree_const_iterator() : current(NULL), end_node(NULL) {
			}

			~tree_const_iterator() {
			}

			explicit tree_const_iterator(T *node, T *end) : current(node), end_node(end) {
			}

			template<class U>
			tree_const_iterator(const tree_iterator<U>& other)
					: current(other.base()), end_node(other.end()) {
			}

			template<class U>
			tree_const_iterator(const tree_const_iterator<U>& other)
					: current(other.base()), end_node(other.end()) {
			}

			T *base() const {
				return current;
			}

			T* end() const {
				return end_node;
			}

			template<class U>
			tree_const_iterator& operator=(const tree_const_iterator<U>& other) {
				end_node = other.end();
				current = other.base();
				return *this;
			}

			template<class U>
			tree_const_iterator& operator=(const tree_iterator<U>& other) {
				end_node = other.end();
				current = other.base();
				return *this;
			}

			reference operator*() const {
				return current->getValue();
			}

			pointer operator->() const {
				return &(current->getValue());
			}

			tree_const_iterator& operator++() {
				current = tree_next_iter(current);
				return *this;
			}

			tree_const_iterator& operator--() {
				current = tree_prev_iter(current);
				return *this;
			}

			tree_const_iterator operator++(int) {
				tree_const_iterator it(*this);
				current = tree_next_iter(current);
				return it;
			}

			tree_const_iterator operator--(int) {
				tree_const_iterator it(*this);
				current = tree_prev_iter(current);
				return it;
			}
	};

	template<class Iterator1, class Iterator2>
	bool operator==(const ft::tree_const_iterator<Iterator1>& lhs, const ft::tree_const_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator==(const ft::tree_const_iterator<Iterator1>& lhs, const ft::tree_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator==(const ft::tree_iterator<Iterator1>& lhs, const ft::tree_const_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator!=(const ft::tree_const_iterator<Iterator1>& lhs, const ft::tree_const_iterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator!=(const ft::tree_iterator<Iterator1>& lhs, const ft::tree_const_iterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator!=(const ft::tree_const_iterator<Iterator1>& lhs, const ft::tree_iterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}
}

#endif
