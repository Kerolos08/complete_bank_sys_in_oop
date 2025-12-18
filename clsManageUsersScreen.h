#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

// cross platform Libs. for Pause/Clear
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:
    enum enManageUsersMenuOption
    {
        eListUsers = 1,
        eAddNewUser = 2,
        eDeleteUser = 3,
        eUpdateUser = 4,
        eFindUser = 5,
        eShowMainMenu = 6
    };

    // cross platform Pause/clear
    static void _Pause()
    {
        // Clear ALL input buffer content
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

#ifdef _WIN32
        _getch();
#else
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    }
    static void _ClearScreen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    static short _ReadManageUsersMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 8]? ";
        short Choice = clsInputValidate::ReadshortNumberbetween(1, 6, "Enter a number between 1 and 6? ");
        return Choice;
    }

    static void _GoBackToManageUsersScreen()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to manage users menu.....\n";
        _Pause();
        // No recursion needed, While Loop will be used.
    }

    static void _ShowAllUsersScreen()
    {
        // cout << "\nUsers List Screen will be here....\n";
        clsUsersListScreen::ShowUsersList();
    }

    static void _ShowAddUserScreen()
    {
        // cout << "\nAdd Users Screen Will Be Here....\n";
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        // cout << "\nDelete Users Screen Will Be Here....\n";
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        // cout << "\nUpdate Usres Screen Will Be Here....\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUsersScreen()
    {
        // cout << "\nFind Usres Screen Will Be Here....\n";
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerformManageUsersMenuOption(enManageUsersMenuOption ManageUsersOption)
    {
        switch (ManageUsersOption)
        {
        case enManageUsersMenuOption::eListUsers:
            _ClearScreen();
            _ShowAllUsersScreen();
            _GoBackToManageUsersScreen();
            break;

        case enManageUsersMenuOption::eAddNewUser:
            _ClearScreen();
            _ShowAddUserScreen();
            _GoBackToManageUsersScreen();
            break;

        case enManageUsersMenuOption::eUpdateUser:
            _ClearScreen();
            _ShowUpdateUserScreen();
            _GoBackToManageUsersScreen();
            break;

        case enManageUsersMenuOption::eDeleteUser:
            _ClearScreen();
            _ShowDeleteUserScreen();
            _GoBackToManageUsersScreen();
            break;

        case enManageUsersMenuOption::eFindUser:
            _ClearScreen();
            _ShowFindUsersScreen();
            _GoBackToManageUsersScreen();
            break;

        case enManageUsersMenuOption::eShowMainMenu:
            // will not do anything, Main menu screen will handle it from here.
            break; // Added.
        }
    }

public:
    static void ShowManageUsersMenu()
    {

        if (!_CheckAccessRights(clsUser::eMainMenuPermissions::pManageUsers))
        {
            return;
            // printing Access Denied and returning to main menu without doing nothing.
        }

        bool ReturnToMainMenu = false; // initial condition to start the loop.
        while (!ReturnToMainMenu)
        {
            _ClearScreen();
            _DrawScreenHeader("\t  Manage Users Screen");
            cout << setw(37) << left << "" << "============================================\n";
            cout << setw(37) << left << "" << "\t\t  Manage Useres Menu\n";
            cout << setw(37) << left << "" << "============================================\n";
            cout << setw(37) << left << "" << "\t[1] Users List.\n";
            cout << setw(37) << left << "" << "\t[2] Add New User.\n";
            cout << setw(37) << left << "" << "\t[3] Delete User.\n";
            cout << setw(37) << left << "" << "\t[4] Update User.\n";
            cout << setw(37) << left << "" << "\t[5] Find User.\n";
            cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
            cout << setw(37) << left << "" << "============================================\n";

            enManageUsersMenuOption Option = (enManageUsersMenuOption)_ReadManageUsersMenuOption();

            if (Option == enManageUsersMenuOption::eShowMainMenu)
            {
                ReturnToMainMenu = true; // doing nothing just breaking the loop.
            }
            else
            {
                _PerformManageUsersMenuOption(Option); // Do what the user's want.
                // Once it done the iteration ends and starts a new one (Drawing the menu again).
            }
        }
    }
};