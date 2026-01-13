#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;

class clsDepositScreen : protected clsScreen {

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
    static void ShowDepositScreen() {
        clsScreen::_PrineScreenHeader("Deposit screen.");
        string AccountNumber = "";

        while (true) {
            AccountNumber = clsInputValidate::ReadString("Enter the account number or enter \"back\" to back to the main menu: ");
            if (clsUtil::IsEqualText(AccountNumber)) {
                cout << "\nThe transaction has been cancelled.\n";
                return;
            }
            if (clsBankClient::IsClientExist(AccountNumber)) {
                break;
            }
            cout << "\nAccount number is not found. ";
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(Client);

        clsBankClient::enSaveResults SaveResults = clsBankClient::enSaveResults::vsFailedOperationCancelled;

        float DepositAmount = 0;
        while (true) {
            DepositAmount = clsInputValidate::ReadPositiveValidNumber<float>("\nEnter the deposit amount: ", "\nInvalid number, Enter the deposit amount: ", "Invalid number. ", true);
            if (DepositAmount == 0) {
                cout << "\nThe transaction has been cancelled.\n";
                return;    
            }
            else {
                break;
            }
        }
        char ConfirmTransaction = clsInputValidate::ReadChar("\nAre you sure you want to perform this transaction? [Y/N]. ");

        if (toupper(ConfirmTransaction) == 'Y') {
            Client.Deposit(DepositAmount);
            SaveResults = clsBankClient::enSaveResults::svSucceeded;
        }

        switch (SaveResults) {
        case clsBankClient::enSaveResults::svSucceeded:
            cout << "\nThe transaction has been done successfully.\n";
            cout << "\nNew balance: " << Client.GetAccountBalance() << endl;
            break;
        case clsBankClient::enSaveResults::svFailedEmptyObject:
            cout << "\nError account hasn't been saved because it's Empty";
            break;
            default:
            cout << "\nThe transaction has been cancelled.\n";
        }
    }
};