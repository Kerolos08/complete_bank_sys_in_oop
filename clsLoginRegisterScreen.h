#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:
    static void _PrintSessionRecordLine(const clsUser::stLoginRegisterRecord &Record) // No edits Read only
    {
        cout << setw(8) << left << "" << "| " << setw(42) << left << Record.TimeStamp;
        cout << "| " << setw(22) << left << Record.Username;
        cout << "| " << setw(22) << left << Record.Password;
        cout << "| " << setw(15) << left << Record.Permissions;
    }

public:
    static void ShowLoginRegisterList()
    {
        if (!_CheckAccessRights(clsUser::eMainMenuPermissions::PLoginRegister))
        {
            return;
            // printing Access Denied and returning to main menu without doing anything.
        }

        vector<clsUser::stLoginRegisterRecord> vRegisterRecords = clsUser::GetLoginRegisterList();

        string Title = "\t  Login Register List Screen";
        string SubTitle = "\t\t    (" + to_string(vRegisterRecords.size()) + ") Record(s).";
        _DrawScreenHeader(Title, SubTitle); // from the inhereted lib clsScreen Super Class

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";

        cout << setw(8) << left << "" << "| " << setw(42) << left << "Date/Time";
        cout << "| " << setw(22) << left << "Username";
        cout << "| " << setw(22) << left << "Password";
        cout << "| " << setw(15) << left << "Permissions";

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";

        if (vRegisterRecords.size() == 0)
        {
            cout << "\t\t\tNo Login Records Available In The System!";
        }
        else
        {
            for (const clsUser::stLoginRegisterRecord &C : vRegisterRecords)
            {
                _PrintSessionRecordLine(C);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";
    }
};