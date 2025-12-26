#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
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
    static void ShowAddNewUserScreen()
    {
        _DrawScreenHeader("\t  Add New User Screen");

        string UserName = "";
        cout << "\nPlease Enter an Username: ";
        UserName = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(UserName))
        {
            cout << "\nUser with this Username is Already Exists, Please Enter another one: ";
            clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResult SaveResult;
        SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case clsUser::enSaveResult::svSucceeded:
            cout << "\nUser Addded Successfully :-)\n";
            _PrintUser(NewUser);
            break;

        case clsUser::enSaveResult::svFaildEmptyObject:
            cout << "\nError, User was not saved becaue it's Empty!\n";
            break;

        case clsUser::enSaveResult::svFaildUsrnameExist:
            cout << "\nError User was not saved because username is used!\n";
        }
    }
};