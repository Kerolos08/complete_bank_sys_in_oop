#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:
    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }

    static void _ReadClientInfo(clsBankClient &Client)
    {
        cout << "\nEnter FirstName: ";
        Client.Set_FirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        Client.Set_LastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        Client.Set_Email(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        Client.Set_Phone(clsInputValidate::ReadString());

        cout << "\nEnter PinCode: ";
        Client.Set_Pincode(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        Client.Set_AccountBalance(clsInputValidate::ReadFloatNumber());
    }

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

public:
    static void ShowUpdateClientScreen()
    {
        clsScreen::_DrawScreenHeader("\t  Update Client Screen");
        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "\n\nUpdate Client Info:";
        cout << "\n--------------------\n";

        _ReadClientInfo(Client1);

        clsBankClient::enSaveResult SaveResult;

        SaveResult = Client1.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResult::svSucceeded:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            _PrintClient(Client1);
            break;
        }
        case clsBankClient::enSaveResult::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;
        }
        }
    }
};