#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;

class clsCurrencyListScreen : protected clsScreen {

private:

    static void _PrintCurrencyRecord(clsCurrency CurrencyRecord) {
        cout << "| " << left << setw(30) << CurrencyRecord.GetCountryName();
        cout << " | " << left << setw(10) << CurrencyRecord.GetCurrencyCode();
        cout << " | " << left << setw(50)<< CurrencyRecord.GetCurrencyName();
        cout << " | " << left << setw(20) << CurrencyRecord.GetCurrencyRate() << " |";
    }

    static void _PrintTableHeader() {
        cout << "\n___________________________________________________________________________________________________________________________\n\n";
        cout << "| " << left << setw(30) << "Country name";
        cout << " | " << left << setw(10) << "C.Code";
        cout << " | " << left << setw(50)<< "Currency name";
        cout << " | " << left << setw(20) << "Currency rate" << " |";
        cout << "\n___________________________________________________________________________________________________________________________\n\n";
    }
    
    static void _PrintTableFooter() {
        cout << "___________________________________________________________________________________________________________________________\n\n";
    }

public:

    static void ShowCurrencyListScreen() {
        vector<clsCurrency> vCurrenciesData = clsCurrency::GetCurrenciesList();
        string Title = "Currencies list";
        string SubTitle = "(" + to_string(vCurrenciesData.size()) + ") currency";

        clsScreen::_PrineScreenHeader(Title, SubTitle);
        _PrintTableHeader();
        if (vCurrenciesData.size() == 0) {
            cout << "\nNo currencies in the system.\n";
        }
        else {
            for (clsCurrency CurrencyRecord : vCurrenciesData) {
                _PrintCurrencyRecord(CurrencyRecord);
                cout << endl;
            }
        }
        _PrintTableFooter();
    }
};