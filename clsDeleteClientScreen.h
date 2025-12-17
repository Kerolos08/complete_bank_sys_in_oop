#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:
    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
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
    static void ShowDeleteClientScreen()
    {
        clsScreen::_DrawScreenHeader("\t  Delete Client Screen");

        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number is not Found, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        char Answer = 'n';
        cout << "\nAre you sure you want to delete this client y/n? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";
                _PrintClient(Client);
            }
            else
            {
                cout << "\nError, Client was not Deleted!\n";
            }
        }
    }
};