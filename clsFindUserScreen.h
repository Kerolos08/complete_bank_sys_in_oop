#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsScreen.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
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
    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("\t  Find User Screen");

        string Username = "";
        cout << "\nPlease Enter Username: ";
        Username = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(Username))
        {
            cout << "\nUsername is not found, choose another one: ";
            Username = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(Username);

        if (!User.Is_Empty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }

        _PrintUser(User);

        cin.putback('\n');
    }
};
