#pragma once

#include <iostream>
#include <string>
#include "clsMainScreen.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsBankClient.h"
#include "Global.h"
using namespace std;

class clsLoginScreen : protected clsScreen {

private:

    static void _Login() {
        string Username = "", Password = "";
        bool LoginFailed = false;

        do {
            if (LoginFailed) {
                cout << "\nInvlaid Username/Password!\n\n";
            }

            Username = clsInputValidate::ReadString("\nEnter the username: ");
            Password = clsInputValidate::ReadString("\nEnter the password: ");

            CurrentUser = clsUser::Find(Username, Password);
            LoginFailed = CurrentUser.IsEmpty();

        } while(LoginFailed);
        clsMainScreen::ShowMainMenuScreen();
    }
public:

    static void ShowLoginScreen() {
        system("cls");
        clsScreen::_PrineScreenHeader("Login screen");
        _Login();
    }

};