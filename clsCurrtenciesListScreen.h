#pragma once
#include <iostream>
#include <iomanip>
#include "clsCurrency.h"
#include "clsScreen.h"

using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
private:
    static void _PrintCurrencyRecordLine(const clsCurrency &Currency) // No edits Read only
    {
        cout << setw(8) << left << "" << "| " << setw(37) << left << Currency.Country();
        cout << "| " << setw(10) << left << Currency.CurrencyCode();
        cout << "| " << setw(45) << left << Currency.CurrencyName();
        cout << "| " << setw(15) << left << Currency.Rate();
    }

public:
    static void ShowCurrenciesList()
    {
        vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

        string Title = "\t  Currencies List Screen";
        string SubTitle = "\t      (" + to_string(vCurrencies.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle); // from the inhereted lib clsScreen Super Class

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";

        cout << setw(8) << left << "" << "| " << setw(37) << left << "Country";
        cout << "| " << setw(10) << left << "Code";
        cout << "| " << setw(45) << left << "Name";
        cout << "| " << setw(15) << left << "Rate/(1$)";

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";

        if (vCurrencies.size() == 0)
        {
            cout << "\t\t\tNo Users Available In The System!";
        }
        else
        {
            for (const clsCurrency &Currency : vCurrencies)
            {
                _PrintCurrencyRecordLine(Currency);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";
    }
};