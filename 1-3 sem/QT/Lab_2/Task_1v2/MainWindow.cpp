#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent) 
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	scene = new QGraphicsScene(0, 0, 1280, 720, this);
	ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow() {
	delete ui;
}
