#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//for (int i = 0; i < 10; i++)
	//{
		//map.getroot() = map.insert(map.getroot(), 3, 7);
	//}
	/*ui.Map->headerItem()->setText(0, "Map");
	ui.Map->insertTopLevelItem(0, new QTreeWidgetItem);
	ui.Map->topLevelItem(0)->setText(0, "Root");
	AddMapWidget(ui.Map->topLevelItem(0), map.getroot());
	ui.Map->expandAll();*/


	//for (int i = 0; i < 10; i++)
	//{
		//set.getroot() = set.insert(set.getroot(), 3);
	//}
	/*ui.Set->headerItem()->setText(0, "Set");
	ui.Set->insertTopLevelItem(0, new QTreeWidgetItem);
	ui.Set->topLevelItem(0)->setText(0, "Root");
	AddSetWidget(ui.Set->topLevelItem(0), set.getroot());
	ui.Set->expandAll();*/
}

void MainWindow::on_AddMapElement_clicked() {
	int a = rand() % 200;
	map.getroot() = map.insert(map.getroot(), a, a);
	ui.Map->clear();
	ui.Map->headerItem()->setText(0, "Map");
	ui.Map->insertTopLevelItem(0, new QTreeWidgetItem);
	ui.Map->topLevelItem(0)->setText(0, "Root");
	AddMapWidget(ui.Map->topLevelItem(0), map.getroot());
	ui.Map->expandAll();
}

void MainWindow::on_AddSetElement_clicked() {
	int a = rand() % 200;
	set.getroot() = set.insert(set.getroot(), a);
	ui.Set->clear();
	ui.Set->headerItem()->setText(0, "Set");
	ui.Set->insertTopLevelItem(0, new QTreeWidgetItem);
	ui.Set->topLevelItem(0)->setText(0, "Root");
	AddSetWidget(ui.Set->topLevelItem(0), set.getroot());
	ui.Set->expandAll();
}

void MainWindow::on_AddUnorderedMapElement_clicked() {
	ui.UnorderedMap->clear();
	int i = rand() % 100000;
	unordered_map.insert(i, i);
	QString temp;
	for (size_t i = 0; i < unordered_map.getsize(); i++)
	{
		temp += QString::number(i + 1) + ") ";
		for (auto j = unordered_map.table[i].begin(); j != unordered_map.table[i].end(); j++)
		{
			temp += QString::number(j->second) + " ";
		}
		ui.UnorderedMap->addItem(temp);
		temp = "";
	}
}

void MainWindow::on_FindMapElement_clicked() {
	QString temp = ui.FindMapElementLine->text();
	int a = temp.toInt();
	ui.FindMapElementLine->clear();
	if (map.find(map.getroot(), a)) {
		QMessageBox::information(this, "Success", "Element " + QString::number(a) + " found");
	}
	else {
		QMessageBox::warning(this, "Error", "Element " + QString::number(a) + " not found");
	}
}

void MainWindow::on_FindSetElement_clicked() {
	QString temp = ui.FindSetElementLine->text();
	int a = temp.toInt();
	ui.FindSetElementLine->clear();
	if (set.find(set.getroot(), a)) {
		QMessageBox::information(this, "Success", "Element " + QString::number(a) + " found");
	}
	else {
		QMessageBox::warning(this, "Error", "Element " + QString::number(a) + " not found");
	}
}

void MainWindow::on_FindUnorderedMapElement_clicked() {
	QString temp = ui.FindUnorderedMapElementLine->text();
	int i = temp.toInt();
	if (unordered_map.find(i, i))
	{
		QMessageBox::information(this, "Success!", "Element " + QString::number(i) + " exists!");
	}
	else {
		QMessageBox::warning(this, "Error!", "Element " + QString::number(i) + " does not exist!");
	}
}

