#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"

using namespace std;

class clsUsersListScreen : protected clsScreen
{
private:
    static void _PrintUserRecordLine(const clsUser &User) // No edits Read only
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << User.Get_Username();
        cout << "| " << setw(25) << left << User.FullName();
        cout << "| " << setw(16) << left << User.Get_Phone();
        cout << "| " << setw(20) << left << User.Get_Email();
        cout << "| " << setw(10) << left << User.Get_Password();
        cout << "| " << setw(12) << left << User.Get_Permissions();
    }

public:
    static void ShowUsersList()
    {
        vector<clsUser> vUsers = clsUser::GetUsersList();

        string Title = "\t  Clients List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle); // from the inhereted lib clsScreen Super Class

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";

        cout << setw(8) << left << "" << "| " << setw(15) << left << "User Number";
        cout << "| " << setw(25) << left << "Full Name";
        cout << "| " << setw(16) << left << "Phone";
        cout << "| " << setw(20) << left << "Email";
        cout << "| " << setw(10) << left << "Password";
        cout << "| " << setw(12) << left << "Permissions";

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";

        if (vUsers.size() == 0)
        {
            cout << "\t\t\tNo Users Available In The System!";
        }
        else
        {
            for (const clsUser &User : vUsers)
            {
                _PrintUserRecordLine(User);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";
    }
};