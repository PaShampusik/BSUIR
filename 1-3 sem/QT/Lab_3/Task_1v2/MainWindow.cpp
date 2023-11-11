#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Staff.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->tableWidget->hide();

	ui->List->hide();
	ui->Sort->hide();
	ui->lineEdit->hide();
	ui->lineEdit_5->hide();
	ui->SearchByName->hide();
	ui->SearchByNumber->hide();
	ui->pushButton_3->hide();
	ui->label_3->hide();
	ui->label_4->hide();
	ui->lineEdit_3->hide();
	ui->lineEdit_4->hide();
	ui->AddCustomer->hide();
	ui->DeleteCustomer->hide();
	ui->AddName->hide();
	ui->AddNumber->hide();
	ui->AddAddress->hide();
	ui->AddDate->hide();
	ui->lineEdit_7->hide();
	ui->addname->hide();
	ui->addprice->hide();
	ui->addgroup->hide();
	ui->AddCustomer->hide();
	ui->AddCustomer_2->hide();
	ui->Save->hide();
	ui->Experience->hide();
	ui->ExpSort->hide();
}


MainWindow::~MainWindow()
{
	delete ui;
}


int MainWindow::on_ShowTable_clicked()
{
	FilePath = QFileDialog::getOpenFileName(this, "Choose text file", "", "Input (*.txt);");
	while (!list_of_elements.isEmpty())
	{
		list_of_elements.nodes.pop_back();
	}

	ui->tableWidget->clearContents();

	std::ifstream file, file1;
	file.open(FilePath.toStdString());

	std::string buffer, Fullname, DepartmentNumber, Position, Date;
	int i = 0;
	if (file.is_open()) {
		/*for (int i = 0; i < 5 + x; i++)
		{*/

		while (!file.eof()) {
			getline(file, buffer);
			while (buffer == "" && !file.eof())
			{
				getline(file, buffer);
			}
			if (file.eof())
			{
				break;
			}

			strFullname = QString::fromStdString(buffer);
			getline(file, DepartmentNumber);
			getline(file, Position);
			getline(file, Date);
			//getline(file, buffer);
			strDepartmentNumber = QString::fromStdString(DepartmentNumber);
			strPosition = QString::fromStdString(Position);
			strDate = QString::fromStdString(Date);
			if (strDate.length() > 10 || strDepartmentNumber.contains("^\d+$") || strDate.contains("^\d+$") || strFullname.isEmpty() || strDate.isEmpty() || strFullname.isEmpty())
			{
				QMessageBox::critical(this, "Error", "You choosed the wrong input file!");
				list_of_elements.clear();
				return 1;
			}

			list_of_elements.add(Staff(strFullname, strDepartmentNumber, strPosition, strDate));

			QTableWidgetItem* itm = new QTableWidgetItem(strFullname);
			ui->tableWidget->setItem(i, 0, itm);
			strFullname.clear();


			QTableWidgetItem* itm1 = new QTableWidgetItem(strDepartmentNumber);
			ui->tableWidget->setItem(i, 1, itm1);
			strDepartmentNumber.clear();

			QTableWidgetItem* itm2 = new QTableWidgetItem(strPosition);
			ui->tableWidget->setItem(i, 2, itm2);
			strPosition.clear();

			QTableWidgetItem* itm3 = new QTableWidgetItem(strDate);
			ui->tableWidget->setItem(i, 3, itm3);
			strDate.clear();

			count = i;
			i++;
		}
		file.close();
	}

	temp_list.nodes = list_of_elements.nodes;


	ui->tableWidget->show();
	ui->Sort->show();
	ui->lineEdit->show();
	ui->lineEdit_5->show();
	ui->SearchByName->show();
	ui->SearchByNumber->show();
	ui->AddCustomer_2->show();
	ui->DeleteCustomer->show();
	ui->List->show();
	ui->Save->show();
	ui->Experience->show();
	ui->ExpSort->show();
	return 0;
}

void MainWindow::on_Sort_clicked() {
	ui->tableWidget->clearContents();
	ui->tableWidget->hide();
	list_of_elements.SortByNumber();
	filltablewithlist(list_of_elements);
	ui->tableWidget->show();
	QMessageBox::information(this, "Notification", "Your lists are sorted!");
}

