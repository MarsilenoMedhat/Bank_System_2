#pragma once

#include <iostream>
#include "../../Lib/clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../clsMainScreen.h"
using namespace std;

class clsAddNewClientScreen : protected clsScreen {

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
    static void _ReadClientData(clsBankClient& Client) {
        Client.SetFirstName(clsInputValidate::ReadString("\nEnter the first name: "));
        Client.SetLastName(clsInputValidate::ReadString("\nEnter the last name: "));
        Client.SetEmail(clsInputValidate::ReadString("\nEnter the email address: "));
        Client.SetPhone(clsInputValidate::ReadString("\nEnter the phone number: "));
        Client.SetPINcode(clsInputValidate::ReadString("\nEnter the PIN code: "));
        Client.SetAccountBalance(clsInputValidate::ReadValidNumber<float>("\nEnter the balance: ", "\nInvalid number, Enter the balance: "));
    }

public:

    static void AddNewClient() {
        if (!clsScreen::_CheckAccessRight(clsUser::enPermissions::eAddNewClient)) {
            return;
        }

        clsScreen::_PrineScreenHeader("Add new client");
        string AccountNumber = "";

        while (true) {
            AccountNumber = clsInputValidate::ReadString("Enter the new account number or enter \"back\" to back to the main menu: ");

            if (clsUtil::IsEqualText(AccountNumber, "back")) {
                cout << "\nOperation has been cancelled.\n";
                return;
            }
            if (!clsBankClient::IsClientExist(AccountNumber)) {
                break;
            }
            cout << "\nAccount number is not found. ";
        }
        clsBankClient NewClient = clsBankClient::GetAddClientObject(AccountNumber);
        _ReadClientData(NewClient);
        clsBankClient::enSaveResults SaveResult = clsBankClient::enSaveResults::vsFailedOperationCancelled;

        char ConfirmAdding = clsInputValidate::ReadChar("\nAre you sure you want to add this client y/n? ");
        if (toupper(ConfirmAdding) == 'Y') {
            SaveResult = NewClient.Save();
        }

        switch(SaveResult) {
            case clsBankClient::enSaveResults::svSucceeded:
                cout << "\nAccount added successfully.\n";
                _PrintClientCard(NewClient);
                break;
            case clsBankClient::enSaveResults::svFailedEmptyObject:
                cout << "\nFaild to save the client data because it's empty.\n";
                break;
            case clsBankClient::enSaveResults::svFailedAccountNumberExists:
                cout << "\nFailed to save the client data because the account number already used.\n";
            default:
                cout << "\nAccount hasn't been added.\n";
        }
    }

};