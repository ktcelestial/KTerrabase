// .cpp of Digital Currency

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <cmath>
#include "DigitalCurrency.h"

using std::cout;
using std::endl;
using std::cin;

DigitalCurrency::DigitalCurrency() {
	// make file for every algorithm.
	// job: create algorithms
	// write to file.
	// Algorithms has a span of 1 day.
	// Ex. General: [.........[Alg1]....[Alg2]....]
	cout << "Almost there! Thank you for waiting." << endl;
	OFS.open("generated_data.txt");
	std::vector<int> alg1_slopes;
	std::vector<int> alg2_slopes;
	std::vector<int> alg3_slopes;

	alg1_slopes.push_back(2); // 2 or higher (limit: 5)
	for (int i = -4; i < 14; i++) {
		alg1_slopes.push_back(i); // i or -4 lower in imagination
	}
	// LIMIT: [0]->[2190] cannot be more than 10,950 (5:1).
	// we just need to know the slopes

	//DOUBLE BOTTOM ALG (easy):=============
	// look for lowest point in the graph.
	// if another point is within the same y-axis area,
		// then, the alg is ident as Double Bottom.
		// no need for vector. Algorithm mightn accidentally be within another algorithm
	// create function: bool doubleBottom();
	// 
	//-----------------------------

	// 
	return;
}

