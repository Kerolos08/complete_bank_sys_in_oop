#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsDepositeScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"

// cross platform Libs. for Pause/Clear
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

class clsTransActionMenu : protected clsScreen
{
private:
    enum enTransactionMenuOption
    {
        // Transaction menu elements.
        eDeposite = 1,
        eWithdraw = 2,
        eTransfer = 3,
        eTotalBalances = 4,
        eShowMainMenu = 5
    };

    // cross platform Pause/clear functions
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

    static short _ReadTransactionMenuOption()
    {
        // Reading short number to be casted to enTransactionMenuOption type.
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadshortNumberbetween(1, 5, "Enter a number between 1 and 5? ");
        return Choice;
    }

    static void _ShowDepositeScreen()
    {
        // cout << "\nDeposite Screen Will be Here....\n";
        clsDepositeScreen::ShowDepositeScreen();
    }

    static void _ShowWithdrawScreen()
    {
        // cout << "\nWithdraw Screen Will be Here....\n";
        clsWithdrawScreen::ShowWithDrawScreen();
    }

    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        // cout << "\nTotal Balances Screen Will be Here....\n";
        clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }

    static void _GoBackToTransactionMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to transaction menu.....\n";
        _Pause();
        // No recursion needed, While Loop will be used.
    }

    static void _PerformTransactionMenuOption(enTransactionMenuOption Option)
    {
        switch (Option)
        {
        case enTransactionMenuOption::eDeposite:
            _ClearScreen();
            _ShowDepositeScreen();
            _GoBackToTransactionMenu();
            break;

        case enTransactionMenuOption::eWithdraw:
            _ClearScreen();
            _ShowWithdrawScreen();
            _GoBackToTransactionMenu();
            break;

        case enTransactionMenuOption::eTransfer:
            _ClearScreen();
            _ShowTransferScreen();
            _GoBackToTransactionMenu();
            break;

        case enTransactionMenuOption::eTotalBalances:
            _ClearScreen();
            _ShowTotalBalancesScreen();
            _GoBackToTransactionMenu();
            break;

        case enTransactionMenuOption::eShowMainMenu:
            // will not do anything, Main menu screen will handle it from here.
            break; // added.
        }
    }

public:
    static void ShowTransactionMenu()
    {

        if (!_CheckAccessRights(clsUser::eMainMenuPermissions::pTransactions))
        {
            return;
            // printing Access Denied and returning to main menu without doing anything.
        }

        bool ReturnToMainMenu = false; // initial condition to start the loop.
        while (!ReturnToMainMenu)
        {
            _ClearScreen();
            _DrawScreenHeader("\t  Transaction Screen");
            cout << setw(37) << left << "" << "============================================\n";
            cout << setw(37) << left << "" << "\t\t  Transaction Menu\n";
            cout << setw(37) << left << "" << "============================================\n";
            cout << setw(37) << left << "" << "\t[1] Deposite.\n";
            cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
            cout << setw(37) << left << "" << "\t[3] Transfer.\n";
            cout << setw(37) << left << "" << "\t[4] Total Balances.\n";
            cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
            cout << setw(37) << left << "" << "============================================\n";

            enTransactionMenuOption Option = (enTransactionMenuOption)_ReadTransactionMenuOption();

            if (Option == enTransactionMenuOption::eShowMainMenu)
            {
                ReturnToMainMenu = true; // doing nothing just breaking the loop.
            }
            else
            {
                _PerformTransactionMenuOption(Option); // Do what the user's want.
                // Once it done the iteration ends and starts a new one (Drawing the menu again).
            }
        }
    }
};