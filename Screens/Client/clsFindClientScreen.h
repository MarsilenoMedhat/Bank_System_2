#pragma once

#include <iostream>
#include "../../Lib/clsUtil.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsScreen.h"
#include "../../Lib/clsInputValidate.h"
using namespace std;

class clsFindClientScreen : protected clsScreen {

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

    static void FindClient() {

        if (!clsScreen::_CheckAccessRight(clsUser::enPermissions::eFindClient)) {
            return;
        }

        clsScreen::_PrineScreenHeader("Find client");
        string AccountNumber = clsInputValidate::ReadString("Enter the account number or enter \"back\" to back to the main menu: ");

        if (clsUtil::IsEqualText(AccountNumber)) {
            cout << "\nOperation has been cancelled.\n";
            return;
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if (Client.IsClientExist(Client.GetAccountNumber())) {
            _PrintClientCard(Client);
        }
        else {
            cout << "\nClient hasn't been found.\n";
        }
    }

};