/**
 * Created by suli on 18/2/7.
 */

#ifndef ALGO_BASE_TREE_H
#define ALGO_BASE_TREE_H
#include <iostream>
#include <typeinfo>
#include <vector>
#include <stdint.h>

namespace TiAlloy {

enum {
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
};
template<typename T>
struct tree_node {
	tree_node(T &v) {
		value = v;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	tree_node(const T &v) {
		value = v;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	T value;
	size_t hash;
	tree_node *left;
	tree_node *right;
	tree_node *parent;
};

template<typename T, typename EqualFun>
class BinaryTree {
	typedef tree_node<T> Node;
 private:
	Node *root;
	size_t num;
	EqualFun equal;
 public:
	BinaryTree() : root(NULL), num(0) {
	}
	BinaryTree(const T &value) {
		root = new Node(value);
		num = 1;
	}
	BinaryTree(T &value) {
		root = new Node(value);
		num = 1;
	}
	BinaryTree(T value) {
		root = new Node(value);
		num = 1;
	}
	~BinaryTree() {
		delete_node(root);
	}
	bool insert(T &v) {
		Node *t = root;
		while (t) {
			if (equal(v, t->value) > 0) {
				if (t->right == NULL) {//找到位置
					Node *tmp = new Node(v);
					tmp->parent = t; //父节点赋值
					t->right = tmp; //挂载又节点上
					num++;
					return true;
				}
				t = t->right;
			} else if (equal(v, t->value) < 0) {
				if (t->left == NULL) {
					Node *tmp = new Node(v);
					tmp->parent = t;
					t->left = tmp;
					num++;
					return true;
				}
				t = t->left;
			} else {
				t->value = v; //刚好找到,跟新数值
				return true;
			}
		}
		if (root == NULL) {
			Node *tmp = new Node(v);
			root = tmp;
			return true;
		}
		return false;
	}
	void print_tree(int type) {
		std::vector<int> t;
		switch (type) {
			case PRE_ORDER:
				pre_order(root, t);
				std::cout << "pre_order:";
				for (int i = 0; i < t.size(); i++) {
					std::cout << t[i] << ",";
				}
				std::cout << "" << std::endl;
				break;
			case IN_ORDER:
				in_order(root, t);
				std::cout << "in_order:";
				for (int i = 0; i < t.size(); i++) {
					std::cout << t[i] << ",";
				}
				std::cout << "" << std::endl;
				break;
			case POST_ORDER:
				post_order(root, t);
				std::cout << "post_order:";
				for (int i = 0; i < t.size(); i++) {
					std::cout << t[i] << ",";
				}
				std::cout << "" << std::endl;
				break;
			default:
				break;
		}
	}

	bool find_rang(const T &v1, const T &v2, std::vector <T> &t) {
		rang_order(root, v1, v2, t);
		return true;
	}
	Node *find(Node *r, const T &v) {
		Node *t = r;
		while (t) {
			if (v > t->value) {
				t = t->right;
			} else if (v < t->value) {
				t = t->left;
			} else {
				return t;
			}
		}
		return NULL;
	}
	bool is_exist(const T &v) {
		return (find(v) != NULL);
	}
	bool remove(const T &v) {
		Node *t = root;
		return remove_node(t, v);
	}
	size_t hash(const unsigned char *str, int32_t len) {
		const unsigned char *p = str;
		size_t h = 0;
		for (int i = 0; i < len; i++) {
			h ^= p[i];
		}
		return h;
	}
 private:
	Node *min() {
		Node *t = root;
		while (t) {
			if (t->left == NULL)
				return t;
			t = t->left;
		}
		return NULL;
	}
	Node *max() {
		Node *t = root;
		while (t) {
			if (t->right == NULL) {
				return t;
			}
			t = t->right;
		}
	}
	void delete_node(Node *r) {
		if (r == NULL) {
			return;
		}
		if (r->left) {
			return delete_node(r->left);
		}
		if (r->right) {
			return delete_node(r->right);
		}
		delete r;
		r = NULL;
	}
	bool rang_order(const Node *r, const T &n1, const T &n2, std::vector <T> &v) {
		if (r) {
			if (n1 < r->value) {
				if (n1 <= r->value && n2 >= r->value) {
					v.push_back(r->value);
				}
				rang_order(r->left, n1, n2, v);
			} else if (n1 >= r->value && n2 >= r->value) {
				v.push_back(r->value);
				rang_order(r->right, n1, n2, v);
			}
		}
		return true;
	}
	void pre_order(const Node *n, std::vector <T> &r) {
		if (n) {
			r.push_back(n->value);
			pre_order(n->left, r);
			pre_order(n->right, r);
		}
	}
	void in_order(const Node *n, std::vector <T> &r) {
		if (n) {
			in_order(n->left, r);
			r.push_back(n->value);
			in_order(n->right, r);
		}
	}
	void post_order(const Node *n, std::vector <T> &r) {
		if (n) {
			post_order(n->left, r);
			post_order(n->right, r);
			r.push_back(n->value);
		}
	}
	Node *find_max_left_tree(const Node *n) {
		if (n == NULL) {
			return NULL;
		}
		if (n->right == NULL) {//右子树为空,已经找到了最大
			return n;
		}
		return find_max_left_tree(n->right);//递归寻找左子树
	}
	bool remove_node(Node *r, const T &v) {
		Node *t = find(r, v);//查找到删除位置
		if (t == NULL) {
			return true;
		}
		if (t->left == NULL && t->right == NULL) {
			if (t->parent->right == t) {
				t->parent->right = NULL;
			} else {
				t->parent->left = NULL;
			}
			delete t; //删除节点
			num--;
			return true;
		} else if (t->left == NULL) { //右节点存在
			Node *tmp = t;
			t = t->right;
			delete tmp;
			num--;
			return true;
		} else if (t->right == NULL) {//左节点存在
			Node *tmp = t;
			t = t->left;
			delete tmp;
			num--;
			return true;
		} else {//两边子树都存在
			Node *tmp = find_max_left_tree(t);
			t = tmp;
			remove_node(tmp->left, tmp->value);
		}
		return true;
	}
};
class TreeEqual {
 public:
	int operator()(const int &a, const int &b) {
		return (a - b);
	}
};

}

#endif //ALGO_BASE_TREE_H
