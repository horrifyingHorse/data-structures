type node<T> = _avltreenode<T> | null | undefined;

class _avltreenode<T> {
  public data: T;
  public height: number;
  public left: node<T>;
  public right: node<T>;

  constructor(data: T) {
    this.data = data;
    this.height = 1;
    this.left = null;
    this.right = null;
  }
}


class AVLTree<T> {
  private root: node<T>;
  private totalNodes: number;
  private remFlag: boolean;

  private _getHeight(root: node<T>): number {
    return (!root) ? 0 : root.height;
  }

  private _height(root: node<T>): number {
    if (!root) return 0;

    return Math.max(
      this._getHeight(root.left), this._getHeight(root.right)
    );
  }

  private _rotateLeft(root: node<T>): node<T> {
    if (!root || !root.right) return root;

    const newRoot = root.right;
    root.right = newRoot.left;
    newRoot.left = root;

    root.height = this._height(root) + 1;
    newRoot.height = this._height(newRoot) + 1;

    return newRoot;
  }

  private _rotateRight(root: node<T>): node<T> {
    if (!root || !root.left) return root;

    const newRoot = root.left;
    root.left = newRoot.right;
    newRoot.right = root;

    root.height = this._height(root) + 1;
    newRoot.height = this._height(newRoot) + 1;

    return newRoot;
  }

  private _balanceTree(root: node<T>): node<T> {
    if (!root) return root;
    const bf = this._getHeight(root.left) - this._getHeight(root.right);

    if (bf > 1) {
      // Left Subtree Taller
      const child: node<T> = root.left;
      if (this._getHeight(child?.right) > this._getHeight(child?.left)) {
        // LR Case
        root.left = this._rotateLeft(root.left);
      }
      root= this._rotateRight(root);
    } else if (bf < -1) {
      // Right Subtree Taller
      const child: node<T> = root.right;
      if (this._getHeight(child?.left) > this._getHeight(child?.right)) {
        // RL Case
        root.right = this._rotateRight(root.right);
      }
      root = this._rotateLeft(root);
    }

    if(root) root.height = this._height(root) + 1;

    return root;
  }

  private _insert(root: node<T>, data: T): node<T> {
    if (root == null) {
      this.totalNodes++;
      return new _avltreenode<T>(data);
    }

    if (data < root.data) {
      root.left = this._insert(root.left, data);
    } else if (data > root.data) {
      root.right = this._insert(root.right, data);
    } else {
      console.log("Duplicate Insertion of ", data);
      return root;
    }

    root.height = this._height(root) + 1;

    const bf = this._getHeight(root.left) - this._getHeight(root.right);

    if (Math.abs(bf) > 1) {
      return this._balanceTree(root);
    }

    return root;
  }

  private _inorderPredecessor(root: node<T>): node<T> {
    if (!root) return root

    root = root.left;
    while (root && root.right) {
      root = root.right;
    }

    return root;
  }

  private _remove(root: node<T>, data: T): node<T> {
    if (!root) return root;

    if (data < root.data) {
      root.left = this._remove(root.left, data);
    } else if (data > root.data) {
      root.right = this._remove(root.right, data);
    } else {
      if (!this.remFlag) this.remFlag = true;
      const ioPre: node<T> = this._inorderPredecessor(root);
      if (!ioPre) {
        // say hallo to de Garbaba Collector
        return root.right;
      }
      root.data = ioPre.data;
      root.left = this._remove(root.left, ioPre.data);
    }

    root.height = this._height(root) + 1;

    const bf = this._getHeight(root.left) - this._getHeight(root.right);

    if (Math.abs(bf) > 1) return this._balanceTree(root);

    return root;
  }

  private _search(root: node<T>, data: T): boolean{
    if (!root) return false;
    
    if(data < root.data) {
      return this._search(root.left, data);
    } else if (data > root.data) {
      return this._search(root.right, data);
    }

    return true;
  }

  private _preorder(root: node<T>) {
    if (!root) return;

    process.stdout.write(`${root.data} `);
    this._preorder(root.left);
    this._preorder(root.right);
  }

  constructor() {
    this.root = null;
    this.totalNodes = 0;
  }

  public search(data: T): boolean {
    return this._search(this.root, data);
  }

  public insert(data: T) {
    this.root = this._insert(this.root, data);
  }

  public remove(data: T) {
    this.remFlag = false;
    this.root = this._remove(this.root, data);
    if (this.remFlag) this.totalNodes--;
  }

  public height(): number {
    return this._getHeight(this.root);
  }

  public size(): number {
    return this.totalNodes;
  }

  public preorder() {
    this._preorder(this.root);
    console.log()
    return;
  }
}

console.log("a  v  l    T  R  E  E");
const t = new AVLTree<number>();
const a: number[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

a.forEach(i => t.insert(i));

t.preorder();
console.log(t.height(), t.size());
console.log("does 9 and 13 exist?:", t.search(9), t.search(13));

a.forEach(i => {
  t.remove(i);
  t.preorder();
})

console.log(t.height(), t.size());