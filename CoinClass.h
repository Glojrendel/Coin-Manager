#ifndef COINCALC_H
#define COINCALC_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <string>
#include <memory>        // smart pointers
#include <vector>
#include <algorithm>   // sort, copy..
#include <iterator>   // STL iterator
#include <string>
#include <cmath>


using std::endl;
using std::cout;
using std::cin;

class CoinCalculator
{
private:
	std::string m_filename;
	std::string m_name{ "None" };
	double m_price{ 0 };
	double m_YourAmountCoins{ 0 };
	double m_emission{ 0 };
	double m_marketCap;
	std::vector<std::string> coinDataBase;

	int coin_ADD_list{ 0 };
	int coin_CLR_list{ 0 };
	int delcoinList{ 0 };
	char quit{ 'q' };
	int delc;			
	int select{Calculate_Profit};           //for Menu switching

	enum Menu
	{
		Calculate_Profit = 1,
		Market_cap,
		Aprox_coin_price,
		Add_coin,
		Show_data,
		Clear_data,
		Print_report
	};

public:
	CoinCalculator(){}
	CoinCalculator(const char* name) : m_name(name) {}
	CoinCalculator(std::string name, double price, int emission)	
				     : m_name(name), m_price(price), m_emission(emission){}
	virtual~CoinCalculator(){}

	std::string Name() { return m_name;}
	double CoinPrice() { return m_price;}
	double AmountCoins() { return m_YourAmountCoins;};
	int CoinEmission() { return m_emission;}
	
	void show();
	double ProfitCalculator();
	double GetDesiredPrice();
	double ApproximatePrice();
	std::string CoinBase(const CoinCalculator& CC);

	int AddCoins();       //CASE 4
	int ShowCoinData();   //CASE 5
	int ClearCoinList();  //CASE 6
	int DataReport();     //CASE 7
	int Menu();
};


#endif // !COINCALC_H

