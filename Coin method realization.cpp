#include "CoinClass.h"

void CoinCalculator::show()
{
		cout << "\nCoin coin: " << m_name;
		cout << "\nCoin price: " << m_price;
		cout << "\nAvailable emission: " << m_emission;
}

double CoinCalculator::ProfitCalculator()
{
	long double profit{};
	cout << "\nEnter a number of coins: "; cin >> m_YourAmountCoins;
	cout << "Enter price per coin($): "; cin >> m_price;

	if (m_YourAmountCoins == 0 && m_price == 0 )
	{
		return Menu();
	}
	else if (m_YourAmountCoins <= 0 )
	{
		cout << "Amount of coins cannot be less than 0 or 0.\n";
		return ProfitCalculator();
	}
	else
	{
		profit = m_YourAmountCoins * m_price;
		cout << "\nProfit: " << profit << "$";
		return profit;
	}
}

double CoinCalculator::GetDesiredPrice()
{
	cout << "\nEnter wished price: "; cin >> m_price;
	cout << "Enter coin emission: "; cin >> m_emission;
	long long desprice = m_price * m_emission;

	if (m_price == 0 && m_emission == 0)
	{
		cout << "\nReturning to menu..\n"; return Menu();
	}
	else if (m_emission == 0 )
	{
		cout << "\nEmission cannot be less than 0 or 0\n";
		return GetDesiredPrice();
	}

	std::cout << "Required capitalization: ";
	if (desprice >= 1000000000) 
	{
		std::cout << std::fixed << std::setprecision(3) << desprice / 1000000000.0 << " billion($) ";
		desprice %= 1000000000;
	}
	else if (desprice >= 1000000) 
	{
		std::cout << std::fixed << std::setprecision(3) << desprice / 1000000.0 << " million($)";
		desprice %= 1000000;
	}

	return desprice;
}

double CoinCalculator::ApproximatePrice()
{
	cout << "\nEnter market cap: "; cin >> m_marketCap;
	cout << "Enter emission: "; cin >> m_emission;

	if (m_marketCap == 0 && m_emission == 0)
	{
		cout << "\nReturning to menu.."; return Menu();
	}

	long double aproxim = m_marketCap / m_emission;
	cout << "Expected price: " << aproxim << "$";
	return aproxim;
}

int CoinCalculator::AddCoins()
{
	if (!coinDataBase.empty())
	{
		cout << "\nCoins already in data: ";
		for (const auto& x : coinDataBase)
		{
			cout << x << " | ";
		}
	}

	cout << "\nNumber of coins: "; int numcoin;
	while (!(cin >> numcoin) || numcoin <= 0) 
	{
		cout << "\nInvalid input. Number of coins should be greater than 0\nUse only numbers.\n\n";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		return Menu();
	}

	cout << "\nUse uppercase letters.";
	cout << "\nEnter " << numcoin << " coin name:\n";
	for (int i = 0; i < numcoin; i++)
	{
		cin >> m_name;
		coinDataBase.push_back(m_name);
	}
	cout << endl;
}

int CoinCalculator::ShowCoinData()
{
	int coin_counter{0};
	if (coinDataBase.empty())
	{
		cout << "No coins in wallet, returning to menu..\n\n";
		return Menu();
	}

	cout << "\nAvailable coins: " << endl;
	for (size_t i = 0; i < coinDataBase.size(); i++)
	{
		std::sort(coinDataBase.begin(), coinDataBase.end());
		cout << "| " << coinDataBase[i] << " |\n";
	}

	cout << "\n|Tap coin below (0 - to quit)|\n";
	for (size_t i = 0; i < coinDataBase.size(); i++)
	{
		std::sort(coinDataBase.begin(), coinDataBase.end());
		cout << "(" << ++coin_counter << ")";
		cout << "| " << coinDataBase[i] << " |\n";
	}

	cin >> coin_ADD_list;
	if (coin_ADD_list == 0)
	{
		cout << "Returning to menu..\n\n"; return Menu();
	}
	else if (coin_ADD_list < 1 || coin_ADD_list > coinDataBase.size())
	{
		cout << "Invalid input. Please enter a number between 1 and " << coinDataBase.size() << ".\n\n";
		return ShowCoinData();
	}
	else
	{
		cout << coinDataBase[coin_ADD_list-1];
		system(std::string("start " + std::string("https://coinmarketcap.com/search/") 
			  + coinDataBase[coin_ADD_list - 1]).c_str());
		cout << "\n search opened..\n";
	}

	// Google search by coin name inputed here
	// system(std::string("start " + std::string("https://coinmarketcap.com/currencies/") + coinDataBase[i]).c_str());

	cout << "\nFor more information, use google search.\n";
	cout << "Open google?(Y/N): "; char YesNo; cin >> YesNo;

	if (YesNo == 'n')
	{
		cout << "\nReturning to menu page..\n\n";
		return Menu();
	}
	else if (YesNo == 'y')
	{
		system(std::string("start " + std::string("https://www.google.com/")).c_str());
		return Menu();
	}

	cout << endl << endl;
}

