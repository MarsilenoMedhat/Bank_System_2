#pragma once

#include <iostream>
#include <string>
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsString.h"
#include "../../Lib/clsUtil.h"
#include "../../Lib/clsScreen.h"
#include "../../Core/clsCurrency.h"
using namespace std;

class clsFindCurrencyScreen : protected clsScreen {

private:

    static void _PrintCurrencyCard(clsCurrency Currency) {
        cout << "\n__________________________________________________________\n";
        cout << "\n\t\tCurrency card:";
        cout << "\n__________________________________________________________\n";
        cout << "\nCountry name         : " << Currency.GetCountryName();
        cout << "\nCurrency code        : " << Currency.GetCurrencyCode();
        cout << "\nCurrency name        : " << Currency.GetCurrencyName();
        cout << "\nCurrency rate [1USD] : " << Currency.GetCurrencyRate();
        cout << "\n__________________________________________________________\n";
    }

    static void _ShowResults(clsCurrency Currency) {
        if (!Currency.IsEmpty()) {
            cout << "\nCurrency has been found.\n";
            _PrintCurrencyCard(Currency);
        }
        else {
            cout << "\nCurrency has not been found.\n";
        }
    }

public:

    static void ShowFindCurrencyScreen() {
        clsScreen::_PrineScreenHeader("Find currency");
        string SearchMethod = "";
        clsCurrency Currency;

        short Choice = clsInputValidate::ReadNumberInRange(0, 2, "\nFind by: [1]Code, [2]Country name or enter 0 to back to currency excharge menu: ", "\nInvalid input, find by: [1]Code, [2]Country name or enter 0 to back to currency excharge menu: ");

        if (Choice == 0) {
            cout << "\nOperation has been cancelled.\n";
            return;
        }

        if (Choice == 1) {
            SearchMethod = clsInputValidate::ReadString("\nEnter the currency code or enter \"back\" to return to currency exchange menu: ");
            if (clsUtil::IsEqualText(SearchMethod, "back")) {
                cout << "\nOperation has been cancelled.\n";
                return;
            }
            Currency = clsCurrency::FindByCurrencyCode(SearchMethod);
        }
        else if (Choice == 2) {
            SearchMethod = clsInputValidate::ReadString("\nEnter the country name or enter \"back\" to return to currency exchange menu: ");
            if (clsUtil::IsEqualText(SearchMethod, "back")) {
                cout << "\nOperation has been cancelled.\n";
                return;
            }
            Currency = clsCurrency::FindByCountry(SearchMethod);
        }
        _ShowResults(Currency);
    }
};