float* DigitalCurrency::simulate(float* arr, const int TOTALTICKS) {
	srand(time(NULL));

	float min, max, f = 0.0;


	float slope;
	int tick_counter = 0;
	int idx = 0;

	cout.setf(std::ios::fixed);
	cout.precision(2);

	// SIMULATION =================
	cout << endl;
	cout << "Would you like to enter a Stock or a Cryptocurrency? ('S' | 'C'): " << endl;
	std::string s_c;
	std::string des_stock;
	float s_c_price;
	IFS.close();
	cin >> s_c;
	bool sc_FLAG = false;
	while (sc_FLAG == false) {
		if (s_c != "S" && s_c != "C" && s_c != "s" && s_c != "c") {
			// wrong input
			//N_FLAG = false;
			cout << "Your input was incorrect." << endl;
			cout << "Enter 'S' for Stock   |   Enter 'C' for Cryptocurrency: ";
			s_c.clear();
			cin >> s_c;
		}
		else {
			std::vector<std::string> intake_CC_vec;
			if (s_c == "S" || s_c == "s") {
				s_c = "s";

				cout << "Please enter a stock name (BY ABBR. -- Ex: TSLA)" << endl;
				cout << "(Feel free to check the list of stocks in Option 1 in the Main Menu)" << endl;
				cout << "Enter here: ";
				cin >> des_stock;
				cout << "Enter current price of '" << des_stock << "': " << endl;
				cin >> f;
				// check File IO. first element '\t' delimited
				std::string line;
				IFS.close();
				IFS.open("stocknames.txt.txt");
				if (IFS.is_open() == true) {
					cout << "Searching stocks..." << endl << endl;
					std::istringstream iss(line);
					std::string fld;
					while (IFS >> line) {
						// std::cout << line << "\n" << endl;
						// cout < < "Current line :" << line << endl;
						while (getline(iss, fld, '\t')) {
							if (fld == des_stock) {
								cout << "Name found!" << endl;
							}
						}
						if (IFS.eof() == false) {
							// then continue
							//cout << "continuing..." << endl;
							break;
						}
						else if (IFS.eof() == true) {
							//cout << "breaking if-else stmt" << endl;

						}
					}
				}
				else if (IFS.is_open()) {
					cout << "File could not be opened..." << endl;
				}
			}
			else if (s_c == "C" || s_c == "c") {
				s_c = "c";
				std::string des_CC;
				cout << "Please enter a cryptocurrency name (BY ABBR. -- Ex: BTC)" << endl;
				cout << "(Feel free to check the list of cryptocurrencies in Option 2 in the Main Menu)" << endl;
				cout << "Enter here: ";
				cin >> des_CC;
				cout << "Enter current price of '" << des_CC << "': " << endl;
				cin >> f;
				// File IO. last element
				std::string line;
				IFS.close();
				IFS.open("CCnames.txt.txt");
				if (IFS.is_open() == true) {
					cout << "Searching cryptocurrencies..." << endl << endl;
					std::istringstream iss(line);
					std::string fld;
					while (IFS >> line) {
						// std::cout << line << "\n" << endl;
						// cout < < "Current line :" << line << endl;
						while (getline(iss, fld, '\t')) {
							if (fld == des_CC) {
								cout << "Name found!" << endl;
							}
						}
						if (IFS.eof() == false) {
							// then continue
							//cout << "continuing..." << endl;
							break;
						}
						else if (IFS.eof() == true) {
							//cout << "breaking if-else stmt" << endl;

						}
					}
				}
				else if (IFS.is_open()) {
					cout << "File could not be opened..." << endl;
				}
			}
			// breaks afterwards
			sc_FLAG = true;
		}
	}



	cout << endl;
	priceVisualDisplaySpan = f;
	float diff = 0.0;
	int inc_dec;

	min = f * 0.99;
	max = (f * 0.01) + f;

	// filling array
	for (int i = 0; i < TOTALTICKS; i++) {
		inc_dec = rand() % 2 + 0;
		if (inc_dec == 1) { // cushion moves up
			max++; min++;
			arr[i] = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
			if (arr[i] < 0.01) {
				// cout << i + 1 << '\t' << 0.01 << endl;
			}
			else {
				// cout << i + 1 << '\t' << arr[i] << endl;
			}

			// OFS << (i + 1) << '\t' << f << '\n';
		}
		else if (inc_dec == 0) { // cushion moves down
			max--; min--;
			arr[i] = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
			if (arr[i] < 0.01) {
				// cout << i + 1 << '\t' << 0.01 << endl;
			}
			else {
				// cout << i + 1 << '\t' << arr[i] << endl;
			}
			// OFS << (i + 1) << '\t' << f << '\n';
		}
	}

	//pulling slopes
	if (!arr || TOTALTICKS == 0) {
		cout << "INT_MAX caught." << endl;
	}
	else {
		cout << "Last element: " << arr[TOTALTICKS - 1] << endl;
	}

	// for loop: 
	float* curr_ptr = arr;
	float* next_ptr = &arr[1];
	// cout << *curr_ptr << "    " << *next_ptr << endl;
	slopes.clear(); // first time occurrence
	for (tick_counter = 1;/* *(next_ptr) != NULL */ idx < TOTALTICKS; curr_ptr = next_ptr, next_ptr++, idx++) {
		if (idx == (TOTALTICKS - 1)) {
			//cout << "*(curr_ptr) is: " << *(curr_ptr) << endl;
			break;
		}
		else {
			//cout << "*(curr_ptr) is: " << *(curr_ptr) << " while *(next_ptr) is: " << *(next_ptr) << " " << idx << endl << endl;
		}
		try {
			if (((tick_counter + 1) - tick_counter) == 0) {
				throw std::runtime_error("Error: Division by zero attempted...");
			}
			else {
				// cout << endl;
				//cout << *(curr_ptr) << "  ->  " << *(next_ptr) << " gives slope: ";
				slope = ((*(next_ptr)-*(curr_ptr)) / 1);
				//cout << " " << slope << endl;

				slopes.push_back(slope);
				//cout << endl;
			}
		}
		catch (std::runtime_error& ex) {
			// something
		}

	}

	// by this point the slope vector is filled with "simulated slopes
	// or another function
	return arr;
}

void DigitalCurrency::showSimulationData(float* a) {
	cout << "Displaying simulation... " << endl << endl;
	for (int i = 0; i < 8760; i++) {
		cout << i + 1 << '\t' << a[i] << endl;
	}
	return;
}

