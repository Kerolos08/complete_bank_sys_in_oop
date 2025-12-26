#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsScreen.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen
{
private:
    static int _ReadUserPermissions()
    {
        int Permissions = 0;
        char Answer = 'n';

        cout << "\n\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to: ";

        cout << "\n\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::eMainMenuPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::eMainMenuPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::eMainMenuPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::eMainMenuPermissions::pUpdateClientInfo;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::eMainMenuPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::eMainMenuPermissions::pTransactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::eMainMenuPermissions::pManageUsers;
        }

        cout << "\nShow Login Register? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Permissions += clsUser::eMainMenuPermissions::PLoginRegister;
        }

        return Permissions;
    }

    static void _ReadUserInfo(clsUser &User)
    {
        cout << "\nEnter FirstName: ";
        User.Set_FirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        User.Set_LastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        User.Set_Email(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        User.Set_Phone(clsInputValidate::ReadString());

        cout << "\nEnter Password: ";
        User.Set_Password(clsInputValidate::ReadString());

        cout << "\nEnter User's Permissions: ";
        User.Set_Permissions(_ReadUserPermissions());
    }

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
    static void ShowUpdateUserScreen()
    {
        _DrawScreenHeader("\t  Update User Screen");
        string Username = "";

        cout << "\nPlease Enter Username: ";
        Username = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(Username))
        {
            cout << "\nUsername is not found, choose another one: ";
            Username = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(Username);
        _PrintUser(User1);

        cout << "\n\nUpdate User Info:";
        cout << "\n--------------------\n";

        _ReadUserInfo(User1);

        clsUser::enSaveResult SaveResult;

        SaveResult = User1.Save();

        switch (SaveResult)
        {
        case clsUser::enSaveResult::svSucceeded:
        {
            cout << "\nUser Updated Successfully :-)\n";
            _PrintUser(User1);
            break;
        }
        case clsUser::enSaveResult::svFaildEmptyObject:
        {
            cout << "\nError user was not saved because it's Empty";
            break;
        }
        }
    }
};