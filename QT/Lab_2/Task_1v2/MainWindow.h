#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsView>
#include <qmessagebox.h>

#include "Rectangle.h"
#include "Unique_Ptr.h"
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
    void CreateRect();
    void Exception();
private:

    Rectangle* rect1 = new Rectangle;
    Unique_Ptr<Rectangle> rect = Unique_Ptr<Rectangle>(rect1);
    //Unique_Ptr<Rectangle> rect2 = rect;
};
#endif MAINWINDOW_H