void DigitalCurrency::displaySimulationSlopes(float* a) {
	cout << "Displaying simulation slopes... " << endl << endl;
	int idx = 1;
	for (iter__ = slopes.begin(); iter__ != slopes.end(); iter__++, idx++) {
		cout << " (Hour #" << idx << " to Hour # " << (idx + 1) << ": " << *(iter__) << endl;
	}

	return;
}

// making void temporarily
void DigitalCurrency::doubleBottom(float* arr) {

	//  lowest data tick in the set: compare to current price, find second lowest
	// second lowest price MUST be lower than the input price
	float lowest = 100000.00;
	float sec_lowest = lowest;

	for (int i = 0; i < 8760; i++) {
		// for every element, find lowest price of span.
		// then find second within range.
		//after second bottom, only up between 1-2 slope
		if (arr[i] < lowest) {
			lowest = arr[i];
		}
	}

	std::vector<std::string> intake_vec;
	// find the lowest data tick in the set
	std::ifstream file_obj;
	file_obj.open("generated_data.txt");
	if (file_obj.is_open()) {
		std::string line;
		int count = 0;
		// WORKS ----------- 09/26/2022
		while (file_obj >> line) {
			// std::cout << line << "\n" << endl;
			cout << "Current line :" << line << endl;
			std::istringstream iss(line);
			std::string fld;
			intake_vec.clear();
			while (getline(iss, fld, '\t')) {
				intake_vec.push_back(fld);
			}
			if (file_obj.eof() == false) {
				// then continue
				cout << "continuing..." << endl;
				break;
			}
			else if (file_obj.eof() == true) {
				cout << "breaking if-else stmt" << endl;

			}
		}
		// cout << "Thank you!" << endl;
		// // ^^^ Don't say thank you until all flags are completed.
	   // when do I "use then fill" the username slot then? Here

		//un_flag = true;
		// end ^
	}
	else {
		// ...
	}
	return;
}

DigitalCurrency::~DigitalCurrency() {
	IFS.close();
	OFS.close();
	return;
}

Stock::Stock() {
	// 

}

void Stock::displayAllStock() {
	IFS.close();
	IFS.open("stocknames.txt.txt");
	if (IFS.is_open()) {
		std::string line;
		// WORKS ----------- 09/26/2022
		while (getline(IFS, line)) {
			cout << line << endl;
		}
	}
	else if (IFS.fail()) {
		cout << "File failed to open. (Er. .fail() returned true)" << endl;
	}
	IFS.close();
	return;
}

Crypto_C::Crypto_C() {

}

void Crypto_C::displayAllCC() {
	// Format
	// 1	Bitcoin		BTC (tab-delimited)
	IFS.close(); // reset file object pointer in file?
	IFS.open("CCnames.txt.txt");
	if (IFS.is_open()) {
		std::string line;
		// WORKS ----------- 09/26/2022
		while (getline(IFS, line)) {
			cout << line << endl;
		}
	}
	else if (IFS.fail()) {
		cout << "File failed to open. (Er. .fail() returned true)" << endl;
	}
	IFS.close();
	return;
}

//Crypto_C::~Crypto_C() {
//
//}

//float DigitalCurrency::findHigh(float* a) {
//	//
//	
//	;}
//
//float DigitalCurrency::findLow(float* a) {
//	
//	return low;
//}

