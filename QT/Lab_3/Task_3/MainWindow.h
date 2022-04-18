#pragma once

#include <QWidget>
#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDateTime>
#include <QDate>
#include <QMessageBox>
#include <QTextStream>
#include <qtablewidget.h>
#include <QTextEdit>
#include <QLineEdit>
#include <string>
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Stack.h"
#include "Queue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
		
public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    double calculate(QString expression, QString variables[]);
    //bool CheckForLeftBracket(char)
    int CompareValues(std::string char1, std::string char2);
    int character_weight[4] = {2, 2, 1, 1};
	char character[4] = {'*' , '/', '+', '-'};
    int Check(QString expression);
	
	
private slots:
    void on_ShowTable_clicked();
    void on_ShowVariables_clicked();
    void on_ShowExpressions_clicked();
    void on_CalculateResults_clicked();
    void on_CalculateYourResult_clicked();
	
private:
    Ui::MainWindow ui;
    Stack Stack;
	Queue Queue;
   // QStringList expressions;
    QString expressions[15];
    QString variables[15][5];
	
};
