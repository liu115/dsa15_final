// regex_translate.h
// Copyright 2015-06 dsa_final15
// it use for translate the wildcard_ID in command "find" become regular expression

//#ifndef SRC_REGEX_TRANSLATE_H_
//#define SRC_REGEX_TRANSLATE_H_

#include <iostream>
#include <string>

using namespace std;

void regex_change( string& wildcard_ID){

	string reg = "[a-zA-Z0-9]";
	int pos = 0;

	while( pos != -1){
		pos = wildcard_ID.find( "*", pos);
		if( pos != -1){
			wildcard_ID.insert( pos, reg);
			pos += 12;
		}
	}

	pos = 0;
	while( pos != -1){
		pos = wildcard_ID.find( "?", pos);
		if( pos != -1){
			wildcard_ID.replace( pos, 1, reg);
			pos += 11;	
		}
	}
}