#pragma once

#include <iostream>
#include <iomanip>
#include "clsDate.h"
#include "clsScreen.h"
#include "clsUser.h"
#include "Global.h"
using namespace std;

class clsLoginRegisterScreen : protected clsScreen {

private:
    
    static void _PrintLoginRecordLine(clsUser::stLoginRegister LoginRecord) {
        cout << "| " << setw(30) << left << LoginRecord.sSystemDateTime;
        cout << "| " << setw(20) << left << LoginRecord.sUsername;
        cout << "| " << setw(10) << left << LoginRecord.sPassword;
        cout << "| " << setw(10) << left << LoginRecord.sPermission << " |";
    }

    public:

    static void ShowLoginRegisterListScreen() {

        if (!clsScreen::_CheckAccessRight(clsUser::enPermissions::eLoginRegister)) {
            return;
        }

        vector<clsUser::stLoginRegister> vLoginRegisterData = clsUser::GetLoginRegisterData();
        string Title = "Login register list";
        string SubTitle = "()" + to_string(vLoginRegisterData.size()) + ") Record(s).";

        clsScreen::_PrineScreenHeader(Title, SubTitle);
        cout << "\n________________________________________________________________________________\n" << endl;
        cout << "| " << left << setw(30) << "Date\\Time";
        cout << "| " << left << setw(20) << "Account number";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(10) << "Permission" << " |";
        cout << "\n________________________________________________________________________________\n" << endl;

        if (vLoginRegisterData.size() == 0) {
            cout << "\t\t\t\tNo login records registered In the System!";
        }
        else {
            for (clsUser::stLoginRegister& SingleLoginRecord : vLoginRegisterData) {
                _PrintLoginRecordLine(SingleLoginRecord);
                cout << endl;
            }
        }
        cout << "________________________________________________________________________________\n" << endl;
    }
};