void MainWindow::filltablewithlist(DoubleLinkedListOnArray& customerList) {
	if (customerList.isEmpty())
	{
		QMessageBox::warning(this, "Warning", "Be careful, you have no such customers");
	}
	else
	{
		QString Fullname, DepartmentNumber, Position, Date;
		for (int i = 0; i < customerList.nodes.size; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Fullname = customerList.nodes[i].product.fullname;
				DepartmentNumber = customerList.nodes[i].product.department_number;
				Position = customerList.nodes[i].product.position;
				Date = customerList.nodes[i].product.date;


				QTableWidgetItem* itm = new QTableWidgetItem(Fullname);
				ui->tableWidget->setItem(i, 0, itm);
				Fullname.clear();

				QTableWidgetItem* itm1 = new QTableWidgetItem(DepartmentNumber);
				ui->tableWidget->setItem(i, 1, itm1);
				DepartmentNumber.clear();

				QTableWidgetItem* itm2 = new QTableWidgetItem(Position);
				ui->tableWidget->setItem(i, 2, itm2);
				Position.clear();

				QTableWidgetItem* itm3 = new QTableWidgetItem(Date);
				ui->tableWidget->setItem(i, 3, itm3);
				Date.clear();
			}
		}
	}
	
}

void MainWindow::on_SearchByNumber_clicked() {
	ui->tableWidget->clearContents();
	ui->tableWidget->hide();
	list_of_elements.searchByNumber(ui->lineEdit->text(), list_of_elements);
	/*if (list_of_elements.isEmpty())
	{
		QMessageBox::warning(this, "Warning", "We have no such customer!");
	}*/
	filltablewithlist(list_of_elements);
	ui->tableWidget->show();
}

void MainWindow::on_SearchByName_clicked() {
	ui->tableWidget->clearContents();
	ui->tableWidget->hide();
	list_of_elements.searchByName(ui->lineEdit_5->text(), list_of_elements);
	/*if (list_of_elements.isEmpty())
	{
		QMessageBox::warning(this, "Warning", "We have no such customer!");
	}*/
	filltablewithlist(list_of_elements);
	ui->tableWidget->show();
}

void MainWindow::on_AddCustomer_clicked() {
	QString number, name, address, date;
	number = ui->AddNumber->text();
	name = ui->lineEdit_7->text();
	address = ui->AddAddress->text();
	date = ui->AddDate->text();
	if (number == "" || name == "" || address == "" || date == "")
	{
		QMessageBox::warning(this, "Error", "You havent filled some fields :(");
	}
	else {
		list_of_elements.add(Staff(number, name, address, date));
		temp_list.nodes = list_of_elements.nodes;
		/*list_of_elements.save(list_of_elements, FilePath);*/
		filltablewithlist(list_of_elements);
		x++;
	}
	ui->AddCustomer_2->setDisabled(0);
	ui->AddName->hide();
	ui->AddNumber->hide();
	ui->AddAddress->hide();
	ui->AddDate->hide();
	ui->lineEdit_7->hide();
	ui->addname->hide();
	ui->addprice->hide();
	ui->addgroup->hide();
	ui->AddCustomer->hide();
}

void MainWindow::on_pushButton_3_clicked() {
	QString number, name;
	number = ui->lineEdit_3->text();
	name = ui->lineEdit_4->text();
	if (name.isEmpty() || number.isEmpty())
	{
		QMessageBox::warning(this, "Error", "You havent filled some fields :(");
	}
	else
	{
		ui->tableWidget->clearContents();
		list_of_elements.deleteelementfromlist(ui->lineEdit_4->text(), ui->lineEdit_3->text());
		temp_list.nodes = list_of_elements.nodes;
		filltablewithlist(list_of_elements);
	}
	ui->DeleteCustomer->setDisabled(0);
	ui->pushButton_3->hide();


	ui->label_3->hide();
	ui->label_4->hide();
	ui->lineEdit_3->hide();
	ui->lineEdit_4->hide();
}

void MainWindow::on_AddCustomer_2_clicked() {
	ui->AddName->show();
	ui->AddNumber->show();
	ui->AddAddress->show();
	ui->AddDate->show();
	ui->lineEdit_7->show();
	ui->addname->show();
	ui->addprice->show();
	ui->addgroup->show();
	ui->AddCustomer->show();
	ui->AddCustomer_2->setDisabled(1);
}

void MainWindow::on_DeleteCustomer_clicked() {
	ui->pushButton_3->show();
	ui->label_3->show();
	ui->label_4->show();
	ui->lineEdit_3->show();
	ui->lineEdit_4->show();
	ui->DeleteCustomer->setDisabled(1);
}

void MainWindow::on_List_clicked() {
	ui->tableWidget->clearContents();
	ui->tableWidget->hide();
	list_of_elements.nodes = temp_list.nodes;
	filltablewithlist(list_of_elements);
	ui->tableWidget->show();
}

void MainWindow::on_Save_clicked() {
	list_of_elements.save(list_of_elements, FilePath);
}

void MainWindow::on_ExpSort_clicked() {
	ui->tableWidget->clearContents();
	list_of_elements.ExperienceSort(ui->Experience->text(), list_of_elements);
	filltablewithlist(list_of_elements);
	
}