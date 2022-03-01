#ifndef ITEMS_H
#define ITEMS_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDateTime>
#include <QDate>
#include <QMessageBox>
#include <QTextStream>

class Items
{
private:


public:
    ///////////////////////////
   // int numer_of_items = 8;
    ////////////////////////////




    bool onstock;
    QString name;
    int amount;
    QString group;
    int price;
    Items(bool onstock = false, QString name = "",
           short amount = 0, QString group = "", int price = 0);

    void setData(bool onstock = false, QString name = "",
                 short amount = 0, QString group = "", int price = 0);

    QString Name();
    QString Amount();
    QString Group();
    QString Price();
    QString Onstock();

};

#endif // ITEMS_H
