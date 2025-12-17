#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include "clsString.h"

using namespace std;

class clsDate
{
private:
    short _Year = 1990;
    short _Month = 1;
    short _Day = 1;

public:
    clsDate()
    {
        // Default constructor Getting current system date
        *this = GetSystemDate();
    }

    clsDate(string Date)
    {
        // Parameterized constructor taking string Date
        vector<string> vDate = clsString::SplitString(Date, "/");

        _Day = stoi(vDate.at(0));
        _Month = stoi(vDate.at(1));
        _Year = stoi(vDate.at(2));
    }

    clsDate(short Day, short Month, short Year)
    {
        _Year = Year;
        _Month = Month;
        _Day = Day;
    }

    clsDate(short Days, short Year)
    {
        // Parameterized constructor taking number of days from the begining of the year and year
        *this = GetDateFromDayOrderInYear(Days, Year);
    }

    void Set_Day(short Day)
    {
        _Day = Day;
    }

    short Get_Day()
    {
        return _Day;
    }

    void Set_Month(short Month)
    {
        _Month = Month;
    }

    short Get_Month()
    {
        return _Month;
    }

    void Set_Year(short Year)
    {
        _Year = Year;
    }

    short Get_Year()
    {
        return _Year;
    }

    void Print()
    {
        cout << DateToString(*this) << endl;
    }

    static string DateToString(clsDate Date)
    {
        return to_string(Date.Get_Day()) + "/" + to_string(Date.Get_Month()) + "/" + to_string(Date.Get_Year());
    }

    string DateToString()
    {
        return DateToString(*this);
    }

    static bool IsValidDate(clsDate Date)
    {

        if (Date.Get_Day() < 1 || Date.Get_Day() > 31)
            return false;

        if (Date.Get_Month() < 1 || Date.Get_Month() > 12)
            return false;

        if (Date.Get_Month() == 2)
        {
            if (IsLeapYear(Date.Get_Year()))
            {
                if (Date.Get_Day() > 29)
                    return false;
            }
            else
            {
                if (Date.Get_Day() > 28)
                    return false;
            }
        }

        short DaysInMonth = NumberOfDaysInAMonth(Date.Get_Month(), Date.Get_Year());

        if (Date.Get_Day() > DaysInMonth)
            return false;

        return true;
    }

    bool IsValidDate()
    {
        return IsValidDate(*this);
    }

    static clsDate GetSystemDate()
    {
        time_t t = time(0);
        tm *now = localtime(&t);
        short Year, Month, Day;
        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;
        return clsDate(Day, Month, Year);
    }

    static bool IsLeapYear(short Year)
    {
        // if year is divisible by 4 AND notdivisible by 100
        // OR if year is divisible by 400
        // then it is a leap year
        return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    }

    bool IsIsLeapYear()
    {
        return IsLeapYear(_Year);
    }

    static short NumberOfDaysInAYear(short Year)
    {
        return IsLeapYear(Year) ? 366 : 365;
    }

    short NumberOfDaysInAYear()
    {
        return NumberOfDaysInAYear(_Year);
    }

    static short NumberOfHoursInAYear(short Year)
    {
        return NumberOfDaysInAYear(Year) * 24;
    }

    short NumberOfHoursInAYear()
    {
        return NumberOfHoursInAYear(_Year);
    }

