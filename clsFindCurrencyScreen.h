#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsCurrency.h"
#include "clsScreen.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:
    static void _PrintCurrency(const clsCurrency &Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "-----------------------------";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$)   : " << Currency.Rate();
        cout << "\n-----------------------------\n";
    }

    static void _PrintResult(const clsCurrency &Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency is not Exists in File....\n";
        }
    }

    static void _FindCurrencyByCurrecnyCode()
    {
        cout << "\nPlease Enter Currency Code: ";
        string CurrencyCode = clsInputValidate::ReadString();
        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        _PrintResult(Currency);
    }

    static void _FindCurrencyByCountryName()
    {
        cout << "\nPlease Enter Country Name: ";
        string CountryName = clsInputValidate::ReadString();
        clsCurrency Currency = clsCurrency::FindByCountry(CountryName);
        _PrintResult(Currency);
    }

public:
    static void ShowFindCurrencyScreen()
    {
        _DrawScreenHeader("\t  Find Currency Screen");
        cout << "\nFind By: [1] Code or [2] Country? ";
        short Choice = clsInputValidate::ReadshortNumberbetween(1, 2, "Find By: [1] Code or [2] Country ? ");

        if (Choice == 1)
        {
            _FindCurrencyByCurrecnyCode();
        }
        else
        {
            _FindCurrencyByCountryName();
        }

        cin.putback('\n');
    }
};