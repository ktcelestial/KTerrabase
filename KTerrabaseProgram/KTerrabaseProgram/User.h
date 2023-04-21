
#ifndef USER
#define USER
#include <iostream>
#include <string>

#include "pw_check.h"

using std::cout;
using std::endl;
using std::cin;

class NewUser {
private:
	// private field
public:
	// firstname, lastname, email, username, password, DOB
	NewUser();
	bool checkReqPassword(std::string);
	// confirm password
	bool checkReqUsername(std::string);
	bool checkReqEmail(std::string);
	bool checkReqDOB(std::string);
};


// thefnaf2mangle -> Testing22!
// or look in file
class ExistingUser {
private:
	std::string un_temp;

public:
	ExistingUser();
	bool checkUsername(std::string);
	bool checkPassword(std::string);
};


//class Stock {
//private:
//
//protected:
//
//public:
//	Stock();
//
//Tick: every second
//Spans : 1min, 5min, 10min, 30min, 45min,
//1hr, ...., 24hr, : (1tick / 10min)
//1day, ...., 1month : (1tick / 12hr)
//1month, ..., 1yr : (1tick / 15days)
//
//
//};
//
//class Stock : public DigitalCurrency {
//private:
//
//public:
//
//};
//
//class Crypto_C : public DigitalCurrency {
//private:
//
//public:
//
//};


#endif