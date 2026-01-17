#pragma once

#include <iostream>
#include <string>
#include "../clsMainScreen.h"
#include "../../Lib/clsScreen.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Core/clsUser.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsDate.h"
using namespace std;

class clsLoginScreen : protected clsScreen {

private:

    static bool _Login() {
        string Username = "", Password = "";
        bool LoginFailed = false;
        short FaildLoginCount = 0;

        do {
            if (LoginFailed) {
                FaildLoginCount++;
                cout << "\nInvlaid Username/Password!\n";
                cout << "You have " << 3 - FaildLoginCount << " chances to login.\n\n";
            }

            if (FaildLoginCount == 3) {
                cout << "The system locked after 3 login attempts.\n";
                return false;
            }
            Username = clsInputValidate::ReadString("\nEnter the username: ");
            Password = clsInputValidate::ReadString("\nEnter the password: ");

            CurrentUser = clsUser::Find(Username, Password);
            LoginFailed = CurrentUser.IsEmpty();

        } while(LoginFailed);
        CurrentUser.RegisterLogin(CurrentUser);
        clsMainScreen::ShowMainMenuScreen();
        return true;
    }
public:

    static bool ShowLoginScreen() {
        system("cls");
        clsScreen::_PrineScreenHeader("Login screen");
        return _Login();
    }

};