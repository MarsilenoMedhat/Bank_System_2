#pragma once

#include <iostream>
#include "clsUser.h"
#include "Global.h"
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
    }

    static bool _CheckAccessRight(clsUser::enPermissions Permission) {
        if (!CurrentUser.CheckAccessPermission(Permission)) {
        cout << "_______________________________________________________\n";
        cout << "\nAccess denied! Please contact you adminstrator.\n";
        cout << "_______________________________________________________\n";
            return false;
        }
        return true;
    }
};