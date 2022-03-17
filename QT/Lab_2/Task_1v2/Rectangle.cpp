#include "rectangle.h"
#include "MainWindow.h"

void MainWindow::on_pushButton_clicked()
{
    CreateRect();
}

void MainWindow::on_pushButton_2_clicked()
{
    Exception();    
}

void MainWindow::Exception() {
    scene->removeItem(rect.get());
    try { 
        throw 0; 
    }
    catch (...) {

    }
}

void MainWindow::on_pushButton_3_clicked()
{
    scene->removeItem(rect.get());
}

void Rectangle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {

    painter->setPen(Qt::gray);
    painter->setBrush(QColor(r, g, b));

    painter->drawRect(-30, -30, width, height);

    painter->drawPoint(QRectF(-30, -30, width, height).center());

    Q_UNUSED(option); Q_UNUSED(widget);
}

void MainWindow::CreateRect()
{
    short width = 150;
    short height = 75;

    rect->setPos(rand() % 1000, rand() % 650);
    scene->addItem(rect.get());
}
