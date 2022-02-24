#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_Rhombus_clicked()
{
    RhombWnd->setModal(true);
    RhombWnd->resize(300, 300);
    InputSideLength->move(100, 100);
    LE_Length->resize(30, 30);
    LE_Length->move(170, 100);
    Enter = new QPushButton("Создать", RhombWnd); Enter->adjustSize();
    Enter->move(200, 200);
    connect(Enter, SIGNAL(clicked()), this, SLOT(CreateRhombus()));
    RhombWnd->show();
}

void MainWindow::CreateRhombus()
{
    QString strLength = LE_Length->text();

        RhombWnd->close();
        short length = strLength.toShort();
        Rhombus *rhombus = new Rhombus(length);
        rhombus->setPos(rand()%600, rand()%700);
        scene->addItem(rhombus);
        ui->lineEdit->setText(rhombus->Parametrs());
}

void Rhombus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->rotate(degree);
    degree += 2;

    painter->setPen(Qt::gray);
    painter->setBrush(QColor(r, g, b));

    QPolygon poly;
    poly<<QPoint(-150, 0)<<QPoint(0, -80)<<QPoint(150, 0) << QPoint(0, 80);

    painter->drawPoint(boundingRect().center());

    painter->drawPolygon(poly);

    QTimer::singleShot(0, this, SLOT(update()));

    Q_UNUSED(option); Q_UNUSED(widget);
}

 void Rhombus::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    this->setPos(mapToScene(event->pos()));
}

 void Rhombus::mousePressEvent (QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Rhombus::mouseReleaseEvent (QGraphicsSceneMouseEvent *event) {

    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Rhombus::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    delete this;
    Q_UNUSED(event);
}

void Rhombus::wheelEvent(QGraphicsSceneWheelEvent *event) {
    if (event->delta() < 0)
        size -= 0.1;
    if ((event->delta() > 0))
        size += 0.1;
    update();
}

QString Rhombus:: Parametrs (){
    QString Parametrs = "Area: ";
    int S_value = 126 * 4 * 80;
    Parametrs += QString::number(S_value);
    QString P = ", Perimeter: ";
    int P_value = length * 4;
    P += QString::number(P_value);
    Parametrs += P;
    QString CentrMass = ", Coordinates of the centre: (";
    CentrMass += QString::number(double(80/2));
    CentrMass += ", ";
    CentrMass += QString::number(double(252/2));
    CentrMass += ")";
    Parametrs += CentrMass;
    return Parametrs;
   }
