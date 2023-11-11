#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	for (int i = 0; i < 10; i++)
	{
		tree.getroot() = tree.insert(tree.getroot(), list[i]);
	}
	ui.Tree->headerItem()->setText(0, "AWL Tree");
	ui.Tree->insertTopLevelItem(0, new QTreeWidgetItem);
	ui.Tree->topLevelItem(0)->setText(0, "Root");
	AddWidget(ui.Tree->topLevelItem(0), tree.getroot());
	ui.Tree->expandAll();
}


void MainWindow::on_Add_clicked() {
	QString temp = ui.Add_input->text();
	if (!temp.isEmpty())
	{
		tree.getroot() = tree.insert(tree.getroot(), temp);

		ui.Add_input->clear();
		ui.Tree->clear();
		ui.Tree->headerItem()->setText(0, "AWL Tree");
		ui.Tree->insertTopLevelItem(0, new QTreeWidgetItem);
		ui.Tree->topLevelItem(0)->setText(0, "Root");
		AddWidget(ui.Tree->topLevelItem(0), tree.getroot());
		ui.Tree->expandAll();
	}
	else {
		QMessageBox::warning(this, "Warning!", "Wrong Input, try again!");
	}
}

void MainWindow::on_Delete_clicked() {
	if (tree.getsize() == 0) {
		QMessageBox::warning(this, "Warning!", "Our Tree is empty!");
	}
	else {
		QString temp = ui.Delete_input->text();
		if (!temp.isEmpty())
		{
			if (temp == tree.getroot()->key)
			{
				tree.setRoot(tree.remove(tree.getroot(), temp));
			}
			else
			{
				tree.remove(tree.getroot(), temp);
			}
			if (tree.getroot() == nullptr)
			{
				ui.Tree->clear();
				return;
			}
			ui.Add_input->clear();
			ui.Tree->clear();
			ui.Tree->headerItem()->setText(0, "AWL Tree");
			ui.Tree->insertTopLevelItem(0, new QTreeWidgetItem);
			ui.Tree->topLevelItem(0)->setText(0, "Root");
			AddWidget(ui.Tree->topLevelItem(0), tree.getroot());
			ui.Tree->expandAll();
		}
		else {
			QMessageBox::warning(this, "Warning!", "Wrong Input, try again!");
		}
	}
}

void MainWindow::on_Childs_clicked() {

	int i = 1;
	ui.Output->setText(QString::number(FindRight(tree.getroot()->right, i)));
}

void MainWindow::AddWidget(QTreeWidgetItem* oof, Node<QString>* root) {


	if (oof->childCount() != 3)
	{
		oof->addChild(new QTreeWidgetItem);
		oof->child(0)->setText(0, "data: " + root->key);

		oof->addChild(new QTreeWidgetItem);
		oof->child(1)->setText(0, "Left");

		oof->addChild(new QTreeWidgetItem);
		oof->child(2)->setText(0, "Right");
	}
	if (root->left) {

		AddWidget(oof->child(1), root->left);
	}

	if (root->right) {
		AddWidget(oof->child(2), root->right);
	}
}

int MainWindow::FindRight(Node<QString>* root, int counter) {

	if (root->left)
	{
		++counter;
		counter = FindRight(root->left, counter);
	}

	if (root->right)
	{
		++counter;
		counter = FindRight(root->right, counter);
	}
	return counter;
}

void MainWindow::on_Find_clicked() {
	QString temp = ui.Find_Line->text();
	
	if (tree.find(tree.getroot(), temp))
	{

		QMessageBox::information(this, "Find", "Your element is found: " + tree.find(tree.getroot(), temp)->key + "!");
	}
	else {
		QMessageBox::warning(this, "Warning!", "Your element is not found!");
	}
	
	
}
