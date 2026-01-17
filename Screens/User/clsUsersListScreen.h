#pragma once

#include <iostream>
#include <iomanip>
#include "../../Lib/clsScreen.h"
#include "../../Core/clsUser.h"
using namespace std;

class clsUsersListScreen : protected clsScreen {

private:

    static void _PrintUserRecordLine(clsUser User)  {
        cout << "| " << left << setw(25) << User.GetUsername();
        cout << "| " << left << setw(20) << User.GetFullName();
        cout << "| " << left << setw(20) << User.GetPhone();
        cout << "| " << left << setw(25) << User.GetEmail();
        cout << "| " << left << setw(10) << User.GetPassword();
        cout << "| " << left << setw(10) << User.GetPermission() << " |";
    }

    static void _PrintTableHeader() {
        cout << "\n____________________________________________________________________________________________________________________________\n\n";
        cout << "| " << left << setw(25) << "Username";
        cout << "| " << left << setw(20) << "Full name";
        cout << "| " << left << setw(20) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(10) << "Permission" << " |";
        cout << "\n____________________________________________________________________________________________________________________________\n\n";        
    }

    static void _PrintTableFooter() {
        cout << "\n____________________________________________________________________________________________________________________________\n\n";
    }

public:

    static void ShowUsersListScreen() {
        vector<clsUser> vUsersData = clsUser::GetUsersList();

        string Title = "Users list screen";
        string SupTitle = "(" + to_string(vUsersData.size()) + ") Users";
        
        clsScreen::_PrineScreenHeader(Title, SupTitle);
        _PrintTableHeader();
        
        if (vUsersData.size() == 0) {
            cout << "No users avaialble in the system!";
        }
        else {
            for (clsUser& User : vUsersData) {
                _PrintUserRecordLine(User);
                cout << endl;
            }
        }
        _PrintTableFooter();
    }
};