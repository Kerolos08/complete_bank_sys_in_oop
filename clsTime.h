// simple/fast .h to git time to use it in bank screens and log files
#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include "clsString.h"

using namespace std;

class clsTime
{
private:
    short _CurrentHour;
    short _CurrentMin;
    short _CurrentSec;

public:
    void Set_CurrentHour(short Hour)
    {
        _CurrentHour = Hour;
    }

    short Get_CurrentHour()
    {
        return _CurrentHour;
    }

    void Set_CurrentMin(short Min)
    {
        _CurrentMin = Min;
    }

    short Get_CurrentMin()
    {
        return _CurrentMin;
    }

    void Set_CurrentSec(short Sec)
    {
        _CurrentSec = Sec;
    }

    short Get_CurrentSec()
    {
        return _CurrentSec;
    }

    clsTime(short Hour, short Min, short Sec)
    {
        _CurrentHour = Hour;
        _CurrentMin = Min;
        _CurrentSec = Sec;
    }

    clsTime()
    {
        *this = GetCurrentTime();
    }

    static clsTime GetCurrentTime()
    {
        time_t t = time(0);
        tm *now = localtime(&t);
        short Hour, Min, Sec;
        Hour = now->tm_hour;
        Min = now->tm_min;
        Sec = now->tm_sec;
        return clsTime(Hour, Min, Sec);
    }

    void Print()
    {
        cout << TimeToString(*this) << endl;
    }

    static string TimeToString(clsTime Time)
    {
        return to_string(Time.Get_CurrentHour()) + ":" + to_string(Time.Get_CurrentMin()) + ":" + to_string(Time.Get_CurrentSec());
    }
};