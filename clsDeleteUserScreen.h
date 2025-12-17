#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsScreen.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private:
    static void _PrintUser(const clsUser &User)
    {
        cout << "\nUser's Info:";
        cout << "\n--------------------------";
        cout << "\nFirst Name  : " << User.Get_FirstName();
        cout << "\nLast Name   : " << User.Get_LastName();
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Get_Email();
        cout << "\nPhone       : " << User.Get_Phone();
        cout << "\nUsername    : " << User.Get_Username();
        cout << "\nPassword    : " << User.Get_Password();
        cout << "\nPermissions : " << User.Get_Permissions();
        cout << "\n--------------------------\n";
    }

public:
    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\t  Delete User Screen");

        string Username = "";
        cout << "\nPlease Enter Username: ";
        Username = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(Username))
        {
            cout << "\nUser is not Found, Choose another one: ";
            Username = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(Username);
        _PrintUser(User);

        char Answer = 'n';
        cout << "\nAre you sure you want to delete this user y/n? ";

        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (User.Delete())
            {
                cout << "\n User Deleted Successfully :-)\n";
                _PrintUser(User);
            }
            else
            {
                cout << "\nError, User was not Deleted!\n";
            }
        }
    }
};