#pragma once
#include <iostream>
#include <string>
using namespace std;

class clsPerson
{
private:
    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone;

public:
    clsPerson(const string &firstname, const string &lastname, const string &email, const string &phone)
    {
        _FirstName = firstname;
        _LastName = lastname;
        _Email = email;
        _Phone = phone;
    }

    void Set_FirstName(const string &firstname) // Avoid unnecessary copies
    {
        // Property Set for First Name
        _FirstName = firstname;
    }
    string Get_FirstName() const // Avoid making any changes
    {
        // Property Get for First Name
        return _FirstName;
    }
    void Set_LastName(const string &lastname) // Avoid unnecessary copies
    {
        // Property Set for Last Name
        _LastName = lastname;
    }
    string Get_LastName() const // Avoid making any changes
    {
        // Property Get for Last Name
        return _LastName;
    }
    void Set_Email(const string &email) // Avoid unnecessary copies
    {
        // Property Set for Email
        _Email = email;
    }
    string Get_Email() const // Avoid making any changes
    {
        // Property Get for Email
        return _Email;
    }
    void Set_Phone(const string &phonenumber) // Avoid unnecessary copies
    {
        // Property Set for Phone
        _Phone = phonenumber;
    }
    string Get_Phone() const // Avoid making any changes
    {
        // Property Get for Phone
        return _Phone;
    }
    string FullName() const // Avoid making any changes
    {
        return _FirstName + " " + _LastName;
    }
    void Print() const // Avoid making any changes
    {
        cout << "\nInfo:";
        cout << "\n--------------------------";
        cout << "\nFirst Name: " << _FirstName;
        cout << "\nLast Name : " << _LastName;
        cout << "\nFull Name : " << FullName();
        cout << "\nEmail     : " << _Email;
        cout << "\nPhone      : " << _Phone;
        cout << "\n--------------------------\n";
    }
};