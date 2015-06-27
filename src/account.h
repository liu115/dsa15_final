// account.h
// Copyright 2015 DSA15_final15
// it's the basic data type for bank system
// it contains user id, deposit, hashed password and transfer record
#ifndef SRC_ACCOUNT_H_
#define SRC_ACCOUNT_H_

#include <iostream>
#include <vector>
#include <string>
#include "md5.h"
#include "sha256.h"

#define FROM true
#define TO false

class Account {
 public:
  Account(const std::string& s1, const std::string& s2): _balance(0), isLogin(0), _id(s1) {
    _passwd_md5 = md5(s2);
    _passwd_sha = sha256(s2);
  }
  ~Account() {}

  void show();
  void login(const std::string& passwd);
  bool verifyPassword(const std::string& passwd);
  void depositMoney(const int& money);
  int transferOut(const std::string id, const int& t, const int& money);
  int transferIn(const std::string id, const int& t, const int& money);
  void merge(Account& b);

 private:
  // logNode is used to record transfer history
  struct logNode {
    std::string id;
    int amount;
    bool isFrom;
    int time_record;
    logNode(const bool b, const int i, const int t, const std::string s): \
    id(s), amount(i), isFrom(b), time_record(t) {}
  };

  int _balance;
  bool isLogin;
  std::string _id;
  std::string _passwd_md5;
  std::string _passwd_sha;
  std::vector<logNode> _log;
};

#endif  // SRC_ACCOUNT_H_
