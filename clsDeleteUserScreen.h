#pragma once

#include <iostream>
#include <string>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsDeleteUserScreen : protected clsScreen {

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

    static void ShowDeleteUserScreen() {

        clsScreen::_PrineScreenHeader("delete user screen");
        string Username = "";

        while (true) {
            Username = clsInputValidate::ReadString("\nEnter the username or  enter \"back\" to back to the users menu: ");

            if (clsUtil::IsEqualText(Username, "back")) {
                cout << "\nOperation has been cancelled.\n";
                return;
            }

            if (clsUser::IsUserExists(Username)) {
                break;
            }
            else {
                cout << "\nThe user is not exists\n";
            }
        }
        clsUser User = clsUser::Find(Username);
        _PrintUserData(User);

        char ConfirmOperation = clsInputValidate::ReadChar("\nDo you want to delete this user? [Y/N]:  ");
        if (toupper(ConfirmOperation) == 'Y') {

            if (Username == "Admin") {
                cout << "\nError, the adming can not be deleted\n";
            }
            else if (User.Delete()) {
                cout << "\nThe user has been deleted successfully.\n";
            }
            else {
                cout << "\nThe user hasn't been deleted.\n";
            }
        }

    }
};