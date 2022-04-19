#pragma once
class MainWindow;
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QTextStream>
#include <QTextEdit>
#include <qfile.h>
#include <qfiledialog.h>
#include <QLineEdit>
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <QTableWidgetItem>
#include "ui_MainWindow.h"
#include "Staff.h"
#include "DoubleLinkedListOnArray.h"
#include "Vector.h"
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
    void filltablewithlist(DoubleLinkedListOnArray& list);
private slots:


    int on_ShowTable_clicked();
    void on_Sort_clicked();
    void on_SearchByNumber_clicked();
    //void on_SearchByDate_clicked();
    void on_SearchByName_clicked();
    //void on_pushButton_2_clicked();
    void on_AddCustomer_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_AddCustomer_2_clicked();
    void on_DeleteCustomer_clicked();
    //void on_ServedList_clicked();
    void on_List_clicked();
    //void on_Clear_clicked();
    void on_Save_clicked();



public:

    int count = 0;

    DoubleLinkedListOnArray list_of_elements, list_of_complete_elements;

    QString FilePath = "C:/Users/shchi/BSUIR/QT/Lab_3/Task_1v2/input.txt";
    QString FilePath2 = "C:/Users/shchi/BSUIR/QT/Lab_3/Task_1v2/output.txt";

    QString strFullname, strDepartmentNumber, strPosition, strDate;
    Ui::MainWindow* ui;

    friend class Staff;
};
