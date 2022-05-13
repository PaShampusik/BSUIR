#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Dequeue.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private slots:
    void on_PushBack_clicked();
	void on_PushFront_clicked();
	void on_PopBack_clicked();
	void on_PopFront_clicked();
	void on_Clear_clicked();
private:
    Ui::MainWindowClass ui;
    Deque<int> Dequeue;
    
};
