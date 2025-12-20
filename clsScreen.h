#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsTime.h"
#include "clsUser.h"
#include "Global.h"
using namespace std;

class clsScreen
{
protected:
    static void _PrintActiveUserDateTimeInHeader()
    {
        cout << "\n\t\t\t\t\tUser: " << ActiveUser.Get_Username();
        cout << "\n\t\t\t\t\tDate: " << clsDate::DateToString(clsDate());
        cout << "                 ";
        clsTime CurrentTime;
        printf("%02d:%02d", CurrentTime.Get_CurrentHour(), CurrentTime.Get_CurrentMin());
    }

    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n";
        _PrintActiveUserDateTimeInHeader();
        cout << "\n\n";
    }

    static bool _CheckAccessRights(clsUser::eMainMenuPermissions Permission)
    {
        if (!ActiveUser.CheckAccessPermissions(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t   Acces Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }
    }
};