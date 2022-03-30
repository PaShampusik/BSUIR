#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDateTime>
#include <QDate>
#include <QMessageBox>
#include <QTextStream>

int customers = 0;

class Customer
{
private:

public:
    int number;
    QString fullname;
    QString address;
    QString date;
    Customer(int number = customers, QString fullname = "Mafioznik",
        QString address = "Winner street, house 3, flat 33", QString date = "01.01.0001");
    

    QString Name();
    QString Amount();
    QString Address();
    QString Date();
}; 

#endif