#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
    static void _ClearScreen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    static void _Login()
    {
        string Username, Password;
        while (true)
        {
            cout << "\nEnter Username? ";
            Username = clsInputValidate::ReadString();

            cout << "\nEnter Password? ";
            Password = clsInputValidate::ReadString();

            ActiveUser = clsUser::Find(Username, Password);

            if (!ActiveUser.Is_Empty())
            {
                break;
            }

            cout << "\nInvalid Username/Password! \n";
        }

        clsMainScreen::ShowMainMenu();
    }

public:
    static void ShowLoginScreen()
    {
        _ClearScreen();
        _DrawScreenHeader("\t     Login Screen");
        _Login();
    }
};