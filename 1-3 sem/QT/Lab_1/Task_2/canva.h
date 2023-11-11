#pragma once

#ifndef GRAPHICSPAINTER_H
#define GRAPHICSPAINTER_H

#include <QWidget>

class Canva : public QWidget
{
    Q_OBJECT
public:
    explicit Canva(QWidget *parent = nullptr);

    void SetDraw(bool bDraw);

signals:
    void singalDrawOver();

//public slots:

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *event);


    bool bDraw;             // Находится ли он в состоянии рисования
    bool bLeftClick;        // Начался ли щелчок левой кнопкой мыши
    bool bMove;             // Находится ли мышь в состоянии рисования

    QVector<QPointF> pointList;
    QPointF movePoint;
};

#endif // GRAPHICSPAINTER_H
