#pragma once
class MainWindow;
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDateTime>
#include <QDate>
#include <QMessageBox>
#include <QTextStream>
#include <QTextEdit>
#include <QLineEdit>
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <QTableWidgetItem>
#include "ui_MainWindow.h"
#include "Customer.h"
#include "DoubleLinkedList.h"
//#include "MainWindow.cpp"
//#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    int x = 0;

public:

    MainWindow(QWidget* parent = Q_NULLPTR);
    ~MainWindow();
    void filltablewithlist(DoubleLinkedList& list);
private slots:


    int on_ShowTable_clicked();
    void on_Sort_clicked();
    void on_SearchByNumber_clicked();
    void on_SearchByDate_clicked();
    void on_SearchByName_clicked();
    void on_pushButton_2_clicked();
    void on_AddCustomer_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_AddCustomer_2_clicked();
    void on_DeleteCustomer_clicked();
    void on_ServedList_clicked();
    void on_List_clicked();
    void on_Clear_clicked();
    void on_Save_clicked();



public:

    int count = 0;

    DoubleLinkedList list_of_elements, list_of_complete_elements;

    QString FilePath = "C:/Users/shchi/BSUIR/QT/Lab_3/input.txt";
    QString FilePath2 = "C:/Users/shchi/BSUIR/QT/Lab_3/output.txt";

    QString strNumber, strFullname, strAddress, strDate;
    Ui::MainWindow* ui;

    friend class Customer;
};
