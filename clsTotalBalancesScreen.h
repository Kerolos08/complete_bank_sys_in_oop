#pragma once
#include <iostream>
#include <iomanip>
#include "clsUtil.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
private:
    static void _PrintClientRecordBalanceLine(const clsBankClient &client)
    {
        cout << setw(25) << left << "" << "| " << setw(20) << left << client.Get_AccountNumber();
        cout << "| " << setw(40) << left << client.FullName();
        cout << "| " << setw(15) << left << client.Get_AccountBalance();
    }

public:
    static void ShowTotalBalancesScreen()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "\t  Balances List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        clsScreen::_DrawScreenHeader(Title, SubTitle);

        double TotalBalances = clsBankClient::GetTotalBalances();

        cout << setw(25) << left << "" << "\n\t\t-----------------------------------------------------------";
        cout << "--------------------------------\n";

        cout << setw(25) << left << "" << "| " << setw(20) << left << "Account Number";
        cout << "| " << setw(40) << left << "Client Name";
        cout << "| " << setw(15) << left << "Balance";

        cout << setw(25) << left << "" << "\n\t\t-----------------------------------------------------------";
        cout << "--------------------------------\n";

        if (vClients.size() == 0)
        {
            cout << "\t\t\tNo Clients Available In The System!";
        }
        else
        {
            for (const clsBankClient &client : vClients)
            {
                _PrintClientRecordBalanceLine(client);
                cout << endl;
            }

            cout << setw(25) << left << "" << "\n\t\t-----------------------------------------------------------";
            cout << "--------------------------------\n";

            cout << setw(8) << left << "" << "\t\t\t\t\t\t\t     Total Balances = " << TotalBalances << endl;
            cout << setw(8) << left << "" << "\t\t\t\t( " << clsUtil::NumberToText(TotalBalances) << " )";
        }
    }
};
