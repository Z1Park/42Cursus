#ifndef SET_HPP
#define SET_HPP
#include <memory>
#include <exception>
#include "iterator.hpp"
#include "utils.hpp"
#include "RedBlackTree.hpp"

namespace ft {
	template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set {
		public:
			typedef Key										key_type;
			typedef Key										value_type;
			typedef typename Allocator::size_type			size_type;
			typedef typename Allocator::difference_type		difference_type;
			typedef Compare									key_compare;
			typedef Compare									value_compare;
			typedef Allocator								allocator_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef RedBlackTree<value_type, value_compare>	base;
			typedef typename base::const_iterator			iterator;
			typedef typename base::const_iterator			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			allocator_type alloc;
			value_compare vc;
			base tree;

		public:
			set() : alloc(), vc(Compare()), tree(vc) {}

			explicit set(const Compare& comp, const Allocator& alloc = Allocator())
					: alloc(alloc), vc(comp), tree(vc) {}

			template <class InputIt>
			set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
					: alloc(alloc), vc(comp), tree(vc) {
				insert(first, last);
			}

			set(const set& other) : alloc(other.alloc), vc(other.vc), tree(other.tree) {}
			~set() {}


			set& operator=(const set& other) {
				alloc = other.alloc;
				vc = other.vc;
				tree = other.tree;
				return *this;
			}

			allocator_type get_allocator() const {
				return alloc;
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
				return tree.erase(key);
			}

			void swap(set& other) {
				std::swap(alloc, other.alloc);
				std::swap(vc, other.vc);
				tree.swap(other.tree);
			}


			size_type count(const Key& key) const {
				if (tree.find_value(key) != end())
					return 1;
				return 0;
			}

			iterator find(const Key& key) {
				return tree.find_value(key);
			}

			const_iterator find(const Key& key) const {
				return tree.find_value(key);
			}

			pair<const_iterator, const_iterator> equal_range(const Key& key) const {
				return pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
			}

			iterator lower_bound(const Key& key) {
				return tree.lower_bound(key);
			}

			const_iterator lower_bound(const Key& key) const {
				return tree.lower_bound(key);
			}

			iterator upper_bound(const Key& key) {
				return tree.upper_bound(key);
			}

			const_iterator upper_bound(const Key& key) const {
				return tree.upper_bound(key);
			}


			key_compare key_comp() const {
				return vc;
			}

			value_compare value_comp() const {
				return vc;
			}
	};

	template <class Key, class Compare, class Alloc>
	bool operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class Compare, class Alloc>
	bool operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class Key, class Compare, class Alloc>
	bool operator<(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class Compare, class Alloc>
	bool operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return !(lhs > rhs);
	}

	template <class Key, class Compare, class Alloc>
	bool operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return rhs < lhs;
	}

	template <class Key, class Compare, class Alloc>
	bool operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template <class Key, class Compare, class Alloc>
	void swap(set<Key, Compare, Alloc>& lhs, set<Key, Compare, Alloc>& rhs) {
		lhs.swap(rhs);
	}
}

#endif
