#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "clsString.h"
#include "clsPerson.h"
#include "clsInputValidate.h"
using namespace std;

class clsBankClient : public clsPerson {
private:
    enum enMode {EmptyMode = 0, UpdateMode = 1, AddMode = 2};
    enMode _Mode;

    bool _MarkedForDelete = false;
    string _AccountNumber;
    string _PINcode;
    double _AccountBalance;

    static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#") {
        vector<string> vClientData = clsString::Split(Line, Seperator);
        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));  
    }

    static clsBankClient _GetEmptyClientData() {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    bool _IsEmpty() {
        return (_Mode == enMode::EmptyMode);
    }

    static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#") {
        string DataLine = Client.GetFirstName() + Seperator;
        DataLine += Client.GetLastName() + Seperator;
        DataLine += Client.GetEmail() + Seperator;
        DataLine += Client.GetPhone() + Seperator;
        DataLine += Client.GetAccountNumber() + Seperator;
        DataLine += Client.GetPINcode() + Seperator;
        DataLine += to_string(Client.GetAccountBalance());
        return DataLine;
    }

    static void _SaveClientsDataToFile(vector<clsBankClient> vClients, string Seperator = "#//#") {
        fstream ClientsDataFile("Clients.txt", ios::out);
        if (ClientsDataFile.is_open()) {
            string DataLine;
            for (clsBankClient& C : vClients) {
                if (C._MarkedForDelete == false) {
                    DataLine = _ConvertClientObjectToLine(C);
                    ClientsDataFile << DataLine << endl;
                }
            }
            ClientsDataFile.close();
        }
    }

    static vector<clsBankClient> _LoadClientDataFromFile() {
        vector<clsBankClient> vClient;
        fstream ClientsDataFile ("Clients.txt", ios::in);
        if (ClientsDataFile.is_open()) {
            string DataLine = "";
            while (getline(ClientsDataFile, DataLine)) {
                clsBankClient Client = _ConvertLineToClientObject(DataLine);
                vClient.push_back(Client);
            }
            ClientsDataFile.close();
        }
        return vClient;
    }

    void _Update() {
        vector<clsBankClient> vClientsData = _LoadClientDataFromFile();
        for (clsBankClient& C : vClientsData) {
            if (C.GetAccountNumber() == _AccountNumber) {
                C = *this;
                break;
            }
        }
        _SaveClientsDataToFile(vClientsData);
    }

    void _AddNew() {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string ClientDataLine) {
        fstream ClientsDataFile("Clients.txt", ios::out | ios::app);
        if (ClientsDataFile.is_open()) {
            ClientsDataFile << ClientDataLine << endl;
        }
        ClientsDataFile.close();
    }

public:
    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PINcode, double AccountBalance) : clsPerson(FirstName, LastName, Email, Phone) {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PINcode = PINcode;
        _AccountBalance = AccountBalance;
    }

    bool GetMarkForDelete() {
        return _MarkedForDelete;
    }

    string GetAccountNumber() {
        return _AccountNumber;
    }

    void SetPINcode(string PINcode) {
        _PINcode = PINcode;
    }

    string GetPINcode() {
        return _PINcode;
    }

    void SetAccountBalance(double AccountBalance) {
        _AccountBalance = AccountBalance;
    }

    double GetAccountBalance() {
        return _AccountBalance;
    }

    static vector<clsBankClient> GetClientsList() {
        return _LoadClientDataFromFile();
    }

    static clsBankClient Find(string AccountNumber) {
        fstream ClientsDataFile("Clients.txt", ios::in);
        if (ClientsDataFile.is_open()) {
            string Line = "";

            while (getline(ClientsDataFile, Line)) {
                clsBankClient Client = _ConvertLineToClientObject(Line);

                if (AccountNumber == Client.GetAccountNumber()) {
                    ClientsDataFile.close();
                    return Client;
                }
            }
            ClientsDataFile.close();
        }
        return _GetEmptyClientData();
    }

    static clsBankClient Find(string AccountNumber, string PINcode) {
        clsBankClient Client = Find(AccountNumber);

        if (PINcode == Client.GetPINcode()) {
            return Client;
        }
        return _GetEmptyClientData();
    }

    static bool IsClientExist(string AccountNumber) {
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        return (!Client._IsEmpty());
    }

    static clsBankClient GetAddClientObject(string AccountNumber) {
        return clsBankClient(enMode::AddMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete() {
        vector<clsBankClient> vClients = _LoadClientDataFromFile();
        
        for (clsBankClient& C : vClients) {
            if (C.GetAccountNumber() == _AccountNumber) {

                // Note: Even though _MarkedForDelete is a private member, 
                // it can still be accessed here because this code is inside 
                // the clsBankClient class itself. 
                // In C++, any object of the same class can access private members 
                // of other objects of that same class.

                C._MarkedForDelete = true;
                break;
            }
        }
        _SaveClientsDataToFile(vClients);
        *this = _GetEmptyClientData();
        return true;
    }

    static double GetTotslBalances() {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        double Total = 0;

        for (clsBankClient& Client : vClients) {
            Total += Client.GetAccountBalance();
        }
        return Total;
    }

    enum enSaveResults {svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExists = 2, vsFailedOperationCancelled = 3};

    enSaveResults Save() {
        switch (_Mode) {
            case enMode::EmptyMode:
                if (_IsEmpty()) {
                    return enSaveResults::svFailedEmptyObject;
                }
            case enMode::UpdateMode:
                if (_IsEmpty()) {
                    return enSaveResults::svFailedEmptyObject;
                }
                else {
                    _Update();
                    return enSaveResults::svSucceeded;
                }
                return enSaveResults::svSucceeded;
            case enMode::AddMode:
                if (clsBankClient::IsClientExist(_AccountNumber)) {
                    return enSaveResults::svFailedAccountNumberExists;
                }
                else {
                    _AddNew();
                    return enSaveResults::svSucceeded;
                }
            default:
                return enSaveResults::vsFailedOperationCancelled;
        }
    }

    void Deposit(float DepositAmount) {
        _AccountBalance += DepositAmount;
        Save();
    }

    bool Withdraw(float WithdrawAmount) {
        if (WithdrawAmount > _AccountBalance) {
            return false;
        }
        else {
            _AccountBalance -= WithdrawAmount;
        }
        Save();
        return true;
    }

    bool Transfer(clsBankClient& Receiver, double TransferAmount) {
        if (TransferAmount > _AccountBalance) {
            return false;
        }
        Withdraw(TransferAmount);
        Receiver.Deposit(TransferAmount);
        return true;
    }
};