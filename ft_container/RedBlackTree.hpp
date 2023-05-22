#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP
#include <memory>
#include <exception>
#include "TreeNode.hpp"
#include "iterator.hpp"
#include "utils.hpp"

namespace ft {
	template <class T, class value_compare>
	class RedBlackTree {
		private:
			typedef TreeNode<T>								node_type;
			typedef std::allocator<node_type>				allocator;
			typedef typename std::allocator<T>::size_type	size_type;

		public:
			typedef T								value_type;
			typedef tree_iterator<node_type>		iterator;
			typedef tree_const_iterator<node_type>	const_iterator;

		private:
			node_type *root;
			node_type *end_node;
			allocator alloc;
			size_type tree_size;
			value_compare vc;

			bool _less(const value_type& lhs, const value_type& rhs) const {
				return vc(lhs, rhs);
			}

			bool _greater(const value_type& lhs, const value_type& rhs) const {
				return vc(rhs, lhs);
			}

			bool _equal(const value_type& lhs, const value_type& rhs) const {
				return !vc(lhs, rhs) && !vc(rhs, lhs);
			}

			bool is_black(node_type *n) {
				return n == NULL || n->color() == BLACK;
			}

			bool is_red(node_type *n) {
				return !is_black(n);
			}

			void set_black(node_type *n) {
				if (n == NULL)
					return;
				n->set_color(BLACK);
			}

			void set_red(node_type *n) {
				n->set_color(RED);
			}

			void change_root(node_type *r) {
				end_node->set_left(r);
				root = r;
				if (root != NULL)
					root->set_parent(NULL);
			}

			node_type *grandparent(node_type *n) {
				if (n != NULL && n->parent() != NULL)
					return n->parent()->parent();
				return NULL;
			}

			node_type *uncle(node_type *n) {
				node_type *g = grandparent(n);
				if (g == NULL)
					return NULL;
				return (n->parent() == g->left()) ? g->right() : g->left();
			}

			void rotate_left(node_type *node) {
				node_type *y = node->right();

				node->set_right(y->left());
				if (y->left() != NULL)
					y->left()->set_parent(node);
				y->set_parent(node->parent());
				if (node->parent() == NULL)
					change_root(y);
				else if (is_left_child(node))
					node->parent()->set_left(y);
				else
					node->parent()->set_right(y);
				y->set_left(node);
				node->set_parent(y);
			}

			void rotate_right(node_type *node) {
				node_type *y = node->left();

				node->set_left(y->right());
				if (y->right() != NULL)
					y->right()->set_parent(node);
				y->set_parent(node->parent());
				if (node->parent() == NULL)
					change_root(y);
				else if (is_right_child(node))
					node->parent()->set_right(y);
				else
					node->parent()->set_left(y);
				y->set_right(node);
				node->set_parent(y);
			}

			void fixInsert(node_type *k){
				node_type *u;

				while (is_red(k->parent())) {
					if (is_right_child(k->parent())) {
						u = uncle(k);
						if (is_red(u)) {
							set_black(u);
							set_black(k->parent());
							set_red(grandparent(k));
							k = grandparent(k);
						}
						else {
							if (is_left_child(k)) {
								k = k->parent();
								rotate_right(k);
							}
							set_black(k->parent());
							set_red(grandparent(k));
							rotate_left(grandparent(k));
						}
					}
					else {
						u = uncle(k);
						if (is_red(u)) {
							set_black(u);
							set_black(k->parent());
							set_red(grandparent(k));
							k = grandparent(k);
						}
						else {
							if (is_right_child(k)) {
								k = k->parent();
								rotate_left(k);
							}
							set_black(k->parent());
							set_red(grandparent(k));
							rotate_right(grandparent(k));
						}
					}
					if (k == root)
						break;
				}
				set_black(root);
			}

			pair<node_type *, bool> insert_node(value_type p, const void *hint = 0) {
				node_type *node;
				node_type *x = root;
				node_type *y = NULL;

				while (x != NULL) {
					y = x;
					if (_less(p, x->getValue()))
						x = x->left();
					else if (_greater(p, x->getValue()))
						x = x->right();
					else
						return ft::make_pair(x, false);
				}
				tree_size++;
				node = alloc.allocate(1, hint);
				alloc.construct(node, p);
				node->set_parent(y);
				if (y == NULL)
					change_root(node);
				else if (_less(node->getValue(), y->getValue()))
					y->set_left(node);
				else
					y->set_right(node);
				if (node->parent() == NULL) {
					node->set_color(BLACK);
					return ft::make_pair(node, true);
				}
				if (node->parent()->parent() == NULL)
					return ft::make_pair(node, true);
				fixInsert(node);
				return ft::make_pair(node, true);
			}

