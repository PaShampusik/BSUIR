#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QCursor>
#include <QtMath>



class Ellipse: public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Ellipse(short scale = 1, QObject *parent = nullptr) : QObject (parent) {
        size = 1;
        this->scale = static_cast<double>(scale);
        r = rand()%255; g = rand()%255; b = rand()%255;
    }

private:
    int degree = 0;
    short r, g, b;
    double R = 50;
    int scale = 1;
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
