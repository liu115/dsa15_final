// bank_unordered_map.h
// Copyright 2015-06 dsa_final15
// This is the bank system implemented with unordered map

#include <iostream>
#include <unordered_map>
#include "account/account.h"
#include "recommend.h"
using std::unordered_map;
using std::make_pair;
using std::string;
using std::cout;

typedef unordered_map<std::string, Account> UMap;

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

 private:
  string current_login_user;
  UMap umap; // unordered_map<std::string, Account>
  TransferLog lg; // this is the log record system with time-record
};
