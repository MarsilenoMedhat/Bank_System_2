#pragma once

#include <iostream>
#include <iomanip>
#include "../../Lib/clsScreen.h"
#include "../../Lib/clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
using namespace std;

class clsTransactionsScreen : protected clsScreen {

private:
    enum enTransactionsMenuOptions {eDeposit = 1, eWithdraw = 2, eTotalBalance = 3, eTransfer = 4, eTransferLog = 5 , eMainMenu = 6};

    static short _ReadTransactionsMenuOption() {
        short Choice = clsInputValidate::ReadNumberInRange(1, 6, "Choose what do you want to do? [1:6]. ", "Invalid input, Choose what do you want to do? [1:6]. ");
        return Choice;
    }

    static void _BackToTransactionsMenuScreen() {
        cout << "\nPress any key to go back to transactions Menu...\n";
        system("pause>0");
        ShowTransactionMenuScreen();
    }

    static void _ShowDepositScreen() {
        // cout << "\nDeposit screen will be here soon...\n";
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen() {
        // cout << "\nWithdraw screen will be here soon...\n";
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalanceScreen() {
        // cout << "\nTotal balance screen will be here soon...\n";
        clsTotalBalanceScreen::ShowTotalBalanceScreen();
    }

    static void _ShowTransferScreen() {
        // cout << "\nTransfer screen will be here soon...\n";
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen() {
        // cout << "\nTransfer log screen will be here soon...\n";
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void _PerforTransactionsMenuOption(clsTransactionsScreen::enTransactionsMenuOptions TransactionMenuChoice) {
        switch (TransactionMenuChoice) {
            case clsTransactionsScreen::enTransactionsMenuOptions::eDeposit:
                system("cls");
                _ShowDepositScreen();
                _BackToTransactionsMenuScreen();
                break;
            case clsTransactionsScreen::enTransactionsMenuOptions::eWithdraw:
                system("cls");
                _ShowWithdrawScreen();
                _BackToTransactionsMenuScreen();
                break;
            case clsTransactionsScreen::enTransactionsMenuOptions::eTotalBalance:
                system("cls");
                _ShowTotalBalanceScreen();
                _BackToTransactionsMenuScreen();
                break;
            case clsTransactionsScreen::enTransactionsMenuOptions::eTransfer:
                system("cls");
                _ShowTransferScreen();
                _BackToTransactionsMenuScreen();
                break;
            case clsTransactionsScreen::enTransactionsMenuOptions::eTransferLog:
                system("cls");
                _ShowTransferLogScreen();
                _BackToTransactionsMenuScreen();
                break;
            case clsTransactionsScreen::enTransactionsMenuOptions::eMainMenu:
                break;
        }
    }
public:

    static void ShowTransactionMenuScreen() {
        system("cls");

        if (!clsScreen::_CheckAccessRight(clsUser::enPermissions::eTransactions)) {
            return;
        }

        clsScreen::_PrineScreenHeader("Transactions menu");
        cout << "\n========================================\n";
        cout << "\n\tTransactions Menu\n";
        cout << "\n========================================\n";
        cout << " [1] Deposit.\n";
        cout << " [2] Withdraw.\n";
        cout << " [3] Total balance.\n";
        cout << " [4] Transfer.\n";
        cout << " [5] Transfer log.\n";
        cout << " [6] Main menu.\n";
        cout << "========================================\n";
        _PerforTransactionsMenuOption((clsTransactionsScreen::enTransactionsMenuOptions)_ReadTransactionsMenuOption());
    }
};