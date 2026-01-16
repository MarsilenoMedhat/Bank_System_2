#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsInputValidate.h"
#include "string.h"
#include "clsUtil.h"
using namespace std;

class clsCurrency {

private:

    enum enMode {eEmpt = 1, eUpdate = 2};

    string _CountryName = "";
    string _CurrencyCode = "";
    string _CurrencyName = "";
    double _CurrencyRate = 0;
    enMode _Mode;


    static clsCurrency _ConvertDataLineToCurrencyObject(string DataLine, string Seperator = "#//#") {
        vector<string> vCurrencyRecord = clsString::Split(DataLine, Seperator);
        return clsCurrency(vCurrencyRecord[0], vCurrencyRecord[1], vCurrencyRecord[2], stod(vCurrencyRecord[3]));
    }

    static vector<clsCurrency> _LoadCurrenciesDataFromFile() {
        vector<clsCurrency> vCurrenciesData;
        fstream CurrenciesDataFile("Currencies.txt", ios::in);
        
        if (CurrenciesDataFile.is_open()) {
            string DataLine = "";
            while (getline(CurrenciesDataFile, DataLine)) {
                clsCurrency CurrencyRecord = _ConvertDataLineToCurrencyObject(DataLine);
                vCurrenciesData.push_back(CurrencyRecord);
            }
        }
        CurrenciesDataFile.close();
        return vCurrenciesData;
    }
    
    static string _ConvertCurrencyRecordToLine(clsCurrency CurrencyRecord, string Seperator = "#//#") {
        string DataLine = "";
        DataLine += CurrencyRecord.GetCountryName() + Seperator;
        DataLine += CurrencyRecord.GetCurrencyCode() + Seperator;
        DataLine += CurrencyRecord.GetCurrencyName() + Seperator;
        DataLine += to_string(CurrencyRecord.GetCurrencyRate());
        return DataLine;
    }

    static void _SaveCurrenciesDataToFile(vector<clsCurrency> vCurrenciesData, string seperator = "#//#") {
        fstream CurrenciesDataFile("Currencies.txt", ios::out);
        if (CurrenciesDataFile.is_open()) {
            string DataLine = "";
            for (clsCurrency& Currency : vCurrenciesData) {
                DataLine = _ConvertCurrencyRecordToLine(Currency);
                CurrenciesDataFile << DataLine << endl;
            }
        }
        CurrenciesDataFile.close();
    }

    static clsCurrency _GetEmptyObject() {
        return clsCurrency("", "", "", 0, enMode::eEmpt);
    }

    
    static clsCurrency _Find(string SearchMethod, bool IsCountry) {
        fstream CurrenciesDataFile("Currencies.txt", ios::in);
        
        if (CurrenciesDataFile.is_open()) {
            string DataLine = "";
            while (getline(CurrenciesDataFile, DataLine)) {
                clsCurrency Currency = _ConvertDataLineToCurrencyObject(DataLine);
                if (IsCountry) {
                    if (clsUtil::IsEqualText(Currency.GetCountryName(), SearchMethod)) {
                        CurrenciesDataFile.close();
                        return Currency;
                    }
                }
                else {
                    if (clsUtil::IsEqualText(Currency.GetCurrencyCode(), SearchMethod)) {
                        CurrenciesDataFile.close();
                        return Currency;
                    }
                }
            }
            CurrenciesDataFile.close();
        }
        return _GetEmptyObject();
    }
    
    void _Update(double NewRate) {
        vector<clsCurrency> vCurrenciesData = _LoadCurrenciesDataFromFile();
        for (clsCurrency& Currency : vCurrenciesData) {
            if (Currency.GetCurrencyCode() == _CurrencyCode) {
                Currency = *this;
                break;
            }
        }
        _SaveCurrenciesDataToFile(vCurrenciesData);
    }
    
    public:
    
    clsCurrency(string CountryName, string CurrencyCode, string CurrencyName, double CurrencyRate, enMode Mode = enMode::eUpdate) {
        _CountryName = CountryName;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _CurrencyRate = CurrencyRate;
        _Mode = Mode;
    }
    
    clsCurrency() {};
    
    string GetCountryName() {
        return _CountryName;
    }
    
    string GetCurrencyCode() {
        return _CurrencyCode;
    }
    
    string GetCurrencyName() {
        return _CurrencyName;
    }
    
    double GetCurrencyRate() {
        return _CurrencyRate;
    }
    
    void SetCurrencyRate(double CurrencyRate) {
        _CurrencyRate = CurrencyRate;
    }
    
    enMode GetMode() {
        return _Mode;
    }
    
    static vector<clsCurrency> GetCurrenciesList() {
        return _LoadCurrenciesDataFromFile();
    }
    
    static clsCurrency FindByCurrencyCode(string Code) {
        return _Find(Code, false);
    }
    
    static clsCurrency FindByCountry(string CountryName) {
        return _Find(CountryName, true);
    }
    
    static bool IsExist(string CurrencyCode) {
        clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
        return (!Currency.IsEmpty());
    }
    
    bool IsEmpty() {
        return (_Mode == enMode::eEmpt);
    }

    void UpdateCurrency(double NewRate) {
        _CurrencyRate = NewRate;
        _Update(NewRate);
    }

    double ExchangeCurrencyToUSD(double ExchangeAmount) {
        return ExchangeAmount / _CurrencyRate;
    }

    double ExchangeCurrencyToOtherCurrency(double ExchangeAmount, clsCurrency Currency2) {
        double ConvertToUSD = ExchangeCurrencyToUSD(ExchangeAmount);
        if (Currency2.GetCurrencyCode() == "USD") {
            return ConvertToUSD;
        }
        else {
            return (ConvertToUSD * Currency2.GetCurrencyRate());
        }
    }
};