#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_Ellipse_clicked()
{
    EllipseWnd->setModal(true);
    EllipseWnd->resize(300, 300);
    InputEll->move(100, 100);
    LE_Ell->resize(30, 30);
    LE_Ell->move(170, 100);
    Enter = new QPushButton("Создать", EllipseWnd); Enter->adjustSize();
    Enter->move(110, 200);
    connect(Enter, SIGNAL(clicked()), this, SLOT(CreateEllipse()));

    EllipseWnd->show();
}

void MainWindow::CreateEllipse()
{
    QString strR1 = LE_Ell->text();
        EllipseWnd->close();
        Ellipse *Ell = new Ellipse(strR1.toShort());
        Ell->setPos(rand()%600, rand()%700);
        scene->addItem(Ell);
        ui->lineEdit->setText(Ell->Parametrs());
}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->rotate(degree);
    degree += 4;

    painter->setPen(Qt::gray);
    painter->setBrush(QColor(r, g, b));

    if (size < 10)
        painter->scale(size, size);

    painter->drawPoint(boundingRect().center());

    int c = R*((scale - 1) * 2 + 1);

    painter->drawEllipse(R - 20, R - 20, c *1.5, R*1.5);

    QTimer::singleShot(0, this, SLOT(update()));

    Q_UNUSED(option); Q_UNUSED(widget);
}

void Ellipse::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    this->setPos(mapToScene(event->pos()));
    Q_UNUSED(event);
}


void Ellipse::mousePressEvent (QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));
}

void Ellipse::mouseReleaseEvent (QGraphicsSceneMouseEvent *event) {

    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Ellipse::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    delete this;
    Q_UNUSED(event);
}

void Ellipse::wheelEvent(QGraphicsSceneWheelEvent *event) {
    if (event->delta() < 0)
        size -= 0.1;
    if ((event->delta() > 0))
        size += 0.1;
    update();
}

QString Ellipse::Parametrs (){
    QString Parametrs = "Площадь: ";

    int S_value = M_PI * R * R * size * size * scale;
    Parametrs += QString::number(S_value);
    QString P = ", Периметр: ";
    int P_value = 4 * (((M_PI * R * size * size * R) + (R * size - R * size)) / (R * size + R * size));
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
