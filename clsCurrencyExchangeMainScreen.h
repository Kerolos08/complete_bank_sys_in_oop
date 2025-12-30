#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsCurrtenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"

// cross platform Libs. for Pause/Clear
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen
{
private:
    enum enCurrencyExchangeMenuOption
    {
        eListCurrencies = 1,
        eFindCurrency = 2,
        eUpdateRate = 3,
        eCurrencyCalculator = 4,
        eShowMainMenu = 5,
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

    static short _ReadCurrencyExchangeMenuOption()
    {
        // uses a function to make the user only can input between the Menu range
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadshortNumberbetween(1, 5, "Enter a number between 1 and 5? ");
        return Choice;
    }

    static void _GoBackToCurrenyExchangeScreen()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to curreny exchange menu.....\n";
        _Pause();
        // No recursion needed, While Loop will be used.
    }

    static void _ShowListCurrenciesScreen()
    {
        // cout << "\nCurrencies List Will be Here....\n";
        clsCurrenciesListScreen::ShowCurrenciesList();
    }

    static void _ShowFindCurrencyScreen()
    {
        // cout << "\nFind Currency Screen Will be Here....\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateCurrencyRateScreen()
    {
        // cout << "\nUpdate Currency Rate Will be Here....\n";
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        cout << "\nCurrency Calculator Screen Will be Here....\n";
    }

    static void _PerformManageUsersMenuOption(enCurrencyExchangeMenuOption CurrencyExchangeOption)
    {
        switch (CurrencyExchangeOption)
        {
        case enCurrencyExchangeMenuOption::eListCurrencies:
            _ClearScreen();
            _ShowListCurrenciesScreen();
            _GoBackToCurrenyExchangeScreen();
            break;

        case enCurrencyExchangeMenuOption::eFindCurrency:
            _ClearScreen();
            _ShowFindCurrencyScreen();
            _GoBackToCurrenyExchangeScreen();
            break;

        case enCurrencyExchangeMenuOption::eUpdateRate:
            _ClearScreen();
            _ShowUpdateCurrencyRateScreen();
            _GoBackToCurrenyExchangeScreen();
            break;

        case enCurrencyExchangeMenuOption::eCurrencyCalculator:
            _ClearScreen();
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrenyExchangeScreen();
            break;

        case enCurrencyExchangeMenuOption::eShowMainMenu:
            // will not do anything, Main menu screen will handle it from here.
            break; // Added.
        }
    }

public:
    static void ShowCurrencyExchangeMenu()
    {

        // We will not check for any permissions as this menu will be public for all users
        //  if (!_CheckAccessRights(clsUser::eMainMenuPermissions::PCurrencyExchange))
        //  {
        //      return;
        //      // printing Access Denied and returning to main menu without doing anything.
        //  }

        bool ReturnToMainMenu = false; // initial condition to start the loop.
        while (!ReturnToMainMenu)
        {
            _ClearScreen();
            _DrawScreenHeader("   Currency Exchange Main Screen");
            cout << setw(37) << left << "" << "============================================\n";
            cout << setw(37) << left << "" << "\t\t  Currency Exchange Menu\n";
            cout << setw(37) << left << "" << "============================================\n";
            cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
            cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
            cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
            cout << setw(37) << left << "" << "\t[4] Currency Calculator\n";
            cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
            cout << setw(37) << left << "" << "============================================\n";

            enCurrencyExchangeMenuOption Option = (enCurrencyExchangeMenuOption)_ReadCurrencyExchangeMenuOption();

            if (Option == enCurrencyExchangeMenuOption::eShowMainMenu)
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