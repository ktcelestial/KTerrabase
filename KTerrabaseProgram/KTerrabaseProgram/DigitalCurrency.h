#ifndef DIGITAL_CURRENCY_H
#define DIGITAL_CURRENCY_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using std::cout;
using std::endl;
using std::cin;

/*

	Digital Currency class is the main class that also holds two classes
	Stock and Crypto_C
	Stock and Crypto_C will now be looked as "brothers"
	in terms of their properties to speed up the process.
	But know that in reality they are different in many ways

*/
/*
		Tick: every second
		Spans: 1min, 5min, 10min, 30min, 45min,
			   1hr, ...., 24hr, : (1tick/10min)
			   1day, ...., 1month : (1tick/12hr)
			   1month, ..., 1yr : (1tick/15days)

		Source Algorithms:

		Key-Value Pairs
*/

class DigitalCurrency {
	// same behavior: Stock and cryptocurrency
private:
	float priceVisualDisplaySpan;
	std::vector<float> slopes;
	std::vector<float> ::iterator iter__;
public:
	std::ifstream IFS;
	std::ofstream OFS;
	float getPrice() {
		return priceVisualDisplaySpan;
	}
	DigitalCurrency();
	float* simulate(float* arr, const int TOTALTICKS); // users input goes here
	void showSimulationData(float* a);
	void showSimulationVisually(float* a, float span);
	void displaySimulationSlopes(float* a);
	// ALGORITHMS =========
	//temporarily void
	float findHigh(float* a);
	float findLow(float* a);
	void doubleBottom(float* arr); // 
	// view spans. make more vectors/arrays?
	void viewSpan_1m(float* a);
	void viewSpan_6m(float* a);
	void viewSpan_1y(float* a);

	//data analysis
	void makeAnalysis(float* a);

	~DigitalCurrency();
};

class Stock : public DigitalCurrency {
private:
	// will this class and this class only use?
	std::vector<std::string> st_names;
	std::vector<std::string> st_iter;
	// 

public:
	Stock();// constructor takes arguments when calling objects
	void displayAllStock();

	//~Stock();

};

class Crypto_C : public DigitalCurrency {
private:

public:
	//Crypto();
	Crypto_C();
	void displayAllCC();

	//~Crypto_C();
};
#endif