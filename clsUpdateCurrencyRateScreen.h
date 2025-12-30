#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsCurrency.h"
#include "clsScreen.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
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

public:
    static void ShowUpdateCurrencyRateScreen()
    {
        _DrawScreenHeader("\tUpdate Currency Screen");

        string CurrencyCode;
        cout << "\nPlease Enter Currency Code: ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, Enter another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        _PrintCurrency(Currency);

        char Answer = 'n';
        cout << "\nAre you sure you want to update the rate of this currency y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\nUpdate Currency Rate: ";
            cout << "\n-----------------------------\n";

            cout << "\nEnter New Rate: ";
            float Rate = clsInputValidate::ReadFloatNumber();

            Currency.UpdateRate(Rate);

            cout << "\nCurrency Rate Updated Successfully :-)\n";

            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nOperation is canceled....\n";
        }
    }
};