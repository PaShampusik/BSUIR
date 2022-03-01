#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDateTime>
#include <QDate>
#include <QMessageBox>
#include <QTextStream>
#include <QTextDecoder>
#include <QTextEdit>
#include <QLineEdit>
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include<iomanip>
#include <QTableWidgetItem>

#include "items.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int g = -1;
    int newitems = 0;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTableWidgetItem *itm;
    QTableWidgetItem *itm1;
    QTableWidgetItem *itm2;
    QTableWidgetItem *itm3;
    QTableWidgetItem *itm4;
private slots:

    void on_ChooseFile_clicked();
    void on_ShowTable_clicked();

    void on_SortByPrice_clicked();

    void on_SearchByName_clicked();

    void name();

    void group();

    void on_AddItem_clicked();

    void on_AddButton_clicked();

    Items *AddMemory(Items *items, int num);

    Items *LessMemory(Items *items, int num);


    void on_SearchByGroup_clicked();

    void on_SearchByNameAndGroup_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:

    Ui::MainWindow *ui;
    Items *items = new Items[8];
    int number_of_rows = 0;
    QDialog *name_wnd;
    QDialog *add_item;
    QLineEdit *addname;
    QLineEdit *addamount;
    QLineEdit *addgroup;
    QLineEdit *addprice;
    QLineEdit *addonstock;
    QLineEdit *line;

    QString buffer;
    QString FilePath;
    QString FilePath2;
    QString oof;

    QString strName, strGroup, amount, price, onstock;
    int Price, Amount;
    bool OnStock;
};
#endif // MAINWINDOW_H
