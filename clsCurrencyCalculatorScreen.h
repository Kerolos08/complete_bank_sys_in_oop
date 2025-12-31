#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsCurrency.h"
#include "clsScreen.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
    static void _ClearScreen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    static void _PrintCurrencyCard(const clsCurrency &Currency, const string &Title)
    {
        cout << "\n" << Title << "\n";
        cout << "-----------------------------";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$)   : " << Currency.Rate();
        cout << "\n-----------------------------\n";
    }

    static clsCurrency _GetCurrencyObject(string msg)
    {
        cout << msg;
        string CurrencyCode;
        CurrencyCode = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, Enter Currency Code: ";
            CurrencyCode = clsInputValidate::ReadString();
        }
        return clsCurrency::FindByCode(CurrencyCode);
    }

    static void _PrintCalculationResult(double Amount, clsCurrency Currency1, clsCurrency Currency2)
    {
        _PrintCurrencyCard(Currency1, "Convert From: ");

        double AmountInUSD = Currency1.ConvertToUSD(Amount);

        cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInUSD << " USD\n";

        if (Currency2.CurrencyCode() == "USD")
        {
            return;
            // Doing nothing.
        }

        cout << "\nConverting from USD to: \n";
        _PrintCurrencyCard(Currency2, "To");

        double AmountInCurrency2 = Currency1.ConvertToOtherCurrencies(Amount, Currency2);

        cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInCurrency2 << Currency2.CurrencyCode() << endl;
    }

public:
    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'y';
        while (Continue == 'y' || Continue == 'Y')
        {
            _ClearScreen();
            _DrawScreenHeader("\t  Currency Calculator");

            clsCurrency From = _GetCurrencyObject("\nPlease Enter Currency1 Code: ");

            clsCurrency To = _GetCurrencyObject("\nPlease Enter Currency2 Code: ");

            cout << "\nEnter Amount to Exchange: ";
            double Amount = clsInputValidate::ReadDoubleNumber();

        _PrintCalculationResult(Amount, From, To);

        cout << "\n\nDo you want to perform another calculation? y/n? ";
        cin >> Continue;
        }
    }
};
