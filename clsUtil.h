#pragma once
#include <iostream>
#include <cstdlib>
#include "clsDate.h"
using namespace std;

class clsUtil
{
public:
    enum enCharType
    {
        SmallLetter = 1,
        CapitalLetter = 2,
        Digit = 3,
        SpecialCharacter = 4,
        MixChars = 5
    };

    static void Srand()
    {
        srand((unsigned)time(NULL));
    }

    static int RandomNumber(int From, int To)
    {
        int RandNum = rand() % (To - From + 1) + From;
        return RandNum;
    }

    static char GetRandomCharacter(enCharType CharType)
    {
        switch (CharType)
        {
        case enCharType::SmallLetter:
        {
            return char(RandomNumber(97, 122));
            break;
        }
        case enCharType::CapitalLetter:
        {
            return char(RandomNumber(65, 90));
            break;
        }
        case enCharType::SpecialCharacter:
        {
            return char(RandomNumber(33, 47));
            break;
        }
        case enCharType::Digit:
        {
            return char(RandomNumber(48, 57));
            break;
        }

        default:
        {
            short RandNum = RandomNumber(1, 3);
            return char(GetRandomCharacter(enCharType(RandNum)));
        }
        }
    }

    static string GenerateWord(enCharType CharType, short Length)
    {
        string Word;
        for (int i = 1; i <= Length; i++) // 1 <= 4 ? | 2 <= 4 ...
        {
            Word += GetRandomCharacter(CharType);
        }
        return Word;
    }

    static string GenerateKey(enCharType CharType)
    {
        string Key = "";
        Key = GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4);
        return Key;
    }

    static void GenerateKeys(short NumberOfKeys, enCharType CharyType)
    {
        for (int i = 1; i <= NumberOfKeys; i++)
        {
            cout << "Kay [" << i << "] : " << GenerateKey(CharyType) << endl;
        }
    }

    static void Swap(int &a, int &b)
    {
        int Temp = a;
        a = b;
        b = Temp;
    }

    static void Swap(double &a, double &b)
    {
        double Temp = a;
        a = b;
        b = Temp;
    }

    static void Swap(string &a, string &b)
    {
        string Temp = a;
        a = b;
        b = Temp;
    }

    static void Swap(clsDate &Date1, clsDate &Date2)
    {
        clsDate TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }

    static void ShuffleArray(int arr[100], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }

    static void ShuffleArray(string arr[100], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }

    static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int from, int to)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = RandomNumber(from, to);
    }

    static void FillArrayWithRandoumWords(string Arr[100], int arrLength, enCharType typechar, int wordLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            Arr[i] = GenerateWord(typechar, wordLength);
        }
    }

    static void FillArrayWithRandoumKeys(string Arr[100], int arrLength, enCharType typechar)
    {
        for (int i = 0; i < arrLength; i++)
        {
            Arr[i] = GenerateKey(typechar);
        }
    }

    static string Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
            cout << t;
        }
        return t;
    }

    static string EncryptText(string Text, short EncryptionKey)
    {
        for (int i = 0; i <= Text.length(); i++)
        {
            Text[i] = char((int)Text[i] + EncryptionKey);
        }
        return Text;
    }

    static string DecryptionText(string Text, short EncryptionKey)
    {
        for (int i = 0; i <= Text.length(); i++)
        {
            Text[i] = char((int)Text[i] - EncryptionKey);
        }
        return Text;
    }

    static string NumberToText(int Number)
    {

        if (Number == 0)
        {
            return "";
        }

        if (Number >= 1 && Number <= 19)
        {
            string arr[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
                            "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
                            "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

            return arr[Number] + " ";
        }

        if (Number >= 20 && Number <= 99)
        {
            string arr[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
            return arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        if (Number >= 100 && Number <= 199)
        {
            return "One Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 200 && Number <= 999)
        {
            return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
        }

        if (Number >= 1000 && Number <= 1999)
        {
            return "One Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999)
        {
            return NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999)
        {
            return "One Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999)
        {
            return NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999)
        {
            return "One Billion " + NumberToText(Number % 1000000000);
        }
        else
        {
            return NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
        }
    }
};