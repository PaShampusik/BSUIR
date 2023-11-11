#include "canva.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

Canva::Canva(QWidget *parent) : QWidget(parent)
{
    // Заливаем цвет фона
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Base);

    bDraw = false;
    bLeftClick = false;
    bMove = false;
    setMouseTracking(true);
}

void Canva::SetDraw(bool bDraw)
{
    this->bDraw = bDraw;
    pointList.clear();
}

void MainWindow::on_pushButton_Canva_clicked()
{
   QDialog *canvasWnd = new QDialog(this);
    canvasWnd->setModal(false);

   canvasWnd->resize(1000, 800);

   Canva *canvas = new Canva(canvasWnd);
   canvas->resize(1000, 800);
   canvas->SetDraw(true);
   canvasWnd->show();
}

void Canva::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if(bDraw)
    {
       painter.setPen(QColor(0,0,0));
       QVector<QLineF> lines;
       for(int i = 0; i<pointList.size()-1; i++)
       {
           QLineF line(QPointF(pointList[i].x(), pointList[i].y()), QPointF(pointList[i+1].x(), pointList[i+1].y()));
           lines.push_back(line);
       }
       if(bMove&&pointList.size()>0)
       {
           QLineF line(QPointF(pointList[pointList.size()-1].x(), pointList[pointList.size()-1].y()), movePoint);
           lines.push_back(line);
       }
       painter.drawLines(lines);
    }
}

//Нажмите
void Canva::mousePressEvent(QMouseEvent *e)
{
    if(bDraw)
    {
        if(!bLeftClick)
        {
            pointList.clear();
            bLeftClick = true;
        }
    }
    //qDebug()<<"Press";
}

// мобильный
void Canva::mouseMoveEvent(QMouseEvent *e)
{
    if(bDraw&&bLeftClick)
    {
        movePoint = e->pos();
        bMove = true;
        this->update();
    }
    //qDebug()<<"Move";
}

//выпуск
void Canva::mouseReleaseEvent(QMouseEvent *e)
{
    if(bDraw&&bLeftClick)
    {
        pointList.push_back(QPointF(e->x(), e->y()));
        bMove = false;
        this->update();
    }
    //qDebug()<<"Release";
}

//Двойной щелчок
void Canva::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(bDraw)
    {
        bLeftClick = false;
        pointList.push_back(pointList[0]);
        this->update();
        singalDrawOver();
    }
    //qDebug()<<"DoubleClick";
}
