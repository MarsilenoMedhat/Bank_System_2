#pragma once

#include <iostream>
#include <iomanip>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsScreen.h"
using namespace std;

class clsTotalBalanceScreen : protected clsScreen {

private:
    static void _PrintClientRecordBalanceLine(clsBankClient Client) {
        cout << "| " << setw(15) << left << Client.GetAccountNumber();
        cout << "| " << setw(20) << left << Client.GetFullName();
        cout << "| " << setw(20) << left << Client.GetAccountBalance() << " |";
    }

public:
    static void ShowTotalBalanceScreen() {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        clsScreen::_PrineScreenHeader("Total balance screen.", "Clients list (" + to_string(vClients.size()) + ") client(s).");

        cout << "\n_______________________________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "Account number";
        cout << "| " << left << setw(20) << "client name";
        cout << "| " << left << setw(20) << "Account balance" << " |";
        cout << "\n_______________________________________________________________\n" << endl;

        if (vClients.size() == 0) {
            cout << "No Clients Available In the System!";
        }
        else {
            for (clsBankClient& Client : vClients) {
                _PrintClientRecordBalanceLine(Client);
                cout << endl;
            }
        }
        cout << "_______________________________________________________________\n" << endl;

        double TotalBalances = clsBankClient::GetTotslBalances();
        cout << "Total Balances = " << TotalBalances << endl;
        string TextNumber = clsUtil::NumberToText((TotalBalances));
        cout << "(" << TextNumber << ")\n";
    }

};