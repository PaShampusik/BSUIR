#include "date.h"


Date::Date(QString date, QString birthday)
{
    this->date = date;
    this->birthday = birthday;
}

void Date::setData(QString date, QString birthday)
{
    this->date = date;
    this->birthday = birthday;
}

QString Date::DaysInMonth(short MonthNumber) {
    if (MonthNumber == 2)
    {
        if (isLeap())
        {
            return "29";
        }
        else
        {
            return "28";
        }
    }
    else if (MonthNumber == 4 || MonthNumber == 6 || MonthNumber == 9 || MonthNumber == 11)
       {
        return "30";
    }
    else
    {
        return "31";
    }
}


QString Date::NextDay()
{
   QString year = date;
   year.remove(0, 6);

   while (year[0] == '0')
   {
       year.remove(0, 1);
   }
   QString month = date;
   month.remove(0, 3);
   month.remove(2, 5);

   if (month[0] == '0')
   {
       month.remove(0, 1);
   }

   QString day = date;
   day.remove(2, 8);

   if (day[0] == '0')
   {
       day.remove(0, 1);
   }

   if (DaysInMonth(month.toInt()) < "30")
   {
       if (day == "29")
       {
           return QString("01.03." + year);
       }
       else if (day == "28" && isLeap())
       {
           return QString("29.02" + year);
       }
       else
       {
           return QString(QString::number(day.toInt() + 1) + ".02." + year);
       }
   }
   if (day == "31" && month == "12")
   {
       return QString("01.01." + QString::number(year.toInt() + 1));
   }
   else if ((DaysInMonth(month.toInt()) == "30" && day == "30") || (day == "31"))
   {
       return QString("01." + QString::number(month.toInt() + 1) + "." + year);
   }
   return QString(QString::number(day.toInt() + 1) + "." + month + "." + year);
}

unsigned long long Date::Duration() {

    QString now = "01.03.2022";

    QString year = date;
    year.remove(0, 6);
    while (year[0] == '0')
        year.remove(0, 1);

    QString month = date;
    month.remove(0, 3); month.remove(2, 5);
    if (month[0] == '0') month.remove(0, 1);

    QString day = date;
    day.remove(2, 8);
    if (day[0] == '0') day.remove(0, 1);



    QString Nowmonth = now;
    Nowmonth.remove(0, 3);Nowmonth.remove(2, 5);
    if (Nowmonth[0] == '0') Nowmonth.remove(0, 1);

    QString Nowday = now;
    Nowday.remove(2, 8);
    if (Nowday[0] == '0') Nowday.remove(0, 1);

    QString Nowyear = now;
    Nowyear.remove(0, 6);
    while (Nowyear[0] == '0')
        Nowyear.remove(0, 1);

    unsigned long long difference = 0;

    int Year = year.toInt();
    int Month = month.toInt();
    int Day = day.toInt();
    int NowYear = Nowyear.toInt();
//    int NowMonth = Nowmonth.toInt();
//    int NowDay = Nowday.toInt();


    if(Year < NowYear){
        for(int i = 12; i > Month; i--)
        {
            difference += arr[i - 1];
        }

        if(Month == 2)
        {
            if(isLeap(Year))
            {
                difference += 29 - Day;
            }
            else
            {
                difference += 28 - Day;
            }
        }
        else
        {
            difference += arr[Month - 1] - Day;
        }

        difference += 60;

        while ((Year + 1) < NowYear){

            if (isLeap(Year))
            {
                difference += 366;
            }
            else
            {
                difference += 365;
            }
            Year++;
        }
    }

   return difference;
}

QString Date::PreviousDay()
{
    QString year = date;
    year.remove(0, 6);

    while (year[0] == '0')
    {
        year.remove(0, 1);
    }
    QString month = date;
    month.remove(0, 3);
    month.remove(2, 5);

    if (month[0] == '0')
    {
        month.remove(0, 1);
    }

    QString day = date;
    day.remove(2, 8);

    if (day[0] == '0')
    {
        day.remove(0, 1);
    }

    if (day == "1")
    {
        if (month == "1" && !(year.toInt() == 1))
        {
            return QString("31.12." + year);
        }
        else if(day == "1" && year.toInt() == 1)
        {
            return QString("31.12.0001 BC");
        }

        else
        {
            return QString(DaysInMonth((month.toInt() - 1)) + "." + QString::number(month.toInt() - 1) + "." + year);
        }
    }
    else
    {
        return QString(QString::number(day.toInt() - 1) + "." + month + "." + year);
    }
}

