#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
using namespace std;

class clsClientListScreen : protected clsScreen {

private:
    static void _PrintClientRecordLine(clsBankClient Client) {
        cout << "| " << setw(15) << left << Client.GetAccountNumber();
        cout << "| " << setw(20) << left << Client.GetFullName();
        cout << "| " << setw(17) << left << Client.GetPhone();
        cout << "| " << setw(35) << left << Client.GetEmail();
        cout << "| " << setw(10) << left << Client.GetPINcode();
        cout << "| " << setw(20) << left << Client.GetAccountBalance() << " |";
    }

public:
    static void ShowClientsList() {

        if (!clsScreen::_CheckAccessRight(clsUser::enPermissions::eShowClientsList)) {
            return;
        }

        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "Clients list";
        string SubTitle = "Clients list (" + to_string(vClients.size()) + ") client(s).";

        clsScreen::_PrineScreenHeader(Title, SubTitle);
        cout << "\n___________________________________________________________________________________________________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "Account number";
        cout << "| " << left << setw(20) << "client name";
        cout << "| " << left << setw(17) << "Phone number";
        cout << "| " << left << setw(35) << "Email address";
        cout << "| " << left << setw(10) << "PIN code";
        cout << "| " << left << setw(20) << "Account balance" << " |";
        cout << "\n___________________________________________________________________________________________________________________________________\n" << endl;

        if (vClients.size() == 0) {
            cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else {
            for (clsBankClient& Client : vClients) {
                _PrintClientRecordLine(Client);
                cout << endl;
            }
        }
        cout << "\n___________________________________________________________________________________________________________________________________\n" << endl;
    }
};