int CoinCalculator::ClearCoinList()
{
	if (coinDataBase.empty())
	{
		cout << "\nData base already empty.\n\n";
	}
	else
	{
		cout << "\nAdded coins: " << endl;

		for (size_t i = 0; i < coinDataBase.size(); i++)
		{
			cout << "(" << coin_CLR_list+1 << ")";
			cout << "| " << coinDataBase[i] << " |\n";
			++coin_CLR_list;
		}

		cout << "\n|Tap to delete (0 - to quit)|\n"; cin >> delc;
		if (delc == 0)
		{
			cout << "\n Returning to menu..\n\n";
			return Menu();
		}
		else if (delc > coinDataBase.size())
		{
			cout << "\nOut of range of available coins. Choose only available\n";
			return ClearCoinList();
		}
		else
		{
			cout << coinDataBase[delc-1] << " deleated.\n";
			--coin_CLR_list; 
		}

		auto iterator = (coinDataBase.begin() + delc - 1);
		if (iterator == coinDataBase.end())
		{
			cout << "Invalid coin index\n";
			return ClearCoinList();
		}
		else
		{
			cout << endl;
			coinDataBase.erase(iterator);
			--coin_CLR_list;
		}
	}
}

int CoinCalculator::DataReport()
{
	std::ofstream fout;
	cout << "\nData report..\n" << "Enter file name: "; cin >> m_filename;
	fout.open(m_filename.c_str());
	fout << "Coins: ";
	for (const auto& x : coinDataBase)
	{
		fout << x << " ";
	}
	fout << "\nPrice($): ";
	fout << "\nMarket cap: ";
	fout << "\nEmission: ";
	cout << "Report has finished.\n\n";

	fout.close();
	return Menu();
}

int CoinCalculator::Menu()
{
	do
	{
		cout << "______________________________\n";
		cout << "(1)| Calculate profit  \n";
		cout << "(2)| Calculate coin cap \n";
		cout << "(3)| Aproximately coin price \n";
		cout << "(4)| Add coin to data base \n";
		cout << "(5)| Show coin data base \n";
		cout << "(6)| Clear list \n";
		cout << "(7)| Print report \n";
		cout << "(0)| Quit";
		cout << "\n_____________________________\n";
		
		cin >> select;
		switch(select)
		{
		case Calculate_Profit:               // CASE 1
			ProfitCalculator();
			cout << endl << endl;
			break;

		case Market_cap:                    // CASE 2
			GetDesiredPrice();
			cout << endl << endl;
			break;

		case Aprox_coin_price:             // CASE 3
			ApproximatePrice();
			cout << endl << endl;
			break;

		case Add_coin:					   // CASE 4
			AddCoins();
			break;

		case Show_data:                    // CASE 5
			ShowCoinData();
			break;

		case Clear_data:                   // CASE 6
			ClearCoinList();
			break;

		case Print_report:                // CASE 7
			DataReport();
			break;

		case 0:
			break;
		default:
			cout << "Unknown command.\n\n";
			break;
			
		}

	} while (cin && select != 0);

	return select;
}


/*#include <curl/curl.h>
int main()
{
    CURL* curl;
    CURLcode res;
    std::string url = "https://example.com";

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Получение HTML-кода
        std::string html;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, static_cast<size_t (*)(char*, size_t, size_t, void*)>([](char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t {
            ((std::string*)userdata)->append(ptr, size * nmemb);
            return size * nmemb;
        }));
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            std::cout << html << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return 0;
}*/ // parsing