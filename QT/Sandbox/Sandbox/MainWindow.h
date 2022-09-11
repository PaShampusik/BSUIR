#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QWidget>
#include <qpushbutton.h>
#include <qlineedit.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
	
private slots:
	void on_Button_clicked();

private:
    Ui::MainWindow ui;
};
