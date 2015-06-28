// umap_unordered_map.cpp
// Copyright 2015-06 dsa_final15

#include "bank_unordered_map.h"

void BankUMap::loginAccount(const string& id, const string& passwd) {
  UMap::iterator it = umap.find(id);
  if (it == umap.end())
    cout << "ID " << id << " not found\n";
  else {
    if ((*it).second.verifyPassword(passwd)) {
      current_login_user = id;
      cout << "success\n";
    } else {
      cout << "wrong password\n";
    }
  }
}

void BankUMap::createAccount(const string& id, const string& passwd) {
  UMap::iterator it = umap.find(id);
  if (it == umap.end()) {
    Account new_ac(id, passwd);
    umap.insert(make_pair(id, new_ac));
    cout << "success\n";
  } else {
    cout << "ID " << id << " exists, ";
    // recommend 10 best account
  }
}

void BankUMap::deleteAccount(const string& id, const string& passwd) {
  UMap::iterator it = umap.find(id);
  if (it == umap.end()) {
    cout << "ID " << id << " not found\n";
  } else {
    if ((*it).second.verifyPassword(passwd)) {
      umap.erase(it);
      cout << "success\n";
    } else {
      cout << "wrong password\n";
    }
  }
}

void BankUMap::mergeAccount(const string& id1, const string& passwd1, const string& id2, const string& passwd2) {
  UMap::iterator it1 = umap.find(id1);
  UMap::iterator it2 = umap.find(id2);
  if (it1 == umap.end()) {
    cout << "ID " << id1 << " not found\n";
    return;
  }
  if (it2 == umap.end()) {
    cout << "ID " << id2 << " not found\n";
    return;
  }
  if (!(*it1).second.verifyPassword(passwd1)) {
    cout << "wrong password1\n";
    return;
  }
  if (!(*it2).second.verifyPassword(passwd2)) {
    cout << "wrong passwd2\n";
    return;
  }
  (*it1).second.mergeAccount((*it2).second);
}

void BankUMap::accountDeposit(const int& money) {
  UMap::iterator it = umap.find(current_login_user);
  (*it).second.depositMoney(money);
}

void BankUMap::accountWithdraw(const int& money) {
  UMap::iterator it = umap.find(current_login_user);
  (*it).second.withdrawMoney(money);
}

void BankUMap::transfer(const string& id, const int& money) {
  UMap::iterator it2 = umap.find(id);
  if (it2 == umap.end()) {
    cout << "ID " << id << " not found\n";
    // recommend 10 best exist id
  } else {
    UMap::iterator it1 = umap.find(current_login_user);
    (*it1).second.transferOut((*it2).second, money, lg);
  }
}

void BankUMap::findAccount(const string& reg_exp) {
  cout << "\n";
}

void BankUMap::searchHistory(const string& id) {
  UMap::iterator it2 = umap.find(id);
  if (it2 == umap.end()) {
    cout << "ID " << id << " not found\n";
  } else {
    UMap::iterator it1 = umap.find(current_login_user);
    (*it1).second.searchHistory(id);
  }
}
