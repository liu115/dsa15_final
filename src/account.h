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
#include "transfer_log.h"

class Account {
 public:
  Account(const std::string& s1, const std::string& s2): _balance(0), _id(s1) {
    _passwd_md5 = md5(s2);
    _passwd_sha = sha256(s2);
  }
  ~Account() {}
 
  // some steps need to verify password first
  // please do verifyPassword() first  
  bool verifyPassword(const std::string& passwd);

  // operations no bound to last-successfully-login-account
  void mergeAccount(Account& b);

  // operations bound to last-successfully-login-account
  void depositMoney(const int& money);
  void withdrawMoney(const int& money);
  // when use transfer, please check that ID is exist or not first
  void transferOut(Account& b, const int& money, TransferLog& lg);
  // when use search, please check that searched ID is exist or not first
  void searchHistory(const string& id);

  // these two is for debugging
  void printHistory();
  void show();

 private:
  int _balance;
  std::string _id;
  std::string _passwd_md5;
  std::string _passwd_sha;
  std::vector<logNode*> _log;
};

#endif  // SRC_ACCOUNT_H_
