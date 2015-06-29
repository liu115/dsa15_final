#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "bank_unordered_map.h"

using namespace std;


int main(){
	
	string command, id, password, id2, password2, reg_exp;
	int money;
	std::ios::sync_with_stdio(false);

	BankUMap bank;

	while(cin >> command){

		if(command == "login"){
			cin >> id >> password;
			bank.loginAccount(id, password);
		}

		else if(command == "create"){
			cin >> id >> password;
			bank.createAccount(id, password);
		}

		else if(command == "delete"){
			cin >> id >> password;
			bank.deleteAccount(id, password);
		}

		else if(command == "deposit"){
			cin >> money;
			bank.accountDeposit(money);
		}

		else if(command == "withdraw"){
			cin >> money;
			bank.accountWithdraw(money);
		}
		
		else if(command == "transfer"){
			cin >> id >> money;
			bank.transfer(id, money);
		}

		else if(command == "merge"){
			cin >> id >> password >> id2 >> password2;
			bank.mergeAccount(id, password, id2, password2);
		}

		else if(command == "find"){
			cin >> reg_exp;
			bank.findAccount(reg_exp);
		}

		else if(command == "search"){
			cin >> id;
			bank.searchHistory(id);
		}
	}
	return 0;
}
