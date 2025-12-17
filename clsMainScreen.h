#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientscreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"

// cross platform Libs. for Pause/Clear
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

class clsMainScreen : protected clsScreen
{
private:
    enum enManageUsersMenuOption
    {
        eListClient = 1,
        eAddNewClient = 2,
        eDeletClient = 3,
        eUpdateClient = 4,
        eFindClient = 5,
        eTransactions = 6,
        eManageUsers = 7,
        eExit = 8
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

    static short _ReadMainMenuOption()
    {
        // uses a function to make the user only can input between the Menu range
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 8]? ";
        short Choice = clsInputValidate::ReadshortNumberbetween(1, 8, "Enter a number between 1 and 8? ");
        return Choice;
    }

    static void _GoBackToMainMenu()
    {
        // Pause is just waiting the user input then excites normally
        cout << setw(37) << left << "" << "\n\tPress any key to go back to main menu.....\n";
        _Pause();
    }

    static void _ShowAllClientsScreen()
    {
        // cout << "\nClient List Screen Will be Here....\n";
        clsClientsListScreen::ShowClientsList();
    }

    static void _ShowAddClientScreen()
    {
        // cout << "\nAdd Client Screen Will be Here....\n";
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        // cout << "\nDelete Client Screen Will be Here....\n";
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        // cout << "\nUpdate Client Screen Will be Here....\n";
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        // cout << "\nFind Client Screen Will be Here....\n";
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransActionMenu()
    {
        // cout << "\nTransaction Screen Will be Here....\n";
        clsTransActionMenu::ShowTransactionMenu();
    }

    static void _ShowManageUsersMenu()
    {
        // cout << "\nManage Users Screen Will be Here....\n";
        clsManageUsersScreen::ShowManageUsersMenu();
    }

    static void _ShowEndScreen()
    {
        cout << "\nEnd Screen Will be Here....\n";
    }

    static void _PerformMainMenuOption(enManageUsersMenuOption MainMenuOption)
    {
        switch (MainMenuOption)
        {
        case enManageUsersMenuOption::eListClient:
            _ClearScreen();
            _ShowAllClientsScreen();
            _GoBackToMainMenu();
            break;

        case enManageUsersMenuOption::eAddNewClient:
            _ClearScreen();
            _ShowAddClientScreen();
            _GoBackToMainMenu();
            break;

        case enManageUsersMenuOption::eDeletClient:
            _ClearScreen();
            _ShowDeleteClientScreen();
            _GoBackToMainMenu();
            break;

        case enManageUsersMenuOption::eUpdateClient:
            _ClearScreen();
            _ShowUpdateClientScreen();
            _GoBackToMainMenu();
            break;

        case enManageUsersMenuOption::eFindClient:
            _ClearScreen();
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;

        case enManageUsersMenuOption::eTransactions:
            _ClearScreen();
            _ShowTransActionMenu();
            _GoBackToMainMenu();
            break;

        case enManageUsersMenuOption::eManageUsers:
            _ClearScreen();
            _ShowManageUsersMenu();
            _GoBackToMainMenu();
            break;

        case enManageUsersMenuOption::eExit:
            _ClearScreen();
            _ShowEndScreen();
            break;
        }
    }

public:
    static void ShowMainMenu()
    {
        bool Exit = false; // initial value to start the loop
        while (!Exit)
        {
            _ClearScreen();
            _DrawScreenHeader("\t\tMain Screen");
            cout << setw(37) << left << "" << "============================================\n";
            cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
            cout << setw(37) << left << "" << "============================================\n";
            cout << setw(37) << left << "" << "\t[1] Show Clients List.\n";
            cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
            cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
            cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
            cout << setw(37) << left << "" << "\t[5] Find Client.\n";
            cout << setw(37) << left << "" << "\t[6] Transactions.\n";
            cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
            cout << setw(37) << left << "" << "\t[8] Exit.\n";
            cout << setw(37) << left << "" << "============================================\n";

            enManageUsersMenuOption Choice = (enManageUsersMenuOption)_ReadMainMenuOption(); // Reads Users choice
            if (Choice == eExit)
            {
                _ClearScreen();
                _ShowEndScreen();
                Exit = true; // modify the loop variable value to get out and close
            }
            else
            {
                _PerformMainMenuOption(Choice); // Do what the user's want
                // Once it done the iteration ends and starts a new one (Drawing the menu again)
            }
        }
    }
};