#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//file input
	QString fileName = "D:/BSUIR/QT/Lab_5/Task_1/input.txt";
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return;
	}
	QTextStream in(&file);
	QStringList oof;
	while (!in.atEnd())
	{
		oof << in.readLine();
	}


	for (int i = 0; i < oof.size(); i++)
	{
		list.insertAtEnd(new Node<QString>(oof[i]));
	}

	Node<QString>* temp;
	temp = list.getHead();
	while (temp != nullptr)
	{
		ui.List->addItem(temp->getdata());
		if (temp->getnext() != nullptr)
		{
			temp = temp->getnext();
		}
		else
		{
			break;
		}
	}

	connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_List_itemDoubleClicked(QListWidgetItem*)));
	connect(this, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(on_List_itemClicked(QListWidgetItem*)));
}

void MainWindow::on_List_itemDoubleClicked(QListWidgetItem* itm) {
	if (ui.List->count() == 2)
	{

	}
	else {
		for (int i = 0; i < ui.List->count(); i++)
		{
			if (ui.List->item(i) == itm)
			{
				ui.List->takeItem(i);
			}
		}
		list.deleteNode(itm->text());
		buffer.push_back(itm->text());
	}
}

void MainWindow::on_List_itemClicked(QListWidgetItem* itm) {
	for (int i = 0; i < ui.List->count(); i++)
	{
		if (ui.List->item(i) == itm)
		{
			last_item_clicked = i;
		}
	}
}

void MainWindow::on_Enqueue_clicked() {
	QString data = QString::number(rand() % 50);
	ui.Queue->addItem(data);
	queue.enqueue(data);
}

void MainWindow::on_Dequeue_clicked() {
	queue.dequeue();
	ui.Queue->takeItem(0);

}

void MainWindow::on_Button_clicked() {
	for (int i = buffer.size(); i > 0; i--)
	{
		list.insert(ui.List->item(last_item_clicked)->text(), buffer[i - 1]);
	}
	buffer.clear();
	ui.List->clear();
	Node<QString>* temp;
	temp = list.getHead();
	while (temp != nullptr)
	{
		ui.List->addItem(temp->getdata());
		if (temp->getnext() != nullptr)
		{
			temp = temp->getnext();
		}
		else
		{
			break;
		}
	}
}

