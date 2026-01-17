#pragma once

#include <iostream>
#include <string>
#include "clsDate.h"
using namespace std;

class clsUtil { 
public:

    // Print a specific number of tabs
    static string Tabs(short TabsNumber) {
        string Tabs = "";
        for (int i = 0; i < TabsNumber; i++) {
            Tabs += "\t";
        }
        return Tabs;
    }

    // Swaps the values of two integer variables by reference.
    static void SwapNumbers(int &Number1, int &Number2) {
        int Temp = Number1;
        Number1 = Number2;
        Number2 = Temp;
    }

    // Swaps the values of two doubles variables by reference.
    static void SwapNumbers(double &Number1, double &Number2) {
        double Temp = Number1;
        Number1 = Number2;
        Number2 = Temp;
    }

    // Swaps the values of two strings variables by reference.
    static void SwapString(string &Text1, string &Text2) {
        string Temp = Text1;
        Text1 = Text2;
        Text2 = Temp;
    }

    // Swaps the values of two characters variables by reference.
    static void SwapCharacters(char &Char1, char &Char2) {
        char Temp = Char1;
        Char1 = Char2;
        Char2 = Temp;
    }

    // Swaps the values of two dates variables by reference.
    static void SwapDates(clsDate &Date1, clsDate &Date2) {
        clsDate Temp = Date1;
        Date1 = Date2;
        Date2 = Temp;
    }

    // Encrypts the given text by shifting each character by the specified EncryptionKey using caesar cipher style.
    static string EncryptKey(string Text, short EncryptioKey) {
        for (int i = 0; i <= Text.length(); i++)
        {
            Text[i] = char((int)Text[i] + EncryptioKey);
        }
        return Text;
    }

    // Decrypts the given text by shifting each character by the specified EncryptionKey using caesar cipher style.
    static string DecryptKey(string Text, short EncryptioKey) {
        for (int i = 0; i <= Text.length(); i++)
        {
            Text[i] = char((int)Text[i] - EncryptioKey);
        }
        return Text;
    }

    // Initial the random functions.
    static void Srand() {
        srand((unsigned)time(NULL));
    }

    // Generate a random number in range.
    static int RandomNumber(int From, int To) {
        int RandNum = rand() % (To - From + 1) + From;
        return RandNum;
    }

    enum enCharacterType {SmallLetter = 1, CapitalLetter = 2, Digit = 3, SpecialCharacter = 4, Mix = 5};

    // Generate a random small letter, capital letter, special character, or digit using enCharacterType
    static char RandomCharacter(enCharacterType CharacterType) {
        switch (CharacterType)
        {
        case enCharacterType::SmallLetter:
            return char(RandomNumber(97, 122));
            break;
        case enCharacterType::CapitalLetter:
            return char(RandomNumber(65, 90));
            break;
        case enCharacterType::Digit:
            return char(RandomNumber(48, 57));
            break;
        case enCharacterType::SpecialCharacter:
            return char(RandomNumber(33, 47));
            break;
        case enCharacterType::Mix:
            return RandomMixCharacter();
        }
        return ' ';
    }

    // Generate a random character from capital letter, small letter, and digit.
    static char RandomMixCharacter() {
        return RandomCharacter(enCharacterType(RandomNumber(1, 3)));
    }


    // Generate a random word by specific type, nd specific length.
    static string GenerateWord(enCharacterType CharacterType, short Length) {
        string word = "";
        for (int i = 1; i <= Length; i++)
        {
            word = word + RandomCharacter(CharacterType);
        }
        return word;
    }

    // Generates a key consisting of multiple words separated by dashes based on the given character type and length.
    static string GenerateKey(enCharacterType CharacterType, short WordsLength, short WordsNumber) {
        string Key = "";
        for (short i =  0; i < WordsNumber; i++) {
            if (i > 0) Key += "-";
            Key = GenerateWord(CharacterType, WordsLength);
        }
        return Key;
    }

    // Generate a specific number of keys using specific character type and length.
    static void GenerateKeys(int KeysNumber, enCharacterType CharacterType, short WordsLength, short WordsNumber) {
        cout << "\n";
        for (int i = 1; i <= KeysNumber; i++)
        {
            cout << "key [" << i << "] : " << GenerateKey(CharacterType, WordsLength, WordsNumber) << endl;
        }
        cout << "\n";
    }

    // Fill arr with random numbers.
    static void FillArrWithRandomNumbers(int ArrLength, int Arr[], int From, int To) {
        for (int i = 0; i < ArrLength; i++)
        {
            Arr[i] = RandomNumber(From, To);
        }
    }

    // checeking the max number exists in the array.
    static int MaxNumberInArr(int ArrLength, int Arr[]) {
        int MaxNum = 0;
        for (int i = 0; i < ArrLength; i++)
        {
            if (MaxNum < Arr[i])
            {
                MaxNum = Arr[i];
            }
        }
        return MaxNum;
    }

    // check the minimum number in array.
    static int MinimumNumberInArr(int ArrLength, int Arr[]) {
        int MiniNum = Arr[0];
        for (int i = 0; i < ArrLength; i++)
        {
            if (MiniNum > Arr[i])
            {
                MiniNum = Arr[i];
            }
        }
        return MiniNum;
    }

    // copy the main array content to another array
    static void CopyArr(int ArrLength, int MainArr[], int CopyArr[]) {
        for (int i = 0; i < ArrLength; i++)
        {
            CopyArr[i] = MainArr[i];
        }
    }

