#pragma once
#ifndef PW_CHECK_H
#define PW_CHECK_H
#include <string>
using namespace std;
bool check_UPCASE(string arg);
bool check_LOWCASE(string arg);

// for main:
/*
	std::string password;
	cout << "Enter your password: " << endl;
	cin >> password;
	bool hold;
	hold = checkReqPassword(password);

	while (hold == false) {
		cout << "Your password does not qualify. Please enter another password: " << endl << endl;
		cin >> password;
		hold = checkReqPassword(password);
	}
*/

#endif
