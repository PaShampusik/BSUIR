#include "rectangle.h"
#include "MainWindow.h"
#include <qpen.h>
#include <qcolor.h>

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
    scene->removeItem(rect_.get());
    scene->removeItem(loop1.get());
    scene->removeItem(loop2.get());
    scene->clear();
    ui->textEdit->hide();
    ui->pushButton_4->setDisabled(1);
    ui->pushButton_8->setDisabled(1);
    try {
        throw 0;
    }
    catch (...) {

    }
}

void MainWindow::on_pushButton_3_clicked()
{   
    
    scene->removeItem(rect.get());
    scene->removeItem(rect_.get());
    scene->removeItem(loop1.get());
    scene->removeItem(loop2.get());

    scene->clear();
    ui->textEdit->hide();
    ui->pushButton_4->setDisabled(1);
    ui->pushButton_8->setDisabled(1);
}

void MainWindow::on_pushButton_5_clicked()
{
    scene->removeItem(rect.get());
    ui->pushButton_4->setDisabled(1);
    ui->pushButton_5->setDisabled(1);
}

void MainWindow::on_pushButton_6_clicked()
{
    scene->removeItem(rect_.get());
    ui->pushButton_4->setDisabled(1);
    ui->pushButton_6->setDisabled(1);
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
    rect->setPos(150, 300);
    scene->addItem(rect.get());
    ui->pushButton_4->setDisabled(0);
    ui->pushButton_5->setDisabled(0);
}

void MainWindow::on_pushButton_4_clicked() 
{
    rect_->setPos(350, 300);
    scene->addItem(rect_.get());
    ui->pushButton_6->setDisabled(0);
}
int i = 1;
void MainWindow::on_pushButton_7_clicked()
{
    ui->textEdit->show();
    
    QPen pen;
    QColor color;
    color.blue();
    pen.setWidth(4);
    pen.setColor(color);
    if (i == 1)
    {
        (*loop1).loop = loop2;
        (*loop2).loop = loop1;
        i = 0;
    }
    
    loop1->setPos(700, 300);
    loop2->setPos(1000, 300);
    scene->addItem(loop1.get());
    scene->addItem(loop2.get());

    scene->addLine(820, 290, 970, 290, pen);
    scene->addLine(820, 320, 970, 320, pen);
    scene->addLine(969, 291, 965, 297, pen);
    scene->addLine(971, 289, 965, 283, pen);
    scene->addLine(821, 321, 827, 327, pen);
    scene->addLine(821, 319, 827, 313, pen);
    ui->pushButton_8->setDisabled(0);
}

void MainWindow::on_pushButton_8_clicked()
{
    scene->removeItem(loop1.get());
    scene->removeItem(loop2.get());
    scene->clear();
    ui->textEdit->hide();
    ui->pushButton_8->setDisabled(1);
}