void DigitalCurrency::showSimulationVisually(float* a, float p) {

	// WORKS ****
	int count = 1;
	cout << "Showing created simulation visually..." << endl << endl;
	float high = 0.0;
	for (int k = 0; k < 8760; k++) {
		if (a[k] > high) {
			high = a[k];
		}
	}
	//low
	float low = high;
	for (int j = 0; j < 8760; j++) {
		if (a[j] < low) {
			low = a[j];
		}
	}
	// high and low done
	int span = high - low;
	cout << endl;
	cout << "Lowest price: $" << low << endl;
	cout << "Highest price: $" << high << endl << endl;
	// how far is l from 0? get that number, then subtrace that from h too
	/*int d_c = 0;
	while (low != 0) {
		low--;
		d_c++;
	}*/
	//cout << "Low to zero is: " << d_c << endl;
	// why^. L is now zero. by using d_c, we can simple output '-' * d_c for printing.

	// CANT READ A YEAR AS THE PROGRAM CAN BE RAN AT ANY TIME OF THE YEAR=====4
	for (int i = 0; i < 8760; i++) {
		//temp = a[i];
		cout << std::setw(14) << std::left;
		/*if (i == 0) {
			cout << "January -> ";
		}
		else if (i == 745) {
			cout << "February ->";
		}
		else if (i == 1417) {
			cout << "March ->";
		}
		else if (i == 2161) {
			cout << "April ->";
		}
		else if (i == 2881) {
			cout << "May ->";
		}
		else if (i == 3625) {
			cout << "June ->";
		}
		else if (i == 4345) {
			cout << "July ->";
		}
		else if (i == 5089) {
			cout << "August ->";
		}
		else if (i == 5833) {
			cout << "September ->";
		}
		else if (i == 6553) {
			cout << "October ->";
		}
		else if (i == 7297) {
			cout << "November ->";
		}
		else if (i == 8017) {
			cout << "December ->";
		}
		else if (i == 8760) {
			cout << "End of year";
		}*/
		/*else {
			cout << " ";
		}*/
		cout << i + 1 << " "; // needs a buffer for 5 digits (iomanip)
		// cout << setw(6) << left; test
		// based on data size ($10.40 vs. $209.34 vs $69,000)
		// SIMPLIFICATION ========
		/*
			if (p) {
				space to breathe -> 60 +/- ?
			}
			each data has a 1% difference or less
			each "display" can be a "-" apart in that case
		*/
		// print "-" away from zero
		// example: if d_c is 423.44, then 423.44 must've been the lowest number.
		// so everything a[k] - d_c will be greater than 0.
		int temp1 = a[i];
		int temp2 = low;
		for (int k = 0; k < (temp1 - temp2); k++) {
			cout << "|";
		}
		cout << "}     ( $" << a[i] << " )      " << endl;
	}
	cout << endl << endl;
	return;
}

void DigitalCurrency::viewSpan_1m(float* a) {
	cout << "Viewing span of 1m into the past... (-744 hours) " << endl << endl;
	for (int i = (8760 - 744); i < 8760; i++) {
		cout << i + 1 << "   ->   " << a[i] << endl;
	}
	cout << endl;
	return;
}

void DigitalCurrency::viewSpan_6m(float* a) {
	cout << "Viewing span of 6m into the past... (-(744*6) hours (for 6m)) " << endl << endl;
	for (int i = (8760 - (744 * 6)); i < 8760; i++) {
		cout << i + 1 << "   ->   " << a[i] << endl;
	}
	cout << endl;
	return;
}

void DigitalCurrency::viewSpan_1y(float* a) {
	cout << "Viewing span of 1y into the past... (standard view) " << endl << endl;
	showSimulationData(a);
	cout << endl;
	return;
}