    // shuffling the main array.
    static void ShuffleArr(int ArrLength, int Arr[]) {
        for (int i = 0; i < ArrLength; i++)
        {
            swap(Arr[RandomNumber(1, ArrLength) - 1], Arr[RandomNumber(1, ArrLength) - 1]);
        }
    }

    // shuffling the array to a new one, and keeping the original as it is.
    static void ShuffleArr(int ArrLength, int Arr[], int ShuffledArr[]) {
        CopyArr(ArrLength, Arr, ShuffledArr);
        ShuffleArr(ArrLength, ShuffledArr);
    }

    // Reversing the main array
    static void ReverseArr(int ArrLength, int Arr[]) {
        for (int i = 0; i < ArrLength / 2; i++)
        {
            swap(Arr[i], Arr[ArrLength - 1 - i]);
        }
    }

    // Reversing the array to a new one, and keeping the original as it is.
    static void ReverseArr(int ArrLength, int Arr[], int ReversedArr[]) {
        CopyArr(ArrLength, Arr, ReversedArr);
        ReverseArr(ArrLength, ReversedArr);
    }

    // Checking the number in the array and return the number.
    static short CheckNumber(int ArrLength, int Arr[], int CheckingNumber) {
        for (int i = 0; i < ArrLength; i++)
        {
            if (CheckingNumber == Arr[i])
            {
                return i;
            }
        }
        return -1;
    }

    // checking is the number in the array, if false will return -1.
    static bool IsNumberInArr(int ArrLength, int Arr[], int CheckingNumber) {
        return CheckNumber(ArrLength, Arr, CheckingNumber) != -1;
    }

    // Adding new element int to the array.
    static void AddElementInArr(int NewNumber, int& ArrLength, int Arr[100]) {
        Arr[ArrLength] = NewNumber;
        ArrLength++;
    }

    // return the number position, and if it doesn't exist will return -1.
    static short NumberPosition(int Number, int ArrLEngth, int Arr[]) {
        for (int i = 0; i < ArrLEngth; i++)
        {
            if (Number == Arr[i])
            {
                return i;
            }
        }
        return -1;
    }

    // check if the number is in the arr or no.
    static bool IsNumberFound(int Number, int ArrLength, int Arr[]) {
        return (NumberPosition(Number, ArrLength, Arr) != -1);
    }

    // copy a specific number to another array.
    static void CopyDistinctNumberInArr(int ArrLength, int& Arr2length, int Arr[], int Arr2[]) {
        for (int i = 0; i < ArrLength; i++)
        {
            if (!IsNumberFound (Arr[i], Arr2length, Arr2))
            {
                AddElementInArr(Arr[i], Arr2length, Arr2);
            }
        }
    }

    // checking if the array is palindrome or no.
    static bool IsPalindromeArr(int ArrLlength, int Arr[]) {
        for (int i = 0; i < ArrLlength - 1 - i; i++)
        {
            if (Arr[i] != Arr[ArrLlength - 1 - i])
            {
                return false;
            }
        }
        return true;
    }

    static string NumberToText(int Number) {
        if (Number == 0) {
            return "";
        }
        if (Number >= 1 && Number <= 19) {
            string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
            return arr[Number] + " ";
        }
        if (Number >= 20 && Number <= 99) {
            string arr[] = {"", "", "Twenty", "Thirty", "Fourty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
            return arr[Number / 10] + " " + clsUtil::NumberToText(Number % 10);
        }
        if (Number >= 100 && Number <= 199) {
            return "One Hundred " + clsUtil::NumberToText(Number % 100); 
        }
        if (Number >= 200 && Number <= 999) {
            return clsUtil::NumberToText(Number / 100) + "Hundreds " + clsUtil::NumberToText(Number % 100);
        }
        if (Number >= 1000 && Number <= 1999) {
            return "One Thousand " + clsUtil::NumberToText(Number % 1000);
        }
        if (Number >= 2000 && Number <= 999999) {
            return clsUtil::NumberToText(Number / 1000) + "Thousands " + clsUtil::NumberToText(Number % 1000);
        }
        if (Number >= 1000000 && Number <= 1999999) {
            return "One Million " + clsUtil::NumberToText(Number % 1000000);
        }
        if (Number >= 2000000 && Number <= 999999999) {
            return clsUtil::NumberToText(Number / 1000000) + "Millions " + clsUtil::NumberToText(Number % 1000000);
        }
        if (Number >= 1000000000 && Number <= 1999999999) {
            return "One Billion " + clsUtil::NumberToText(Number % 1000000000);
        }
        else {
            return (Number / 1000000000) + "Billions " + clsUtil::NumberToText(Number % 1000000000);
        }
    }

    // convert all the letters in text to a lower cases
    static string ConvertTextToLowerCases(string Text) {
        string ConvertedText = "";
        int Length = Text.length();
        for (int i = 0; i < Length; i++) {
            ConvertedText += tolower(Text[i]);
        }
        return ConvertedText;
    }

    // convert all the letters in text to a upper cases
    static string ConvertTextToUpperCases(string Text) {
        string ConvertedText = "";
        int Length = Text.length();
        for (int i = 0; i < Length; i++) {
            ConvertedText += toupper(Text[i]);
        }
        return ConvertedText;
    }

    static bool IsEqualText(const string& Text, const string& Key = "back") {
        return clsUtil::ConvertTextToLowerCases(Text) == clsUtil::ConvertTextToLowerCases(Key);
    }
};  