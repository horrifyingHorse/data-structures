#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>

template <class T>
class SplayTree;

template <typename T>
class SplayTreeNode {
 public:
  friend class SplayTree<T>;
  SplayTreeNode(T data) : data(data), left(nullptr), right(nullptr) {}

 private:
  T data;
  SplayTreeNode<T>*left, *right;
};

template <typename T>
class SplayTree {
 public:
  SplayTree() : root(nullptr) {}

  SplayTree<T>& insert(T data) {
    this->root = _insertSplay(this->root, data);
    return *this;
  }

  SplayTree<T>& search(T data) {
    root = splay(root, data);
    return *this;
  }

  SplayTree<T>& remove(T data) {
    root = splay(root, data);
    if (data != root->data) return *this;

    SplayTreeNode<T>* ioPre = _inorderPredecessor(root);
    if (ioPre == nullptr) {
      SplayTreeNode<T>* oldRoot = root;
      root = root->right;
      free(oldRoot);
    } else {
      root->data = ioPre->data;
      free(ioPre);
    }

    return *this;
  }

  void preorder() { _preorder(root); }

 private:
  SplayTreeNode<T>* root;
  int nodeCount;

  SplayTreeNode<T>* _rotateRight(SplayTreeNode<T>* root) {
    if (!root || !root->left) return root;
    SplayTreeNode<T>* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
  }

  SplayTreeNode<T>* _rotateLeft(SplayTreeNode<T>* root) {
    if (!root || !root->right) return root;
    SplayTreeNode<T>* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
  }

  SplayTreeNode<T>* splay(SplayTreeNode<T>* root, T data) {
    if (root == nullptr || root->data == data) {
      return root;
    }

    if (data < root->data) {
      if (root->left == nullptr) {
        return root;
      }
      if (data < root->left->data) {  // Zig Zig
        root->left->left = splay(root->left->left, data);
        root = _rotateRight(root);
      } else if (data > root->left->data) {  // Zag Zig
        root->left->right = splay(root->left->right, data);
        // if (root->left->right != nullptr) {
        root->left = _rotateLeft(root->left);  // Checked for root->left->right
                                               // == nullptr in _rotateLeft()
        // }
      }
      return (root->left == nullptr) ? root : _rotateRight(root);
    } else {
      if (root->right == nullptr) {
        return root;
      }
      if (data < root->right->data) {  // Zig Zag
        root->right->left = splay(root->right->left, data);
        root->right = _rotateRight(root->right);
      } else if (data > root->right->data) {  // Zag Zag
        root->right->right = splay(root->right->right, data);
        root = _rotateLeft(root);
      }
      return (root->right == nullptr) ? root : _rotateLeft(root);
    }

    return root;
  }

  SplayTreeNode<T>* _insertSplay(SplayTreeNode<T>* root, T data) {
    if (!root) {
      return new SplayTreeNode<T>(data);
    }

    root = splay(root, data);

    SplayTreeNode<T>* newNode = new SplayTreeNode<T>(data);
    if (data < root->data) {
      newNode->right = root;
      newNode->left = root->left;
      root->left = nullptr;
    } else if (data > root->data) {
      newNode->left = root;
      newNode->right = root->right;
      root->right = nullptr;
    }

    return newNode;
  }

  SplayTreeNode<T>* _inorderPredecessor(SplayTreeNode<T>* root) {
    if (!root || !root->left) return nullptr;
    SplayTreeNode<T>* temp = root->left;
    while (temp->right != nullptr && temp->right->right != nullptr) {
      temp = temp->right;
    }

    if (temp->right == nullptr) {
      root->left = temp->left;
      return temp;
    }

    SplayTreeNode<T>* ret = temp->right;
    temp->right = ret->left;
    return ret;
  }

  void _preorder(SplayTreeNode<T>* root) {
    if (!root) return;

    std::cout << root->data << " ";
    _preorder(root->left);
    _preorder(root->right);

    return;
  }
};

int main() {
  SplayTree<int> st;
  int arr[] = {15, 10, 20, 5, 13, 17, 25, 30, 12, 18};

  for (int i : arr) {
    st.insert(i);
  }

  st.preorder();

  std::cout << "\nSearch 15\n";
  st.search(15);
  st.preorder();

  std::cout << "\nDeleting 17, 15\n";
  st.remove(17);
  st.preorder();
  std::cout << "\n";
  st.remove(15);
  st.preorder();
  std::cout << "\n";
  st.search(1);
  st.preorder();

  return 0;
}
