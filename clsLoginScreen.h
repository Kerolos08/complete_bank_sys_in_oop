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

    static bool _Login()
    {
        bool Loginfailed = false;
        short FailedLoginCount = 0;
        const short MaxAttemps = 3;
        string Username, Password;

        do
        {
            if (Loginfailed)
            {
                FailedLoginCount++;

                if (FailedLoginCount == MaxAttemps)
                {
                    cout << "\n\nSystem locked after 3 failed tries.\n";
                    return false;
                }

                cout << "\nInvalid Username/Password!";
                cout << "\nYou have " << MaxAttemps - FailedLoginCount << " login trail(s) left.\n\n";
            }

            cout << "Enter Username? ";
            Username = clsInputValidate::ReadString();
            cout << "Enter Password? ";
            Password = clsInputValidate::ReadString();

            ActiveUser = clsUser::Find(Username, Password);
            Loginfailed = ActiveUser.Is_Empty();

        } while (Loginfailed);

        clsMainScreen::ShowMainMenu();
        return true;
    }

public:
    static bool ShowLoginScreen()
    {
        _ClearScreen();
        _DrawScreenHeader("\t     Login Screen");
        return _Login();
    }
};