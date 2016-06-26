#ifndef _TREE_H_
#define _TREE_H_

class Tree {
  struct TreeNode;
  TreeNode *root;

public:
  Tree();
  ~Tree();

  void insert (int data);

  class Iterator {
	  TreeNode *node;
	  explicit Iterator(TreeNode *node);
	  static TreeNode *leftMostLeaf(TreeNode *node);
	  static TreeNode *subtreeParent(TreeNode *node);

  public:
	  int &operator*() const;
	  Iterator &operator++();
	  bool operator==(const Iterator &other) const;
	  bool operator!=(const Iterator &other) const;

	  friend class Tree;
  };

  Iterator begin();
  Iterator end();
};

#endif
