class _bstreenode {
  public data: number;
  public left: _bstreenode | null;
  public right: _bstreenode | null;

  constructor(d: number);
  constructor(d: number) {
    this.data = d;
    this.left = null;
    this.right = null;
  }
}

class BSTree {
  private root: _bstreenode | null;
  private cur: _bstreenode | null;
  private prev: _bstreenode | null;
  private size: number;

  private dataExists: boolean;

  private _ptrReset() {
    this.cur = this.root;
    this.prev = this.root;
    this.dataExists = false;
  }

  private _bstreeSearch(data: number) {
    if (this.cur === null) {
      this.cur = this.prev;
      return false;
    }

    if (data === this.cur?.data) {
      this.dataExists = true;
      return true;
    }

    this.prev = this.cur;
    if (data < this.cur?.data) {
      this.cur = this.cur.left;
    } else {
      this.cur = this.cur?.right;
    }

    return this._bstreeSearch(data);
  }

  private _inorderSucc() {
    if (this.cur === null) return;
    this.cur = this.cur.right;

    while (this.cur != null && this.cur.left != null) {
      this.prev = this.cur;
      this.cur = this.cur.left;
    }

    return;
  }

  private _removeHelper(data: number) {
    this._bstreeSearch(data);

    if (!this.dataExists || this.cur === null || this.prev == null) {
      return;
    }

    this.dataExists = false;
    this.size--;

    // root node with no inorder successor
    if (this.cur == this.prev && this.cur?.right === null) {
      this.root = this.cur?.left;
      // Garbage Collector in working
      return;
    }

    // both the children exist
    if (this.cur?.left != null && this.cur?.right != null) {
      const el: _bstreenode = this.cur;
      this._inorderSucc();
      el.data = this.cur.data;

      this.prev = this.cur;
      this.cur = el.right;
      this.size++;
      this._removeHelper(el.data);

      return
    }

    // leaf node or @least 1 child
    let pointTo: _bstreenode | null =
      (this.cur.right != null)
        ? this.cur.right
        : this.cur.left;

    if (this.cur === this.prev.left) {
      this.prev.left = pointTo;
    } else if (this.cur === this.prev.right) {
      this.prev.right = pointTo
    } else {  // rot node
      this.root = pointTo;
    }

    return;
  }

  private _inorder() {
    if (this.cur === null) return;
    const cur: _bstreenode = this.cur;

    this.cur = cur.left;
    this._inorder();

    process.stdout.write(`${cur.data} `);

    this.cur = cur.right;
    this._inorder();

    return;
  }

  constructor() {
    this.root = null;
    this.cur = this.root;
    this.prev = this.root;
  }

  public search(data: number): boolean {
    this._ptrReset();
    return this._bstreeSearch(data);
  }

  public insert(data: number): void {
    this._ptrReset();
    this._bstreeSearch(data);

    if (this.dataExists) {
      this.dataExists = false;
      return;
    }

    this.size++;

    // root condition
    if (this.root === null || this.cur === null) {
      this.root = new _bstreenode(data);
      return;
    }

    const newNode: _bstreenode = new _bstreenode(data);
    if (data < this.cur.data) {
      this.cur.left = newNode;
    } else {
      this.cur.right = newNode;
    }
  }

  public remove(data: number) {
    this._ptrReset();
    this._removeHelper(data);

    return;
  }

  public inorder() {
    this._ptrReset();
    this._inorder();

    console.log();
    return;
  }

}

const myTree = new BSTree();
const a: number[] = [4, 7, 5, 3, 2, 1]

a.forEach((el: number) => {
  myTree.insert(el);
  myTree.inorder();
})

a.forEach((el: number) => {
  myTree.remove(el);
  myTree.inorder();
})
