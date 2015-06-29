//bank_rb_tree.cpp
//Copyright 2015-6 dsa_final15

#include "bank_rb_tree.h"
extern "C"{
	#include "rb.h"
}

void BankRBTree::loginAccount(const string& id, const string& passwd){
	Account* res = (Account*)rb_find(rb_tree, &id);
	if(res == NULL)
		cout << "ID " << id << " not found\n";
	else{
		if(res->verifyPassword(passwd) == true){
			current_login_user = id;
			cout << "success\n";
		}
		else {
			cout << "wrong password\n";
		}
	}
}

void BankRBTree::createAccount(const string& id, const string& passwd){
	if(rb_find(rb_tree, &id) == NULL){
		Account* new_ac = new Account(id, passwd);
		rb_probe(rb_tree, new_ac);
		cout << "success\n";
	}
	else{
		cout << "ID " << id << " exists, ";
		// recommend 10 best account
	}
}

void BankRBTree::deleteAccount(const string& id, const string& passwd){
	Account* res = (Account*)rb_find(rb_tree, &id);
	if(res == NULL)
		cout << "ID " << id << " not found\n";
	else
		if(res->verifyPassword(passwd) == true){
			rb_delete(rb_tree, res);
			cout << "success\n";
		}
		else
			cout << "wrong password\n";
}

void BankRBTree::mergeAccount(const string& id1, const string& passwd1, const string& id2, const string& passwd2){
	Account* res1 = (Account*)rb_find(rb_tree, &id1);
	Account* res2 = (Account*)rb_find(rb_tree, &id2);
	if(res1 == NULL){
		cout << "ID " << id1 << " not found\n";
		return;
	}
	if(res2 == NULL){
		cout << "ID " << id2 << " not found\n";
		return;
	}
	if(res1->verifyPassword(passwd1) == false){
		cout << "wrong password1\n";
		return;
	}
	if(res2->verifyPassword(passwd2) == false){
		cout << "wrong password2\n";
		return;
	}
	res1->mergeAccount(*res2);
}

void BankRBTree::accountDeposit(const int& money){
	Account* res = (Account*)rb_find(rb_tree, &current_login_user);
	res->depositMoney(money);
}

void BankRBTree::accountWithdraw(const int& money){
	Account* res = (Account*)rb_find(rb_tree, &current_login_user);
	res->withdrawMoney(money);
}

void BankRBTree::transfer(const string& id, const int& money){
	Account* res2 = (Account*)rb_find(rb_tree, &id);
	if(res2 == NULL){
		cout << "ID " << id << " not found\n";
		// recommend 10 best exist id
	}
	else{
		Account* res1 = (Account*)rb_find(rb_tree, &current_login_user);
		res1->transferOut(*res2, money, lg);
	}
}

void BankRBTree::findAccount(const string& rex_exp){
	cout << "\n";
}

void BankRBTree::searchHistory(const string& id){
	Account* res2 = (Account*)rb_find(rb_tree, &id);
	if(res2 == NULL)
		cout << "ID " << id << " not found\n";
	else{
		Account* res1 = (Account*)rb_find(rb_tree, &current_login_user);
		res1->searchHistory(id);
	}		
}