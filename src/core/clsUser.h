#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../utils/clsUtil.h"
#include "../utils/clsDate.h"
#include "../utils/clsTime.h"
#include "../utils/clsString.h"
#include "clsPerson.h"

using namespace std;

class clsUser : public clsPerson
{
public:
    // to avoid the undefined structure issue
    struct stLoginRegisterRecord;

private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };

    enMode _Mode;
    string _Username;
    string _Password;
    int _Permissions;

    static clsUser _ConvertLineToUserObject(const string &Line, const string &Delim = "#//#")
    {
        vector<string> vUser;
        vUser = clsString::SplitString(Line, Delim);
        return clsUser(enMode::UpdateMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4], clsUtil::DecryptionText(vUser[5]), stoi(vUser[6]));
        // as the imported client is exists in file it is imported with update mode.
    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static vector<clsUser> _LoadUsersDataFromFile()
    {
        vector<clsUser> vUsers;
        fstream MyFile;
        MyFile.open("data/Users.txt", ios::in); // Read Only
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);
                vUsers.push_back(User);
            }
            MyFile.close();
        }
        return vUsers;
    }

    static string _ConvertUserObjectToLine(const clsUser &User, const string &Delim = "#//#")
    {
        string stUserLine = "";
        stUserLine += User.Get_FirstName() + Delim;
        stUserLine += User.Get_LastName() + Delim;
        stUserLine += User.Get_Email() + Delim;
        stUserLine += User.Get_Phone() + Delim;
        stUserLine += User.Get_Username() + Delim;
        // Storing the Encrypted password not the real one
        stUserLine += clsUtil::EncryptText(User.Get_Password()) + Delim;
        stUserLine += to_string(User.Get_Permissions());
        return stUserLine;
    }

    static void _SaveUsersDataToFile(const vector<clsUser> &vUser)
    {
        fstream MyFile;
        MyFile.open("data/Users.txt", ios::out);
        if (MyFile.is_open())
        {
            string DataLine;
            for (const clsUser &U : vUser)
            {
                DataLine = _ConvertUserObjectToLine(U);
                MyFile << DataLine << endl;
            }
            MyFile.close();
        }
    }

    static void _AddNewDataLineToFile(const string &stDataLine)
    {
        fstream MyFile;
        MyFile.open("data/Users.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsUser> vUsers = _LoadUsersDataFromFile();
        for (clsUser &c : vUsers)
        {
            if (c.Get_Username() == Get_Username())
            {
                c = *this;
                break;
            }
        }
        _SaveUsersDataToFile(vUsers);
    }

    void _AddNewUser()
    {
        _AddNewDataLineToFile(_ConvertUserObjectToLine(*this));
    }

    string _PrepareLoginRecord(const string &Delim = "#//#")
    {
        string stRegisteryline = "";
        stRegisteryline += clsDate::DateToString(clsDate()) + " - " + clsTime::TimeToString(clsTime()) + Delim;
        stRegisteryline += Get_Username() + Delim;
        stRegisteryline += clsUtil::EncryptText(Get_Password()) + Delim;
        stRegisteryline += to_string(Get_Permissions());
        return stRegisteryline;
    }

    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(const string &Line, const string &Delim = "#//#")
    {
        stLoginRegisterRecord Record;
        vector<string> vSession = clsString::SplitString(Line, Delim);
        Record.TimeStamp = vSession.at(0);
        Record.Username = vSession.at(1);
        Record.Password = vSession.at(2);
        Record.Permissions = stoi(vSession.at(3));
        return Record;
    }

public:
    struct stLoginRegisterRecord
    {
        string TimeStamp;
        string Username;
        string Password;
        short Permissions;
    };

    enum eMainMenuPermissions
    {
        pAll = -1,
        pListClients = 1,
        pAddNewClient = 2,
        pDeleteClient = 4,
        pUpdateClientInfo = 8,
        pFindClient = 16,
        pTransactions = 32,
        pManageUsers = 64,
        PLoginRegister = 128,
    };

    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string Username, string Password, int Permissions) : clsPerson(FirstName, LastName, Email, Phone)
    {
        // Parameterized Constructor
        _Mode = Mode;
        _Username = Username;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool Is_Empty() const
    {
        // Checking the current mode
        return (_Mode == enMode::EmptyMode);
    }

    // Read only Property Get for (UserName)
    string Get_Username() const
    {
        return _Username;
    }

    // Set/Get property for (Password)
    void Set_Password(const string &Password)
    {
        _Password = Password;
    }

    string Get_Password() const
    {
        return _Password;
    }

    // Set/Get property for (Permissions)
    void Set_Permissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int Get_Permissions() const
    {
        return _Permissions;
    }

    static clsUser Find(const string &Username)
    {
        fstream MyFile;
        MyFile.open("data/Users.txt", ios::in); // Read Only
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line, "#//#");
                if (User.Get_Username() == Username)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    static clsUser Find(const string &Username, const string &Password) // Overloaded.
    {
        fstream MyFile;
        MyFile.open("data/Users.txt", ios::in); // Read Only
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line, "#//#");
                if (User.Get_Username() == Username && User.Get_Password() == Password)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    bool Delete()
    {
        vector<clsUser> vUsers = _LoadUsersDataFromFile();
        // Not using MarkForDelete Flag
        for (auto it = vUsers.begin(); it < vUsers.end(); it++)
        {
            if (it->Get_Username() == _Username)
            {
                vUsers.erase(it);
                _SaveUsersDataToFile(vUsers);
                *this = _GetEmptyUserObject();
                return true;
            }
        }
        return false;
    }

    enum enSaveResult
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildUsrnameExist = 2
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
            if (IsUserExist(_Username))
            {
                return enSaveResult::svFaildUsrnameExist;
            }
            else
            {
                _AddNewUser();
                _Mode = enMode::UpdateMode;
                return enSaveResult::svSucceeded;
            }

        default:
            return enSaveResult::svFaildEmptyObject;
        }
    }

    static bool IsUserExist(const string &Username)
    {
        clsUser User = clsUser::Find(Username);
        return !(User.Is_Empty());
    }

    static vector<clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    static clsUser GetAddNewUserObject(const string &Username)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", Username, "", 0);
    }

    bool CheckAccessPermissions(eMainMenuPermissions Permission)
    {
        if (this->Get_Permissions() == eMainMenuPermissions::pAll)
            return true;

        return ((this->Get_Permissions() & Permission) == Permission);
    }

    void RegisterLogin()
    {
        // Writing the current object to the register file.
        string stRegisteryline = _PrepareLoginRecord();
        fstream MyFile;
        MyFile.open("data/LoginRegister.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << stRegisteryline << endl;
            MyFile.close();
        }
    }

    static vector<stLoginRegisterRecord> GetLoginRegisterList()
    {
        vector<stLoginRegisterRecord> vLoginRegisterRecords;
        fstream MyFile;
        MyFile.open("data/LoginRegister.txt", ios::in); // Read Only
        if (MyFile.is_open())
        {
            string Line;
            stLoginRegisterRecord Session;
            while (getline(MyFile, Line))
            {
                Session = _ConvertLoginRegisterLineToRecord(Line);
                vLoginRegisterRecords.push_back(Session);
            }
            MyFile.close();
        }
        return vLoginRegisterRecords;
    }
};
