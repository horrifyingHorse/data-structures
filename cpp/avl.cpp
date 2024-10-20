#include <iostream>

template <typename T> class AVLTree;

template <typename T>
class AVLTree {
  class _avltreenode {
  protected:
    T data;
    int height;
    _avltreenode *left, *right;

  public:
    _avltreenode(T data):
      data(data),
      height(1),
      left(nullptr),
      right(nullptr) {}

    _avltreenode():
      height(1),
      left(nullptr),
      right(nullptr) {}

    friend class AVLTree<T>;
  };

protected:
  _avltreenode* root;

  _avltreenode* _createNode(T data) {
    return new _avltreenode(data);
  }

  int _getHeight(_avltreenode* root) {
    return (!root) ? 0 : root->height;
  }

  int _getBF(_avltreenode* root) {
    return _getHeight(root->left) - _getHeight(root->right);
  }

  int _height(_avltreenode* root) {
    return (_getHeight(root->left) > _getHeight(root->right))
      ? _getHeight(root->left) + 1
      : _getHeight(root->right) + 1;
  }

  _avltreenode* rotateLeft(_avltreenode* root) {
    _avltreenode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;

    root->height = _height(root);
    newRoot->height = _height(newRoot);

    return newRoot;
  }

  _avltreenode* rotateRight(_avltreenode* root) {
    _avltreenode* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;

    root->height = _height(root);
    newRoot->height = _height(newRoot);

    return newRoot;
  }

  _avltreenode* _balanceAVL(_avltreenode* root) {
    int bf = _getBF(root);

    if (bf > 1) {
      // Left subtree Imbalance
      _avltreenode* child = root->left;
      if (_getHeight(child->right) > _getHeight(child->left)) {
        // LR Imbalance
        root->left = rotateLeft(root->left);
      } // else LL Imbalance
      root = rotateRight(root);
    }
    else if (bf < -1) {
      // Right Imbalance
      _avltreenode* child = root->right;
      if (_getHeight(child->left) > _getHeight(child->right)) {
        // RL Imbalance
        root->right = rotateRight(root->right);
      } // else RR Imbalance
      root = rotateLeft(root);
    }

    return root;
  }

  _avltreenode* _insert(_avltreenode* root, T data) {
    if (!root) {
      return _createNode(data);
    }

    if (data < root->data) {
      root->left = _insert(root->left, data);
    } else if (data > root->data) {
      root->right = _insert(root->right, data);
    } else { // data == root->data
      std::cerr << "Duplicate insertion in AVL Tree: " << data;
      exit(1);
    }

    root->height = _height(root);

    if (abs(_getBF(root)) > 1) return _balanceAVL(root);

    return root;
  }

  _avltreenode* _inorderPredecessor(_avltreenode* root) {
    _avltreenode* child = root->left;
    while (child && child->right) {
      child = child->right;
    }

    return child;
  }

  _avltreenode* _remove(_avltreenode* root, T data) {
    if (!root) return root;

    if (data < root->data) {
      root->left = _remove(root->left, data);
    } else if (data > root->data) {
      root->right = _remove(root->right, data);
    } else {
      _avltreenode* ioPre = _inorderPredecessor(root);
      if (!ioPre) {
        _avltreenode* rightChild = root->right;
        delete root;
        return rightChild;
      }

      root->data = ioPre->data;
      root->left = _remove(root->left, root->data);
    } 

    root->height = _height(root);

    if (abs(_getBF(root)) > 1) return _balanceAVL(root);

    return root;
  }

  bool _search(_avltreenode* root, T data) {
    if (!root) return false;

    if (data < root->data) {
      return _search(root->left, data);
    } else if (data > root->data) {
      return _search(root->right, data);
    }

    return true;
  }

  void _preorder(_avltreenode* root) {
    if (!root) return;

    std::cout << root->data << " ";
    _preorder(root->left);
    _preorder(root->right);

    return;
  }

  void _clear(_avltreenode* root) {
    if (!root) return;

    _clear(root->left);
    _clear(root->right);

    delete root;
  }

public:
  AVLTree() {
    root = nullptr;
  }

  AVLTree<T>* insert(T data) {
    this->root = _insert(this->root, data);
    
    return this;
  }

  AVLTree<T>* remove(T data) {
    this->root = _remove(this->root, data);

    return this;
  }

  bool search(T data) {
    return _search(this->root, data);
  }

  void preorder() {
    _preorder(this->root);
  }

  int height() {
    return _getHeight(this->root);
  }

  void clear() {
    _clear(this->root);
    this->root = nullptr;

    return;
  }

};

int main() {
  AVLTree<int> t;
  int a[] = {100, 5, 29, 64, 33, 44, 55, 89, 115, 95, 14, 59};

  for (auto i : a) {
    t.insert(i);
  }

  t.preorder();
  std::cout << "\nht: " << t.height() << "\n";

  std::cout << "\nfound 44: " << t.search(44) << "\n";
  std::cout << "\nfound 45: " << t.search(45) << "\n";

  // t.clear();
  for (auto i : a) {
    t.remove(i);
    t.preorder();
    std::cout << "; ht: " << t.height() << "\n";
  }

  return 0;
}