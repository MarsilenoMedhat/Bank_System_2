#pragma once

#include <iostream>
#include <iomanip>
#include "../../Core/clsCurrency.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsScreen.h"
#include "clsCurrencyListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen {

private:

    enum enCurrencyExchangeMenuOptions {eCurrenciesList = 1, eFindCurrency = 2, eUpdateCurrency = 3, eCurrencyCalculator = 4, eMainMenu = 5};

    static short _ReadCurrencyExchangeMenuOptions() {
        short Choice = clsInputValidate::ReadNumberInRange(1, 5, "Choose what do you want to do? [1:5]. ", "Invalid input, Choose what do you want to do? [1:5]. ");
        return Choice;
    }

    static void _BackToMainMenuScreen() {
        cout << "\nPress any key to go back to currency exchange Menu...\n";
        system("pause>0");
        ShowCurrencyExchangeScreen();
    }

    static void _ShowCurrenciesListScreen() {
        // cout << "\nCurrency list screen will be here soon.\n";
        clsCurrencyListScreen::ShowCurrencyListScreen();
    }

    static void _ShowFindCurrencyScreen() {
        // cout << "\nFind currency screen will be here soon.\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateCurrencyScreen() {
        // cout << "\nUpdate currency screen will be here soon.\n";
        clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
    }

    static void _ShowCurrrencyCalculatorScreen() {
        // cout << "\nCurrency calculator screen will be here soon.\n";
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _PerformCurrencyExchangeMenuOption(clsCurrencyExchangeScreen::enCurrencyExchangeMenuOptions Choice) {
        switch (Choice)
        {
        case clsCurrencyExchangeScreen::enCurrencyExchangeMenuOptions::eCurrenciesList:
            system("cls");
            _ShowCurrenciesListScreen();
            _BackToMainMenuScreen();
            break;
        case clsCurrencyExchangeScreen::enCurrencyExchangeMenuOptions::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _BackToMainMenuScreen();
            break;
        case clsCurrencyExchangeScreen::enCurrencyExchangeMenuOptions::eUpdateCurrency:
            system("cls");
            _ShowUpdateCurrencyScreen();
            _BackToMainMenuScreen();
            break;
        case clsCurrencyExchangeScreen::enCurrencyExchangeMenuOptions::eCurrencyCalculator:
            system("cls");
            _ShowCurrrencyCalculatorScreen();
            _BackToMainMenuScreen();
            break;
        case clsCurrencyExchangeScreen::enCurrencyExchangeMenuOptions::eMainMenu:
            break;
        }
    }

public:
    
    static void ShowCurrencyExchangeScreen() {
        system("cls");

        if (!clsScreen::_CheckAccessRight(clsUser::enPermissions::eCurrencyExchange)) {
            return;
        }
        
        clsScreen::_PrineScreenHeader("Currency exchage screen");
        cout << "\n========================================\n";
        cout << "\n\tCurrency exchage Menu\n";
        cout << "\n========================================\n";
        cout << " [1] Currencies list.\n";
        cout << " [2] Find currency.\n";
        cout << " [3] Update rate.\n";
        cout << " [4] Currency calculator.\n";
        cout << " [5] Main menu.\n";
        cout << "========================================\n";
        _PerformCurrencyExchangeMenuOption((clsCurrencyExchangeScreen::enCurrencyExchangeMenuOptions)_ReadCurrencyExchangeMenuOptions());
    }
};