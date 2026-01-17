#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include "clsDate.h"
#include "clsUtil.h"
using namespace std;

class clsInputValidate {
public:

    // Method 1

    static string ReadString(string Message) {
        string Text = "";
        cout << Message;
        getline(cin >> ws, Text);
        return Text;
    }

    static char ReadChar(string Message) {
        char C = ' ';
        cout << Message;
        cin >> C;
        return C;
    }

    // Validate if the number.
    static bool IsValidNumber() {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }
        return true;
    }

    // Validate if the number is in range wether it's int or double.
    template <typename T>
    static bool IsNumberInRange(T From, T To, T Number) {
        if (!IsValidNumber()) {
            return false;
        }
        if (From > To) {
            clsUtil::SwapNumbers(From, To);
        }
        return (From <= Number && To >= Number);
    }


    // Read number wether it's int or double with custom message.
    template <typename T>
    static T ReadNumber(string Message) {
        T Num = 0;
        cout << Message;
        cin >> Num;
        return Num;
    }

    template <typename T>
    static T ReadValidNumber(string RequestMessage, string ErrorMessage) {
        T Num = ReadNumber<T>(RequestMessage);
        while (!IsValidNumber()) {
            Num = ReadNumber<T>(ErrorMessage);
        }
        return Num;
    }

    template <typename T>
    static T ReadNumberInRange(T From, T To, string RequestMessage, string ErrorMessage) {
        T Num = ReadNumber<T>(RequestMessage);
        while (!IsNumberInRange(From, To, Num) || !IsValidNumber()) {
            Num = ReadNumber<T>(ErrorMessage);
        }
        return Num;
    }

    template <typename T>
    static T ReadPositiveValidNumber(string RequestMessage, string ErrorMessage, string InternalErrorMessage, bool IncludeZero = false) {
        T Num = 0;
        while (true) {
            Num = ReadValidNumber<T>(RequestMessage, ErrorMessage);
            if ((IncludeZero && Num >= 0) || (!IncludeZero && Num > 0)) {
                return Num;
            }
            cout << endl << InternalErrorMessage;
        }
    }

    template <typename T>
    static T ReadNegativeValidNumber(string RequestMessage, string ErrorMessage, string InternalErrorMessage, bool IncludeZero = false) {
        T Num = 0;
        while (true) {
            Num = ReadValidNumber<T>(RequestMessage, ErrorMessage);
            if ((IncludeZero && Num <= 0) || (!IncludeZero && Num < 0)) {
                return Num;
            }
            cout << endl << InternalErrorMessage;
        }
    }





    // Method 2

    // template <typename T>
    // static bool IsNumberInRange(T From, T To, T Number) {
    //     if (From > To) {
    //     clsUtil::SwapNumbers(From, To);
    //     }
    //     return (From <= Number && To >= Number);
    // }


    // template <typename T>
    // T ReadNumber(string Message) {
    //     T Num = 0;
    //     cout << Message;
    //     cin >> Num;
    //     return Num;
    // }

    // template <typename T>
    // void IsValidNumber(T &Number, string ErrorMessage) {
    //     while (cin.fail()) {
    //         cin.clear();
    //         cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //         Number = ReadNumber(ErrorMessage);
    //     }
    // }

    // template <typename T>
    // static T ReadNumber(string RequestMessage, string ErrorMessage) {
    //     T Num = ReadNumber(RequestMessage);
    //     IsValidNumber(Num, ErrorMessage);
    //     return Num;
    // }

    // template <typename T>
    // static T ReadNumberInRange(T From, T To, string RequestMessage, string ErrorMessage) {
    //     T Num = ReadNumber(RequestMessage);

    //     while (!IsNumberInRange(From, To, Num)) {
    //         IsValidNumber(Num, ErrorMessage);
    //     }
    //     return Num;

    // }






    // Method 3

    // // check if the int number is between 2 numbers.
    // static bool IsNumberInRange(int From, int To, int Number) {
    //     if (From > To) {
    //         clsUtil::SwapNumbers(From, To);
    //     }
    //     return (From < Number && To > Number);
    // }

    // // check if the double number is between 2 numbers.
    // static bool IsNumberInRange(double From, double To, double Number) {
    //     if (From > To) {
    //         clsUtil::SwapNumbers(From, To);
    //     }
    //     return (From < Number && To > Number);
    // }

    // // Checking if the date is between 2 dates.
    // static bool IsDateBetween(clsDate From, clsDate To, clsDate Date) {
    //     if (clsDate::IsDate1AfterDate2(From, To)) {
    //         clsDate::Swap(From, To);
    //     }

    //     return (clsDate::IsDate1AfterDate2(Date, From) && clsDate::IsDate1BeforeDate2(Date, To));
    // }
    
    // int ReadInt(string Message) {
    //     int Num = 0;
    //     cout << Message;
    //     cin >> Num;
    //     return Num;
    // }

    // double ReadDbl(string Message) {
    //     double Num = 0;
    //     cout << Message;
    //     cin >> Num;
    //     return Num;
    // }

    // void IsValidInt(int &Number, string Message) {
    //     while (cin.fail()) {
    //         cin.clear();
    //         cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //         Number = ReadInt(Message);
    //     }
    // }

    // void IsValidDbl(double &Number, string Message) {
    //     while (cin.fail()) {
    //         cin.clear();
    //         cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //         Number = ReadDbl(Message);
    //     }
    // }

    // // Read int number only, if the user intered another type will display the ErrorMessage and ask for another input
    // static int ReadInt(string RequestMessage, string ErrorMessage) {
    //     int Num = ReadInt(RequestMessage);
    //     IsValidInt(Num, ErrorMessage);
    //     return Num;
    // }

    // // Read double number only, if the user intered another type will display the ErrorMessage and ask for another input
    // static double ReadDbl(string RequestMessage, string ErrorMessage) {
    //     double Num = ReadDbl(RequestMessage);
    //     return Num;
    // }

    // // Read int number in range.
    // static int ReadIntInRange(int From, int To, string RequestMessage, string ErrorMessage) {
    //     int Num = ReadInt(RequestMessage);

    //     while (!IsNumberInRange(From, To, Num)) {
    //         IsValidInt(Num, ErrorMessage);
    //     }
    //     return Num;
    // }

    // // Read double number in range.
    // static double ReadDblInRange(double From, double To, string RequestMessage, string ErrorMessage) {
    //     double Num = ReadDbl(RequestMessage);

    //     while (!IsNumberInRange(From, To, Num)) {
    //        IsValidDbl(Num, ErrorMessage);
    //     }
    //     return Num;
    // }

};