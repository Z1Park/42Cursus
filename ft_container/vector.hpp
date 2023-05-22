#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include "iterator.hpp"
#include "utils.hpp"

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			typedef T										value_type;
			typedef Allocator								allocator_type;
			typedef typename Allocator::size_type			size_type;
			typedef typename Allocator::difference_type		difference_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef random_access_iterator<T>				iterator;
			typedef random_access_iterator<const T>			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			pointer _begin;
			pointer _end;
			pointer _end_cap;
			allocator_type alloc;

			size_type recommend(size_type new_size) const {
				const size_type ms = max_size();
				if (new_size > ms)
					throw std::length_error("ft_vector:length error");
				const size_type cap = capacity();
				if (cap >= ms / 2)
					return ms;
				return std::max(2 * cap, new_size);
			}

			template <class InputIt>
			difference_type count_iterator_difference(InputIt it1, InputIt it2) {
				difference_type count = 0;
				for (; it1 != it2; it1++)
					count++;
				return count;
			}

		public:
			vector() : _begin(NULL), _end(NULL), _end_cap(NULL), alloc() {
			}

			explicit vector(const Allocator& alloc) : _begin(NULL), _end(NULL), _end_cap(NULL), alloc(alloc) {
			}

			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
						: _begin(NULL), _end(NULL), _end_cap(NULL), alloc(alloc) {
				_begin = this->alloc.allocate(recommend(count));
				_end = _begin;
				_end_cap = _begin + count;
				insert(begin(), count, value);
			}

			template<class InputIt>
			vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL)
						: _begin(NULL), _end(NULL), _end_cap(NULL), alloc(alloc) {
				size_type count = count_iterator_difference(first, last);
				_begin = this->alloc.allocate(recommend(count));
				_end = _begin;
				_end_cap = _begin + count;
				insert(begin(), first, last);
			}

			vector(const vector& other) : _begin(NULL), _end(NULL), _end_cap(NULL), alloc() {
				_begin = alloc.allocate(other.size());
				_end = _begin;
				_end_cap = _begin + other.size();
				insert(begin(), other.begin(), other.end());
			}

			~vector() {
				clear();
				if (capacity() > 0) {
					alloc.deallocate(_begin, capacity());
					_end_cap = _begin;
				}
			}

			vector& operator=(const vector& other) {
				clear();
				insert(begin(), other.begin(), other.end());
				return *this;
			}

			void assign(size_type count, const T& value) {
				clear();
				insert(begin(), count, value);
			}

			template<class InputIt>
			void assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL) {
				clear();
				insert(begin(), first, last);
			}

			allocator_type get_allocator() const {
				return alloc;
			}


			reference at(size_type pos) {
				if (!(pos < size()))
					throw std::out_of_range("ft_vector:out of range");
				return *(_begin + pos);
			}

			const_reference at(size_type pos) const {
				if (!(pos < size()))
					throw std::out_of_range("ft_vector:out of range");
				return *(_begin + pos);
			}

			reference operator[](size_type pos) {
				return *(_begin + pos);
			}

			const_reference operator[](size_type pos) const {
				return *(_begin + pos);
			}

			reference front() {
				return *_begin;
			}

			const_reference front() const {
				return *_begin;
			}

			reference back() {
				return *(_end - 1);
			}

			const_reference back() const {
				return *(_end - 1);
			}

			T* data() {
				return _begin;
			}

			const T* data() const {
				return _begin;
			}


			iterator begin() {
				iterator it(_begin);
				return it;
			}

			const_iterator begin() const {
				const_iterator it(_begin);
				return it;
			}

			iterator end() {
				iterator it(_end);
				return it;
			}

			const_iterator end() const {
				const_iterator it(_end);
				return it;
			}

			reverse_iterator rbegin() {
				reverse_iterator rit(end());
				return rit;
			}

			const_reverse_iterator rbegin() const {
				const_reverse_iterator rit(end());
				return rit;
			}

			reverse_iterator rend() {
				reverse_iterator rit(begin());
				return rit;
			}

			const_reverse_iterator rend() const {
				const_reverse_iterator rit(begin());
				return rit;
			}


			bool empty() const {
				return size() == 0;
			}

			size_type size() const {
				return _end - _begin;
			}

			size_type max_size() const {
				return alloc.max_size();
			}


			void reserve(size_type new_cap) {
				if (new_cap > max_size())
					throw std::length_error("ft_vector:length error");
				if (new_cap > capacity()) {
					pointer new_alloc = alloc.allocate(new_cap);
					for (pointer it = _begin; it != _end; it++) {
						alloc.construct(new_alloc + (it - _begin), *it);
						alloc.destroy(it);
					}
					alloc.deallocate(_begin, capacity());
					_end_cap = new_alloc + new_cap;
					_end = new_alloc + size();
					_begin = new_alloc;
				}
			}

			size_type capacity() const {
				return _end_cap - _begin;
			}


			void clear() {
				erase(begin(), end());
			}

			iterator insert(const_iterator pos, const T& value) {
				return insert(pos, 1, value);
			}

			iterator insert(const_iterator pos, size_type count, const T& value) {
				difference_type idx = pos - begin();
				if (size() + count > capacity())
					reserve(recommend(size() + count));
				for (difference_type i = size() - 1; i >= idx; i--)
					*(_begin + i + count) = *(_begin + i);
				_end += count;
				for (size_type i = 0; i < count; i++)
					*(_begin + idx + i) = value;
				return begin() + idx;
			}

			template<class InputIt>
			iterator insert(const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value >::type* = NULL) {
				difference_type idx = pos - begin();
				difference_type count = count_iterator_difference(first, last);
				if (size() + count > capacity())
					reserve(recommend(size() + count));
				for (difference_type i = size() - 1; i >= idx; i--)
					*(_begin + i + count) = *(_begin + i);
				for (difference_type i = 0; first != last; i++)
					*(_begin + idx + i) = *first++;
				_end += count;
				return begin() + idx;
			}

			iterator erase(iterator pos) {
				for (pointer p = &*pos; p + 1 != _end; p++)
					*p = *(p + 1);
				alloc.destroy(--_end);
				return pos;
			}

			iterator erase(iterator first, iterator last) {
				iterator pos = first;
				if (first >= last)
					return last;
				while (last != end())
					*first++ = *last++;
				_end -= count_iterator_difference(first, last);
				while (first != last)
					alloc.destroy(&*first++);
				return pos;
			}

			void push_back(const T& value) {
				if (size() + 1 > capacity())
					reserve(recommend(size() + 1));
				alloc.construct(_end, value);
				_end++;
				back() = value;
			}

			void pop_back() {
				alloc.destroy(--_end);
			}

			void resize(size_type count, T value = T()) {
				if (count < size())
					erase(begin() + count, end());
				else if (count > size())
					insert(end(), count - size(), value);
			}

			void swap(vector& other) {
				ft::swap(_begin, other._begin);
				ft::swap(_end, other._end);
				ft::swap(_end_cap, other._end_cap);
				ft::swap(alloc, other.alloc);
			}
	};

	template<class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template<class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template<class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return rhs < lhs;
	}

	template<class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template<class T, class Alloc>
	void swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs) {
		lhs.swap(rhs);
	}
}

#endif
