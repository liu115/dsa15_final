// account.cpp
// Copyright 2015-06 dsa_final15

#include "account.h"

void Account::show() {
	std::cout << "id = " << _id << std::endl;
	std::cout << "deposit = " << _balance << std::endl;
	for (int i=0; i < _log.size(); ++i) {
	  std::cout << ((_log[i].isFrom)?"From":"To") \
	  << " " << _log[i].id << " " << _log[i].amount << std::endl;
	}
}

void Account::login(const std::string& passwd){
	isLogin = verifyPassword(passwd);
}

bool Account::verifyPassword(const std::string& passwd) {
	return (md5(passwd) == _passwd_md5) && (sha256(passwd) == _passwd_sha);
}

void Account::depositMoney(const int& money) {
	_balance += money;
}

int Account::transferOut(const std::string id, const int& t, const int& money) {
	_balance -= money;
	Account::logNode new_node(TO, money, t, id);
	_log.push_back(new_node);
	return 0;
}

int Account::transferIn(const std::string id, const int& t, const int& money) {
	_balance += money;
	Account::logNode new_node(FROM, money, t, id);
	_log.push_back(new_node);
	return 0;
}

void Account::merge(Account& b) {
	_balance += b._balance;
	_log.insert(_log.end(), b._log.begin(), b._log.end());
	b._log.clear();
}
