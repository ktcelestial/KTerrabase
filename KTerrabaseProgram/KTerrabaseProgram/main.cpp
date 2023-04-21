#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <ctime>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "User.h"
#include "DigitalCurrency.h"
/*
	Stock and Cryptocurrency Simulation and decision-making.
	Difference between stocks and cryptocurrency
*/
using std::cout;
using std::endl;
using std::cin;

void dt() {
	cout << endl << endl;
}

void pause(int dur) {
	int temp = time(NULL) + dur;
	while (temp > time(NULL));
}

/*
	Before begin:
		Do NOT clear files:
			- CCNames.txt
			- stocknames.txt

		Clear files
			- users(.txt)
			-

*/

int main() {
	cout << endl;
	cout.setf(ios::fixed);
	cout.precision(2);
	std::vector<std::string> user_profile;
	std::vector<std::string>::iterator iter; // iterator
	std::ofstream OFS;
	cout << "Welcome to KTerrabase!" << endl << endl;
	cout << "*** RECOMMENDED: FULL SCREEN VIEW ***" << endl << endl;
	cout << "Note: (Common Trading Knowlegde, Etiquette and general advice for trading upon purposeful intentions)" << endl;
	cout << '\t' << "All investments involve great risk and not all risk are suitable for every investor. The value" << endl;
	cout << '\t' << "securities and may flucuate and as a result, investors may lose more than their original investment." << endl;
	cout << '\t' << "The past performance of a security, or financial product does not guarantee future results or returns." << endl;
	cout << '\t' << "Free trading of stocks, ETFs and options refers to $0 commission" << endl;
	cout << endl;
	cout << "Note: (This version of KTerrabase mayh be running on static directory.) " << endl;
	cout << '\t' << "(User-supported directory will be fully implemented soon.)" << endl;
	cout << endl << endl;
	cout << "Are you a new user or an existing user?" << endl;
	cout << "Enter 'N' for New User   |   Enter 'E' for Existing User: ";
	string user_type;
	bool N_FLAG = false;
	bool E_FLAG = false;
	cin >> user_type;
	string n_e; //lowercase for simplicity
	while (N_FLAG == false) {
		if (user_type != "N" && user_type != "E" && user_type != "n" && user_type != "e") {
			// wrong input
			//N_FLAG = false;
			cout << "Your input was incorrect." << endl;
			cout << "Enter 'N' for New User   |   Enter 'E' for Existing User: ";
			user_type.clear();
			cin >> user_type;
		}
		else {

			if (user_type == "N" || user_type == "n") {
				n_e = "n";
			}
			else if (user_type == "E" || user_type == "e") {
				n_e = "e";
			}
			// breaks afterwards
			N_FLAG = true;
		}
	}
	// user_type will be used to until the user's path is decided.
	// NEW USER ===============
	std::string fn;
	std::string ln;
	std::string un;
	std::string pw;
	std::string em;
	std::string DOB;

	if (n_e == "n") {
		// NEW USER! [FN | LN | UN | PW | EMAIL | DOB]
		// do not fill vectors in functions.
		// global and individual variables. fill user_profile vector for writing to file.

		cout << "Thanks for choosing KTerrabase! " << endl;
		NewUser OBJ_1;

		cout << "Please enter your first name (no spaces): ";
		cin >> fn;
		dt();
		cout << "Please enter your last name (no spaces): ";
		cin >> ln;
		dt();
		cout << "Please enter your new username: ";
		un.clear();
		cin >> un;
		N_FLAG = OBJ_1.checkReqUsername(un);
		while (N_FLAG == false) {
			cout << "Your username does not qualify. Please enter another username: " << endl << endl;
			cin >> un;
			N_FLAG = OBJ_1.checkReqUsername(un);
		}
		// once acceptable, write the 
		// OFS.open()
		dt();
		cout << "Please enter your new password: ";
		pw.clear();
		cin >> pw;
		N_FLAG = OBJ_1.checkReqPassword(pw);
		while (N_FLAG == false) {
			cout << "Your password does not qualify. Please enter another password: " << endl << endl;
			cin >> pw;
			N_FLAG = OBJ_1.checkReqPassword(pw);
		}
		dt();
		cout << "Please enter your Date of Birth (mmddyyyy):";
		DOB.clear();
		cin >> DOB;
		N_FLAG = OBJ_1.checkReqDOB(DOB);
		while (N_FLAG == false) {
			cout << "You did not enter your DOB correctly. Please enter your DOB again: " << endl << endl;
			cin >> DOB;
			N_FLAG = OBJ_1.checkReqDOB(DOB);
		}
		dt();
		cout << "Please enter your email address: ";
		em.clear();
		cin >> em;
		N_FLAG = OBJ_1.checkReqEmail(em);
		while (N_FLAG == false) {
			cout << "You did not enter your email correctly. Please enter your email address again: " << endl << endl;
			cin >> em;
			N_FLAG = OBJ_1.checkReqEmail(em);
		}
		dt();

		if (N_FLAG == true) {
			cout << "Thank you!" << endl;
			dt();

			user_profile.push_back(fn);
			user_profile.push_back(ln);
			user_profile.push_back(un);
			user_profile.push_back(pw);
			user_profile.push_back(em);
			user_profile.push_back(DOB);
			// FOR vector into the file as a writing procedure
			OFS.open("users.txt", std::ios::app);
			if (OFS.is_open()) {
				cout << "user file opened" << endl;
				for (iter = user_profile.begin(); iter != user_profile.end(); iter++) {
					OFS << *(iter) << '\t';
				}
				OFS << '\n';
			}
			else if (!OFS.is_open()) {
				cout << "File found, but could not open..." << endl;
			}
			else if (OFS.fail()) {
				cout << "File failed to open..." << endl;
			}
			else {
				cout << "Last else statement... (after user_profile writing)" << endl;
			}
		}
		else {
			cout << "N_FLAG boolean value: FALSE ";
			dt();
		}
		OFS.close();
	}
	else if (n_e == "e") {
		// [ un | pw ]
		// ExistingUser class, so you need object
		ExistingUser OBJ_2;
		cout << endl;
		cout << "Welcome back! We missed you!";
		dt();
		cout << "Please enter your username: ";
		cin >> un;
		int attempts = 3;
		//file check for username
		E_FLAG = false;
		while (E_FLAG == false) {
			E_FLAG = OBJ_2.checkUsername(un);
			if (E_FLAG == true) { // username found
				cout << "Please enter your password: ";
				cin >> pw;
				E_FLAG = OBJ_2.checkPassword(pw);
				while (E_FLAG == false && attempts > 0) {
					attempts--;
					cout << "Wrong password... Please try again. (Attempts remaining: " << attempts << ")" << endl;
					cin >> pw;
					E_FLAG = OBJ_2.checkPassword(pw);
				}
				if (attempts == 0) {
					cout << "Too many attempts! Exiting program... " << endl;
					return 0;
				}
				// if here, username found, AND password is correct
				if (E_FLAG == true) {
					// ... 
				}
			}
			else if (E_FLAG == false) {
				attempts--;
				cout << "Username incorrect. Please try again... " << "Attempts remaining: " << attempts << endl;
				cin >> un;
			}
			if (attempts == 0) {
				// here if: username returns false. password wasn't approached
				cout << "Exiting KTerrabase..." << endl;
				return 0;
			}
		}
	}
	else {
		// nothing. Wrong inputs were already situated.
		cout << "Last else statement... (Wrong input if arriving here)" << endl;
	}

	int main_menu = 0;
	while (main_menu != 4) {
		// At this point, only registered users will proceed.
		// Trying to lessen the load in main() and put in funtions/classes
		cout << endl;
		cout << " ========  KTerrabase: Main Menu  ========" << endl << endl;
		cout << "  What would you like to do? Enter the number next to the option: " << endl;
		cout << "     1.) See list of stocks currently available in KTerrabase" << endl;
		cout << "     2.) See list of Cryptocurrencies available in KTerrabase" << endl;
		cout << "     3.) Open KTerrabase Trading Tool" << endl;
		cout << "     4.) Quit KTerrabase" << endl;

		/*			IDEAS
		*
		* DISPLAY VISUALS FOR THE SIMULATION (MUST BE FULL SCREEN HERE | USING C# TO DISPLAY LINE GRAPH WITH VISUALS? )

		*/

		cout << "Enter here: ";

		cin >> main_menu;
		cout << endl;
		if (main_menu == 1) {
			// display the full names of the stocks
			Stock stock_obj;
			stock_obj.displayAllStock();
		}
		else if (main_menu == 2) {
			// display cryptocurrencies
			// 
			Crypto_C crypto_obj;
			crypto_obj.displayAllCC();
		}
		else if (main_menu == 3) {
			// MAIN === KTERRABASE TRADING TOOL
			/*

			This is the primary part of the code.'
			The trading tool. Due to the main libraries failing to integrate.
			No other option but to

			*/

			cout << "Initiating Trading Tool..." << endl;
			cout << "Running simulation... " << endl;
			DigitalCurrency main_obj;

			const int TOTALTICKS = 8760;
			float* arr = new float[TOTALTICKS];
			// before simulating get the stock/CC name then 
			main_obj.simulate(arr, TOTALTICKS);

			cout << "Simulation finished. " << endl << endl;

			cout << " *** To view ONLY Time stamps and prices at that time, select Option 1. *** " << endl;
			cout << " *** To view visual graph of simulated data, select Option 2. ***" << endl;

			int TRADING_TOOL_MENU = 0;
			while (TRADING_TOOL_MENU != 4) {
				cout << endl << endl;
				cout << "===== KTerrabase: Trading Tool Menu =====" << endl;
				cout << "  What would you like to do? Enter the number next to the option: " << endl;
				cout << "     1.) Display Simulated data values" << endl;
				cout << "     2.) Display Simulated data graph" << endl;
				cout << "     3.) Display Integrated Algorithms" << endl;
				cout << "     4.) Display Calculated Slopes from data values" << endl;
				cout << "     5.) Display Simulation (Last month's performance)" << endl;
				cout << "     6.) Display Simulation (Last 6 month's performance)" << endl;
				cout << "     7.) Display Simulation (Full View / Option 1)" << endl;
				cout << "     8.) Make Analysis on Simulation" << endl;
				cout << "     9.) Quit Trading Tool" << endl << endl;
				cin >> TRADING_TOOL_MENU;

				if (TRADING_TOOL_MENU == 1) {
					main_obj.showSimulationData(arr);
				}
				else if (TRADING_TOOL_MENU == 2) {
					main_obj.showSimulationVisually(arr, main_obj.getPrice());
				}
				else if (TRADING_TOOL_MENU == 3) {
					// Explain which algorithms are used and why.
					// here
					cout << endl;
					cout << "Integrate algorithms are patterns and structures in which can have a " << endl;
					cout << "return in a buy or sell at a different time (refresh)." << endl;
				}
				else if (TRADING_TOOL_MENU == 4) {
					cout << endl;
					main_obj.displaySimulationSlopes(arr);
				}
				else if (TRADING_TOOL_MENU == 5) {
					main_obj.viewSpan_1m(arr);
					cout << endl;
				}
				else if (TRADING_TOOL_MENU == 6) {
					main_obj.viewSpan_6m(arr);
					cout << endl;
				}
				else if (TRADING_TOOL_MENU == 7) {
					main_obj.viewSpan_1y(arr);
					cout << endl;
				}
				else if (TRADING_TOOL_MENU == 8) {
					main_obj.makeAnalysis(arr);
				}
				else if (TRADING_TOOL_MENU == 9) {
					cout << "Exiting KTerrabase Trading Tool" << endl;
					cout << endl;
				}
				else {
					// nothing
				}
			}

			cout << "Would like to perform algorithm analysis on your current simulation?" << endl;
			cout << "(Three most common algorithms are optimized here in KTerrabase.)" << endl;
			cout << "   -   Cup with/without handle" << endl;
			cout << "   -   Double Bottom " << endl;
			cout << "   -   Ascending/Descending Triangle " << endl; // 
			cout << endl;
			cout << "These primary algorithms will be automatically applied on their own depending on simulated data." << endl;
			cout << "..." << endl;
			delete[] arr;
		}
		else if (main_menu == 4) {
			cout << "Exiting KTerrabase..." << endl;
			pause(3);
			return 0;
		}
	}

	return 0;
}