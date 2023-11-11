#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include <qmessagebox.h>
#include <qstring.h>
#include <qlineedit.h>
#include <string>



class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    void lineEditChange();
    void decimal(int n);
    mainwindow(QWidget *parent = Q_NULLPTR);

private slots:
	void on_pushButton_clicked();
private:
    Ui::mainwindowClass ui;
};
