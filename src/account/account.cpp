// account.cpp
// Copyright 2015-06 dsa_final15

#include "account.h"
#include "transfer_log.h"

bool Account::verifyPassword(const std::string& passwd) {
  return (md5(passwd) == _passwd_md5) && (sha256(passwd) == _passwd_sha);
}

void Account::depositMoney(const int& money) {
  _balance += money;
  std::cout << "success, " << _balance << " dollars in current account\n";
}

void Account::withdrawMoney(const int& money) {
  if (_balance < money)
    std::cout << "fail, " << _balance << " dollars only in current account\n";
  else {
    _balance -= money;
    std::cout << "success, " << _balance << " dollars left in current account\n";
  }
}

void Account::transferOut(Account& b, const int& money, TransferLog& lg) {
  // check whether the balance is enough or not
  if (_balance < money) {
    std::cout << "fail, " << _balance << " dollars only in current account\n";
    return;
  }

  // if current balance is enough
  _balance -= money;
  b._balance += money;

  // add new transfer log
  lg.addLog(_id, b._id, money);
  _log.push_back((lg.getCurrPos())->pre); // TO transfer record
  b._log.push_back(lg.getCurrPos()); // FROM transfer record

  std::cout << "success, " << _balance << " dollars left in current account\n";
}

// This is used for checking transfer history, not really used in program
void Account::printHistory() {
  std::vector<logNode*>::iterator it;
  for (it = _log.begin(); it != _log.end(); ++it) {
    if ((*it)->isFrom)
      std::cout << (*it)->time_record << " From " << (*it)->id << " " << (*it)->amount << "\n";
    else
      std::cout << (*it)->time_record << " To " << (*it)->id << " " << (*it)->amount << "\n";
  }
}

void Account::searchHistory(const string& id) {
  bool no_record = true;
  std::vector<logNode*>::iterator it;
  for (it = _log.begin(); it != _log.end(); ++it) {
    if ((*it)->id == id) {
      if (no_record)
        no_record = false;

      if ((*it)->isFrom)
        std::cout << "From " << (*it)->id << " " << (*it)->amount << "\n";
      else
        std::cout << "To " << (*it)->id << " " << (*it)->amount << "\n";
    }
  }
  if (no_record) {
    std::cout << "no record\n";
  }
}

void Account::mergeAccount(Account& b) {
  _balance += b._balance;

  std::vector<logNode*> new_log;
  new_log.reserve(_log.size() + b._log.size());

  std::vector<logNode*>::iterator it_a = _log.begin();
  std::vector<logNode*>::iterator it_b = b._log.begin();

  while (it_a != _log.end() && it_b != b._log.end()) {
    if ((*it_a)->time_record <= (*it_b)->time_record) {
      new_log.push_back(*it_a);
      it_a++;
    } else {
      new_log.push_back(*it_b);
      if ((*it_b)->isFrom)
        (*it_b)->pre->id = _id;
      else
        (*it_b)->next->id = _id;
      it_b++;
    }
  }

  if (it_b != b._log.end()) {
    for (it_b; it_b != b._log.end(); ++it_b) {
      new_log.push_back(*it_b);
      if ((*it_b)->isFrom)
        (*it_b)->pre->id = _id;
      else
        (*it_b)->next->id = _id;
    }
  } else {
    new_log.insert(new_log.end(), it_a, _log.end());
  }

  _log = new_log;

  std::cout << "success, " << _id << " has " << _balance << " dollars\n";
}

void Account::show() {
  std::cout << "_id=" << _id << "\n";
  std::cout << "_balance=" << _balance << "\n";
}
