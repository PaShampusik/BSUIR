#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rectangle.h"

void MainWindow::on_pushButton_Rectangle_clicked()
{
    RectWnd->setModal(true);
    RectWnd->resize(300, 300);
    InputWidth->move(100, 100); InputHeight->move(100, 150);
    LE_Width->resize(30, 30); LE_Height->resize(30, 30);
    LE_Width->move(170, 100); LE_Height->move(170, 140);
    Enter = new QPushButton("Создать", RectWnd); Enter->adjustSize();
    Enter->move(200, 200);
    connect(Enter, SIGNAL(clicked()), this, SLOT(CreateRect()));

    RectWnd->show();
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->rotate(degree);
    degree += 2;

    painter->setPen(Qt::gray);
    painter->setBrush(QColor(r, g, b));

    painter->drawRect(-30, -30, width, height);

    painter->drawPoint(QRectF(-30, -30, width, height).center());

    QTimer::singleShot(0, this, SLOT(update()));

    Q_UNUSED(option); Q_UNUSED(widget);
}

void MainWindow::CreateRect()
{
    QString strHeight = LE_Height->text();
    QString strWidth = LE_Width->text();

        RectWnd->close();
        short width = strWidth.toShort();
        short height = strHeight.toShort();
        Rectangle *rect = new Rectangle(height, width);
        rect->setPos(rand()%700, rand()%800);
        scene->addItem(rect);
        ui->lineEdit->setText(rect->Parametrs());
}

 void Rectangle::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    this->setPos(mapToScene(event->pos()));
}

 void Rectangle::mousePressEvent (QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Rectangle::mouseReleaseEvent (QGraphicsSceneMouseEvent *event) {

    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Rectangle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    delete this;
    Q_UNUSED(event);
}

void Rectangle::wheelEvent(QGraphicsSceneWheelEvent *event) {
    if (event->delta() < 0)
        size -= 0.1;
    if ((event->delta() > 0))
        size += 0.1;
    update();
}

QString Rectangle:: Parametrs (){
    QString Parametrs = "Area: ";
    int S_value = height * width;
    Parametrs += QString::number(S_value);
    QString P = ", Perimeter: ";
    int P_value = 2*(height + width);
    P += QString::number(P_value);
    Parametrs += P;
    QString CentrMass = ", Coordinates of the centre: (";
    CentrMass += QString::number(double(height/2));
    CentrMass += ", ";
    CentrMass += QString::number(double(width/2));
    CentrMass += ")";
    Parametrs += CentrMass;
    return Parametrs;
   }
