#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
    static string _ReadAccountNumber(string msg)
    {
        string AccountNumber;
        cout << "\n";
        cout << msg;
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }

    static void _PrintClientMiniCard(const clsBankClient &Client)
    {
        cout << "\nClient Card: ";
        cout << "\n---------------------\n";
        cout << "Full Name  : " << Client.FullName() << endl;
        cout << "Acc. Number: " << Client.Get_AccountNumber() << endl;
        cout << "Balance    : " << Client.Get_AccountBalance() << endl;
        cout << "---------------------\n";
    }

    static double _ReadTransferAmount(const clsBankClient &SourceClient)
    {
        cout << "\nEnter Transfer Amount: ";
        double Amount = clsInputValidate::ReadDoubleNumber();

        while (Amount > SourceClient.Get_AccountBalance())
        {
            cout << "\nAmount Exceeds the Available Balance, Enter another Amount? ";
            Amount = clsInputValidate::ReadDoubleNumber();
        }

        return Amount;
    }

public:
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\t  Transfer Screen");

        string AccountNumber = "";
        AccountNumber = _ReadAccountNumber("Please, Enter an Account Number to Transfer From: ");
        clsBankClient SourceClient = clsBankClient::Find(AccountNumber);
        _PrintClientMiniCard(SourceClient);

        AccountNumber = _ReadAccountNumber("Please, Enter an Account Number to Transfer To: ");
        clsBankClient DestinationClient = clsBankClient::Find(AccountNumber);

        while (SourceClient.Get_AccountNumber() == DestinationClient.Get_AccountNumber())
        {
            cout << "\nSender and Reciver Account Numbers cannot be the same. ";
            AccountNumber = _ReadAccountNumber("Enter another Account Number to Transfer To: ");
            DestinationClient = clsBankClient::Find(AccountNumber);
        }
        _PrintClientMiniCard(DestinationClient);

        double Amount = _ReadTransferAmount(SourceClient);

        char AreYouSure = 'n';
        cout << "\nAre you sure you want to perform this operation? y/n? ";
        cin >> AreYouSure;

        if (AreYouSure == 'Y' || AreYouSure == 'y')
        {
            if (SourceClient.Transfare(Amount, DestinationClient))
            {
                cout << "\nTransfer done successfully.\n";
                _PrintClientMiniCard(SourceClient);
                _PrintClientMiniCard(DestinationClient);
            }
            else
            {
                cout << "\nOperation not done due to Error.";
            }
        }
        else
        {
            cout << "\nOperation was Cancelled.\n";
        }
    }
};
