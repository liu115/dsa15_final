//bank_rb_tree.h
//Copyright 2015-6 dsa_final15
//This is the bank system implemented with rb tree

#ifndef SRC_BANK_RB_TREE_H_
#define SRC_BANK_RB_TREE_H_

#include <iostream>
#include <string>
#include <vector>
//#include <regex>
#include <algorithm>
#include "account/account.h"
extern "C" {
#include "rb.h"
}
using std::make_pair;
using std::string;
using std::vector;
using std::pair;
using std::cout;

#define RECOMMEND_SIZE 10
#define MAX_STRING_SIZE 100

typedef vector<string> RecommendId;
typedef pair<string*, Account*> DataNode;

int word_compare(const void *pa, const void *pb, void *param);

class BankRBTree{
public:
	BankRBTree(): lg() {
		rb_tree = rb_create(word_compare, NULL, NULL);
	}
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
	
	int max_num(const int a, const int b);
	int min_num(const int a, const int b);
	int abs_num(const int a);
	char next_char(const char);
	char prev_char(const char);
	int computeScoring(const string&, const string&);
	void getRecommend(const string&, RecommendId&);
	void runRecommend(string, string, int, RecommendId&, int, int);

	void existRecommend(const string&, RecommendId&);

private:
	string current_login_user;
	rb_table *rb_tree;
	TransferLog lg;
};

#endif // SRC_BANK_RB_TREE_H_
