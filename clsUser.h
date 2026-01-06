#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsPerson.h"
#include "clsUtil.h"
using namespace std;

class clsUser : public clsPerson {

private:

    enum enMode {eEmptyMode = 1, eUpdateMode = 2, eAddMode = 3};
    enMode _Mode = enMode::eUpdateMode;

    string _Username;
    string _Password;
    int _Permission;
    bool _MarkForDelete = false;

    static clsUser _GetEmptyUserObject() {
        return clsUser("", "", "", "", "", "", 0, clsUser::enMode::eEmptyMode);
    }

    static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#") {
        vector<string> vUser = clsString::Split(Line, Seperator);

        return clsUser(vUser[0], vUser[1], vUser[2], vUser[3], vUser[4], vUser[5], stoi(vUser[6]), clsUser::enMode::eUpdateMode);
    }

    static string _ConvertUserObjestToLine(clsUser User, string Seperator = "#//#") {
        string UserRecord = User.GetFirstName() + Seperator;
        UserRecord += User.GetLastName() + Seperator;
        UserRecord += User.GetEmail() + Seperator;
        UserRecord += User.GetPhone() + Seperator;
        UserRecord += User.GetUsername() + Seperator;
        UserRecord += User.GetPassword() + Seperator;
        UserRecord += to_string(User.GetPermission());
        return UserRecord;
    }

    static void _SaveUsersDataToFile(vector<clsUser> vUsers, string Seperator = "#//#") {
        fstream UsersDataFile("Users.txt", ios::out);

        if(UsersDataFile.is_open()){
            string UserRecord = "";
            for (clsUser& User : vUsers) {
                if (User.GetMarkForDelete() == false) {
                    //we only write records that are not marked for delete.
                    UserRecord = _ConvertUserObjestToLine(User);
                    UsersDataFile << UserRecord << endl;
                }
            }
            UsersDataFile.close();
        }
    }

    static vector<clsUser> _LoadUsersDataFromFile() {
        vector<clsUser> vUsers;
        fstream UsersDataFile("Users.txt", ios::in);

        if (UsersDataFile.is_open()) {
            string UserRecord = "";
            while (getline(UsersDataFile, UserRecord)) {
                clsUser UserObject = _ConvertLineToUserObject(UserRecord);
                vUsers.push_back(UserObject);
            }
            UsersDataFile.close();
        }
        return vUsers;
    }

    void _AddUserDataToFile(string UserDataLine) {
        fstream UsersDataFile("Users.txt", ios::in | ios::app);
        if (UsersDataFile.is_open()) {
            UsersDataFile << UserDataLine << endl;
        }
        UsersDataFile.close();
    }

    void _Update() {
    vector<clsUser> vUsers = _LoadUsersDataFromFile();
        for (clsUser& User : vUsers) {
            if (User._Username == _Username) {
                User = *this;
                break;
            }
        }
    }

    void _AddNew() {
        _AddUserDataToFile(_ConvertUserObjestToLine(*this));
    }

public:

    clsUser(string FirstName, string LastName, string Email, string Phone, string Username, string Password, int Permission, enMode Mode = enMode::eUpdateMode) : clsPerson (FirstName, LastName, Email, Phone) {
        _Username = Username;
        _Password = Password;
        _Permission = Permission;
        _Mode = Mode;
    }

    string GetUsername() {

        return _Username;
    }

    void SetUsername(string Username) {
        _Username = Username;
    }

    string GetPassword() {
        return _Password;
    } 

    void SetPassword(string Password) {
        _Password = Password;
    }

    int GetPermission() {
        return _Permission;
    }

    void SetPermission(int Permission) {
        _Permission = Permission;
    }

    bool GetMarkForDelete() {
        return _MarkForDelete;
    }

    bool IsEmpty() {
        return (_Mode == enMode::eEmptyMode); 
    }

    bool Delete() {
        vector<clsUser> vUsers = _LoadUsersDataFromFile();

        for (clsUser& User : vUsers) {
            if (User.GetUsername() == _Username) {
                User._MarkForDelete = true;
            }
        }
        _SaveUsersDataToFile(vUsers);
        *this = _GetEmptyUserObject();
        return true;
    }

    static clsUser Find(string Username) {
        fstream UsersDataFile("Users.txt", ios::in);
        string UserDataLine;

        if (UsersDataFile.is_open()) {
            while (getline(UsersDataFile, UserDataLine)) {
                clsUser User = _ConvertLineToUserObject(UserDataLine);
                if (User.GetUsername() == Username) {
                    UsersDataFile.close();
                    return User;
                }
            }
        }
        return _GetEmptyUserObject();
    }

    static clsUser Find(string Username, string Password) {
        clsUser User = Find(Username);
        if (!User.IsEmpty()) {
            if (User.GetPassword() == Password) {
                return User;
            }
        }
        return _GetEmptyUserObject();
    }

    void Update() {
        vector<clsUser> vUsers = _LoadUsersDataFromFile();

        for (clsUser& User : vUsers) {
            if (User._Username == _Username) {
                User = *this;
                break;
            }
        }
        _SaveUsersDataToFile(vUsers);
    }

    static bool IsUserExists(string Username) {
        clsUser User = clsUser::Find(Username);
        return (!User.IsEmpty());
    }

    static vector<clsUser> GetUsersList() {
        return _LoadUsersDataFromFile();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults Save() {
        switch(_Mode) {
            case enMode::eEmptyMode:
                if (IsEmpty()) {
                    return enSaveResults::svFaildEmptyObject;
                }
            case enMode::eUpdateMode:
                Update();
                return enSaveResults::svSucceeded;
            case enMode::eAddMode:
                if (IsUserExists(_Username)) {
                    return enSaveResults::svFaildUserExists;
                }
                _AddNew();
                _Mode == enMode::eUpdateMode;
                return enSaveResults::svSucceeded;
        }
    }
};