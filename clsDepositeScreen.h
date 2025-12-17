#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsDepositeScreen : protected clsScreen
{
private:
    static void _PrintClient(const clsBankClient &clinet) // No edits Read only
    {
        cout << "\nClient Card:";
        cout << "\n--------------------------";
        cout << "\nFirst Name  : " << clinet.Get_FirstName();
        cout << "\nLast Name   : " << clinet.Get_LastName();
        cout << "\nFull Name   : " << clinet.FullName();
        cout << "\nEmail       : " << clinet.Get_Email();
        cout << "\nPhone       : " << clinet.Get_Phone();
        cout << "\nAcc. Number : " << clinet.Get_AccountNumber();
        cout << "\nPassword    : " << clinet.Get_Pincode();
        cout << "\nBalance     : " << clinet.Get_AccountBalance();
        cout << "\n--------------------------\n";
    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }

public:
    static void ShowDepositeScreen()
    {
        _DrawScreenHeader("\t    Deposite Screen");
        string AccountNumber = _ReadAccountNumber();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\nPlease Enter Deposite Amount: ";
        double Amount = clsInputValidate::ReadDoubleNumber();

        cout << "\nAre you sure you want to perform that transaction?\n";
        cout << Amount << " Will be deposited from your account y/n: ";
        char Answer = 'N';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            Client.Depostie(Amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Account Balance is: " << Client.Get_AccountBalance();
            cout << "\n";
        }
        else
        {
            cout << "\nOperation was Cancelled.\n";
        }
    }
};