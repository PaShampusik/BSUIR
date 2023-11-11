#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_Triangle_clicked()
{
    TriangleWnd->setModal(true);
    TriangleWnd->resize(200, 200);
    LE_X1->resize(40, 30);
    LE_X2->resize(40, 30);
    LE_X3->resize(40, 30);
    LE_Y1->resize(40, 30);
    LE_Y2->resize(40, 30);
    LE_Y3->resize(40, 30);
    InputX1->move(10, 50); InputY1->move(110, 50);
    InputX2->move(10, 80); InputY2->move(110, 80);
    InputX3->move(10, 110); InputY3->move(110, 110);
    LE_X1->move(30, 50); LE_Y1->move(130, 50);
    LE_X2->move(30, 80); LE_Y2->move(130, 80);
    LE_X3->move(30, 110); LE_Y3->move(130, 110);
    Enter = new QPushButton("Создать", TriangleWnd); Enter->adjustSize();
    Enter->move(60, 160);
    connect(Enter, SIGNAL(clicked()), this, SLOT(CreateTriangle()));

    TriangleWnd->show();
}

void MainWindow::CreateTriangle()
{
    QString strX1 = LE_X1->text(), strY1 = LE_Y1->text(),
            strX2 = LE_X2->text(), strY2 = LE_Y2->text(),
            strX3 = LE_X3->text(), strY3 = LE_Y3->text();

        TriangleWnd->close();
        short x1 = strX1.toShort(), y1 = strY1.toShort(),
                x2 = strX2.toShort(), y2 = strY2.toShort(),
                x3 = strX3.toShort(), y3 = strY3.toShort();
       Triangle *trngl = new Triangle(x1, y1, x2, y2, x3, y3);
       trngl->setPos(rand()%600, rand()%600);
       scene->addItem(trngl);
       ui->lineEdit->setText(trngl->Parametrs());
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->rotate(degree);
    degree += 0.5;

    painter->setPen(Qt::gray);
    painter->setBrush(QColor(r, g, b));

    QPolygon poly;
    poly<<QPoint(x1,y1)<<QPoint(x2,y2)<<QPoint(x3,y3);

    if (size < 20) {
        painter->scale(size, size);
        //prepareGeometryChange();
    }

    painter->drawPoint(boundingRect().center());

    painter->drawPolygon(poly);

    QTimer::singleShot(0, this, SLOT(update()));

    Q_UNUSED(option); Q_UNUSED(widget);
}

void Triangle::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    this->setPos(mapToScene(event->pos()));
}


void Triangle::mousePressEvent (QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));

    Q_UNUSED(event);
}

void Triangle::mouseReleaseEvent (QGraphicsSceneMouseEvent *event) {

    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Triangle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    delete this;
    Q_UNUSED(event);
}

void Triangle::wheelEvent(QGraphicsSceneWheelEvent *event) {
    if (event->delta() < 0)
        size -= 0.1;
    if ((event->delta() > 0))
        size += 0.1;
    update();
//    MainWindow::ui
}

QString Triangle::Parametrs (){
    QString Parametrs = "Площадь: ";

    int p = (AB + BC + AC)/2;

    int S_value = sqrt(p*(p - AB)*(p-AC)*(p-AC));
    Parametrs += QString::number(S_value);
    QString P = ", Периметр: ";
    int P_value = AB + BC + AC;
    P += QString::number(P_value);
    Parametrs += P;
    QString CentrMass = ", Координаты центра масс: (";
    CentrMass += QString::number(double((x1 + x2 + x3)/3));
    CentrMass += ", ";
    CentrMass += QString::number(double((y1 + y2 + y3)/3));
    CentrMass += ")";
    Parametrs += CentrMass;
    return Parametrs;
   }
