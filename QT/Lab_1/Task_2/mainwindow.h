#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSound>
#include <QDialog>
#include <QRegularExpression>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsView>

#include "rectangle.h"
#include "circle.h"
#include "Hexagon.h"
#include "Star.h"
#include "Triangle.h"
#include "Square.h"
#include "Rhombus.h"
#include "ellipse.h"
#include "canva.h"
#include "Rhombus.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:


    Ui::MainWindow *ui;

    QGraphicsScene *scene;

    QPushButton *Enter;

    QDialog *RhombWnd;
    QLabel *InputSideLength;
    QLineEdit *LE_Length;

    QDialog *RectWnd;
    QLabel *InputWidth, *InputHeight;
    QLineEdit *LE_Width, *LE_Height;

    short width, heigh;

    QDialog *SquareWnd;
    QLabel *InputSquareWidth;
    QLineEdit *LE_SquareWidth;

    QDialog *TriangleWnd;
    QLabel *InputX1, *InputX2, *InputX3, *InputY1, *InputY2, *InputY3;
    QLineEdit *LE_X1, *LE_X2, *LE_X3, *LE_Y1, *LE_Y2, *LE_Y3;


    short x1, y1, x2, y2, x3, y3;

    QDialog *StarWnd;
    QRadioButton *Verticles_5, *Verticles_6, *Verticles_8;

    short verticles = 0;

    QDialog *CircleWnd;
    QLabel *InputR;
    QLineEdit *LE_R;

    QMovie *movie;
    QLabel *gif;
    
    QDialog *EllipseWnd;
    QLabel *InputEll;
    QLineEdit *LE_Ell;



public slots:

    void CreateEllipse();
    void CreateRect();
    void CreateSquare();
    void CreateRhombus();
    void CreateTriangle();
    void CreateCircle();
    void CreateStar();
    void SetVerticles_5();
    void SetVerticles_6();
    void SetVerticles_8();
    void on_pushButton_Triangle_clicked();
    void on_pushButton_Rhombus_clicked();
    void on_pushButton_Star_clicked();
    void on_pushButton_Hex_clicked();
    void on_pushButton_Circle_clicked();
    void on_pushButton_Rectangle_clicked();
    void on_pushButton_Square_clicked();
    void on_pushButton_Ellipse_clicked();
    void on_pushButton_Canva_clicked();
};
#endif // MAINWINDOW_H


