#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsDate.h"
#include "clsTime.h"
#include "clsString.h"
#include "clsPerson.h"
using namespace std;

class clsBankClient : public clsPerson
{
public:
    // to avoid the undefined structure issue
    struct stTransferLogRecord;

private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };
    enMode _Mode;

    string _AccountNumber;
    string _Pincode;
    double _AccountBalance;

    static clsBankClient _ConvertLineToClientObject(const string &Line, const string &Delim)
    {
        vector<string> vClient;
        vClient = clsString::SplitString(Line, Delim);
        return clsBankClient(enMode::UpdateMode, vClient[0], vClient[1], vClient[2], vClient[3], vClient[4], vClient[5], stod(vClient[6]));
        // as the imported client is exists in file it is imported with update mode.
    }

    static string _ConvertClientObjectToLine(const clsBankClient &Client, const string &Delim = "#//#")
    {
        string stClientLine = "";
        stClientLine += Client.Get_FirstName() + Delim;
        stClientLine += Client.Get_LastName() + Delim;
        stClientLine += Client.Get_Email() + Delim;
        stClientLine += Client.Get_Phone() + Delim;
        stClientLine += Client.Get_AccountNumber() + Delim;
        stClientLine += Client.Get_Pincode() + Delim;
        stClientLine += to_string(Client.Get_AccountBalance());
        return stClientLine;
    }

    static clsBankClient _GetEmptyClientObject()
    {
        // send a full empty object used for checking if client exists in file
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static vector<clsBankClient> _LoadClientsDataFromFile()
    {
        vector<clsBankClient> vClients;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient client = _ConvertLineToClientObject(Line, "#//#");
                vClients.push_back(client);
            }
            MyFile.close();
        }
        return vClients;
    }

    static void _SaveClientsDataToFile(const vector<clsBankClient> &vClients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);
        if (MyFile.is_open())
        {
            string DataLine;
            for (const clsBankClient &c : vClients)
            {
                DataLine = _ConvertClientObjectToLine(c);
                MyFile << DataLine << endl;
            }
            MyFile.close();
        }
    }

    static void _AddNewDataLineToFile(const string &stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();
        for (clsBankClient &C : vClients)
        {
            if (C.Get_AccountNumber() == Get_AccountNumber())
            {
                C = *this;
                break;
            }
        }
        _SaveClientsDataToFile(vClients);
    }

    void _AddNewCleint()
    {
        _AddNewDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    string _PrepareTransferLogRecord(const clsBankClient &DestinationClient, double Amount, const string &Username, const string &Delim = "#//#")
    {
        string stTransferLogline = "";
        stTransferLogline += clsDate::DateToString(clsDate()) + " - " + clsTime::TimeToString(clsTime()) + Delim;
        stTransferLogline += Get_AccountNumber() + Delim;
        stTransferLogline += DestinationClient.Get_AccountNumber() + Delim;
        stTransferLogline += to_string(Amount) + Delim;
        stTransferLogline += to_string(Get_AccountBalance()) + Delim;
        stTransferLogline += to_string(DestinationClient.Get_AccountBalance()) + Delim;
        stTransferLogline += ActiveUser.Get_Username();
        return stTransferLogline;
    }

    void _RegisterTranferLog(const clsBankClient &DestinationClient, double Amount, const string &Username)
    {
        // Writing the the prepared record line to transfer log file
        string stTransferLogline = _PrepareTransferLogRecord(DestinationClient, Amount, Username);
        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << stTransferLogline << endl;
            MyFile.close();
        }
    }

    static stTransferLogRecord _ConvertTransferRegisterLineToRecord(const string &Line, const string &Delim = "#//#")
    {
        stTransferLogRecord Record;
        vector<string> vOperation = clsString::SplitString(Line, Delim);
        Record.TimeStamp = vOperation.at(0);
        Record.SourceAccountNumber = vOperation.at(1);
        Record.DestinationAccountNumber = vOperation.at(2);
        Record.Amount = stod(vOperation.at(3));
        Record.SourceBalance = stod(vOperation.at(4));
        Record.DestinationBalance = stod(vOperation.at(5));
        Record.Username = vOperation.at(6);
        return Record;
    }

