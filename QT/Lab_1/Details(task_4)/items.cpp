#include "items.h"
#include "mainwindow.h"

Items::Items(bool onstock, QString name,
       short amount, QString group, int price) {

    this->onstock = onstock;
    this->name = name;
    this->amount = amount;
    this->group = group;
    this->price = price;
}

void Items::setData(bool onstock, QString name,
             short amount, QString group, int price) {

    this->onstock = onstock;
    this->name = name;
    this->amount = amount;
    this->group = group;
    this->price = price;
}

QString Items::Name(){
    return name;
}

QString Items::Amount(){
    return QString::number(amount);
}

QString Items::Group(){
    return group;
}

QString Items::Price(){
    return QString::number(price);
}

QString Items::Onstock(){
    if (onstock)
    {
        return QString("In Stock");
    }else
    {
        return QString("Not In Stock");
    }
}
