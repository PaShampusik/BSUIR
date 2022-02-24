#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsView>
#include <QTimer>
#include <QPushButton>
#include <cmath>
#include <QSound>


#include "wheels.h"
#include "telega.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {

        QSound::play("D:/QT/qtProjects/FinalTelega/Himn.wav");

        scn = new QGraphicsScene();
        wdg = new QGraphicsView(scn);
        scn->setSceneRect(0, 0, 1000, 600);

        btn = new QPushButton("Move", wdg); btn->adjustSize();

        btn->move(1000, 600);

        connect(btn, SIGNAL(clicked()), this, SLOT(ConnectMove()));

        telega->setPos(0, 800);
        scn->addItem(telega);
        scn->addItem(wheels);

        tmr = new QTimer(this);

        wdg->show();
    }
    ~MainWindow() {}

public slots:

    void moveforward() {
        static int pos = 0;              
        telega->setPos(++pos, 0);
        wheels->setPos(++pos, 0);
        if(pos == 1500){
            pos = -1000;
        }
    }

    void ConnectMove() {

        btn->setText("Faster");



        connect(tmr, SIGNAL(timeout()), this, SLOT(moveforward()));

        tmr->start(1000/60);

        wheels->speedup();
    }

private:
    QGraphicsScene *scn;
    QGraphicsView *wdg; //для того, чтобы разместить здесь сцену
    Telega *telega = new Telega(500, 200);
    Wheels *wheels = new Wheels();

    QTimer *tmr; //для механизма сигналов и слотов
    QPushButton *btn;
};


#endif // MAINWINDOW_H
