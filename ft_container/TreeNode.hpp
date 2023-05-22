#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <memory>
#include "utils.hpp"

#define BLACK 0
#define RED 1

namespace ft {
	template <class T>
	class TreeNode {
		public:
			typedef T	value_type;

		private:
			TreeNode *_parent;
			TreeNode *_left;
			TreeNode *_right;
			int _color;
			value_type p;

		public:
			TreeNode() : _parent(NULL), _left(NULL), _right(NULL), _color(RED), p() {
			}

			TreeNode(value_type p) : _parent(NULL), _left(NULL), _right(NULL), _color(RED), p(p) {
			}

			TreeNode *parent() const {
				return _parent;
			}

			void set_parent(TreeNode *parent) {
				_parent = parent;
			}

			TreeNode *left() const {
				return _left;
			}

			void set_left(TreeNode *left) {
				_left = left;
			}

			TreeNode *right() const {
				return _right;
			}

			void set_right(TreeNode *right) {
				_right = right;
			}

			int color() const {
				return _color;
			}

			void set_color(int color) {
				_color = color;
			}

			value_type& getValue() {
				return p;
			}

			const value_type& getValue() const {
				return p;
			}
	};

	template <class T>
	bool is_left_child(T *n) {
		if (n == NULL || n->parent() == NULL)
			return false;
		return n->parent()->left() == n;
	}

	template <class T>
	bool is_right_child(T *n) {
		if (n == NULL || n->parent() == NULL)
			return false;
		return n->parent()->right() == n;
	}
}

#endif
