#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_Star_clicked()
{
    StarWnd->setModal(true);
    StarWnd->resize(300, 300);
    QLabel *Text_5 = new QLabel("5", StarWnd); Text_5->adjustSize();
    QLabel *Text_6 = new QLabel("6", StarWnd); Text_6->adjustSize();
    QLabel *Text_8 = new QLabel("8", StarWnd); Text_8->adjustSize();
    Text_5->move(200, 100); Text_6->move(200, 140); Text_8->move(200, 180);
    Verticles_5->move(170, 100); Verticles_6->move(170, 140); Verticles_8->move(170, 180);
    connect(Verticles_5, SIGNAL(clicked()), this, SLOT(SetVerticles_5()));
    connect(Verticles_6, SIGNAL(clicked()), this, SLOT(SetVerticles_6()));
    connect(Verticles_8, SIGNAL(clicked()), this, SLOT(SetVerticles_8()));
    Enter = new QPushButton("Создать", StarWnd); Enter->adjustSize();
    Enter->move(200, 240);
    connect(Enter, SIGNAL(clicked()), this, SLOT(CreateStar()));
    StarWnd->show();
}

void MainWindow::CreateStar()
{
        StarWnd->close();
        Star *star = new Star(verticles, 50, 25);
        star->setPos(rand()%600, rand()%700);
        scene->addItem(star);
        ui->lineEdit->setText(star->Parametrs());
}

void MainWindow::SetVerticles_5()
{
    verticles = 5;
}

void MainWindow::SetVerticles_6()
{
    verticles = 6;
}

void MainWindow::SetVerticles_8()
{
    verticles = 8;
}

void Star::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->rotate(degree);
    degree += 4;

    painter->setPen(Qt::black);

    painter->setBrush(Qt::green);

    double a = 0;

    for (int i=0; i < VerticlesAmount*2; ++i)
    {
     if (!(i%2)) //При выполнении условия четности следующие формулы
      {
       p_x[i]=x * size +(r * size)/2*cos(a*M_PI/180);
       p_y[i]=y * size- (r * size)/2*sin(a*M_PI/180);
      }
      else //При невыполнении условия четности следующие формулы
       {
        p_x[i]=x * size+R * size * cos(a*M_PI/180);
        p_y[i]=y * size-R * size * sin(a*M_PI/180);
       }
       a += 180/VerticlesAmount;
    }//Завершаем построение звезды соединяя её окончание с начальной точкой

    p_x[VerticlesAmount*2]=p_x[0];
    p_y[VerticlesAmount*2]=p_y[0];

    QPainterPath star12;
    star12.moveTo(p_x[0], p_y[0]);

    for (int i=0;i<VerticlesAmount*2+1;++i) {
       star12.lineTo(p_x[i], p_y[i]);
   }

    painter->drawPath(star12);

    painter->drawPoint(boundingRect().center());

    QTimer::singleShot(0,this, SLOT(update()));

    Q_UNUSED(option);
    Q_UNUSED(widget);

}

void Star::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    this->setPos(mapToScene(event->pos()));
}


void Star::mousePressEvent (QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));

    Q_UNUSED(event);
}

void Star::mouseReleaseEvent (QGraphicsSceneMouseEvent *event) {

    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Star::wheelEvent(QGraphicsSceneWheelEvent *event) {
    if (event->delta() < 0)
        size -= 0.1;
    if ((event->delta() > 0))
        size += 0.1;
    update();

}

int R, r, VerticlesAmount;
double degree;

double DefaultSize, size;

double *p_x, *p_y;

double x, y;

void Star::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    delete this;
    Q_UNUSED(event);
}

QString Star::Parametrs() {
    QString Parametrs = "Площадь: ";
    int S_value = R * R * VerticlesAmount * sin(2 * M_PI / VerticlesAmount) / 2;
    Parametrs += QString::number(S_value);
    QString P = ", Периметр: ";
    int P_value = 2 * S_value / r;
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
