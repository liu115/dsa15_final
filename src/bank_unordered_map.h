// bank_unordered_map.h
// Copyright 2015-06 dsa_final15
// This is the bank system implemented with unordered map

#include "account.h"

class BankUMap {
 public:
  BankUMap(): current_login_user(0) {}
  ~BankUMap() {}

  void createAccount();
  void deleteAccount();
  void mergeAccount();
  const Account& getAccount();
  void transfer();
  void searchHistory();

 private:
  std::string current_login_user;
};
