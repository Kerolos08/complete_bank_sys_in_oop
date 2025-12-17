#pragma once
#include <iostream>
#include <limits>
#include <string>
#include "clsDate.h"
#include "clsString.h"

class clsInputValidate
{
public:
    static bool IsNumberBetween(short Number, short from, short to)
    {
        if (from > to)
            swap(from, to);
        return (Number >= from && Number <= to);
    }

    static bool IsNumberBetween(int Number, int from, int to)
    {
        if (from > to)
            swap(from, to);
        return (Number >= from && Number <= to);
    }

    static bool IsNumberBetween(float Number, float from, float to)
    {
        if (from > to)
            swap(from, to);
        return (Number >= from && Number <= to);
    }

    static bool IsNumberBetween(double Number, double from, double to)
    {
        if (from > to)
            swap(from, to);
        return (Number >= from && Number <= to);
    }

    static bool IsDateBetween(clsDate Date, clsDate from, clsDate to)
    {
        if (clsDate::IsDate1AfterDate2(from, to))
            swap(from, to);
        return !(Date.IsDate1AfterDate2(Date, to) || Date.IsDate1BeforeDate2(Date, from));
    }

    static short ReadShortNumber(string Errormsg = "Invalid Number, Enter again: \n")
    {
        short Number;
        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << Errormsg;
            cin >> Number;
        }
        return Number;
    }

    static short ReadshortNumberbetween(short from, short to, string Errormsg = "Invalid Number, Enter again: \n")
    {
        short Number = ReadIntNumber(Errormsg);
        while (!IsNumberBetween(Number, from, to))
        {
            cout << Errormsg;
            Number = ReadIntNumber(Errormsg);
        }
        return Number;
    }

    static int ReadIntNumber(string Errormsg = "Invalid Number, Enter again: \n")
    {
        int Number;
        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << Errormsg;
            cin >> Number;
        }
        return Number;
    }

    static int ReadIntNumberbetween(int from, int to, string Errormsg = "Invalid Number, Enter again: \n")
    {
        int Number = ReadIntNumber(Errormsg);
        while (!IsNumberBetween(Number, from, to))
        {
            cout << Errormsg;
            Number = ReadIntNumber(Errormsg);
        }
        return Number;
    }

    static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        float Number;
        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    static float ReadFloatNumberBetween(float From, float To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        float Number = ReadFloatNumber();
        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadFloatNumber();
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return Number;
    }

    static double ReadDoubleNumber(string Errormsg = "Invalid Number, Enter again: \n")
    {
        double Number;
        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << Errormsg;
            cin >> Number;
        }
        return Number;
    }

    static double ReadDoubleNumberbetween(double from, double to, string Errormsg = "Invalid Number, Enter again: \n")
    {
        double Number = ReadDoubleNumber(Errormsg);
        while (!IsNumberBetween(Number, from, to))
        {
            cout << Errormsg;
            Number = ReadIntNumber(Errormsg);
        }
        return Number;
    }

    static bool IsValidDate(clsDate Date)
    {
        return clsDate::IsValidDate(Date);
    }

    static string ReadString()
    {
        string S1 = "";
        // Usage of std::ws will extract all the whitespace character
        getline(cin >> ws, S1);
        return S1;
    }
};