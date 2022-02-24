#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::on_pushButton_Circle_clicked()
{
    CircleWnd->setModal(true);
    CircleWnd->resize(300, 300);
    InputR->move(100, 100);
    LE_R->resize(30, 30);
    LE_R->move(170, 100);
    Enter = new QPushButton("Создать", CircleWnd); Enter->adjustSize();
    Enter->move(200, 200);
    connect(Enter, SIGNAL(clicked()), this, SLOT(CreateCircle()));

    CircleWnd->show();
}

void MainWindow::CreateCircle()
{
    QString strR = LE_R->text();
        CircleWnd->close();
        Circle *crcl = new Circle(strR.toShort());
        crcl->setPos(rand()%600, rand()%700);
        scene->addItem(crcl);
        ui->lineEdit->setText(crcl->Parametrs());
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->rotate(degree);
    degree += 4;

    painter->setPen(Qt::gray);
    painter->setBrush(QColor(r, g, b));

    if (size < 10)
        painter->scale(size, size);

    painter->drawPoint(boundingRect().center());

    painter->drawEllipse(R - 20, R - 20, R*1.5, R*1.5);

    QTimer::singleShot(0, this, SLOT(update()));

    Q_UNUSED(option); Q_UNUSED(widget);
}

void Circle::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    this->setPos(mapToScene(event->pos()));
    Q_UNUSED(event);
}


void Circle::mousePressEvent (QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));
}

void Circle::mouseReleaseEvent (QGraphicsSceneMouseEvent *event) {

    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Circle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    delete this;
    Q_UNUSED(event);
}

void Circle::wheelEvent(QGraphicsSceneWheelEvent *event) {
    if (event->delta() < 0)
        size -= 0.1;
    if ((event->delta() > 0))
        size += 0.1;
    update();
}

QString Circle::Parametrs (){
    QString Parametrs = "Площадь: ";

    int S_value = M_PI * R * R * size * size;
    Parametrs += QString::number(S_value);
    QString P = ", Периметр: ";
    int P_value = 2 * M_PI * R * size;
    P += QString::number(P_value);
    Parametrs += P;
    QString CentrMass = ", Координаты центра масс: (";
    CentrMass += QString::number(double(R/2));
    CentrMass += ", ";
    CentrMass += QString::number(double(R/2));
    CentrMass += ")";
    Parametrs += CentrMass;
    return Parametrs;
   }
