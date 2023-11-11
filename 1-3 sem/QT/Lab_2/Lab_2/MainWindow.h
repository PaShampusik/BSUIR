#pragma once

#include <QPushButton>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsView>
#include <cassert>
#include <qpainter.h>


#include "Rectangle.h"
#include "Unique_Ptr.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

    

private slots:
    void on_pushButton2_clicked();
    void on_pushButton_clicked();
    void on_pushButton3_clicked();
    void CreateRect();
private:
    Ui::MainWindowClass* ui;
    QGraphicsScene* scene;
    Rectangle* rect1 = new Rectangle;
    My_unique_ptr<Rectangle> rect = My_unique_ptr<Rectangle>(rect1);

};
