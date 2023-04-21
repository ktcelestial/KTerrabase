// #pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

#include "User.h"
#include "pw_check.h"
using namespace std;

NewUser::NewUser() {
	//cout << "Accessing NewUser (constructor) now...";
	return;
}

//====================================================
bool NewUser::checkReqPassword(std::string password) {
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
			break;
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
	return PWgate_OPEN; // this will be return and check for main loop in int main()
}

//=====================================================
bool NewUser::checkReqUsername(std::string username) {
	bool us_lengthgate_OPEN = 0;
	bool spacesgate_OPEN = 0;
	bool takengate_OPEN = 0;
	int us_LENGTH = 0;

	//check the length then if spaces are present. 
	us_LENGTH = username.length(); // testing out length instead of manual
	// length check

	if (us_LENGTH <= 50 || us_LENGTH >= 10) {
		us_lengthgate_OPEN = true;
	}
	else {
		us_lengthgate_OPEN = false;
	}
	// cout if's -------------------------------------
	if (us_LENGTH < 10) {
		cout << "Username is too short. (Must be more than 10 characters!) " << endl;
		return false;

	}
	else if (us_LENGTH > 20) {
		cout << "Username is too long. (Must be less than 20 characters) " << endl;
		return false;
	}

	//spaces
	for (int i = 0; i < us_LENGTH; i++) {
		// will stop at index "us_LENGTH - 1"
		if (username[i] == ' ') {
			cout << "No spaces are allowed!" << endl;
			spacesgate_OPEN = false; // keep gate closed as space was found
			break;
		}
		else {
			spacesgate_OPEN = true;
		}
	}
	// file i/o outside of function if initial username gates are all open
	takengate_OPEN = true;
	bool un_flag = false;
	ifstream IFS_obj;

	std::vector<std::string> intake_vec;
	IFS_obj.open("users.txt", std::ios::in);
	//std::ofstream OFS_OBJ;
	do {
		if (IFS_obj.is_open()) {
			std::string line;
			int count = 0;
			// WORKS ----------- 09/26/2022
			while (getline(IFS_obj, line)) {
				// std::cout << line << "\n" << endl;
				// cout << "Current line :" << line << endl;     <---Debug

				std::istringstream iss(line);
				std::string fld;
				intake_vec.clear();
				while (getline(iss, fld, '\t')) { //  tab delimit
					intake_vec.push_back(fld);
				}
				// vector filled. vec[0], vec[1], vec[2], vec[3]
				// std::vector<std::string>::iterator iter__;
				
				if (username == intake_vec[2]) {
					// if the username is the same on that line, then choose a different username
					un_flag = false;
					cout << "Username is already taken. Please enter another username: ";
					cin >> username;
				}
				else if (IFS_obj.eof() == false) {
					// then continue
					cout << "continuing..." << endl;
					break;
				}
				else if (IFS_obj.eof() == true) {
					cout << "breaking if-else stmt" << endl;
					break;
				}
			}
			// cout << "Thank you!" << endl;
			// // ^^^ Don't say thank you until all flags are completed.
		   // when do I "use then fill" the username slot then? Here

			un_flag = true;
			// end ^
		}
		else if (IFS_obj.fail()) {
			cout << "Could not connect to file system..." << endl;
			break;
		}
		else if (!IFS_obj.is_open()) {
			cout << "File found, but can not open..." << endl;
		}
		else {
			cout << "Inside last else statement..." << endl;
		}
	} while (un_flag == false);




	//MAIN USERNAME GATE =============================
	if (spacesgate_OPEN == true && us_lengthgate_OPEN == true && takengate_OPEN == true) {
		return true;
	}
	else {
		return false;
	}

	IFS_obj.close();
	return false;
}

bool NewUser::checkReqEmail(std::string em) {
	// look for @ symbol
	for (int i = 0; em[i] != '\0'; i++) {
		if (em[i] == '@') {
			// good
			return true;
		}
		else {
			// nothing
		}
	}
	return false;
}

//===============================================
bool NewUser::checkReqDOB(string mmddyyyy) {
	// mmddyyyy -> mm: [0][1]
	//          -> dd: [2][3]
	//          -> yyyy: [4][5][6][7]

	//splitting into mm dd yyyy
	bool mm_O = false;
	bool dd_O = false;
	bool yyyy_O = false;
	std::string mm, dd, yyyy;
	for (int i = 0; i < 2; i++) {
		mm += mmddyyyy[i];
	}
	for (int i = 2; i < 4; i++) {
		dd += mmddyyyy[i];
	}
	for (int i = 4; i < 8; i++) {
		yyyy += mmddyyyy[i];
	}

	// mm
	if (mm[0] == '0') {
		if (mm[1] >= '1' && mm[1] <= '9') {
			mm_O = true;
		}
		else
			mm_O = false;
	}
	else if (mm[0] == '1') {
		if (mm[1] == '0' || mm[1] == '1' || mm[1] == '2') {
			mm_O = true;
		}
		else
			mm_O = false;
	}
	// dd -------------------------------------
	if (dd[0] == '0') {
		if (dd[1] >= '1' && dd[1] <= '9') {
			dd_O = true;
		}
		else
			dd_O = false;
	}
	else if (dd[0] == '1') {
		if (dd[1] >= '0' && dd[1] <= '9') {
			dd_O = true;
		}
		else
			dd_O = false;
	}
	else if (dd[0] == '2') {
		if (dd[1] >= '0' && dd[1] <= '9') { // february 28th is ignored
			dd_O = true;
		}
		else
			dd_O = false;
	}
	else if (dd[0] == '3') {
		if (dd[1] == '0' || dd[1] == '1') { // february 28th is ignored
			dd_O = true;
		}
		else
			dd_O = false;
	}
	else
		dd_O = false;
	// yyyy
	// yyyy ignored to pass current date check
	yyyy_O = true;

	// cout << "DOB flag check: " << mm_O << " " << dd_O << " " << yyyy_O << endl;
	if (mm_O == true && dd_O == true && yyyy_O == true) {
		return true;
	}
	else {
		return false;
	}


	// ==========================================
	// 

}

