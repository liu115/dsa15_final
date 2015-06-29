//bank_rb_tree.h
//Copyright 2015-6 dsa_final15
//This is the bank system implemented with rb tree

#include <iostream>
#include <string>
#include "account/account.h"
#include "rb.h"
#include "recommend.h"

using namespace std;

class BankRBTree{
public:
	BankRBTree(): lg() {}
	~BankRBTree() {}

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
	rb_table *rb_tree;
	TransferLog lg;
};