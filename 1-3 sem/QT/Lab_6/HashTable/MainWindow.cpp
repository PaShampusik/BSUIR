#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void MainWindow::on_SetTable_clicked() {
	hashTable.clear();
	ui.List->clear();
	for (int i = 0; i < 200; i++)
	{
		hashTable.insert(i, i);
	}
	QString str = " ";
	Node<std::pair<const int, int>>* temp;
	for (int i = 0; i < 100; i++)
	{
		str += QString::number(i + 1) + ")  ";
		temp = hashTable.table[i].getHead();
		while (temp != nullptr)
		{
			str += QString::number(temp->data.second) + " ";
			temp = temp->next;
		}
		ui.List->addItem(str);
		str = " ";
	}
}

void MainWindow::on_FindMin_clicked() {
	ui.label->setText(QString::number(hashTable.FindMin()));
}
