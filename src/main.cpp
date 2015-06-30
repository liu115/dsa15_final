#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

#if defined(BANK_UM)
  #include "bank_unordered_map.h"
#elif defined(BANK_RB)
  // #include "bank_rb_tree.h"
#elif defined(BANK_TR)
   #include "bank_trie.h"
#else
  // #include "bank_unordered_map.h"
#endif

using std::cin;


int main(){
	
	string command, id, password, id2, password2, reg_exp;
	int money;
	std::ios::sync_with_stdio(false);

	#if defined(BANK_UM)
		BankUMap bank;
	#elif defined(BANK_RB)
		// BankRBTree bank;
	#elif defined(BANK_TR)
		 BankTrie bank;
	#else
		// BankUMap bank;
	#endif

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
