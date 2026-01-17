#pragma once

#include <iostream>
#include <string>
#include "../../Lib/clsScreen.h"
#include "../../Core/clsUser.h"
#include "../../Lib/clsInputValidate.h"
using namespace std;

class clsFindUserScreen : protected clsScreen {

private:

    static void _PrintUserData(clsUser User) {
        cout << "User card:";
        cout << "\n________________________________________";
        cout << "\nFirst name    : " << User.GetFirstName();
        cout << "\nLast name     : " << User.GetLastName();
        cout << "\nFull name     : " << User.GetFullName();
        cout << "\nEmail address : " << User.GetEmail();
        cout << "\nPhone number  : " << User.GetPhone();
        cout << "\nUsername      : " << User.GetUsername();
        cout << "\nPassword      : " << User.GetPassword();
        cout << "\nPermissions   : " << User.GetPermission();
        cout << "\n________________________________________\n";
    }

public:

    static void ShowFindUserScreen() {

        clsScreen::_PrineScreenHeader("Find user screen");
        string Username = clsInputValidate::ReadString("\nEnter the username or  enter \"back\" to back to the users menu: ");

        if (clsUtil::IsEqualText(Username, "back")) {
            cout << "\nOperation has been cancelled.\n";
            return;
        }
        clsUser User = clsUser::Find(Username);

        if (clsUser::IsUserExists(Username)) {
            _PrintUserData(User);
        }
        else {
            cout << "\nThe user is not exist\n";
        }
    }

};