void DigitalCurrency::makeAnalysis(float* a) {
	float high = 0.0;
	int high_loc, low_loc;
	for (int k = 0; k < 8760; k++) {
		if (a[k] > high) {
			high = a[k];
			high_loc = (k + 1);
		}
	}
	float low = high;
	for (int j = 0; j < 8760; j++) {
		if (a[j] < low) {
			low = a[j];
			low_loc = (j + 1);
		}
	}
	cout << "Highest price is $" << high << " and is located at Hour # " << high_loc << endl;
	cout << "Lowest price is $" << low << " and is located at Hour # " << low_loc << endl;
	// here. We are finding "high location" and "low location"
	// Once we do, we'll talk about what is going on there.
	cout << endl;
	cout << "KTerrabase    --===--    SIMULATION ANALYSIS  --==================--  " << endl;
	if (high_loc > 0 && high_loc < 2900) {
		cout << endl << endl;
		cout << "In the first few months of the 1y span, the price seemed to be higher than usual." << endl;
		cout << "Buying at that point may have been dangerous as the price can easily fall." << endl;
		cout << "Selling or 'Holding' will be best to avoid a loss." << endl;
		cout << "Holding is more of a loss than selling, but holding in general never returns in a loss." << endl;
		cout << "(Holding means to wait instead buying or selling at the current time.)" << endl;
		cout << endl;
	}
	else if (high_loc >= 2900 && high_loc < 5500) {
		cout << endl << endl;
		cout << "Approximately 6 months ago, the price seemed to be at its highest within the 1y span." << endl;
		cout << "Buying at that point may have been dangerous as the price can easily fall." << endl;
		cout << "Selling or 'Holding' will be best to avoid a loss." << endl;
		cout << "Holding is more of a loss than selling, but holding in general never returns in a loss." << endl;
		cout << "(Holding means to wait instead buying or selling at the current time.)" << endl;
		cout << endl;
	}
	else if (high_loc >= 5500 && high_loc < 8760) {
		cout << endl << endl;
		cout << "Towards the end of the 1y span, the price seemed to be at its highest within the 1y span." << endl;
		cout << "Buying at that point may have been dangerous as the price can easily fall." << endl;
		cout << "Selling or 'Holding' will be best to avoid a loss." << endl;
		cout << "Holding is more of a loss than selling, but holding in general never returns in a loss." << endl;
		cout << "(Holding means to wait instead buying or selling at the current time.)" << endl;
		cout << endl;
	}
	if (low_loc > 0 && low_loc < 2900) {
		cout << endl << endl;
		cout << "The price seemed to be at its lowest more than 8 months ago. " << endl;
		cout << "Buying at that point may have been the best time." << endl;
		cout << "When buying when the price is below its natural price zone, the chance of a loss occurring is 20% or lower " << endl;
		cout << "If a loss tends to happen, it should not be a large loss. The support line under should keep the price at level." << endl;
		cout << "IF A LOSS OCCURS, NEVER SELL YOUR CURRENT STATE. Loss will be guaranteed. HOLDING IS THE BEST OPTION. " << endl;
		cout << endl;
	}
	else if (low_loc >= 2900 && low_loc < 5500) {
		cout << endl << endl;
		cout << "The price seemed to be at its lowest more than 8 months ago. " << endl;
		cout << "Buying at that point may have been the best time." << endl;
		cout << "When buying when the price is below its natural price zone, the chance of a loss occurring is 20% or lower " << endl;
		cout << "If a loss tends to happen, it should not be a large loss. The support line under should keep the price at level." << endl;
		cout << "IF A LOSS OCCURS, NEVER SELL YOUR CURRENT STATE. Loss will be guaranteed. HOLDING IS THE BEST OPTION. " << endl;
		cout << endl;
	}
	else if (low_loc >= 5500 && low_loc < 8760) {
		cout << endl << endl;
		cout << "The price seemed to be at its lowest more than 8 months ago. " << endl;
		cout << "Buying at that point may have been the best time." << endl;
		cout << "When buying when the price is below its natural price zone, the chance of a loss occurring is 20% or lower " << endl;
		cout << "If a loss tends to happen, it should not be a large loss. The support line under should keep the price at level." << endl;
		cout << "IF A LOSS OCCURS, NEVER SELL YOUR CURRENT STATE. Loss will be guaranteed. HOLDING IS THE BEST OPTION. " << endl;
		cout << endl;
	}
	else {
		// nothing
	}
	return;
}