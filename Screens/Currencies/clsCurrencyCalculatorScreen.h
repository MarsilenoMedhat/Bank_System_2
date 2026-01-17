#pragma once

#include <iostream>
#include <cmath>
#include "../../Lib/clsMath.h"
#include "../../Lib/clsUtil.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsScreen.h"
#include "../../Core/clsCurrency.h"
using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen {

private:

    static void _PrintCurrencyCard(clsCurrency Currency, string Title) {
        cout << "\n__________________________________________________________\n";
        cout << "\n\t\t" << Title;
        cout << "\n__________________________________________________________\n";
        cout << "\nCountry name         : " << Currency.GetCountryName();
        cout << "\nCurrency code        : " << Currency.GetCurrencyCode();
        cout << "\nCurrency name        : " << Currency.GetCurrencyName();
        cout << "\nCurrency rate [1USD] : " << Currency.GetCurrencyRate();
        cout << "\n__________________________________________________________\n";
    }

    static string _ReadCurrencyCode(string Message) {
        while (true) {
            string Code = clsInputValidate::ReadString(Message);

            if (clsUtil::IsEqualText(Code, "back")) {
                return "back";
            }

            if (clsCurrency::IsExist(Code)) {
                return Code;
            }
            cout << "\nCurrency has not been found.";
        }
    }

    static void _PrintResilts(clsCurrency Currency1, clsCurrency Currency2, double ExchangeAmount) {
        double TotalAmount = 0;
        _PrintCurrencyCard(Currency1, "Conver from");
        _PrintCurrencyCard(Currency2, "Conver to");
        
        TotalAmount = Currency1.ExchangeCurrencyToOtherCurrency(ExchangeAmount, Currency2);
        
        cout << endl << ExchangeAmount << " " << Currency1.GetCurrencyCode() << " = " << TotalAmount <<  " " << Currency2.GetCurrencyCode() << endl;
    }

public:

    static void ShowCurrencyCalculatorScreen() {
        while (true) {
            system("cls");
            clsScreen::_PrineScreenHeader("Currency calculator");

            string Code1 = _ReadCurrencyCode("\nPlease enter currency1 code or enter \"back\" to return to currency exchage screen: ");
            if (clsUtil::IsEqualText(Code1, "back")) {
                cout << "\nOperation has been cancelled.\n";
                return;
            }
            clsCurrency Currency1 = clsCurrency::FindByCurrencyCode(Code1);

            string Code2 = _ReadCurrencyCode("\nPlease enter currency2 code or enter \"back\" to return to currency exchage screen: ");
            if (clsUtil::IsEqualText(Code2, "back")) {
                cout << "\nOperation has been cancelled.\n";
                return;
            }
            clsCurrency Currency2 = clsCurrency::FindByCurrencyCode(Code2);
            
            double ExchangeAmount = clsInputValidate::ReadPositiveValidNumber<double>("\nEnter amount to exchange: ", "\nInvalid input, enter amount to exchange: ", "\nInvalid input, ");

            _PrintResilts(Currency1, Currency2, ExchangeAmount);

            char AnotherCal = 'N';
            do {
                AnotherCal = clsInputValidate::ReadChar("\nDo you want to perform another calculation? [Y/N]: ");
            } while (toupper(AnotherCal) != 'Y' && toupper(AnotherCal) != 'N');

            if (toupper(AnotherCal) != 'Y') {
                return;
            }
        }
    }
};