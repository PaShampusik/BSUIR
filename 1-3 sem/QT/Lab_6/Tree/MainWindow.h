#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Tree.h"
#include "Tree.h"
#include <QtCore/qhash.h>
#include <qmessagebox.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    void AddWidget(QTreeWidgetItem* oof, Node<QString>* root);
    int FindRight(Node<QString>* root, int counter);

private slots:
    void on_Find_clicked();
    void on_Add_clicked();
    void on_Delete_clicked();
    void on_Childs_clicked();

private:
    Ui::MainWindowClass ui;
    Tree<QString> tree;
    QStringList list = { "Pavel Shchirov", "Vadzim Vladimtsev", "Sanya", "Vadzim", "Boys", "Girls", "Dogs", "Cats", "Elephants", "Monkeys"};
};
