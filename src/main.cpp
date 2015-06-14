#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>


using namespace std;


int main(){
	
	string command, id, password, id2, password2;
	int money;
	std::ios::sync_with_stdio(false);

	while(cin >> command){

		if(command == "login"){
			cin >> id >> password;
			if(/*successful login operation*/)
				cout << "success\n";
			else if(/*no such account ID*/)
				cout << "ID " << id << " not found\n";
			else if(/*wrong password*/)
				cout << "wrong password\n";
		}

		else if(command == "create"){
			cin >> id >> password;
			if(/*ID already exists*/){
			    cout << "ID " << id << " exists, ";
			    //cout << [best 10 unused IDs (separated by ",")];
			}
			else if(/*successful create operation*/)
			    cout << "success\n";
		}

		else if(command == "delete"){
			cin >> id >> password;
			if(/*no such account ID*/)
			    cout << "ID " << id << " not found\n";
			else if(/*wrong password*/)
			    cout << "wrong password\n";
			else if(/*success delete operation*/)
			    cout << "success\n";
		}

		else if(command == "deposit"){
			cin >> money;
			//do deposit money in current account
			cout << "success, " << /*money in account*/ << " dollars in current account\n";
		}

		else if(command == "withdraw"){
			cin >> money;
			if(/*not enough money in account*/)
			    cout << "fail, " << /*money in account*/ << " dollars only in current account\n";
			else if(/*successful withdraw operation*/){
			    //do withdraw money in current account
			    cout << "success, " << /*money in account*/ << " dollars left in  current account\n";
		    }
		}
		
		else if(command == "transfer"){
			cin >> id >> money;
			if(/*ID not found*/){
			    cout << "ID " << id << " not found, ";
			    //cout << [best 10 unused IDs (separated by ",")];
		    }
		    else if(/*not enough money*/){
		        cout << "fail, " << /*money in account*/ << " dollars only in current account";
		    }
		    else if(/*successful transfer operation*/){
		        cout << "success " << /*money in account*/ << " dollars left in current account";
		    }
		}

		else if(command == "merge"){
			cin >> id >> password >> id2 >>password2;
			if(/*no such account ID*/)
			    cout << "ID " << id << " not found";
		    else if(/*no such account ID2*/)
		        count << "ID " << id2 << " not found";
		    else if(/*wrong password*/)
		        cout << "wrong password1";
		    else if(/*wrong password2*/)
		        cout << "wrong password2";
		    else if(/*success merge operation*/)
		        cout << "success, " << id << " has " << /*money in account*/ << " dollars";
		}

		else if(command == "search"){
			cin >> id;
			if(/*no such account ID*/)
			    cout << "ID " << id << " not found";
			else if(/*no record exists*/)
			    cout << "no record";
			else if(/*successful search*/){
			    //do cout all history
			}
		}
	}
	return 0;
}