#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsClientsListScreen : protected clsScreen
{
private:
    static void _PrintClientRecordLine(const clsBankClient &client) // No edits Read only
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << client.Get_AccountNumber();
        cout << "| " << setw(20) << left << client.FullName();
        cout << "| " << setw(16) << left << client.Get_Phone();
        cout << "| " << setw(30) << left << client.Get_Email();
        cout << "| " << setw(10) << left << client.Get_Pincode();
        cout << "| " << setw(12) << left << client.Get_AccountBalance();
    }

public:
    static void ShowClientsList()
    {

        if (!_CheckAccessRights(clsUser::eMainMenuPermissions::pListClients))
        {
            return;
            // printing Access Denied and returning to main menu without doing nothing.
        }

        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "\t  Clients List Screen";
        string SubTitle = "\t      (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle); // from the inhereted lib clsScreen Super Class

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";

        cout << setw(8) << left << "" << "| " << setw(15) << left << "Account Number";
        cout << "| " << setw(20) << left << "Client Name";
        cout << "| " << setw(16) << left << "Phone";
        cout << "| " << setw(30) << left << "Email";
        cout << "| " << setw(10) << left << "Pincode";
        cout << "| " << setw(12) << left << "Balance";

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";

        if (vClients.size() == 0)
        {
            cout << "\t\t\tNo Clients Available In The System!";
        }
        else
        {
            for (const clsBankClient &client : vClients)
            {
                _PrintClientRecordLine(client);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";
    }
};