int Date::WeekNumber(){

    QString month = date;
    month.remove(0, 3); month.remove(2, 5);
    if (month[0] == '0')
    {
        month.remove(0, 1);
    }

    QString day = date;
    day.remove(2, 8);
    if (day[0] == '0')
    {
        day.remove(0, 1);
    }

    int days = 0;
    for(int i = 0; i <= month.toInt(); i++)
    {
        if (month.toInt() == (i + 1))
        {
           days += day.toInt();
           break;
        }
        if(month.toInt() > 2 && (i + 1) == 2 && isLeap())
        {
            days += 29;
        }else if(month.toInt() > 2 && (i + 1) == 2 && !isLeap())
        {
            days += 28;
        }
        if(month.toInt() != (i + 1) && (i + 1) != 2)
        {
            days += arr[i];
        }
    }

    int week = days / 7 + 1;


    return week;
}

unsigned long long Date::DaysTillYourBirthday(QString birthday){

    QString year = date;
    year.remove(0, 6);
    while (year[0] == '0')
        year.remove(0, 1);

    QString month = date;
    month.remove(0, 3); month.remove(2, 5);
    if (month[0] == '0') month.remove(0, 1);

    QString day = date;
    day.remove(2, 8);
    if (day[0] == '0') day.remove(0, 1);



    QString Nowmonth = birthday;
    Nowmonth.remove(0, 3);Nowmonth.remove(2, 5);
    if (Nowmonth[0] == '0') Nowmonth.remove(0, 1);

    QString Nowday = birthday;
    Nowday.remove(2, 8);
    if (Nowday[0] == '0') Nowday.remove(0, 1);

    QString Nowyear = birthday;
    Nowyear.remove(0, 6);
    while (Nowyear[0] == '0')
        Nowyear.remove(0, 1);

    unsigned long long days = 0;

    int Year = year.toInt();
    int Month = month.toInt();
    int Day = day.toInt();
    int NowYear = Nowyear.toInt();
    int NowMonth = Nowmonth.toInt();
    int NowDay = Nowday.toInt();


    if(Year <= NowYear){
        if(Year < NowYear){
        for(int i = 12; i > Month; i--)
        {
            days += arr[i - 1];
        }

        if(Month == 2)
        {
            if(isLeap(Year))
            {
                days += 29 - Day;
            }
            else
            {
                days += 28 - Day;
            }
        }
        else
        {
            days += arr[Month - 1] - Day;
        }

        days += 60;

        while ((Year + 1) < NowYear){

            if (isLeap(Year))
            {
                days += 366;
            }
            else
            {
               days += 365;
            }
            Year++;
        }

        }
        else
        {
            if(Month <= NowMonth)
            {
                if(Month == NowMonth)
                {
                    if(Day <= NowDay)
                    {
                       days = NowDay - Day;
                    }
                    if(Day > NowDay)
                    {
                        if(isLeap(Year) || isLeap(Year + 1))
                        {
                            days = 366 - (Day - NowDay);
                        }
                        else
                        {
                            days = 365 - (Day - NowDay);
                        }
                    }
                }
                else
                {
                    days += arr[Month - 1] - Day;
                    days += NowDay;
                    while ((Month + 1) != NowYear){

                        if (Month == 2)
                        {
                            if(isLeap(Year))
                            {
                                days += 29;
                            }
                            else
                            {
                                days += 28;
                            }
                        }
                        else
                        {
                           days += arr[Month - 1];
                        }
                        if(Month == 12)
                        {
                            Month = 1;
                        }
                        else
                        {
                        Month++;
                        }
                    }
                }
            }
        }
    }
    else
    {
        if(Month == NowMonth)
        {
            if(Day <= NowDay)
            {
               days = NowDay - Day;
            }
            if(Day > NowDay)
            {
                if(isLeap(Year) || isLeap(Year + 1))
                {
                    days = 366 - (Day - NowDay);
                }
                else
                {
                    days = 365 - (Day - NowDay);
                }
            }
        }
        else
        {
            days += arr[Month - 1] - Day;
            days += NowDay;
            while ((Month + 1) != NowMonth){

                if (Month == 2)
                {
                    if(isLeap(Year))
                    {
                        days += 29;
                    }
                    else
                    {
                        days += 28;
                    }
                }
                else
                {
                   days += arr[Month - 1];
                }
                if(Month == 12)
                {
                    Month = 1;
                }
                else
                {
                Month++;
                }

            }
    }
}

    return days;
}

bool Date::isLeap() {
    QString TempDate = date;
    TempDate.remove(0, 6);
    if (TempDate[0] == '0')
    {
        TempDate.remove(0, 1);
    }

    int year = TempDate.toInt();

    if (!(year % 4))
    {
        if (!(year % 100))
        {
            if (!(year % 400))
                {
                    return true;
                }
            else
            {
               return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return false;
}

bool Date::isLeap(short year) {
    if (!(year % 4))
    {
        if (!(year % 100))
        {
            if (!(year % 400))
            {
                return true;
            }
            else
            {
                return false;
            }

        }
        else return true;
    }
    else return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////



