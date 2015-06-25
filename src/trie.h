// trie.h
// Copyright <em pleh esaelp> 2015-06

#ifndef SRC_TRIE_H_
#define SRC_TRIE_H_

#include <string>

#define TREE_WIDTH 62

class Trie {
 private:
  struct trie_node {
    bool isKey;
    trie_node* father;
    trie_node* child[TREE_WIDTH];
    trie_node(bool k): isKey(k) {}
  };

  int map_key(const char& c) {
    int mp = (int)c - 48; // mapping 0 - 9
    if (mp > 16) mp -= 7; // mapping A - Z
    if (mp > 35) mp -= 6; // mapping a - z
    return mp;
  }

  trie_node *root;

 public:
  Trie() {
    root = new trie_node(false);
    // root->father = NULL
  }

  int insert(const std::string s) {
    int i = 0, mp;
    trie_node *curr = root;
    while (s[i] != '\0') {
      mp = map_key(s[i]);
      if (!curr->child[mp]) {
        curr->child[mp] = new trie_node(false);
        curr->child[mp]->father = curr;
      }
      curr = curr->child[mp];
      i++;
    }
    if (curr->isKey) return 0;
    else {
      curr->isKey = true;
      return 1;
    }
  }

  bool find(const std::string s) {
    int i = 0, mp;
    trie_node *curr = root;
    while (s[i] != '\0') {
      mp = map_key(s[i]);
      if (!curr->child[mp]) {
        return false;
      }
      curr = curr->child[mp];
      i++;
    }
    if (curr->isKey) return true;
    else return false;
  }

  // to do wrong operation protection, it will return NULL
  trie_node* getPos(const std::string s) {
    int i = 0, mp;
    trie_node *curr = root;
    while (s[i] != '\0') {
      mp = map_key(s[i]);
      if (!curr->child[mp])
        return NULL;
      curr = curr->child[mp];
      i++;
    }
    if (curr->isKey) return curr;
    else return NULL;
  }
};

#endif // SRC_TRIE_H_

