#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"
using namespace std;

class clsTransferLogScreen : protected clsScreen {

private:

    static void _PrintTransferRecord(clsBankClient::stTransferLog TransferRecord) {
        cout << "| " << left << setw(30) << TransferRecord.DateTime;
        cout << " | " << left << setw(10) << TransferRecord.SenderAccountNumber;
        cout << " | " << left << setw(10) << TransferRecord.ReceiverAccountNumber;
        cout << " | " << left << setw(20) << TransferRecord.TransferAmount;
        cout << " | " << left << setw(20) << TransferRecord.SenderNewBalance;
        cout << " | " << left << setw(20) << TransferRecord.ReceiverNewBalance;
        cout << " | " << left << setw(10) << TransferRecord.Username << " |";
    }

    static void _PrintTableHeader() {
        cout << "\n______________________________________________________________________________________________________________________________________________\n\n";
        cout << "| " << left << setw(30) << "Date/Time";
        cout << " | " << left << setw(10) << "S.Acc";
        cout << " | " << left << setw(10) << "R.Acc";
        cout << " | " << left << setw(20) << "Transfer amount";
        cout << " | " << left << setw(20) << "S.new balance";
        cout << " | " << left << setw(20) << "R.new balance";
        cout << " | " << left << setw(10) << "Username" << " |";
        cout << "\n______________________________________________________________________________________________________________________________________________\n\n";
    }
    
    static void _PrintTableFooter() {
        cout << "______________________________________________________________________________________________________________________________________________\n\n";
    }

public:

    static void ShowTransferLogScreen() {
        vector<clsBankClient::stTransferLog> vTransferLog = clsBankClient::GetTransferLogData();

        string Title = "Transfer log";
        string SubTitle = to_string(vTransferLog.size()) + "Records";
        clsScreen::_PrineScreenHeader(Title, SubTitle);
        _PrintTableHeader();
        
        if (vTransferLog.size() == 0) {
            cout << "No records avaialble in the system!";
        }
        else {
            for (clsBankClient::stTransferLog& TransferData : vTransferLog) {
                _PrintTransferRecord(TransferData);
                cout << endl;
            }
        }
        _PrintTableFooter();
    }
};