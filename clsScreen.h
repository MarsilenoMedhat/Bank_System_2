#pragma once

#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"
using namespace std;

class clsScreen {

protected:
    static void _PrineScreenHeader(string Title, string SubTitle = "") {
        cout << "_______________________________________________________";
        cout << "\n\n\t\t" << Title;
        if (SubTitle != "") {
            cout << "\n\t\t" << SubTitle;
        }
        cout << "\n_______________________________________________________\n\n";
        cout << "User: " << CurrentUser.GetUsername() << endl;
        cout << "Date: " << clsDate::DateToString(clsDate::getSystemTime());
        cout << "\n_______________________________________________________\n\n";
    }   

    static bool _CheckAccessRight(clsUser::enPermissions Permission) {
        if (!CurrentUser.CheckAccessPermission(Permission)) {
            _PrineScreenHeader("Access denied!", "Please contact you adminstrator.");
            return false;
        }
        return true;
    }
};