void MainWindow::on_RemoveMapElement_clicked() {
	if (map.getsize() == 0) {
		QMessageBox::warning(this, "Warning!", "Our Map is empty!");
	}
	else {
		int temp = ui.RemoveMapElementLine->text().toInt();
		ui.RemoveMapElementLine->clear();
		if (temp)
		{
			if (temp == map.getroot()->data.second)
			{
				QMessageBox::information(this, "Success", "Element " + QString::number(temp) + " removed");
				map.setRoot(map.remove(map.getroot(), temp, temp));
			}
			else
			{
				QMessageBox::information(this, "Success", "Element " + QString::number(temp) + " removed");
				map.remove(map.getroot(), temp, temp);
			}
			if (map.getroot() == nullptr)
			{
				ui.Map->clear();
				return;
			}
			ui.Map->clear();
			ui.Map->headerItem()->setText(0, "Map");
			ui.Map->insertTopLevelItem(0, new QTreeWidgetItem);
			ui.Map->topLevelItem(0)->setText(0, "Root");
			AddMapWidget(ui.Map->topLevelItem(0), map.getroot());
			ui.Map->expandAll();
		}
		else {
			QMessageBox::warning(this, "Warning!", "Wrong Input, try again!");
		}
	}
}

void MainWindow::on_RemoveSetElement_clicked() {
	if (!(set.getroot() == nullptr))
	{
		QString temp = ui.RemoveSetElementLine->text();
		int a = temp.toInt();
		ui.RemoveSetElementLine->clear();
		if (set.remove(set.getroot(), a)) {
			QMessageBox::information(this, "Success", "Element " + QString::number(a) + " removed");
		}
		else {
			QMessageBox::information(this, "Error", "Element " + QString::number(a) + " not found");
		}
		ui.Set->clear();
		ui.Set->headerItem()->setText(0, "Set");
		ui.Set->insertTopLevelItem(0, new QTreeWidgetItem);
		ui.Set->topLevelItem(0)->setText(0, "Root");
		AddSetWidget(ui.Set->topLevelItem(0), set.getroot());
		ui.Set->expandAll();
	}
}

void MainWindow::on_RemoveUnorderedMapElement_clicked() {
	QString temp = ui.RemoveUnorderedMapElementLine->text();
	int i = temp.toInt();
	if (unordered_map.find(i, i))
	{
		unordered_map.remove(i, i);
		ui.UnorderedMap->clear();
		for (size_t i = 0; i < unordered_map.getsize(); i++)
		{
			temp += QString::number(i + 1) + ") ";
			for (auto j = unordered_map.table[i].begin(); j != unordered_map.table[i].end(); j++)
			{
				temp += QString::number(j->second) + " ";
			}
			ui.UnorderedMap->addItem(temp);
			temp = "";
		}
		QMessageBox::information(this, "Success!", "Element " + QString::number(i) + " removed!");
	}
	else {
		QMessageBox::warning(this, "Error!", "Element " + QString::number(i) + " does not exist!");
	}
}

void MainWindow::AddMapWidget(QTreeWidgetItem* oof, Map<int, int>::Node* root) {


	if (oof->childCount() != 3)
	{
		oof->addChild(new QTreeWidgetItem);
		oof->child(0)->setText(0, "data: " + QString::number(root->data.second));

		oof->addChild(new QTreeWidgetItem);
		oof->child(1)->setText(0, "Left");

		oof->addChild(new QTreeWidgetItem);
		oof->child(2)->setText(0, "Right");
	}
	if (root->left) {

		AddMapWidget(oof->child(1), root->left);
	}

	if (root->right) {
		AddMapWidget(oof->child(2), root->right);
	}
}

void MainWindow::AddSetWidget(QTreeWidgetItem* oof, Set<int>::Node* root) {


	if (oof->childCount() != 3)
	{
		oof->addChild(new QTreeWidgetItem);
		oof->child(0)->setText(0, "data: " + QString::number(root->data));

		oof->addChild(new QTreeWidgetItem);
		oof->child(1)->setText(0, "Left");

		oof->addChild(new QTreeWidgetItem);
		oof->child(2)->setText(0, "Right");
	}
	if (root->left) {

		AddSetWidget(oof->child(1), root->left);
	}

	if (root->right) {
		AddSetWidget(oof->child(2), root->right);
	}
}