// account.h
// Copyright 2015 DSA15_final15
// it's the basic data type for bank system
// it contains user id, deposit, hashed password and transfer record
#ifndef SRC_ACCOUNT_H_
#define SRC_ACCOUNT_H_

#include <iostream>
#include <vector>
#include <string>

#define FROM true
#define TO false

class Account {
 public:
  Account(const std::string& s1, const std::string& s2): \
  _id(s1), _passwd(s2), _deposit(0) {}
  ~Account() {}

  // test function
  void show() {
    std::cout << "id = " << _id << std::endl;
    std::cout << "deposit = " << _deposit << std::endl;
    for (int i=0; i < _log.size(); ++i) {
      std::cout << ((_log[i].isFrom)?"From":"To") \
      << " " << _log[i].id << " " << _log[i].amount << std::endl;
    }
  }
  void deposit(const int& money) {
    _deposit += money;
  }
  int transferOut(const std::string id, const int& money) {
    _deposit -= money;
    logNode new_node(TO, money, id);
    _log.push_back(new_node);
    return 0;
  }
  int transferIn(const std::string id, const int& money) {
    _deposit += money;
    logNode new_node(FROM, money, id);
    _log.push_back(new_node);
    return 0;
  }
  void merge(const Account& b) {
    _deposit += b._deposit;
    _log.insert(_log.end(), b._log.begin(), b._log.end());
    b._log.clear();
  }

 private:
  // logNode is used to record transfer history
  struct logNode {
    std::string id;
    int amount;
    bool isFrom;
    logNode(const bool b, const int i, const std::string s): \
    isFrom(b), amount(i), id(s) {}
  };
  std::string _id;
  std::string _passwd;
  int _deposit;
  std::vector<logNode> _log;
};

#endif  // SRC_ACCOUNT_H_
