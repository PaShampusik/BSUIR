#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "HashTable.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private slots:
	void on_SetTable_clicked();
	void on_FindMin_clicked();

private:
    Ui::MainWindowClass ui;
	HashTable<int, int> hashTable;
	
};
