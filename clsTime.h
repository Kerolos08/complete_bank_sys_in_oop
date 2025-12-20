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

public:
    void Set_CurrentHour(short Hour)
    {
        _CurrentHour = Hour;
    }

    short Get_CurrentHour() const
    {
        return _CurrentHour;
    }

    void Set_CurrentMin(short Min)
    {
        _CurrentMin = Min;
    }

    short Get_CurrentMin() const
    {
        return _CurrentMin;
    }

    clsTime(short Hour, short Min)
    {
        _CurrentHour = Hour;
        _CurrentMin = Min;
    }

    clsTime()
    {
        *this = GetCurrentTime();
    }

    static clsTime GetCurrentTime()
    {
        time_t t = time(0);
        tm *now = localtime(&t);
        short Hour, Min;
        Hour = now->tm_hour;
        Min = now->tm_min;
        return clsTime(Hour, Min);
    }

    static string TimeToString(clsTime Time)
    {
        return to_string(Time.Get_CurrentHour()) + ":" + to_string(Time.Get_CurrentMin());
    }
};