			void replace_node(node_type *u, node_type *v){
				if (u->parent() == NULL)
					change_root(v);
				else if (is_left_child(u))
					u->parent()->set_left(v);
				else
					u->parent()->set_right(v);
				if (v != NULL)
					v->set_parent(u->parent());
			}

			void fixDelete(node_type *x) {
				node_type *s;

				while (x != root && is_black(x)) {
					if (is_left_child(x)) {
						s = x->parent()->right();
						if (is_red(s)) {
							s->set_color(BLACK);
							x->parent()->set_color(RED);
							rotate_left(x->parent());
							s = x->parent()->right();
						}
						if (is_black(s->left()) && is_black(s->right())) {
							s->set_color(RED);
							x = x->parent();
						}
						else {
							if (is_black(s->right())) {
								s->left()->set_color(BLACK);
								s->set_color(RED);
								rotate_right(s);
								s = x->parent()->right();
							}
							s->set_color(x->parent()->color());
							x->parent()->set_color(BLACK);
							s->right()->set_color(BLACK);
							rotate_left(x->parent());
							x = root;
						}
					}
					else {
						s = x->parent()->left();
						if (is_red(s)) {
							s->set_color(BLACK);
							x->parent()->set_color(RED);
							rotate_right(x->parent());
							s = x->parent()->left();
						}
						if (is_black(s->right()) && is_black(s->right())) {
							s->set_color(RED);
							x = x->parent();
						}
						else {
							if (is_black(s->left())) {
								s->right()->set_color(BLACK);
								s->set_color(RED);
								rotate_left(s);
								s = x->parent()->left();
							}
							s->set_color(x->parent()->color());
							x->parent()->set_color(BLACK);
							s->left()->set_color(BLACK);
							rotate_right(x->parent());
							x = root;
						}
					}
				}
				x->set_color(BLACK);
			}

			void delete_node(const value_type& value) {
				node_type *node = root;
				node_type *x = NULL;
				node_type *y = NULL;
				node_type *z = NULL;

				while (node != NULL){
					if (_equal(node->getValue(), value))
						z = node;
					if (!_greater(node->getValue(), value))
						node = node->right();
					else
						node = node->left();
				}
				if (z == NULL)
					return;
				y = z;
				int y_original_color = y->color();
				if (z->left() == NULL) {
					x = z->right();
					replace_node(z, z->right());
				}
				else if (z->right() == NULL) {
					x = z->left();
					replace_node(z, z->left());
				}
				else {
					y = min_node(z->right());
					y_original_color = y->color();
					x = y->right();
					if (y->parent() == z) {
						if (x != NULL)
							x->set_parent(y);
					}
					else {
						replace_node(y, y->right());
						y->set_right(z->right());
						y->right()->set_parent(y);
					}
					replace_node(z, y);
					y->set_left(z->left());
					y->left()->set_parent(y);
					y->set_color(z->color());
				}
				alloc.destroy(z);
				alloc.deallocate(z, 1);
				tree_size--;
				if (y_original_color == BLACK && x != NULL)
					fixDelete(x);
			}

			node_type *find_node(const value_type& value) const {
				node_type *temp = root;

				while (temp != NULL && !_equal(temp->getValue(), value)) {
					if (_less(temp->getValue(), value))
						temp = temp->right();
					else if (_greater(temp->getValue(), value))
						temp = temp->left();
				}
				return temp;
			}

			node_type *find_bound(const value_type &value) const {
				node_type *temp = root;
				node_type *prev = end_node;

				while (temp != NULL) {
					prev = temp;
					if (_equal(temp->getValue(), value))
						return temp;
					else if (_greater(temp->getValue(), value))
						temp = temp->left();
					else
						temp = temp->right();
				}
				return prev;
			}

		public:
			RedBlackTree(value_compare vc) : root(NULL), alloc(), tree_size(0), vc(vc) {
				end_node = this->alloc.allocate(1);
				this->alloc.construct(end_node, value_type());
			}

			RedBlackTree(const RedBlackTree& other) : root(NULL), alloc(), tree_size(0), vc(other.vc) {
				end_node = this->alloc.allocate(1);
				this->alloc.construct(end_node, value_type());
				insert(other.begin(), other.end());
			}

