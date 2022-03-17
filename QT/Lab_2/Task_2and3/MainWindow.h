#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsView>
#include <qmessagebox.h>

#include "Rectangle.h"
#include "Shared_Ptr.h"
#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow* ui;

    QGraphicsScene* scene;

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void CreateRect();
    void Exception();
private:

    Rectangle* rect1 = new Rectangle;
    Shared_Ptr<Rectangle> rect = Shared_Ptr<Rectangle>(rect1);

    Rectangle* rect2 = new Rectangle;
    Shared_Ptr<Rectangle> rect_ = Shared_Ptr<Rectangle>(rect2);

    Rectangle* rect3 = new Rectangle;
    Shared_Ptr<Rectangle> loop1 = Shared_Ptr<Rectangle>(rect3);

    Rectangle* rect4 = new Rectangle;
    Shared_Ptr<Rectangle> loop2 = Shared_Ptr<Rectangle>(rect4);

    


    
};
#endif MAINWINDOW_H