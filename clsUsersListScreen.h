#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

class clsUsersListScreen : protected clsScreen {

private:

    static void _PrintUserRecordLine(clsUser User)  {
        cout << "| " << left << setw(20) << User.GetFirstName();
        cout << "| " << left << setw(20) << User.GetLastName();
        cout << "| " << left << setw(25) << User.GetEmail();
        cout << "| " << left << setw(20) << User.GetPhone();
        cout << "| " << left << setw(25) << User.GetUsername();
        cout << "| " << left << setw(10) << User.GetPassword();
        cout << "| " << left << setw(10) << User.GetPermission() << " |";
    }

public:

    static void ShowUsersListScreen() {
        vector<clsUser> vUsersData = clsUser::GetUsersList();

        string Title = "Users list screen";
        string SupTitle = "(" + to_string(vUsersData.size()) + ") Users";
        
        clsScreen::_PrineScreenHeader(Title, SupTitle);
        cout << "\n__________________________________________________________________________________________________________________________________________________\n" << endl;
        cout << "| " << left << setw(20) << "First name";
        cout << "| " << left << setw(20) << "Last name";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(20) << "Phone";
        cout << "| " << left << setw(25) << "Username";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(10) << "Permission" << " |"; 
        cout << "\n__________________________________________________________________________________________________________________________________________________\n" << endl;
        
        if (vUsersData.size() == 0) {
            cout << "No users avaialble in the system!";
        }
        else {
            for (clsUser& User : vUsersData) {
                _PrintUserRecordLine(User);
                cout << endl;
            }
        }
        cout << "__________________________________________________________________________________________________________________________________________________\n" << endl;
    }

};