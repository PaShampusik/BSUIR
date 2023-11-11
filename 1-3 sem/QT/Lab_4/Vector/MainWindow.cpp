#include "MainWindow.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	
	for (int i = 0; i < 10; i++)
	{
		vector.push_back(i);
	}

	for (auto& i : vector) {
		ui.List->addItem(QString::number(i));
	}
	std::vector<int8_t> a;
	ui.List->addItem(QString::number(a.max_size()));
}


