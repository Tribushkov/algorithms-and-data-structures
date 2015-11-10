#include <iostream>
#include <stack>

template <typename data_t> struct tree_node_t {
	data_t data;
	tree_node_t *left;
	tree_node_t *right;

	tree_node_t(data_t _data) : data(_data), left(NULL), right(NULL) { }

	tree_node_t* find(data_t data) {
		tree_node_t *current_node = this;

		while (current_node != NULL) {
			if (current_node->data > data) {
				if (current_node->left != NULL) {
					current_node = current_node->left;
				} else {
					return current_node;
				}
			} else if (current_node->data < data) {
				if (current_node->right != NULL) {
					current_node = current_node->right;
				} else {
					return current_node;
				}
			} else {
				return current_node;
			}
		}

		return NULL;
	}

	template <typename func_t>
	void traverse(func_t &foo) {
		std::stack<tree_node_t *> s;
		tree_node_t *node = this;

		for (;;) {
			foo(node);

			if (node->left != NULL) {
				if (node->right != NULL) s.push(node->right);
				node = node->left;
			} else if (node->right != NULL) {
				node = node->right;
			} else {
				if (!s.size()) break;

				node = s.top();
				s.pop();
			}
		}

		std::cout << std::endl;
	}
};

template <typename data_t> struct tree_t {
	tree_node_t<data_t> *root;

	tree_t() : root(NULL) { }

	void add(data_t data) {
		tree_node_t<data_t> *node = root->find(data);

		if (node == NULL) {
			root = new tree_node_t<data_t>(data);
		} else if (node->data >= data) {
			node->left = new tree_node_t<data_t>(data);
		} else {
			node->right = new tree_node_t<data_t>(data);
		}
	}

	template <typename func_t>
	void traverse(func_t &foo) {
		if (root == NULL) return;

		root->traverse<func_t>(foo);
	}
};

template <typename data_t> struct print_tree_node_t {
	void operator ()(tree_node_t<data_t> *node) {
		std::cout << node->data << " ";
	}
};

int main() {
	size_t n;

	std::cin >> n;

	tree_t<int> tree;

	for (size_t i = 0; i < n; ++i) {
		int data;

		std::cin >> data;
		tree.add(data);
	}

	print_tree_node_t<int> print_tree_node;

	tree.traverse< print_tree_node_t<int> >(print_tree_node);

	return 0;
};
