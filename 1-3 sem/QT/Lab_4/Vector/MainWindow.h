#pragma once
#pragma comment(lib, "MyVector.lib")

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "MyVector.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui;
	MyVector<int> vector;
	
};