public:
    struct stTransferLogRecord
    {
        string TimeStamp;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        double Amount;
        double SourceBalance;
        double DestinationBalance;
        string Username;
    };

    clsBankClient(enMode Mode, const string &FirstName, const string &LastName, const string &Email, const string &PhoneNumber, const string &AccountNumber, const string &Pincode, double AccountBalance) : clsPerson(FirstName, LastName, Email, PhoneNumber)
    {
        // Parameterized constructor
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _Pincode = Pincode;
        _AccountBalance = AccountBalance;
    }

    bool Is_Empty() const
    {
        // to check the current mode
        return (_Mode == enMode::EmptyMode);
    }

    // Read only property for (AccountNumber)
    string Get_AccountNumber() const
    {
        return _AccountNumber;
    }

    // Set/Get property for (Pincode)
    void Set_Pincode(const string &Pincode)
    {
        _Pincode = Pincode;
    }

    string Get_Pincode() const
    {
        return _Pincode;
    }

    // Set/Get property for (Account Balance)
    void Set_AccountBalance(double AccBalance)
    {
        _AccountBalance = AccBalance;
    }

    double Get_AccountBalance() const
    {
        return _AccountBalance;
    }

    static clsBankClient Find(const string &AccNumber)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in); // Read only
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line, "#//#");
                if (Client.Get_AccountNumber() == AccNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    static clsBankClient Find(const string &AccNumber, const string &Pincode) // Overloaded.
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in); // Read only
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line, "#//#");
                if (Client.Get_AccountNumber() == AccNumber && Client.Get_Pincode() == Pincode)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    bool Delete()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();
        // not using flags
        for (auto it = vClients.begin(); it != vClients.end(); it++)
        {
            if (it->Get_AccountNumber() == _AccountNumber)
            {
                vClients.erase(it);
                _SaveClientsDataToFile(vClients);
                *this = _GetEmptyClientObject();
                return true;
            }
        }
        return false;
    }

    enum enSaveResult
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildAccountNumberExist = 2
    };

    enSaveResult Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            return enSaveResult::svFaildEmptyObject;

        case enMode::UpdateMode:
            _Update();
            return enSaveResult::svSucceeded;

        case enMode::AddNewMode:
            if (IsClientExist(_AccountNumber))
            {
                return enSaveResult::svFaildAccountNumberExist;
            }
            else
            {
                _AddNewCleint();
                _Mode = enMode::UpdateMode;
                return enSaveResult::svSucceeded;
            }

        default:
            return enSaveResult::svSucceeded;
        }
    }

    static bool IsClientExist(const string &AccNumber)
    {
        clsBankClient client = clsBankClient::Find(AccNumber);
        return !(client.Is_Empty());
    }

    static clsBankClient GetAddNewClient(const string &AccountNumber)
    {
        // creats an empty object but with AddNewMode to be filled later by the save function
        // so its changing the state of the object after creating it empty
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalances()
    {
        vector<clsBankClient> vClients = GetClientsList();
        double TotalBalances = 0;
        for (clsBankClient &client : vClients)
        {
            TotalBalances += client.Get_AccountBalance();
        }
        return TotalBalances;
    }

    void Depostie(double Amount)
    {
        _AccountBalance += Amount;
        Save(); // using the UdateMode (look at line 29)
        /*
        when importing the existing clients list it imported it is saved to the vector
        <clsBankCLient> with _Mode = UpdateMode.
        so the Save() method updating the current imported client.
        */
    }

    bool Withdraw(double Amount)
    {
        // checkint if the withdraw amount.
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
    }

    bool Transfare(double Amount, clsBankClient &DestinationClient, const string &Username)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            // Any transfer is a withdraw from the source and deposite for the Destination
            Withdraw(Amount);
            DestinationClient.Depostie(Amount);
            _RegisterTranferLog(DestinationClient, Amount, Username);
            return true;
        }
    }

    static vector<stTransferLogRecord> GetTransferRegisterList()
    {
        vector<stTransferLogRecord> vTransfers;
        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in); // Read only
        if (MyFile.is_open())
        {
            string Line;
            stTransferLogRecord Record;
            while (getline(MyFile, Line))
            {
                Record = _ConvertTransferRegisterLineToRecord(Line);
                vTransfers.push_back(Record);
            }
            MyFile.close();
        }
        return vTransfers;
    }
};