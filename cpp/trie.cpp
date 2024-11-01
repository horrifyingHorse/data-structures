#include <cstdlib>
#include <iostream>
#include <string>

class TrieNode {
 public:
  friend class Trie;
  TrieNode() {
    c = ' ';
    isWord = false;
    for (int i = 0; i < 26; i++) {
      child[i] = nullptr;
    }
  }

 protected:
  char c;
  TrieNode* child[26];
  bool isWord;
};

class Trie {
 public:
  friend std::ostream& operator<<(std::ostream& s, Trie& t);

  Trie() { root = new TrieNode; }

  Trie& insert(std::string word) {
    TrieNode* cur = root;
    for (char c : word) {
      if (cur->child[c - 'a'] == nullptr) {
        cur->child[c - 'a'] = new TrieNode;
      }
      cur = cur->child[c - 'a'];
    }
    cur->isWord = true;

    return *this;
  }

  Trie& insert(const char* word) { return insert(std::string(word)); }

  bool search(std::string word) {
    TrieNode* cur = root;
    for (char c : word) {
      if (cur->child[c - 'a'] == nullptr) {
        return false;
      }
      cur = cur->child[c - 'a'];
    }
    return cur->isWord;
  }

  bool search(const char* word) { return search(std::string(word)); }

  Trie& remove(std::string word) {
    bool found = true;
    root = removeHelper(root, word, found);

    return *this;
  }

  Trie& remove(const char* word) { return remove(std::string(word)); }

  Trie& clear() {
    root = clearHelper(root);
    root = new TrieNode;
    return *this;
  }

 private:
  TrieNode* root;

  TrieNode* removeHelper(TrieNode* root, std::string word, bool& found) {
    if (root == nullptr) {
      found = false;
      return root;
    }

    if (word == "\0") {
      root->isWord = false;
    } else {
      root->child[word[0] - 'a'] =
          removeHelper(root->child[word[0] - 'a'], word.substr(1), found);
    }

    if (!found) return root;

    bool flag = false;
    for (auto child : root->child) {
      if (child != nullptr) {
        flag = true;
        break;
      }
    }
    if (flag || root->isWord) return root;

    delete root;
    return nullptr;
  }

  void list(std::ostream& s, TrieNode* root, std::string& prefix) {
    if (root == nullptr) return;
    if (root->isWord) std::cout << prefix << "\n";

    std::string storePrefix(prefix);
    int count = 0;

    for (count = 0; count < 26; count++) {
      if (root->child[count] == nullptr) continue;

      prefix += ('a' + count);
      list(s, root->child[count], prefix);
      prefix = storePrefix;
    }
  }

  TrieNode* clearHelper(TrieNode* root) {
    if (!root) return root;

    for (int i = 0; i < 26; i++) {
      if (!root->child[i]) continue;
      root->child[i] = clearHelper(root->child[i]);
    }

    delete root;
    root = nullptr;

    return nullptr;
  }
};

std::ostream& operator<<(std::ostream& s, Trie& t) {
  std::string prefix = "";
  t.list(s, t.root, prefix);
  return s;
}

int main() {
  Trie t;

  while (1) {
    char method;
    std::string query;

    std::cout << "> ";
    std::cin >> method >> query;

    switch (method) {
      case 'i':
        t.insert(query);
        std::cout << "Insertion Satisfied\n";
        break;

      case 's':
        if (t.search(query))
          std::cout << "true\n";
        else
          std::cout << "false\n";
        break;

      case 'd':
        t.remove(query);
        std::cout << "Removed In time.\n";
        break;

      case 'l':
        std::cout << t;
        break;

      case 'c':
        t.clear();
        break;

      case 'e':
        return 0;
    }
  }

  return 0;
}
