#pragma once

#include <iostream>
#include <cmath>
using namespace std;

class clsMath {
public:

    // Checking the validation of a number in a spisific range.
    static bool CheckNumberValidationInRange(int Number, int From, int To) {
        return (Number >= From && Number <= To);
    }

    enum enEvenOdd {Odd = 1, Even = 2};

    // Check is the number is odd or even.
    static enEvenOdd CheckOddOrEven(int Number) {
        if (Number % 2 == 0) {
            return enEvenOdd::Even;
        }
        else {
            return enEvenOdd::Odd;
        }
    }

    // check if the number is a even number.
    static bool IsEvenNumber(int Number) {
        if (clsMath::CheckOddOrEven(Number) == enEvenOdd::Even) {
            return true;
        }
        return false;
    }

    // Resevsing a number and return the reversed value.
    static int ReverseNumber(int number)
    {
        short remainder = 0;
        int ReversedNumber = 0;
        while (number > 0)
        {
            remainder = number % 10;
            number = number /10;
            ReversedNumber =  ReversedNumber * 10 + remainder;
        }
        return ReversedNumber;
    }

    // Check if the number is a palindrome number or no.
    static bool CheckPalindromeNumber(int number)
    {
        return number == ReverseNumber(number);
    }

    // return the total of summing the array numbers.
    static int SumNumbersInArr(int ArrLength, int Arr[]) {
        int sum = 0;
        for (int i = 0; i < ArrLength; i++)
        {
            sum += Arr[i];
        }
        return sum;
    }

    static float AverageArrNumber(int ArrLength, int Arr[])
    {
        return (float)SumNumbersInArr(ArrLength, Arr) / ArrLength;
    }

    enum enPrimeNonprime {prime = 1, NonPrime = 2};

    // check if the number is prime or non-prime and return it enPrimeNotprime type.
    static enPrimeNonprime CheckPrimeNumber(int Number) {
        int HalfNumber = round(Number / 2);
        if (Number == 1)
        {
            return enPrimeNonprime::NonPrime;
        }
        for (int i = 2; i <= HalfNumber; i++)
        {
            if (Number % i == 0)
            {
                return enPrimeNonprime::NonPrime;
            }
        }
        return enPrimeNonprime::prime;
    }

    // check if the number is prime or no.
    static bool IsPrimeNumber(int Number) {
        return (CheckPrimeNumber(Number) == clsMath::enPrimeNonprime::prime);
    }

    // Copy prime number or non-prime numbers in another array
    static void CopyPrimeNonprimeNumbersInArr(int MainArrLength, int& CopyArrLength, int MainArr[], int CopyArr[], bool CopyPrime = true) {
        for (int i = 0; i < MainArrLength; i++)
        {
            if (IsPrimeNumber(MainArr[i]) == CopyPrime)
            {
                CopyArr[CopyArrLength] = MainArr[i];
                CopyArrLength++;
            }
        }
    }

    // Counts the add numbers in the array.
    static int CountOddNumbersInArr(int ArrLength, int Arr[]) {
        int counter = 0;
        for (int i = 0; i < ArrLength; i++)
        {
            if (IsEvenNumber(Arr[i]))
            {
                counter++;
            }
        }
        return counter;
    }

    // Counts the even numbers in the array.
    static int CountEvenNumbersInArr(int ArrLength, int Arr[]) {
        int counter = 0;
        for (int i = 0; i < ArrLength; i++)
        {
            if (IsEvenNumber(Arr[i]))
            {
                counter++;
            }
        }
        return counter;
    }

    // Checking if the number if positive or no.
    static bool IsPositiveNumber(int Number) {
        return (Number > 0);
    }

    // Checking if the number if negative or no.
    static bool IsNegativeNumber(int Number) {
        return !IsPositiveNumber(Number);
    }

    // Counts the positive numbers in the array.
    static int CountPositiveNumbersInArray(int ArrLength, int Arr[]) {
        int counter = 0;
        for (int i = 0; i < ArrLength; i++)
        {
            if (IsPositiveNumber(Arr[i]))
            {
                counter++;
            }
        }
        return counter;
    }

    // Counts the negative numbers in the array.
    static int CountNegativeNumbersInArray(int ArrLength, int Arr[]) {
        int counter = 0;
        for (int i = 0; i < ArrLength; i++)
        {
            if (IsNegativeNumber(Arr[i]))
            {
                counter++;
            }
        }
        return counter;
    }

};