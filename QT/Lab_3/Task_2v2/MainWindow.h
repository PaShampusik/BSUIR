#pragma once

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
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Stack.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);
    ~MainWindow();

private slots:
    void on_Quit_clicked();
    void on_ChooseFile_clicked();
    void on_CheckFile_clicked();
    void on_CheckHandwriting_clicked();

private:
    Ui::MainWindow* ui;

    Stack Stack;
};
