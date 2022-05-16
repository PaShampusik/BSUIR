#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	/*while (Dequeue.size() < 2) {
		Dequeue.push_back(1);
		Dequeue.pop_front();
	}*/
}

void MainWindow::on_PushBack_clicked() {
	
	Dequeue.push_back(rand() % 100);
	ui.Dequeue->clear();
	for (auto i = Dequeue.Begin(); i != Dequeue.End(); i++)
	{
		ui.Dequeue->addItem(QString::number(*i));
	}
	ui.Size->setText(QString::QString("Size: ") + QString::number(Dequeue.size()));
}

void MainWindow::on_PushFront_clicked() {
	Dequeue.push_front(rand() % 100);
	ui.Dequeue->clear();
	for (auto i = Dequeue.Begin(); i != Dequeue.End(); i++)
	{
		ui.Dequeue->addItem(QString::number(*i));
	}
	ui.Size->setText(QString::QString("Size: ") + QString::number(Dequeue.size()));

}

void MainWindow::on_PopBack_clicked() {
	if (Dequeue.empty())
	{
		return;
	}
	Dequeue.pop_back();
	ui.Dequeue->clear();
	for (auto i = Dequeue.Begin(); i != Dequeue.End(); i++)
	{
		ui.Dequeue->addItem(QString::number(*i));
	}
	ui.Size->setText(QString::QString("Size: ") + QString::number(Dequeue.size()));

}

void MainWindow::on_PopFront_clicked() {
	if (Dequeue.empty())
	{
		return;
	}
	
	Dequeue.pop_front();
	ui.Dequeue->clear();
	for (auto i = Dequeue.Begin(); i != Dequeue.End(); i++)
	{
		ui.Dequeue->addItem(QString::number(*i));
	}
	ui.Size->setText(QString::QString("Size: ") + QString::number(Dequeue.size()));

}


void MainWindow::on_Clear_clicked() {
	Dequeue.clear();
	ui.Dequeue->clear();
	ui.Size->setText(QString::QString("Size: ") + QString::number(Dequeue.size()));
}