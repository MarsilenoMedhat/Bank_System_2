#pragma once

#include <iostream>
#include "clsUtil.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen {

private:

    static void _PrintClientCard(clsBankClient Client) {
        cout << "\n---------------------------------------------------";
        cout << "\n\t\tClient data:";
        cout << "\n---------------------------------------------------";
        cout << "\n- First name       : " << Client.GetFirstName();
        cout << "\n- Last name        : " << Client.GetLastName();
        cout << "\n- Full name        : " << Client.GetFullName();
        cout << "\n- Phone number     : " << Client.GetPhone();
        cout << "\n- Email address    : " << Client.GetEmail();
        cout << "\n- Account number   : " << Client.GetAccountNumber();
        cout << "\n- PIN code         : " << Client.GetPINcode();
        cout << "\n- Account balance  : " << Client.GetAccountBalance();
        cout << "\n---------------------------------------------------";
    }

public:

    static void DeleteClient() {

        if (!clsScreen::_CheckAccessRight(clsUser::enPermissions::eDeleteClient)) {
            return;
        }

        clsScreen::_PrineScreenHeader("Delete client");
        string AccountNumber = "";

        while (true) {
            AccountNumber = clsInputValidate::ReadString("Enter the account number or enter \"back\" to back to the main menu: ");
            if (clsUtil::IsEqualText(AccountNumber)) {
                cout << "\nOperation has been cancelled..\n";
                return;
            }
            if (clsBankClient::IsClientExist(AccountNumber)) {
                break;
            }
            cout << "\nAccount number is not found. ";
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(Client);

        char ConfirmDelete = clsInputValidate::ReadChar("\nAre you sure you want to delete this client y/n? ");
        if (toupper(ConfirmDelete) == 'Y') {

            if (Client.Delete()) {
                cout << "\nClient has been Deleted Successfully.\n";
            }
            else {
                cout << "\nError Client hasn't been Deleted\n";
            }
        }
        else if (toupper(ConfirmDelete) == 'N') {
            cout << "\nAccount hasn't been deleted.\n";
        }
    }
};