    static int NumberOfMinutesInAYear(short Year)
    {
        return NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfMinutesInAYear()
    {
        return NumberOfMinutesInAYear(_Year);
    }

    static int NumberOfSecondsInAYear(short Year)
    {
        return NumberOfMinutesInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear()
    {
        return NumberOfSecondsInAYear(_Year);
    }

    static short NumberOfDaysInAMonth(short Month, short Year)
    {
        if (Month < 1 || Month > 12)
            return 0;
        int NumberOfDays[12] = {
            31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
    }

    short NumberOfDaysInAMonth()
    {
        return NumberOfDaysInAMonth(_Month, _Year);
    }

    static short NumberOfHoursInAMonth(short Month, short Year)
    {
        return NumberOfDaysInAMonth(Month, Year) * 24;
    }

    short NumberOfHoursInAMonth()
    {
        return NumberOfHoursInAMonth(_Month, _Year);
    }

    static int NumberOfMinutesInAMonth(short Month, short Year)
    {
        return NumberOfHoursInAMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInAMonth()
    {
        return NumberOfMinutesInAMonth(_Month, _Year);
    }

    static int NumberOfSecondsInAMonth(short Month, short Year)
    {
        return NumberOfMinutesInAMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInAMonth()
    {
        return NumberOfSecondsInAMonth(_Month, _Year);
    }

    static short DayOfWeekOrder(short Day, short Month, short Year)
    {
        short a, y, m;
        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2;
        // Gregorian:
        // 0:sun, 1:Mon, 2:Tue...etc.
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    short DayOfWeekOrder()
    {
        return DayOfWeekOrder(_Day, _Month, _Year);
    }

    static string DayShortName(short DayOfWeekOrder)
    {
        string arrDayNames[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return arrDayNames[DayOfWeekOrder];
    }

    static string DayShortName(short Day, short Month, short Year)
    {
        string arrDayNames[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return arrDayNames[DayOfWeekOrder(Day, Month, Year)];
    }

    string DayShortName()
    {
        return DayShortName(_Day, _Month, _Year);
    }

    static string MonthShortName(short MonthNumber)
    {
        string Months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        return (Months[MonthNumber - 1]);
    }

    string MonthShortName()
    {
        return MonthShortName(_Month);
    }

    static void PrintMonthCalendar(short Month, short Year)
    {
        int NumberOfDays;
        // Index of the day from 0 to 6
        int current = DayOfWeekOrder(1, Month, Year);
        NumberOfDays = NumberOfDaysInAMonth(Month, Year);
        // Print the current month name
        printf("\n _______________%s__________________\n\n", MonthShortName(Month).c_str());
        // Print the columns
        printf(" Sun Mon Tue Wed Thu Fri Sat\n");
        // Print appropriate spaces
        int i;
        for (i = 0; i < current; i++)
            printf(" ");
        for (int j = 1; j <= NumberOfDays; j++)
        {
            printf("%5d", j);
            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }
        printf("\n ____________________________________\n");
    }

    void PrintMonthCalendar()
    {
        PrintMonthCalendar(_Month, _Year);
    }

    static void PrintYearCalendar(short Year)
    {
        printf("\n _________________________________\n\n");
        printf(" Calendar - %d\n", Year);
        printf(" _________________________________\n");
        for (short i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(i, Year);
        }
    }

    void PrintYearCalendar()
    {
        PrintYearCalendar(_Year);
    }

    static short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
    {
        short TotalDays = 0;
        for (int i = 1; i <= Month - 1; i++)
        {
            TotalDays += NumberOfDaysInAMonth(i, Year);
        }
        TotalDays += Day;
        return TotalDays;
    }

    short NumberOfDaysFromTheBeginingOfTheYear()
    {
        return NumberOfDaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
    }

    static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
    {
        clsDate Date;
        short RemainingDays = DateOrderInYear;
        short MonthDays = 0;
        Date.Set_Year(Year);
        Date.Set_Month(1);
        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date.Get_Month(), Date.Get_Year());
            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date.Set_Month(Date.Get_Month() + 1);
            }
            else
            {
                Date.Set_Day(RemainingDays);
                break;
            }
        }
        return Date;
    }

    void DateAddDays(short Days)
    {
        short RemainingDays = Days + NumberOfDaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
        short MonthDays = 0;
        _Month = 1;
        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(_Month, _Year);
            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                _Month++;
                if (_Month > 12)
                {
                    _Month = 1;
                    _Year++;
                }
            }
            else
            {
                _Day = RemainingDays;
                break;
            }
        }
    }

    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1.Get_Year() < Date2.Get_Year()) ? true : ((Date1.Get_Year() == Date2.Get_Year()) ? (Date1.Get_Month() < Date2.Get_Month() ? true : (Date1.Get_Month() == Date2.Get_Month() ? Date1.Get_Day() < Date2.Get_Day() : false)) : false);
    }

    bool IsDate1BeforeDate2(clsDate Date2)
    {
        return IsDate1BeforeDate2(*this, Date2);
    }

    static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1.Get_Year() == Date2.Get_Year()) ? ((Date1.Get_Month() == Date2.Get_Month()) ? ((Date1.Get_Day() == Date2.Get_Day()) ? true : false) : false) : false;
    }

    bool IsDate1EqualDate2(clsDate Date2)
    {
        return IsDate1EqualDate2(*this, Date2);
    }

    static bool IsLastDayInMonth(clsDate Date)
    {
        return (Date.Get_Day() == NumberOfDaysInAMonth(Date.Get_Month(), Date.Get_Year()));
    }

    bool IsLastDayInMonth()
    {
        return IsLastDayInMonth(*this);
    }

    static bool IsLastMonthInYear(short Month)
    {
        return (Month == 12);
    }

    bool IsLastMonthInYear()
    {
        return (_Month == 12);
    }

    static clsDate AddOneDay(clsDate Date)
    {
        if (IsLastDayInMonth(Date))
        {
            if (IsLastMonthInYear(Date.Get_Month()))
            {
                Date.Set_Month(1);
                Date.Set_Day(1);
                Date.Set_Year(Date.Get_Year() + 1);
            }
            else
            {
                Date.Set_Day(1);
                Date.Set_Month(Date.Get_Month() + 1);
            }
        }
        else
        {
            Date.Set_Day(Date.Get_Day() + 1);
        }
        return Date;
    }

    void AddOneDay()
    {
        *this = AddOneDay(*this);
    }

    static void SwapDates(clsDate &Date1, clsDate &Date2)
    {
        clsDate TempDate;
        TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }

    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        short SwapFlagValue = 1;
        if (!IsDate1BeforeDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
            SwapFlagValue = -1;
        }
        while (IsDate1BeforeDate2(Date1, Date2))
        {
            Days++;
            Date1 = AddOneDay(Date1);
        }
        return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
    }

    int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
    {
        return GetDifferenceInDays(*this, Date2, IncludeEndDay);
    }

    static int CalaculateYourAgeinDays(clsDate YourBirthdayDate)
    {
        return GetDifferenceInDays(YourBirthdayDate, clsDate::GetSystemDate(), true);
    }

    static clsDate IncreaseDateByXDays(short Days, clsDate &Date)
    {
        for (short i = 1; i <= Days; i++)
        {
            Date = AddOneDay(Date);
        }
        return Date;
    }

    void IncreaseDateByXDays(short Days)
    {
        IncreaseDateByXDays(Days, *this);
    }

    static clsDate IncreaseDateByOneWeek(clsDate &Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = AddOneDay(Date);
        }
        return Date;
    }

    void IncreaseDateByOneWeek()
    {
        IncreaseDateByOneWeek(*this);
    }

    static clsDate IncreaseDateByXWeeks(short Weeks, clsDate &Date)
    {
        for (short i = 1; i <= Weeks; i++)
        {
            Date = IncreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void IncreaseDateByXWeeks(short Weeks)
    {
        IncreaseDateByXWeeks(Weeks, *this);
    }

    static clsDate IncreaseDateByOneMonth(clsDate &Date)
    {
        if (Date.Get_Month() == 12)
        {
            Date.Set_Month(1);
            Date.Set_Year(Date.Get_Year() + 1);
        }
        else
        {
            Date.Set_Month(Date.Get_Month() + 1);
        }
        // last check day in date should not exceed max days in the current month
        //  example if date is 31/1/2022 increasing one month should not be 31 / 2 / 2022, it should be 28/2/2022
        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Get_Month(), Date.Get_Year());
        if (Date.Get_Day() > NumberOfDaysInCurrentMonth)
        {
            Date.Set_Day(NumberOfDaysInCurrentMonth);
        }
        return Date;
    }

    void IncreaseDateByOneMonth()
    {
        IncreaseDateByOneMonth(*this);
    }

    static clsDate IncreaseDateByXMonths(short Months, clsDate &Date)
    {
        for (short i = 1; i <= Months; i++)
        {
            Date = IncreaseDateByOneMonth(Date);
        }
        return Date;
    }

    void IncreaseDateByXMonths(short Months)
    {
        IncreaseDateByXMonths(Months, *this);
    }

    static clsDate IncreaseDateByOneYear(clsDate &Date)
    {
        Date.Set_Year(Date.Get_Year() + 1);
        return Date;
    }

    void IncreaseDateByOneYear()
    {
        IncreaseDateByOneYear(*this);
    }

    static clsDate IncreaseDateByXYears(short Years, clsDate &Date)
    {
        for (short i = 1; i <= Years; i++)
        {
            Date = IncreaseDateByOneYear(Date);
        }
        return Date;
    }

    void IncreaseDateByXYears(short Years)
    {
        IncreaseDateByXYears(Years, *this);
    }

    static clsDate IncreaseDateByXYearsFaster(short Years, clsDate &Date)
    {
        Date.Set_Year(Date.Get_Year() + Years);
        return Date;
    }

    void IncreaseDateByXYearsFaster(short Years)
    {
        IncreaseDateByXYearsFaster(Years, *this);
    }

    static clsDate IncreaseDateByOneDecade(clsDate &Date)
    {
        // Period of 10 years
        Date.Set_Year(Date.Get_Year() + 10);
        return Date;
    }

    void IncreaseDateByOneDecade()
    {
        IncreaseDateByOneDecade(*this);
    }

    static clsDate IncreaseDateByXDecades(short Decade, clsDate &Date)
    {
        for (short i = 1; i <= Decade * 10; i++)
        {
            Date = IncreaseDateByOneYear(Date);
        }
        return Date;
    }

    void IncreaseDateByXDecades(short Decade)
    {
        IncreaseDateByXDecades(Decade, *this);
    }

    static clsDate IncreaseDateByXDecadesFaster(short Decade, clsDate &Date)
    {
        Date.Set_Year(Date.Get_Year() + Decade * 10);
        return Date;
    }

    void IncreaseDateByXDecadesFaster(short Decade)
    {
        IncreaseDateByXDecadesFaster(Decade, *this);
    }

    clsDate IncreaseDateByOneCentury(clsDate &Date)
    {
        // Period of 100 years
        Date.Set_Year(Date.Get_Year() + 100);
        return Date;
    }

    void IncreaseDateByOneCentury()
    {
        IncreaseDateByOneCentury(*this);
    }

    clsDate IncreaseDateByOneMillennium(clsDate &Date)
    {
        // Period of 1000 years
        Date.Set_Year(Date.Get_Year() + 1000);
        return Date;
    }

    void IncreaseDateByOneMillennium()
    {
        IncreaseDateByOneMillennium(*this);
    }

    static clsDate DecreaseDateByOneDay(clsDate Date)
    {
        if (Date.Get_Day() == 1)
        {
            if (Date.Get_Month() == 1)
            {
                Date.Set_Month(12);
                Date.Set_Day(31);
                Date.Set_Year(Date.Get_Year() - 1);
            }
            else
            {
                Date.Set_Month(Date.Get_Month() - 1);
                Date.Set_Day(NumberOfDaysInAMonth(Date.Get_Month(), Date.Get_Year()));
            }
        }
        else
        {
            Date.Set_Day(Date.Get_Day() - 1);
        }

        return Date;
    }

    void DecreaseDateByOneDay()
    {
        *this = DecreaseDateByOneDay(*this);
    }

    static clsDate DecreaseDateByXDays(short Days, clsDate &Date)
    {
        for (short i = 1; i <= Days; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }

    void DecreaseDateByXDays(short Days)
    {
        DecreaseDateByXDays(Days, *this);
    }

    static clsDate DecreaseDateByOneWeek(clsDate &Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }

    void DecreaseDateByOneWeek()
    {
        DecreaseDateByOneWeek(*this);
    }

    static clsDate DecreaseDateByXWeeks(short Weeks, clsDate &Date)
    {
        for (short i = 1; i <= Weeks; i++)
        {
            Date = DecreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void DecreaseDateByXWeeks(short Weeks)
    {
        DecreaseDateByXWeeks(Weeks, *this);
    }

    static clsDate DecreaseDateByOneMonth(clsDate &Date)
    {
        if (Date.Get_Month() == 1)
        {
            Date.Set_Month(12);
            Date.Set_Year(Date.Get_Year() - 1);
        }
        else
        {
            Date.Set_Month(Date.Get_Month() - 1);
        }
        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Get_Month(), Date.Get_Year());
        if (Date.Get_Day() > NumberOfDaysInCurrentMonth)
        {
            Date.Set_Day(NumberOfDaysInCurrentMonth);
        }
        return Date;
    }

    void DecreaseDateByOneMonth()
    {
        DecreaseDateByOneMonth(*this);
    }

    static clsDate DecreaseDateByXMonths(short Months, clsDate &Date)
    {
        for (short i = 1; i <= Months; i++)
        {
            Date = DecreaseDateByOneMonth(Date);
        }
        return Date;
    }

    void DecreaseDateByXMonths(short Months)
    {
        DecreaseDateByXMonths(Months, *this);
    }

    static clsDate DecreaseDateByOneYear(clsDate &Date)
    {
        Date.Set_Year(Date.Get_Year() - 1);
        return Date;
    }

    void DecreaseDateByOneYear()
    {
        DecreaseDateByOneYear(*this);
    }

    static clsDate DecreaseDateByXYears(short Years, clsDate &Date)
    {
        for (short i = 1; i <= Years; i++)
        {
            Date = DecreaseDateByOneYear(Date);
        }
        return Date;
    }

    void DecreaseDateByXYears(short Years)
    {
        DecreaseDateByXYears(Years, *this);
    }

    static clsDate DecreaseDateByXYearsFaster(short Years, clsDate &Date)
    {
        Date.Set_Year(Date.Get_Year() - Years);
        return Date;
    }

    void DecreaseDateByXYearsFaster(short Years)
    {
        DecreaseDateByXYearsFaster(Years, *this);
    }

    static clsDate DecreaseDateByOneDecade(clsDate &Date)
    {
        // Period of 10 years
        Date.Set_Year(Date.Get_Year() - 10);
        return Date;
    }

    void DecreaseDateByOneDecade()
    {
        DecreaseDateByOneDecade(*this);
    }

    static clsDate DecreaseDateByXDecades(short Decade, clsDate &Date)
    {
        for (short i = 1; i <= Decade * 10; i++)
        {
            Date = DecreaseDateByOneYear(Date);
        }
        return Date;
    }

    void DecreaseDateByXDecades(short Decade)
    {
        DecreaseDateByXDecades(Decade, *this);
    }

    static clsDate DecreaseDateByXDecadesFaster(short Decade, clsDate &Date)
    {
        Date.Set_Year(Date.Get_Year() - Decade * 10);
        return Date;
    }

    void DecreaseDateByXDecadesFaster(short Decade)
    {
        DecreaseDateByXDecadesFaster(Decade, *this);
    }

    static clsDate DecreaseDateByOneCentury(clsDate &Date)
    {
        // Period of 100 years
        Date.Set_Year(Date.Get_Year() - 100);
        return Date;
    }

    void DecreaseDateByOneCentury()
    {
        DecreaseDateByOneCentury(*this);
    }

    static clsDate DecreaseDateByOneMillennium(clsDate &Date)
    {
        // Period of 1000 years
        Date.Set_Year(Date.Get_Year() - 1000);
        return Date;
    }

    void DecreaseDateByOneMillennium()
    {
        DecreaseDateByOneMillennium(*this);
    }

    static bool IsEndOfWeek(clsDate Date)
    {
        return DayOfWeekOrder(Date.Get_Day(), Date.Get_Month(), Date.Get_Year()) == 6;
    }

    bool IsEndOfWeek()
    {
        return IsEndOfWeek(*this);
    }

    static bool IsWeekEnd(clsDate Date)
    {
        // Weekends are Fri and Sat
        short DayIndex = DayOfWeekOrder(Date.Get_Day(), Date.Get_Month(), Date.Get_Year());
        return (DayIndex == 6 || DayIndex == 5);
    }

    bool IsWeekend()
    {
        return IsWeekEnd(*this);
    }

    static bool IsBusinessDay(clsDate Date)
    {
        // Weekends are Sun , Mon , Tue , Wed and Thur
        /*
        short DayIndex = DayOfWeekOrder(Date);
        return ( DayIndex >= 0 && DayIndex <= 4 );
        */
        return !IsWeekEnd(Date);
    }

    bool IsBusinessDay()
    {
        return IsBusinessDay(*this);
    }

    static short DaysUntilTheEndOfWeek(clsDate Date)
    {
        return 6 - DayOfWeekOrder(Date.Get_Day(), Date.Get_Month(), Date.Get_Year());
    }

    short DaysUntilTheEndOfWeek()
    {
        return DaysUntilTheEndOfWeek(*this);
    }

    static short DaysUntilTheEndOfMonth(clsDate Date)
    {
        clsDate EndOfMonthDate;
        EndOfMonthDate.Set_Day(NumberOfDaysInAMonth(Date.Get_Month(), Date.Get_Year()));
        ;
        EndOfMonthDate.Set_Month(Date.Get_Month());
        EndOfMonthDate.Set_Year(Date.Get_Year());
        return GetDifferenceInDays(Date, EndOfMonthDate, true);
    }

    short DaysUntilTheEndOfMonth()
    {
        return DaysUntilTheEndOfMonth(*this);
    }

    static short DaysUntilTheEndOfYear(clsDate Date)
    {
        clsDate EndOfYearDate;
        EndOfYearDate.Set_Day(31);
        EndOfYearDate.Set_Month(12);
        EndOfYearDate.Set_Year(Date.Get_Year());
        return GetDifferenceInDays(Date, EndOfYearDate, true);
    }

    short DaysUntilTheEndOfYear()
    {
        return DaysUntilTheEndOfYear(*this);
    }

    static short ClaculateBusinessDays(clsDate From, clsDate To)
    {
        short BusinessDays = 0;
        while (IsDate1BeforeDate2(From, To))
        {
            if (IsBusinessDay(From))
            {
                BusinessDays++;
            }
            From = AddOneDay(From);
        }
        return BusinessDays;
    }

    static short ClaculateVacationDays(clsDate From, clsDate To)
    {
        // this calculates the vacation days to be It deducts from employee vacations balance between 2 dates
        // so if the day is already a working day it will deducts from his balance
        return ClaculateBusinessDays(From, To);
    }

    static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
    {
        short WeekEndCounter = 0;
        // in case the data is weekend keep adding one day util you reach business day
        // we get rid of all weekends before the first business day
        while (IsWeekEnd(DateFrom))
        {
            DateFrom = AddOneDay(DateFrom);
        }
        // here we increase the vacation dates to add all weekends to it.
        for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
        {
            if (IsWeekEnd(DateFrom))
                WeekEndCounter++;
            DateFrom = AddOneDay(DateFrom);
        }
        // in case the return date is week end keep adding one day util you reachbusiness day
        while (IsWeekEnd(DateFrom))
        {
            DateFrom = AddOneDay(DateFrom);
        }
        return DateFrom;
    }

    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
    }

    bool IsDate1AfterDate2(clsDate Date2)
    {
        return IsDate1AfterDate2(*this, Date2);
    }

    enum enDateCompare
    {
        Before = -1,
        Equal = 0,
        After = 1
    };

    static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2))
            return enDateCompare::Before;
        if (IsDate1EqualDate2(Date1, Date2))
            return enDateCompare::Equal;
        return enDateCompare::After;
    }

    enDateCompare CompareDates(clsDate Date2)
    {
        return CompareDates(*this, Date2);
    }
};