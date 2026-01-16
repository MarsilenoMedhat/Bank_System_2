#pragma once

#include <iostream>
#include <string>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsString.h"
#include "clsUtil.h"
using namespace std;

class clsUpdateCurrencyScreen : protected clsScreen {

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

public:

    static void ShowUpdateCurrencyScreen() {
        clsScreen::_PrineScreenHeader("Update currency");
        string Code = "";

        while (true) {
            Code = clsInputValidate::ReadString("\nEnter the currency code or enter \"back\" to return to currency exchange menu: ");

            if (clsUtil::IsEqualText(Code, "back")) {
                cout << "\nOperation has been cancelled.\n";
                return;
            }
            
            if (clsCurrency::IsExist(Code)) {
                break;
            }
            cout << "\nCurrency has not been found.\n";
        }
        clsCurrency Currency = clsCurrency::FindByCurrencyCode(Code);
        _PrintCurrencyCard(Currency);
        char ConfirmOperation = clsInputValidate::ReadChar("\nDo you want to update this currency [Y/N]: ");

        if (toupper(ConfirmOperation) == 'Y') {
            double NewRate = clsInputValidate::ReadPositiveValidNumber<double>("\nEnter the new rate: ", "\nInvalid Input, Enter the new rate: ", "\nInvalid input,");
            Currency.UpdateCurrency(NewRate);
            _PrintCurrencyCard(Currency);
            cout << "\nCurrency rate updated successfully.\n";
        }
        else {
            "\nCurrency rate has not been updated.\n";
        }
    }
};