#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //QSound::play("D:/QT/qtProjects/Task_2/spin.wav");

    ui->setupUi(this);

    scene = new QGraphicsScene(0, 0, 600, 700, this);
    ui-> graphicsView -> setScene(scene);

    RhombWnd = new QDialog(this);
    RectWnd = new QDialog(this);
    SquareWnd = new QDialog(this);
    TriangleWnd = new QDialog(this);
    StarWnd = new QDialog(this);
    CircleWnd = new QDialog(this);
    EllipseWnd = new QDialog(this);

    InputSideLength = new QLabel("Сторона:", RhombWnd); InputSideLength->adjustSize();
    InputWidth = new QLabel("Ширина:", RectWnd); InputWidth->adjustSize();
    InputHeight = new QLabel("Длина:", RectWnd); InputHeight->adjustSize();
    InputSquareWidth = new QLabel("Сторона:", SquareWnd); InputSquareWidth->adjustSize();
    InputR = new QLabel("Радиус:", CircleWnd); InputR->adjustSize();
    InputEll = new QLabel("Отношение a/b", EllipseWnd); InputEll->adjustSize();
    InputX1 = new QLabel("Х1:", TriangleWnd); InputX1->adjustSize();
    InputX2 = new QLabel("Х2:", TriangleWnd); InputX2->adjustSize();
    InputX3 = new QLabel("Х3:", TriangleWnd); InputX3->adjustSize();
    InputY1 = new QLabel("У1:", TriangleWnd); InputY1->adjustSize();
    InputY2 = new QLabel("У2:", TriangleWnd); InputY2->adjustSize();
    InputY3 = new QLabel("У3:", TriangleWnd); InputY3->adjustSize();

    LE_Length = new QLineEdit(RhombWnd);
    LE_Height = new QLineEdit(RectWnd);
    LE_Width = new QLineEdit(RectWnd);
    LE_SquareWidth = new QLineEdit(SquareWnd);
    LE_R = new QLineEdit(CircleWnd);
    LE_Ell = new QLineEdit(EllipseWnd);
    LE_X1 = new QLineEdit(TriangleWnd);
    LE_X2 = new QLineEdit(TriangleWnd);
    LE_X3 = new QLineEdit(TriangleWnd);
    LE_Y1 = new QLineEdit(TriangleWnd);
    LE_Y2 = new QLineEdit(TriangleWnd);
    LE_Y3 = new QLineEdit(TriangleWnd);

    Verticles_5 = new QRadioButton(StarWnd);
    Verticles_6 = new QRadioButton(StarWnd);
    Verticles_8 = new QRadioButton(StarWnd);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete RhombWnd;
    delete InputSideLength;
    delete LE_Length;

    delete RectWnd;
    delete InputWidth, delete InputHeight;
    delete LE_Width; delete LE_Height;

    delete SquareWnd;
    delete InputSquareWidth;
    delete LE_SquareWidth;

    delete TriangleWnd;
    delete InputX1; delete InputX2; delete InputX3; delete InputY1; delete InputY2; delete InputY3;
    delete LE_X1; delete LE_X2; delete LE_X3; delete LE_Y1; delete LE_Y2; delete LE_Y3;

    delete StarWnd;
    delete Verticles_5; delete Verticles_6; delete Verticles_8;

    delete CircleWnd;
    delete InputR;
    delete LE_R;

    delete EllipseWnd;
    delete InputEll;
    delete LE_Ell;
}

void MainWindow::on_pushButton_Square_clicked()
{
    SquareWnd->setModal(true);
    SquareWnd->resize(300, 300);
    InputSquareWidth->move(100, 100);
    LE_SquareWidth->resize(30, 30);
    LE_SquareWidth->move(170, 100);
    Enter = new QPushButton("Создать", SquareWnd); Enter->adjustSize();
    Enter->move(100, 150);
    connect(Enter, SIGNAL(clicked()), this, SLOT(CreateSquare()));
    SquareWnd->show();
}

void MainWindow::CreateSquare()
{
    QString strWidth = LE_SquareWidth->text();
        SquareWnd->close();
        short width = strWidth.toShort();
        Square *square = new Square(width);
        square->setPos(rand()%600, rand()%700);
        scene->addItem(square);
        ui->statusbar->showMessage(square->Parametrs());
}






