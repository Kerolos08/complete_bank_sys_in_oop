#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsAddNewClientScreen : clsScreen
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
    static void ShowAddNewClientScreen()
    {

        if (!_CheckAccessRights(clsUser::eMainMenuPermissions::pAddNewClient))
        {
            return;
            // printing Access Denied and returning to main menu without doing anything.
        }

        clsScreen::_DrawScreenHeader("\tAdd New Client Screen");
        string AccountNumber = _ReadAccountNumber();
        {
            cout << "\nClient with this Account Number is Already Exists, Please Enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient NewCLient = clsBankClient::GetAddNewClient(AccountNumber);
        _ReadClientInfo(NewCLient);

        clsBankClient::enSaveResult SaveResult;
        SaveResult = NewCLient.Save();
        switch (SaveResult)
        {
        case clsBankClient::enSaveResult::svSucceeded:
            cout << "\nAccount Addded Successfully :-)\n";
            _PrintClient(NewCLient);
            break;

        case clsBankClient::enSaveResult::svFaildEmptyObject:
            cout << "\nError, Account was not saved becaue it's Empty!\n";
            break;

        case clsBankClient::enSaveResult::svFaildAccountNumberExist:
            cout << "\nError Account was not saved because account number is used!\n";
        }
    }
};