			RedBlackTree& operator=(const RedBlackTree& other) {
				erase(begin(), end());
				insert(other.begin(), other.end());
				return *this;
			}

			iterator begin() {
				if (root == NULL)
					return iterator(end_node, end_node);
				return iterator(min_node(root), end_node);
			}

			const_iterator begin() const {
				if (root == NULL)
					return const_iterator(end_node, end_node);
				return const_iterator(min_node(root), end_node);
			}

			iterator end() {
				return iterator(end_node, end_node);
			}

			const_iterator end() const {
				return const_iterator(end_node, end_node);
			}

			size_type size() const {
				return tree_size;
			}

			size_type max_size() const {
				return alloc.max_size();
			}

			pair<iterator, bool> insert(const value_type& value) {
				pair<node_type *, bool> ip = insert_node(value);
				return ft::make_pair(iterator(ip.first, end_node), ip.second);
			}

			iterator insert(iterator pos, const value_type& value) {
				pair<node_type *, bool> ip = insert_node(value, pos.base());
				return iterator(ip.first, end_node);
			}

			const_iterator insert(const_iterator pos, const value_type& value) {
				pair<node_type *, bool> ip = insert_node(value, pos.base());
				return iterator(ip.first, end_node);
			}

			template <class InputIt>
			void insert(InputIt first, InputIt last) {
				for (; first != last; first++) {
					insert_node(*first);
				}
			}

			iterator erase(iterator pos) {
				iterator it = upper_bound(*pos);
				delete_node(*pos);
				return it;
			}

			iterator erase(const_iterator pos) {
				iterator it = upper_bound(*pos);
				delete_node(*pos);
				return it;
			}

			iterator erase(iterator first, iterator last) {
				iterator it(end_node, end_node);
				if (first == last)
					return it;
				last--;
				while (first != last)
					delete_node(*first++);
				it = upper_bound(*first);
				delete_node(*first);
				return it;
			}

			iterator erase(const_iterator first, const_iterator last) {
				iterator it(end_node, end_node);
				if (first == last)
					return it;
				last--;
				while (first != last)
					delete_node(*first++);
				it = upper_bound(*first);
				delete_node(*first);
				return it;
			}

			size_type erase(const value_type& value) {
				size_type t = tree_size;
				delete_node(value);
				return t - tree_size;
			}

			iterator find_value(const value_type& value) {
				node_type *temp = find_node(value);
				if (temp == NULL)
					return end();
				return iterator(temp, end_node);
			}

			const_iterator find_value(const value_type& value) const {
				node_type *temp = find_node(value);
				if (temp == NULL)
					return end();
				return const_iterator(temp, end_node);
			}

			iterator lower_bound(const value_type& value) {
				node_type *temp = find_bound(value);
				if (_less(temp->getValue(), value)) {
					if (temp != max_node(root))
						return ++iterator(temp, end_node);
					else
						return end();
				}
				return iterator(temp, end_node);
			}

			const_iterator lower_bound(const value_type& value) const {
				node_type *temp = find_bound(value);
				if (_less(temp->getValue(), value)) {
					if (temp != max_node(root))
						return ++const_iterator(temp, end_node);
					else
						return end();
				}
				return const_iterator(temp, end_node);
			}

			iterator upper_bound(const value_type& value) {
				node_type *temp = find_bound(value);
				if (!_greater(temp->getValue(), value)) {
					if (temp != max_node(root))
						return ++iterator(temp, end_node);
					else
						return end();
				}
				return iterator(temp, end_node);
			}

			const_iterator upper_bound(const value_type& value) const {
				node_type *temp = find_bound(value);
				if (!_greater(temp->getValue(), value)) {
					if (temp != max_node(root))
						return ++const_iterator(temp, end_node);
					else
						return end();
				}
				return const_iterator(temp, end_node);
			}

			void swap(RedBlackTree& other) {
				std::swap(root, other.root);
				std::swap(end_node, other.end_node);
				std::swap(alloc, other.alloc);
				std::swap(tree_size, other.tree_size);
			}
	};

	template <class node_type>
	node_type *min_node(node_type *n) {
		while (n->left() != NULL)
			n = n->left();
		return n;
	}

	template <class node_type>
	node_type *max_node(node_type *n) {
		while (n->right() != NULL)
			n = n->right();
		return n;
	}
}

#endif
