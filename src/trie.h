// trie.h
// Copyright 2015-06 dsa_final15

#ifndef SRC_TRIE_H_
#define SRC_TRIE_H_

#include <string>
using namespace std;
#define TREE_WIDTH 62
template<class T>
class Trie {
 private:
  int map_key(const char& c) {
    int mp = (int)c - 48; // mapping 0 - 9
    if (mp > 16) mp -= 7; // mapping A - Z
    if (mp > 35) mp -= 6; // mapping a - z
    return mp;
  }
  int prefix(const string &x, int x_begin, int x_end, \
      const string &key, int key_begin, int key_end) {
    for (int i = x_begin; i <= x_end; i++) {
      if (i > key_end || x[i] != key[i]) return i - 1;
    }
    return x_end;
  }
  
 public:
  struct trie_node {
    bool isLeaf;
    T *element;
    const string &str;
    int begin, end;
    trie_node *parent;
    trie_node *child[TREE_WIDTH];
    trie_node(T *ele, const string &_str, int b, int e): \
      element(ele), str(_str), begin(b), end(e) {
      }
  };
  trie_node *root;
  
  Trie() {
    string *empty = new string("");
    root = new trie_node(NULL, *empty, 0, 0); //root->element = NULL
    // root->parent = NULL
  }
  ~Trie() {
    delete &(root->str);
    delete root;
  }

  trie_node *find(trie_node *node, const string &x, int begin, int end) {
    if (node == NULL) return NULL;
    if (node == root) 
      return find(node->child[map_key(x[begin])], x, begin, end);
    int p = prefix(x, begin, end, node->str, node->begin, node->end);
    if (p == end && p == node->end) return node;
    if (p == end) return NULL;
    if (p == node->end)
      return find(node->child[map_key(x[p + 1])], x, p + 1, end);
    return NULL;
  }
  void print_trie(trie_node *node, int d) {
    if (node == NULL) return;
    for (int i = 0; i < d; i++) cout << " ";
    for (int i = node->begin; i <= node->end; i++) cout << (node->str[i]);
    if (node->element) cout << " " << *(node->element);
    puts("@");
    for (int i = 0; i < TREE_WIDTH; i++) {
      print_trie(node->child[i], d + 1);
    }
  }
  void split(trie_node *node, int end) {
    trie_node *parent = node->parent;
    trie_node *new_node = new trie_node(NULL, node->str, node->begin, end);
    node->begin = end + 1;
    new_node->parent = parent;
    parent->child[map_key(new_node->str[new_node->begin])] = new_node;
    new_node->child[map_key(node->str[node->begin])] = node;
    node->parent = new_node;

  }

  trie_node *insert(trie_node *node, const string &x, int begin, int end, T *element) {
    if (node == NULL) {
      trie_node *new_node = new trie_node(element, x, begin, end);
      //hang element
      return new_node;
    }
    //cout << node->str << " " << node->begin << " " << node->end << '\n';
    if (node == root) {
      trie_node *new_node = insert(node->child[map_key(x[begin])], x, begin, end, element);
      node->child[map_key(x[begin])] = new_node;
      new_node->parent = node;
      return new_node;
    }
    int p = prefix(x, begin, end, node->str, node->begin, node->end);
    if (p == node->end && p == end) {
      node->element = element;
      return node; //hang the element
    }
    if (p < node->end && p < end) {
      split(node, p);
      //puts("HAHAHA");
      node = node->parent;
      //cout << "split " << node->str << " " << node->begin << " " << node->end << '\n';
      trie_node *new_node = insert(node->child[map_key(x[p + 1])], x, p + 1, end, element);
      node->child[map_key(x[p + 1])] = new_node;
      new_node->parent = node;
      return node;
    }
    else if (p < node->end) { //going to split
      split(node, p);
      node = node->parent;
      //cout << "split "<< node->str << " " << node->begin << " " << node->end << '\n';
      node->element = element; //hang the element
      return node;
    }
    else if (p < end) {
      trie_node *new_node = insert(node->child[map_key(x[p + 1])], x, p + 1, end, element);
      node->child[map_key(x[p + 1])] = new_node;
      new_node->parent = node;
      return node;
    }
  }/*
  void merge_parent(trie_node *node) {
    trie_node *parent = node->parent;
    //parent->child[map_key(node->str[node->begin])] = NULL;
    for (int i = 0; i < 62; i++) {
      node->child[i]->parent = parent;
      parent->child[i] = node->child[i];
    }
    parent->str = node->str;
    parent->end = node->end;
    parent->element = node->element;
    delete node;
  }*/
  void merge_child(trie_node *node, trie_node *child) {
    child->parent = node->parent;
    node->parent->child[map_key(node->str[node->begin])] = child;
    child->begin = node->begin;
    delete node;
  }
  void remove(trie_node *node, const string &x, int begin, int end) {
    if (node == NULL) return;
    if (node == root) {
      remove(node->child[map_key(x[begin])], x, begin, end);
      return ;
    }
    int p = prefix(x, begin, end, node->str, node->begin, node->end);
    if (p == end && p == node->end) {
      //delete this node
      trie_node *parent = node->parent;
      int sibling_num = 0, child_num = 0;
      trie_node *first_sibling = NULL, *first_child;
      for (int i = 0; i < 62; i++) {
        if (parent->child[i] && parent->child[i] != node) {
          sibling_num++;
          first_sibling = parent->child[i];
        }
        if (node->child[i]) {
          child_num++;
          first_child = node->child[i];
        }
      }
      if (sibling_num == 0) {
        if (child_num == 0) {
          node->parent->child[map_key(node->str[node->begin])] = NULL;
          delete node;
        }
        else if (child_num == 1) {
          merge_child(node, first_child);
        }
        else if (child_num > 1) {
          node->element = NULL;
        }
      }
      else if (sibling_num == 1) {
        if (child_num == 0) {
          node->parent->child[map_key(node->str[node->begin])] = NULL;
          delete node;
          if (parent->element == NULL) {
            merge_child(parent, first_sibling);
          }
        }
        else if (child_num == 1) {
          merge_child(node, first_child);
        }
        else if (child_num > 1) {
          node->element = NULL;
        }
      }
      else if (sibling_num > 1) {
         if (child_num == 0) {
          node->parent->child[map_key(node->str[node->begin])] = NULL;
          delete node;
        }
        else if (child_num == 1) {
          merge_child(node, first_child);
        }
        else if (child_num > 1) {
          node->element = NULL;
        }
      }
    }
    if (p == end) {
      return;
    }
    if (p == node->end) {
      remove(node->child[map_key(x[p + 1])], x, p + 1, end);
    }
    

  }
  // to do wrong operation protection, it will return NULL
  /*
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
  */
};

#endif // SRC_TRIE_H_
