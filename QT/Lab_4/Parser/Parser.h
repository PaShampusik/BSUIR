#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Parser.h"
#include <qmessagebox.h>
#include <qfiledialog.h>
#include<regex>
#include <stack>
#include<fstream>
#include "Stack.h"
#include "MyString.h"

class Parser : public QMainWindow
{   
    Q_OBJECT

public:
    Parser(QWidget *parent = Q_NULLPTR);

private slots:
    void on_OpenFile_clicked();
    void on_pushButton_clicked();
	
	

private:
    Ui::ParserClass ui;
};