ExistingUser::ExistingUser() {
	// empty
}

bool ExistingUser::checkUsername(std::string username) {
	// match the given username with one the exist in the file.
	// open up the file object again or make a new one.
	//bool un_check = false;
	std::ifstream EXIST_IFSOBJ;
	EXIST_IFSOBJ.open("users.txt", std::ios::in);
	if (EXIST_IFSOBJ.is_open()) {
		// At some point: check: eof(), fail()
		std::vector<std::string> intake_vec2;
		std::vector<std::string>::iterator iter__;
		std::string line;
		int count = 0;
		char RETRY_F = '\0';
		// WORKS ----------- 09/26/2022
		while (getline(EXIST_IFSOBJ, line) || RETRY_F == 'y' || RETRY_F == 'Y') {
			// std::cout << line << "\n" << endl;
			std::istringstream iss(line);
			std::string fld;
			intake_vec2.clear();
			while (getline(iss, fld, '\t')) {
				intake_vec2.push_back(fld);
			}
			// vector filled. vec[0], vec[1], vec[2], vec[3]
			// std::vector<std::string>::iterator iter__;
			if (username == intake_vec2[2]) {
				// if the username is the same on that line, then choose a different username
				un_temp = username; // un_temp is a private var
				EXIST_IFSOBJ.close();
				return true;
			}
			else if (EXIST_IFSOBJ.eof() == true && username != intake_vec2[2]) {
				cout << "Username '" << username << "' not found." << endl;
				cout << "Would you like to enter another username?  Y  |  N ";
				cin >> RETRY_F;
			}
		}
	}
	else if (!EXIST_IFSOBJ.is_open()) {
		cout << "Could not connect to server. " << endl;
		return false;
	}
	else if (EXIST_IFSOBJ.fail() == true) {
		cout << "File found, but can not be opened. " << endl;
		return false;
	}
	else {
		// empty
		cout << "passing" << endl;
	}
}

bool ExistingUser::checkPassword(std::string pw) {
	// assume username softly as it already ran
	std::ifstream EXIST_IFSOBJ;
	EXIST_IFSOBJ.open("users.txt", std::ios::in);
	if (EXIST_IFSOBJ.is_open()) {
		// At some point: check: eof(), fail()
		std::vector<std::string> intake_vec2;
		std::vector<std::string>::iterator iter__;
		std::string line;
		while (getline(EXIST_IFSOBJ, line)) {
			// std::cout << line << "\n" << endl;
			std::istringstream iss(line);
			std::string fld;
			intake_vec2.clear();
			while (getline(iss, fld, '\t')) {
				intake_vec2.push_back(fld);
			}
			// cout << intake_vec2[0] << " " << intake_vec2[1] << " " << intake_vec2[2] << " " << intake_vec2[3];
			// std::vector<std::string>::iterator iter__;
			if (un_temp == intake_vec2[2]) {
				// if the username is the same on that line, then choose a different username
				if (pw == intake_vec2[3]) {
					cout << "Access granted to " << un_temp << endl;
					cout << endl;
					cout << "Welcome back " << intake_vec2[0] << " " << intake_vec2[1] << "!" << endl;
					cout << "You are successfully logged in." << endl << endl;
					EXIST_IFSOBJ.close();
					return true;
				}
				else {
					EXIST_IFSOBJ.close();
					return false;
				}
				EXIST_IFSOBJ.close();
				return true;
			}
			else if (EXIST_IFSOBJ.eof() == true) {
				cout << "Username '" << un_temp << "' not found." << endl;
				EXIST_IFSOBJ.close();
				return false;
			}
		}
		cout << "getline(EXIST_IFSOBJ, line) ... fault!" << endl;
	}
}


/*

IFS_obj.open("C:/Users/ktvei/source/repos/FileIO_Usage/FileIO_Usage/users.txt", std::ios::in);
		do {
			if (IFS_obj.is_open()) {
				std::string line;

				int count = 0;
				while (getline(IFS_obj, line)) {
					// std::cout << line << "\n" << endl;
					cout << "Current line :" << line << endl;
					std::istringstream iss(line);
					std::string fld;
					intake_vec.clear();
					while (getline(iss, fld, '\t')) {
						intake_vec.push_back(fld);
					}
					// vector filled. vec[0], vec[1], vec[2], vec[3]
					// std::vector<std::string>::iterator iter__;
					cout << "intake_vec[2]" << intake_vec[2] << endl;
					if (un == intake_vec[2]) {
						// if the username is the same on that line, then choose a different username
						un_flag = false;
						cout << "Username is already taken. Please enter another username: ";
						cin >> un;
					}
					else if (IFS_obj.eof() == false) {
						// then continue
						cout << "continuing..." << endl;
						break;
					}
					else if (IFS_obj.eof() == true) {
						cout << "breaking if-else stmt" << endl;
						break;
					}
				}
				cout << "Thank you!" << endl;
				un_flag = true;
				// end ^
			}
		} while (un_flag == false);
	}
	else {
		// empty
	}
	// check by username, password: vec[2], vec[3]

	IFS_obj.close();
	OFS_obj.close();

*/
