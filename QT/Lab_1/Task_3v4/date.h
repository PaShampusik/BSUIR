#ifndef DATE_H
#define DATE_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDateTime>
#include <QDate>
#include <QMessageBox>
#include <QTextStream>


class Date {
public:

    Date(QString date = "", QString birthday = "");

    virtual ~Date(){}

    void setData(QString date, QString birthday);

    QString NextDay();

    QString PreviousDay();

    bool isLeap();

    int WeekNumber();

    unsigned long long  DaysTillYourBirthday(QString birth);

    unsigned long long Duration();

    QString date, birthday = "10.03.2003";
private:

    int arr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    QString DaysInMonth(short MonthNumber);

    bool isLeap(short year);

};

#endif // DATE_H
