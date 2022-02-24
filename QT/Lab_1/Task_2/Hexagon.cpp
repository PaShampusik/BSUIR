#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::on_pushButton_Hex_clicked()
{
    Hexagon *hexagon = new Hexagon();
    hexagon->setPos(rand()%600, rand()%700);
    scene->addItem(hexagon);
    ui->lineEdit->setText(hexagon->Parametrs());
}

void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->rotate(degree);
    degree += 3;

    painter->setPen(Qt::gray);
    painter->setBrush(QColor(r, g, b));

    QPolygon poly;
    poly<<QPoint(-115, 0)<<QPoint(-55, -80)<<QPoint(55, -80) << QPoint(115, 0)
       << QPoint(55, 80) << QPoint(-55, 80) << QPoint(-115, 0);

    painter->drawPoint(boundingRect().center());

    painter->drawPolygon(poly);

    QTimer::singleShot(0, this, SLOT(update()));

    Q_UNUSED(option); Q_UNUSED(widget);
}


void Hexagon::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    this->setPos(mapToScene(event->pos()));
}


void Hexagon::mousePressEvent (QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));

    Q_UNUSED(event);
}

void Hexagon::mouseReleaseEvent (QGraphicsSceneMouseEvent *event) {

    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Hexagon::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    delete this;
    Q_UNUSED(event);
}

void Hexagon::wheelEvent(QGraphicsSceneWheelEvent *event) {
    if (event->delta() < 0)
        size -= 0.1;
    if ((event->delta() > 0))
        size += 0.1;
    update();
}

QString Hexagon::Parametrs (){
    QString Parametrs = "Площадь: ";
    double S_value = DefaultSize * DefaultSize * 1.71 * 1.5;
    Parametrs += QString::number(S_value);
    QString P = ", Периметр: ";
    int P_value = DefaultSize * 6;
    P += QString::number(P_value);
    Parametrs += P;
    QString CentrMass = ", Координаты центра масс: (";
    CentrMass += "100.0";
    CentrMass += ", ";
    CentrMass += QString::number(double(200*sin(M_PI/3)));
    CentrMass += ")";
    Parametrs += CentrMass;
    return Parametrs;
   }
