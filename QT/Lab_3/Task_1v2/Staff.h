#pragma once

//#include <QMainWindow>
//#include <QFileDialog>
//#include <QFile>
//#include <QDateTime>
//#include <QDate>
//#include <QMessageBox>
//#include <QTextStream>

class Staff
{
private:

public:
    QString fullname;
    QString department_number;
    QString position;
    QString date;
    Staff(QString fullname = "ASSert", QString departmant_number = "228",
        QString position = "Winner", QString date = "01.01.0001") {
        this->fullname = fullname;
        this->department_number = departmant_number;
        this->position = position;
        this->date = date;
    }
    QString getnumber() {
        return department_number;
    }
    QString getname() {
        return fullname;
    }
    QString getposition() {
        return position;
    }
    QString getdate() {
        return date;
    }
	
};

