#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	
	for (int i = 0; i < 10; i++)
	{
		vector[i] = i;
	}

	for (auto& i : vector) {
		ui.List->addItem(QString::number(i));
	}
}


