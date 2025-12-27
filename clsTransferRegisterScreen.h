#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsTransferRegisterScreen : protected clsScreen
{
private:
    static void _PrintOperationRecordLine(const clsBankClient::stTransferLogRecord &Record) // No edits Read only
    {
        cout << setw(8) << left << "" << "| " << setw(24) << left << Record.TimeStamp;
        cout << "| " << setw(12) << left << Record.SourceAccountNumber;
        cout << "| " << setw(12) << left << Record.DestinationAccountNumber;
        cout << "| " << setw(12) << left << Record.Amount;
        cout << "| " << setw(12) << left << Record.SourceBalance;
        cout << "| " << setw(12) << left << Record.DestinationBalance;
        cout << "| " << setw(12) << left << Record.Username;
    }

public:
    static void ShowTransferRegisterList()
    {
        vector<clsBankClient::stTransferLogRecord> vRegisterRecords = clsBankClient::GetTransferRegisterList();

        string Title = "   Transfer Register List Screen";
        string SubTitle = "\t\t    (" + to_string(vRegisterRecords.size()) + ") Record(s).";
        _DrawScreenHeader(Title, SubTitle); // from the inhereted lib clsScreen Super Class

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";

        cout << setw(8) << left << "" << "| " << setw(24) << left << "Date/Time";
        cout << "| " << setw(12) << left << "s.Acct";
        cout << "| " << setw(12) << left << "d.Acct";
        cout << "| " << setw(12) << left << "Amount";
        cout << "| " << setw(12) << left << "s.Balance";
        cout << "| " << setw(12) << left << "d.Balance";
        cout << "| " << setw(12) << left << "User";

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";

        if (vRegisterRecords.size() == 0)
        {
            cout << "\t\t\tNo Login Records Available In The System!";
        }
        else
        {
            for (const clsBankClient::stTransferLogRecord &C : vRegisterRecords)
            {
                _PrintOperationRecordLine(C);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------";
        cout << "----------------------------------------------------\n";
    }
};