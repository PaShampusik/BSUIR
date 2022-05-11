#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "DoubleLinkedList.h"
#include "Queue.h"
#include <qlistwidget.h>
#include <qfile>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);
private slots:
    void on_Enqueue_clicked();
    void on_Dequeue_clicked();
    void on_Button_clicked();
    void on_List_itemDoubleClicked(QListWidgetItem*);
    void on_List_itemClicked(QListWidgetItem*);

private:
    Ui::MainWindowClass ui;
    Queue queue;
    DoubleLinkedList<QString> list;
    std::vector<QString> buffer;
    int last_item_clicked = 0;
};