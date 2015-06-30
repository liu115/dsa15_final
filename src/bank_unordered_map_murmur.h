// bank_unordered_map.h
// Copyright 2015-06 dsa_final15
// This is the bank system implemented with unordered map

#ifndef SRC_BANK_UNORDERED_MAP_H_
#define SRC_BANK_UNORDERED_MAP_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "account/account.h"
extern "C" {
  #include "account/encoder/murmurhash.h"  
}

using std::unordered_map;
using std::make_pair;
using std::string;
using std::vector;
using std::pair;
using std::cout;

#define RECOMMEND_SIZE 10
#define MAX_STRING_SIZE 100

uint32_t seed = 479909;

class Hasher {
 public:
  std::size_t operator() (std::string const& key) const {
    uint32_t hashed_key;
    // MurmurHash3_x64_128(&key, key.length(), seed, &hashed_key);
    hashed_key = murmurhash(key.c_str(), key.length(), seed);
    return hashed_key;
  }
};

class EqualFn{
 public:
  bool operator() (std::string const& t1, std::string const& t2) const {
    return t1 == t2;
  }
};

typedef vector<string> RecommendId;

typedef unordered_map<std::string, Account, Hasher, EqualFn> UMap;

class BankUMap {
 public:
  BankUMap(): lg() {}
  ~BankUMap() {}

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
  UMap umap; // unordered_map<std::string, Account>
  TransferLog lg; // this is the log record system with time-record
};

#endif // SRC_BANK_UNORDERED_MAP_H_
