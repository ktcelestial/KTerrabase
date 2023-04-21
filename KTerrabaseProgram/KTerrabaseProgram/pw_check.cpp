#include <iostream>
#include <string>
#include "pw_check.h"
using namespace std;

bool check_UPCASE(string p) {
	for (int i = 0; p[i] != '\0'; i++) {
		if (p[i] >= 'A' && p[i] <= 'Z') { // for lower
			return true;
		}
	}
	return false; // meaning a lowercase letter wasn't found
}
bool check_LOWCASE(string p) {
	for (int i = 0; p[i] != '\0'; i++) {
		if (p[i] >= 'a' && p[i] <= 'z') { // for lower
			return true;
		}
	}
	return false; // meaning a uppercaseletter wasn't found
}

bool checkReqPassword(string password) {
	bool pw_lengthgate_OPEN = 0;
	bool specialgate_OPEN = 0;
	bool capitalgate_OPEN = 0;
	bool PWgate_OPEN = 0;
	bool UP_case = false;
	bool LOW_case = false;
	// check password length ===================
	int totalChar = 0;
	for (int i = 0; password[i] != '\0'; i++) {
		if (password[i] != ' ') { // checking for space during
			totalChar++;
		}
	}

	if (totalChar <= 50 && totalChar >= 10) {
		pw_lengthgate_OPEN = true;
	}
	else {
		pw_lengthgate_OPEN = false;
	}
	// as false, why false.
	if (pw_lengthgate_OPEN == false) {
		if (totalChar > 50) {
			cout << "Your password is too large: Exceeding maximum allowed length: 50 characters " << endl;
		}
		if (totalChar < 10) {
			cout << "Your password is too short: Shorter than minimal allowed length: 10 characters " << endl;
		}
	}

	// =============================== 
	// at least one special character. keep counting through for every loop. 
	for (int i = 0; password[i] != '\0'; i++) {
		if (password[i] == '!' || password[i] == '@' || password[i] == '#' || password[i] == '$'
			|| password[i] == '%' || password[i] == '^' || password[i] == '&' || password[i] == '*'
			|| password[i] == '(' || password[i] == ')' || password[i] == '<' || password[i] == '>'
			|| password[i] == '[' || password[i] == ']' || password[i] == '-' || password[i] == '=') {
			specialgate_OPEN = true; // symbol was found. gate can open.
		}
		else {
			specialgate_OPEN = false;
		}
	}

	//================================ 
	if (check_UPCASE(password) == true && check_LOWCASE(password) == true) {
		capitalgate_OPEN = true;
	}
	else if (check_UPCASE(password) == false && check_LOWCASE(password) == true) {
		cout << "There are no capital letters in your input" << endl;
		capitalgate_OPEN = false;
	}
	else if (check_UPCASE(password) == true && check_LOWCASE(password) == false) {
		cout << "There are no lowercase letter in your input" << endl;
		capitalgate_OPEN = false;
	}
	else {
		// empty
	}

	//===============================
	// cout if's ------------
	// specialgate 
	if (specialgate_OPEN == false) { // saying specialgate_OPEN is false
		cout << "There are no special characters in your password. " << endl;
	}
	// capitalgatecheck_UPCASE(password) == true && check_LOWCASE(password) == trueP_
	// PWgate_OPEN needs every gate to be open
	if (specialgate_OPEN == true && pw_lengthgate_OPEN == true && capitalgate_OPEN == true) {
		PWgate_OPEN = true;
	}
	else {
		PWgate_OPEN = false;
	}
	cout << PWgate_OPEN << endl;
	return PWgate_OPEN; // this will be return and check for main loop in int main()
}
