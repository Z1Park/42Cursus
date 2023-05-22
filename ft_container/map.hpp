#ifndef MAP_HPP
#define MAP_HPP
#include <memory>
#include <exception>
#include "iterator.hpp"
#include "utils.hpp"
#include "RedBlackTree.hpp"

namespace ft {
	template <class Key,class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
	class map {
		private:
			class value_compare;

		public:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef pair<const key_type, mapped_type>		value_type;
			typedef typename Allocator::size_type			size_type;
			typedef typename Allocator::difference_type		difference_type;
			typedef RedBlackTree<value_type, value_compare>	base;
			typedef Compare									key_compare;
			typedef Allocator								allocator_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef typename base::iterator					iterator;
			typedef typename base::const_iterator			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			class value_compare {
				protected:
					key_compare comp;

				public:
					friend class map;

					value_compare(Compare c) : comp(c) {
					}

					bool operator()(const value_type& lhs, const value_type& rhs) const {
						return comp(lhs.first, rhs.first);
					}
			};

			allocator_type alloc;
			value_compare vc;
			base tree;

		public:
			map() : alloc(), vc(Compare()), tree(vc) {}

			explicit map(const Compare& comp, const Allocator& alloc = Allocator())
					: alloc(alloc), vc(comp), tree(vc) {}

			template <class InputIt>
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
					: alloc(alloc), vc(comp), tree(vc) {
				insert(first, last);
			}

			map(const map& other) : alloc(other.alloc), vc(other.vc), tree(other.tree) {}
			~map() {
				clear();
			}


			map& operator=(const map& other) {
				alloc = other.alloc;
				vc = other.vc;
				tree = other.tree;
				return *this;
			}

			allocator_type get_allocator() const {
				return alloc;
			}


			T& at(const Key& key) {
				iterator it = tree.find_value(make_pair(key, T()));
				if (it == end())
					throw std::out_of_range("ft::map : out of range");
				return it->getValue().second;
			}

			const T& at(const Key& key) const {
				const_iterator it = tree.find_value(ft::make_pair(key, T()));
				if (it == end())
					throw std::out_of_range("ft::map : out of range");
				return it->getValue().second;
			}

			T& operator[](const Key& key) {
				iterator it = tree.find_value(ft::make_pair(key, T()));
				if (it == end())
					it = insert(pair<Key, T>(key, T())).first;
				return it->second;
			}


			iterator begin() {
				return tree.begin();
			}

			const_iterator begin() const {
				return tree.begin();
			}

			iterator end() {
				return tree.end();
			}

			const_iterator end() const {
				return tree.end();
			}

			reverse_iterator rbegin() {
				return reverse_iterator(tree.end());
			}

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(tree.end());
			}

			reverse_iterator rend() {
				return reverse_iterator(tree.begin());
			}

			const_reverse_iterator rend() const {
				return const_reverse_iterator(tree.begin());
			}


			bool empty() const {
				return size() == 0;
			}

			size_type size() const {
				return tree.size();
			}

			size_type max_size() const {
				return tree.max_size();
			}


			void clear() {
				erase(begin(), end());
			}

			pair<iterator, bool> insert(const value_type& value) {
				return tree.insert(value);
			}

			iterator insert(iterator pos, const value_type& value) {
				return tree.insert(pos, value);
			}

			template <class InputIt>
			void insert(InputIt first, InputIt last) {
				tree.insert(first, last);
			}

			iterator erase(iterator pos) {
				return tree.erase(pos);
			}

			iterator erase(iterator first, iterator last) {
				return tree.erase(first, last);
			}

			size_type erase(const Key& key) {
				return tree.erase(ft::make_pair(key, T()));
			}

			void swap(map& other) {
				std::swap(alloc, other.alloc);
				std::swap(vc, other.vc);
				tree.swap(other.tree);
			}


			size_type count(const Key& key) const {
				if (tree.find_value(ft::make_pair(key, T())) != end())
					return 1;
				return 0;
			}

			iterator find(const Key& key) {
				return tree.find_value(ft::make_pair(key, T()));
			}

			const_iterator find(const Key& key) const {
				return tree.find_value(ft::make_pair(key, T()));
			}

			pair<iterator,iterator> equal_range(const Key& key) {
				return pair<iterator, iterator>(lower_bound(key), upper_bound(key));
			}

			pair<const_iterator, const_iterator> equal_range(const Key& key) const {
				return pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
			}

			iterator lower_bound(const Key& key) {
				return tree.lower_bound(ft::make_pair(key, T()));
			}

			const_iterator lower_bound(const Key& key) const {
				return tree.lower_bound(ft::make_pair(key, T()));
			}

			iterator upper_bound(const Key& key) {
				return tree.upper_bound(ft::make_pair(key, T()));
			}

			const_iterator upper_bound(const Key& key) const {
				return tree.upper_bound(ft::make_pair(key, T()));
			}


			key_compare key_comp() const {
				return vc.comp;
			}

			value_compare value_comp() const {
				return vc;
			}
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return !(lhs > rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return rhs < lhs;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs) {
		lhs.swap(rhs);
	}
}

#endif
