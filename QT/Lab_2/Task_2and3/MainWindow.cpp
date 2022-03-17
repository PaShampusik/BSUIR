#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	scene = new QGraphicsScene(0, 0, 1280, 720, this);
	ui->graphicsView->setScene(scene);
	ui->pushButton_4->setDisabled(1);
	ui->pushButton_6->setDisabled(1);
	ui->pushButton_5->setDisabled(1);
	ui->textEdit->hide();
	ui->pushButton_8->setDisabled(1);
	
}

MainWindow::~MainWindow() {
	delete ui;
}
