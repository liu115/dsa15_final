// bank_trie.h
// Copyright 2015-06 dsa_final15
// using trie.h to impliement the Bank


#ifndef SRC_BANK_TRIE_H_
#define SRC_BANK_TRIE_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "account/account.h"
#include "trie.h"
using std::make_pair;
using std::string;
using std::vector;
using std::pair;
using std::cout;

#define RECOMMEND_SIZE 10
#define MAX_STRING_SIZE 100

typedef vector<string> RecommendId;

typedef Trie<Account>::trie_node Node;
typedef vector< pair<int, string> > ScoringId;

class BankTrie {
 public:
  BankTrie(): lg() {}
  ~BankTrie() {}
  void loginAccount(const string& id, const string& passwd);
  void createAccount(const string& id, const string& passwd);
  void deleteAccount(const string& id, const string& passwd);
  void mergeAccount(const string& id1, const string& passwd1, const string& id2, const string& passwd2);

  void accountDeposit(const int& money);
  void accountWithdraw(const int& money);
  void transfer(const string& id, const int& money);
  void findAccount(const string& reg_exp);
  void searchHistory(const string& id);

  int max_num(const int a, const int b);
  int min_num(const int a, const int b);
  int abs_num(const int a);
  char next_char(const char);
  char prev_char(const char);
  int computeScoring(const string&, const string&);
  void getRecommend(const string&, RecommendId&);
  void runRecommend(string, string, int, RecommendId&, int, int);

  void existRecommend(const string&, RecommendId&);

 private:
  string current_login_user;
  Trie<Account> tree; // trie.h
  TransferLog lg; // this is the log record system with time-record
  Account *getAccount(const string &id);
  void addAccount(const string &id, Account *ac);
  void computeAllScore(Trie<Account>::trie_node *node, ScoringId &container, const string &oid) {
    if (node == NULL) return;
    if (node->element) {
      string buffer;
      buffer.assign(node->str, 0, ((node->end) + 1));
      int score = computeScoring(oid, buffer);
      container.push_back(make_pair(score, buffer));
    }
    for (int i = 0; i < TREE_WIDTH; i++) {
      computeAllScore(node->child[i], container, oid);
    }
  }
};

#endif
