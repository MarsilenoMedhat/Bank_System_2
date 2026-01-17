#pragma once

#include <iostream>
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"
#include "../../Lib/clsScreen.h"
#include "../../Core/clsBankClient.h"
using namespace std;

class clsWithdrawScreen : protected clsScreen {

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

    static void ShowWithdrawScreen() {
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

        float WithdrawAmount = 0;
        while (true) {
            WithdrawAmount = clsInputValidate::ReadPositiveValidNumber<float>("\nEnter the withdraw amount or enter 0 to cancel the transaction: ", "\nInvalid number, Enter the withdraw amount or enter 0 to cancel the transaction: ", "Invalid number. ", true);
            if (WithdrawAmount == 0) {
                cout << "\nThe transaction has been cancelled.\n";
                return;
            }
            if (WithdrawAmount <= Client.GetAccountBalance()) {
                break;
            }
            cout << "\nThe withdraw amount exceeds the current balance.\n";
        }

        char ConfirmTransaction = clsInputValidate::ReadChar("\nAre you sure you want to perform this transaction? [Y/N]. ");

        if (toupper(ConfirmTransaction) == 'Y') {
            Client.Withdraw(WithdrawAmount);
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
            break;
        }
    }
};