#pragma once
//class MainWindow;
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
#include "Two_Linked_List.h"
#include "MainWindow.cpp"
//#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int customers = 0;
    MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

private slots:

    void on_ShowTable_clicked();

public:
    
    QString FilePath = QFileDialog::getOpenFileName(this, "Choose text file", "D:/QT/qtProjects/Details(task_4)", "Input (*.txt);");
    QString FilePath2 = QFileDialog::getOpenFileName(this, "Choose text file", "D:/QT/qtProjects/Details(task_4)", "Output (*.txt);");
    
    QString strNumber, strFullname, strAddress, strDate;
    Ui::MainWindow* ui;

};
