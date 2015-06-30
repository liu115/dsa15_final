// trie.h
// Copyright 2015-06 dsa_final15
// Caution: allocate a new trie_node must also allocate memory for string and element
#ifndef SRC_TRIE_H_
#define SRC_TRIE_H_

#include <string>
#include <vector>
using namespace std;
#define TREE_WIDTH 62
typedef vector<string> RegString;
template<class T>
class Trie {
 private:
  int size;
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
    T *element;
    const string &str;
    int begin, end;
    trie_node *parent;
    trie_node *child[TREE_WIDTH];
    trie_node(T *ele, const string &_str, int b, int e): \
      element(ele), str(_str), begin(b), end(e) {
        for (int i = 0; i < TREE_WIDTH; i++) {
          child[i] = NULL;
        }
      }
  };
  trie_node *root;
  trie_node *childOf(const char c, trie_node *node) {
    return node->child[map_key(c)];
  }
  
  Trie() {
    size = 0;
    string *empty = new string("");
    root = new trie_node(NULL, *empty, 0, 0); //root->element = NULL
    // root->parent = NULL
  }
  ~Trie() {
    delete &(root->str);
    delete root;
  }
  int getSize() {
    return size;
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
      size++;
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
      size++;
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
      size++;
      return node;
    }
    else if (p < end) {
      trie_node *new_node = insert(node->child[map_key(x[p + 1])], x, p + 1, end, element);
      node->child[map_key(x[p + 1])] = new_node;
      new_node->parent = node;
      return node;
    }
    return NULL;
  }
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
      size--;
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
          if (parent->element == NULL && parent != root) {
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
  
  void regFind(trie_node *node, int node_index, const string &reg, int now, RegString &rs) {
    if (node == NULL) return;
    if (node_index == node->end && now == reg.length() && node && node->element) {
      string tmpid;
      tmpid.assign(node->str, 0, node->end + 1);
      for (int i = 0; i < rs.size(); i++) {
        if (rs[i] == tmpid) return;
      }
      rs.push_back(tmpid);
      return;
    }
    if (reg[now] == '*') {
      regFind(node, node_index, reg, now + 1, rs);
      if (node == root) {
        for (int i = 0; i < TREE_WIDTH; i++) {
          if (node->child[i]) {
            regFind(node->child[i], node_index + 1, reg, now, rs);
          }
        }
        return;
      }
      if (node_index < node->end) {
        regFind(node, node_index + 1, reg, now, rs);
      }
      else if (node_index == node->end) {
        for (int i = 0; i < TREE_WIDTH; i++) {
          if (node->child[i]) {
            regFind(node->child[i], node_index + 1, reg, now, rs);
          }
        }
      }
    }
    else if (reg[now] == '?') {
      if (node == root) {
        for (int i = 0; i < TREE_WIDTH; i++) {
          if (node->child[i]) {
            regFind(node->child[i], node_index, reg, now + 1, rs);
          }
        }
        return;
      }
      if (node_index < node->end) {
        regFind(node, node_index + 1, reg, now + 1, rs);
      }
      else if (node_index == node->end) {
        for (int i = 0; i < TREE_WIDTH; i++) {
          if (node->child[i]) {
            regFind(node->child[i], node_index + 1, reg, now + 1, rs);
          }
        }
      }
    }
    
    else {
      if (node == root) {
        regFind(node->child[map_key(reg[now])], node_index, reg, now + 1, rs);
        return;
      }
      if (node_index < node->end) {
        if (node->str[node_index + 1] == reg[now]) {
          regFind(node, node_index + 1, reg, now + 1, rs);
        }
      }
      if (node_index == node->end) {
        if (node->child[map_key(reg[now])] == NULL) return;
        regFind(node->child[map_key(reg[now])], node_index + 1, reg, now + 1, rs);
      }
    }
  }
};

#endif // SRC_TRIE_H_
