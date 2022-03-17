#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rectangle.h"

void MainWindow::on_pushButton_clicked()
{
    CreateRect();
}

void MainWindow::on_pushButton2_clicked() 
{
    QMessageBox::critical(this, "Error", "Random Exception!");
}

void MainWindow::on_pushButton3_clicked() 
{
  //  delete rect;
    exit(0);
}

void Rectangle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {

    painter->setPen(Qt::gray);
    painter->setBrush(QColor(r, g, b));

    painter->drawRect(-30, -30, width, height);

    painter->drawPoint(QRectF(-30, -30, width, height).center());

   // QTimer::singleShot(0, this, SLOT(update()));


   Q_UNUSED(option); Q_UNUSED(widget);
}

void MainWindow::CreateRect()
{
    short width = 200;
    short height = 100;
    /////////////////////////////////////////////////////////////////
    
    rect->setPos(rand() % 1000, rand() % 800);
    scene->addItem(rect.get());
}

//

//void Rectangle::mousePressEvent(QGraphicsSceneMouseEvent* event) {
//    this->setCursor(QCursor(Qt::ClosedHandCursor));
//    Q_UNUSED(event);
//}
//
//void Rectangle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
//    delete this;
//    Q_UNUSED(event);
//}


