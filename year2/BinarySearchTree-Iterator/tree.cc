#include "tree.h"

struct Tree::TreeNode {
  int data;
  TreeNode *left, *right, *parent;
  enum class Kind {Left, Right, Root};
  Kind kind;
  TreeNode(int data, Kind kind, TreeNode *parent, TreeNode *left = nullptr, TreeNode *right = nullptr):
    data{data}, parent{parent}, left{left}, right{right}, kind{kind} {}
  ~TreeNode() {
    delete left;
    delete right;
  }
};

Tree::Tree(): root{nullptr} {}
Tree::~Tree() { delete root; } 

void Tree::insert (int data) {
  if (!root) {
    root = new TreeNode(data, TreeNode::Kind::Root, nullptr);
    return;
  }
  TreeNode *cur = root;
  while (true) {
    if (cur->data == data) return;
    if (cur->data < data) {
      if (!cur->right) {
        cur->right = new TreeNode(data, TreeNode::Kind::Right, cur);
        return;
      }
      else {
        cur = cur->right;
      }
    }
    else if (cur->data > data) {
      if (!cur->left) {
        cur->left = new TreeNode(data, TreeNode::Kind::Left, cur);
        return;
      }
      else {
        cur = cur->left;
      }
    }
  }
}

Tree::Iterator Tree::begin() { return Iterator(Iterator::leftMostLeaf(root)); } // Return the left-most leaf node

Tree::Iterator Tree::end() { return Iterator(nullptr); }

Tree::Iterator::Iterator(TreeNode *node) : node{ node } {} // Iterator Constructor

int &Tree::Iterator::operator*() const { return node->data; }

Tree::Iterator &Tree::Iterator::operator++() {
	if (!node)  // If node is the nullptr, do nothing and return the Iterator obj
		return *this;

	if (node->right != nullptr) {
		node = leftMostLeaf(node->right);
	}
	else {
		node = subtreeParent(node);
	}
	return *this;
}

bool Tree::Iterator::operator==(const Iterator &other) const {
	return node == other.node;
}

bool Tree::Iterator::operator!=(const Iterator &other) const {
	return !(*this == other);
}

Tree::TreeNode *Tree::Iterator::leftMostLeaf(TreeNode *node) { // Return the TreeNode pointer to the left-most leaf node in the subtree
	if (!node) // If the argument node is a nullptr, then just return it
		return node;

	while (node->left) // While not leaf node
		node = node->left;

	return node; // Return left-most leaf or itself if no left node
}

Tree::TreeNode *Tree::Iterator::subtreeParent(TreeNode *node) { // Given node is the right-most leaf of a subtree, return the parent of the subtree
	if (!node) // If the argument node is a nullptr, then just return it
		return node;

	while (node->kind == TreeNode::Kind::Right) // While not root of subtree
		node = node->parent;

	if (node->kind == TreeNode::Kind::Root) { // If subtree parent is the root of the whole tree
		node = nullptr;
	}
	else {
		node = node->parent; // Else, return the subtree parent
	}
	return node;
}

