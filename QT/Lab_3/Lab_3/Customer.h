#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDateTime>
#include <QDate>
#include <QMessageBox>
#include <QTextStream>

class Customer
{
private:

public:
    QString number;
    QString fullname;
    QString address;
    QString date;
    Customer(QString number = "777", QString fullname = "Mafioznik",
        QString address = "Winner street, house 3, flat 33", QString date = "01.01.0001") {
		this->number = number;
		this->fullname = fullname;
		this->address = address;
		this->date = date;
    }
    QString getnumber() {
		return number;
    }
    QString getname() {
		return fullname;
	}
    QString getaddress() {
		return address;
    }
    QString getdate() {
		return date;
    }
}; 

#endif CUSTOMER_H