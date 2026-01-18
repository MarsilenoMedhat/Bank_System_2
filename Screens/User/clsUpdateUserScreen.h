#pragma once

#include <iostream>
#include <string>
#include "../../Core/clsUser.h"
#include "../../Lib/clsScreen.h"
#include "../../Lib/clsString.h"
#include "../../Lib/clsInputValidate.h"
using namespace std;

class clsUpdateUserScreen : protected clsScreen {

private:

    static void _ReadUserData(clsUser& User) {
        User.SetFirstName(clsInputValidate::ReadString("\nEnter first name: "));
        User.SetLastName(clsInputValidate::ReadString("\nEnter last name: "));
        User.SetEmail(clsInputValidate::ReadString("\nEnter email address: "));
        User.SetPhone(clsInputValidate::ReadString("\nEnter phone number: "));
        User.SetPassword(clsInputValidate::ReadString("\nEnter password: "));
        User.SetPermission(_ReadPermissions());
    }

    static int _ReadPermissions() {
        cout << "\nEnter permission:\n";
        char Answer = 'Y';
        
        Answer = clsInputValidate::ReadChar("\nDo you want to give full access? [Y/N]:  ");
        if (toupper(Answer) == 'Y') {
            return -1;
        }

        int permission = 0;
        cout << "\nDo you want to give access to:\n";
        Answer = clsInputValidate::ReadChar("\nShow client list? [Y/N]:  ");
        if (toupper(Answer) == 'Y') {
            permission += clsUser::enPermissions::eShowClientsList;
        }

        Answer = clsInputValidate::ReadChar("\nAdd new client? [Y/N]:  ");
        if (toupper(Answer) == 'Y') {
            permission += clsUser::enPermissions::eAddNewClient;
        }

        Answer = clsInputValidate::ReadChar("\nDelete client? [Y/N]:  ");
        if (toupper(Answer) == 'Y') {
            permission += clsUser::enPermissions::eDeleteClient;
        }

        Answer = clsInputValidate::ReadChar("\nUpdate client? [Y/N]:  ");
        if (toupper(Answer) == 'Y') {
            permission += clsUser::enPermissions::eUpdateClient;
        }

        Answer = clsInputValidate::ReadChar("\nFind client? [Y/N]:  ");
        if (toupper(Answer) == 'Y') {
            permission += clsUser::enPermissions::eFindClient;
        }

        Answer = clsInputValidate::ReadChar("\nTransactions? [Y/N]:  ");
        if (toupper(Answer) == 'Y') {
            permission += clsUser::enPermissions::eTransactions;
        }

        Answer = clsInputValidate::ReadChar("\nManage users? [Y/N]:  ");
        if (toupper(Answer) == 'Y') {
            permission += clsUser::enPermissions::eManageUsers;
        }

        Answer = clsInputValidate::ReadChar("\nLogin register? [Y/N]:  ");
        if (toupper(Answer) == 'Y') {
            permission += clsUser::enPermissions::eLoginRegister;
        }

        Answer = clsInputValidate::ReadChar("\nCurrency exchange? [Y/N]:  ");
        if (toupper(Answer) == 'Y') {
            permission += clsUser::enPermissions::eCurrencyExchange;
        }
        return permission;
    }
    static void _PrintUserData(clsUser User) {
        cout << "\n________________________________________";
        cout << "\nUser card:";
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

    static void ShowUpdateUserScreen() {
        clsScreen::_PrineScreenHeader("Update user screen");
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
                cout << "\nThe user is not exist\n";
            }
        }
        clsUser User = clsUser::Find(Username);
        _PrintUserData(User);
        clsUser::enSaveResults SaveResults = clsUser::enSaveResults::svFaildEmptyObject;

        char ConfirmOperation = clsInputValidate::ReadChar("\nDo you want to update this user? [Y/N]:  ");
        if (toupper(ConfirmOperation) == 'Y') {

            int UpdateType = clsInputValidate::ReadNumberInRange<int>(1, 2, "\nDo you want to update [1]All data, [2]Permissions: ", "\nInvalid input, Do you want to update [1]All data, [2]Permissions: ");

            if (UpdateType == 1) {
                _ReadUserData(User);
            }
            else {
                User.SetPermission(_ReadPermissions());
            }
            _PrintUserData(User);
        }

        ConfirmOperation = clsInputValidate::ReadChar("\nFinal confirmation, do you want to update this user? [Y/N]:  ");
        if (toupper(ConfirmOperation) == 'Y') {
            SaveResults = User.Save();
        }

        switch(SaveResults) {
            case clsUser::enSaveResults::svSucceeded:
                cout << "\nThe user has been updated successfully.\n";
                break;
            case clsUser::enSaveResults::svFaildEmptyObject:
                cout << "\nThe user has not been updated.\n";
                break;
            default:
                cout << "\nThe user hasn't been updated.\n";
                break;
        }

    }
};