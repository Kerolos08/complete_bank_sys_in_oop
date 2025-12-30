#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1
    };
    enMode _Mode;

    string _County;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;

    static clsCurrency _ConvertLinetoCurrencyObject(const string &Line, const string &Delim = "#//#")
    {
        vector<string> vCurrencyData = clsString::SplitString(Line, Delim);
        return clsCurrency(enMode::UpdateMode, vCurrencyData.at(0), vCurrencyData.at(1), vCurrencyData.at(2), stof(vCurrencyData.at(3)));
    }

    static vector<clsCurrency> _LoadCurrenciesDataFromFile()
    {
        vector<clsCurrency> vCurrencies;
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in); // Read mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                vCurrencies.push_back(Currency);
            }
            MyFile.close();
        }
        return vCurrencies;
    }

    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

    string _ConvertCurrencyObjectToDataLine(const clsCurrency &Currency, const string &Delim = "#//#")
    {
        string stCurrencyLine = "";
        stCurrencyLine += Currency.Country() + Delim;
        stCurrencyLine += Currency.CurrencyCode() + Delim;
        stCurrencyLine += Currency.CurrencyName() + Delim;
        stCurrencyLine += to_string(Currency.Rate());
        return stCurrencyLine;
    }

    void _SaveCurrenciesDataToFile(const vector<clsCurrency> &vCurrencies)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out); // Overwrite mode
        if (MyFile.is_open())
        {
            string stCurrencyLine;
            for (const clsCurrency &C : vCurrencies)
            {
                stCurrencyLine = _ConvertCurrencyObjectToDataLine(C);
                MyFile << stCurrencyLine << endl;
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();
        for (clsCurrency &C : vCurrencies)
        {
            if (C.CurrencyCode() == CurrencyCode())
            {
                C = *this;
                break;
            }
        }
        _SaveCurrenciesDataToFile(vCurrencies);
    }

public:
    clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _County = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }

    // Read Only Properties.
    string Country() const
    {
        return _County;
    }

    string CurrencyCode() const
    {
        return _CurrencyCode;
    }

    string CurrencyName() const
    {
        return _CurrencyName;
    }

    // Set/Update Rate
    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }

    // Get Rate
    float Rate() const // No need for const as float is much cheaper than string
    {
        return _Rate;
    }

    bool IsEmpty() const
    {
        return _Mode == enMode::EmptyMode;
    }

    static clsCurrency FindByCode(const string &CurrencyCode)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in); // Read mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (Currency.CurrencyCode() == clsString::UpperAllLetter(CurrencyCode))
                {
                    MyFile.close();
                    return Currency;
                }
            }
        }
        return _GetEmptyCurrencyObject();
    }

    static clsCurrency FindByCountry(const string &Country)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in); // Read mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (clsString::UpperAllLetter(Currency.Country()) == clsString::UpperAllLetter(Country))
                {
                    MyFile.close();
                    return Currency;
                }
            }
        }
        return _GetEmptyCurrencyObject();
    }

    static bool IsCurrencyExist(const string &CountryCode)
    {
        clsCurrency C = clsCurrency::FindByCode(CountryCode);
        return (!C.IsEmpty());
    }

    static vector<clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrenciesDataFromFile();
    }
};