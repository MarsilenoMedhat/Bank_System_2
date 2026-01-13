#pragma once

#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "Global.h"
using namespace std;

class clsMainScreen : protected clsScreen {

private:
    enum enMainMenuOptions {eClientList = 1, eAddClient = 2, eDeleteClient = 3, eUpdatedClient = 4, eFindClient = 5, eTransactions = 6, eManageUsers = 7,eLoginRegister = 8, eLogout = 9};

    static short _ReadMainMenuOption() {
        short Choice = clsInputValidate::ReadNumberInRange(1, 9, "Choose what do you want to do? [1:9]. ", "Invalid input, Choose what do you want to do? [1:9]. ");
        return Choice;
    }

    static void _BackToMainMenuScreen() {
        cout << "\nPress any key to go back to Main Menu...\n";
        system("pause>0");
        ShowMainMenuScreen();
    }

    static void _ShowClientListScreen() {
        // cout << "\nClient list screen will be here soon...\n";   
        clsClientListScreen::ShowClientsList();
    }
    
    static void _ShowAddClientScreen() {
        // cout << "\nAdd client screen will be here soon...\n";
        clsAddNewClientScreen::AddNewClient();
    }

    static void _ShowDeleteClientScreen() {
        // cout << "\nDelete client screen will be here soon...\n";
        clsDeleteClientScreen::DeleteClient();
    }

    static void _ShowUpdateClientScreen() {
        // cout << "\nUpdate client screen will be here soon...\n";
        clsUpdateClientScreen::UpdateClient();
    }

    static void _ShowFindClientScreen() {
        // cout << "\nFind client screen will be here soon...\n";
        clsFindClientScreen::FindClient();
    }

    static void _ShowTransactionScreen() {
        // cout << "\nTransaction screen will be here soon...\n";
        clsTransactionsScreen::ShowTransactionMenuScreen();
    }

    static void _ShowManageUsersScreen() {
        // cout << "\nManage users screen will be here soon...\n";
        clsManageUsersScreen::ShowManageUsersMenuScreen();
    }

    static void _ShowLoginRegisterScreen() {
        // cout << "\nLogin register screen will be here soon...\n";
        clsLoginRegisterScreen::ShowLoginRegisterListScreen();
    }

    static void _Logout() {
        // cout << "\nLogout screen will be here soon...\n";
        CurrentUser = clsUser::Find("", "");
    }

    static void _PerforMainMenuOption(clsMainScreen::enMainMenuOptions MainMenuChoice) {
        switch(MainMenuChoice) {
            case clsMainScreen::enMainMenuOptions::eClientList:
                system("cls");
                _ShowClientListScreen();
                _BackToMainMenuScreen();
                break;
            case clsMainScreen::enMainMenuOptions::eAddClient:
                system("cls");
                _ShowAddClientScreen();
                _BackToMainMenuScreen();
                break;
            case clsMainScreen::enMainMenuOptions::eDeleteClient:
                system("cls");
                _ShowDeleteClientScreen();
                _BackToMainMenuScreen();
                break;
            case clsMainScreen::enMainMenuOptions::eUpdatedClient:
                system("cls");
                _ShowUpdateClientScreen();
                _BackToMainMenuScreen();
                break;
            case clsMainScreen::enMainMenuOptions::eFindClient:
                system("cls");
                _ShowFindClientScreen();
                _BackToMainMenuScreen();
                break;
            case clsMainScreen::enMainMenuOptions::eTransactions:
                system("cls");
                _ShowTransactionScreen();
                _BackToMainMenuScreen();
                break;
            case clsMainScreen::enMainMenuOptions::eManageUsers:
                system("cls");
                _ShowManageUsersScreen();
                _BackToMainMenuScreen();
                break;
            case clsMainScreen::enMainMenuOptions::eLoginRegister:
                system("cls");
                _ShowLoginRegisterScreen();
                _BackToMainMenuScreen();
                break;
            case clsMainScreen::enMainMenuOptions::eLogout:
                system("cls");
                _Logout();
                break;
        }
    }

public:

    static void ShowMainMenuScreen() {
        system("cls");
        clsScreen::_PrineScreenHeader("MainScreen");
        cout << "\n========================================\n";
        cout << "\n\t\tMain Menu\n";
        cout << "\n========================================\n";
        cout << " [1] Show clients list.\n";
        cout << " [2] Add new client.\n";
        cout << " [3] Delete client.\n";
        cout << " [4] Update client.\n";
        cout << " [5] Find client.\n";
        cout << " [6] Transactions.\n";
        cout << " [7] Manage users.\n";
        cout << " [8] Login register.\n";
        cout << " [9] Logout.\n";
        cout << "========================================\n";
        _PerforMainMenuOption((clsMainScreen::enMainMenuOptions)_ReadMainMenuOption());
    }
};