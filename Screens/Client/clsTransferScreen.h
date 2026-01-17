#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include "../../Lib/clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"
#include "../../Global.h"
using namespace std;

class clsTransferScreen : protected clsScreen {

private:

    static void _PrintClientCard(clsBankClient Client, string ClientType) {
        cout << "\n_________________________________\n";
        cout << "\n\t" << ClientType << " Card";
        cout << "\n_________________________________\n";
        cout << "\nFull name  : " << Client.GetFullName();
        cout << "\nAcc number : " << Client.GetAccountNumber();
        cout << "\nBalance    : " << Client.GetAccountBalance();
        cout << "\n_________________________________\n";
    }

    static string _ReadAccountNumber(string ClientType) {
        string AccountNumber = "";
        while (true) {
            string Message = "\nEnter the " + ClientType + " account number or enter \"back\" to back to the transactions menu: ";
            AccountNumber = clsInputValidate::ReadString(Message);

            if (clsUtil::IsEqualText(AccountNumber, "back")) {
                return "back";
            }

            if (clsBankClient::IsClientExist(AccountNumber)) {
                return AccountNumber;
            }
            cout << "\nAccount number is not found. ";
        }
    }

public:

    static void ShowTransferScreen() {
        clsScreen::_PrineScreenHeader("Transfer Screen");

        string SenderAccountNumber = _ReadAccountNumber("sender");
        if(SenderAccountNumber == "back") {
            cout << "\nTransaction has been cancelled.\n";
            return;
        }
        clsBankClient Sender = clsBankClient::Find(SenderAccountNumber);
        _PrintClientCard(Sender, "Sender");
        
        string ReceiverAccountNumber = "";
        while (true) {
			ReceiverAccountNumber = _ReadAccountNumber("receiver");
            if (!(ReceiverAccountNumber == SenderAccountNumber)) {
				break;
            }
            cout << "\nError, the sender and teh receiver are the same account.\n";
        }

        if(ReceiverAccountNumber == "back") {
            cout << "\nTransaction has been cancelled.\n";
            return;
        }
        clsBankClient Receiver = clsBankClient::Find(ReceiverAccountNumber);
        _PrintClientCard(Receiver, "Receiver");
        
        double TransferAmount = 0;

        while (true) {
            TransferAmount = clsInputValidate::ReadPositiveValidNumber<float>("\nEnter the withdraw amount or enter 0 to cancel the transaction: ", "\nInvalid number, Enter the withdraw amount or enter 0 to cancel the transaction: ", "Invalid number. ", true);
            if (TransferAmount == 0) {
                cout << "\nThe transaction has been cancelled.\n";
                return;
            }
            if (TransferAmount <= Sender.GetAccountBalance()) {
                break;
            }
            cout << "\nThe withdraw amount exceeds the current balance.\n";
        }

        char ConfirmTransaction = clsInputValidate::ReadChar("\nDo you want to process this transaction? [Y/N]:  ");
        
        if (toupper(ConfirmTransaction) == 'Y') {
            if (Sender.Transfer(Receiver, TransferAmount, CurrentUser.GetUsername())) {
                cout << "\nTransaction has been done successfully.\n";
                _PrintClientCard(Sender, "Sender");
                _PrintClientCard(Receiver, "Receiver");
            }
        }
        else {
            cout << "\nTransaction has been cancelled.\n";
        }
    }

};