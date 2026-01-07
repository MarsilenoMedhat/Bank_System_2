#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
using namespace std;

class clsManageUsersScreen : protected clsScreen {

private:
    enum enManageUsersMenuOptions { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenu = 6};

    static short _ReadManageUserMenuOption() {
        short Choice = clsInputValidate::ReadNumberInRange(1, 6, "Choose what do you want to do? [1:6]. ", "Invalid input, Choose what do you want to do? [1:6]. ");
        return Choice;
    }

    static void _ShowUsersListScreen() {
        cout << "\nShow users list screen will be here soon...\n";
        clsUsersListScreen::ShowUsersListScreen();
    }

    static void _ShowAddNewUserScreen() {
        clsAddNewUserScreen::ShowAddUserScreen();
        // cout << "\nAdd new user screen will be here soon...\n";
    }

    static void _ShowDeleteUserScreen() {
        clsDeleteUserScreen::ShowDeleteUserScreen();
        // cout << "\nDelete user screen will be here soon...\n";
    }

    static void _ShowUpdateUserScreen() {
        clsUpdateUserScreen::ShowUpdateUserScreen();
        // cout << "\nUpdate user screen will be here soon...\n";
    }

    static void _ShowFindUserScreen() {
        clsFindUserScreen::ShowFindUserScreen();
        // cout << "\nFind user screen will be here soon...\n";
    }

    static void _BackToManageUsersMenuScreen() {
        cout << "\nPress any key to go back to Manage Users Menu...\n";
        system("pause>0");
        ShowManageUsersMenuScreen();
    }

    static void _PerformManageUserMenuOption(enManageUsersMenuOptions Choice) {
        switch (Choice) {
        case enManageUsersMenuOptions::eListUsers:
            system("cls");
            _ShowUsersListScreen();
            _BackToManageUsersMenuScreen();
            break;
        case enManageUsersMenuOptions::eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            _BackToManageUsersMenuScreen();
            break;
        case enManageUsersMenuOptions::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _BackToManageUsersMenuScreen();
            break;
        case enManageUsersMenuOptions::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _BackToManageUsersMenuScreen();
            break;
        case enManageUsersMenuOptions::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _BackToManageUsersMenuScreen();
            break;
        case enManageUsersMenuOptions::eMainMenu:
            break;
        }
    }

public:
    static void ShowManageUsersMenuScreen() {
        system("cls");

        if (!clsScreen::_CheckAccessRight(clsUser::enPermissions::eManageUsers)) {
            return;
        }

        clsScreen::_PrineScreenHeader("Manage users screen");
        cout << "\n========================================\n";
        cout << "\n\t\tMain Menu\n";
        cout << "\n========================================\n";
        cout << " [1] Show users list.\n";
        cout << " [2] Add new user.\n";
        cout << " [3] Delete user.\n";
        cout << " [4] Update user.\n";
        cout << " [5] Find user.\n";
        cout << " [6] Main menu.\n";
        cout << "========================================\n";
        _PerformManageUserMenuOption((clsManageUsersScreen::enManageUsersMenuOptions)_ReadManageUserMenuOption());
    }
};