#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QCursor>
#include <QtMath>



class Circle: public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Circle(short R = 20, QObject *parent = nullptr) : QObject (parent) {
        size = 1;
        this->R = static_cast<double>(R);
        r = rand()%255; g = rand()%255; b = rand()%255;
    }
    Circle(QPainter *painter)
    {
        painter->rotate(degree);
        degree += 4;
    }

private:
    int degree = 0;
    short r, g, b;
    double R;
    double size;

    QRectF boundingRect() const {
        return QRectF(-R - 2000, -R - 2000, R + 4500, R + 4500);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:

    virtual void mouseMoveEvent (QGraphicsSceneMouseEvent *event);

    virtual void mousePressEvent (QGraphicsSceneMouseEvent *event);

    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent *event);

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);

    QString Parametrs ();
};
