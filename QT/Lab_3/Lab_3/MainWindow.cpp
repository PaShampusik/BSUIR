#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Customer.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->tableWidget->hide();

}


MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_ShowTable_clicked()
{
	while(!list_of_elements.isEmpty())
	{
		list_of_elements.deleteFromEnd();
	}
	
	ui->tableWidget->clearContents();
	
	std::ifstream file;
	file.open(FilePath.toStdString());
	
	std::string buffer, Name, Group, Date, Address;

	if (file.is_open()) {
		for (int i = 0; i < 5 + x; i++)
		{
			getline(file, buffer);
			while (buffer == "")
			{
				getline(file, buffer);
			}
			
			strNumber = QString::fromStdString(buffer);
			getline(file, Name);
			getline(file, Address);
			getline(file, Date);
			getline(file, buffer);
			strFullname = QString::fromStdString(Name);
			strAddress = QString::fromStdString(Address);
			strDate = QString::fromStdString(Date);
			
			list_of_elements.insertAtEnd(new Node(new Customer(strNumber, strFullname, strAddress, strDate)));

			QTableWidgetItem* itm = new QTableWidgetItem(strNumber);
			ui->tableWidget->setItem(i, 0, itm);
			strNumber.clear();

			QTableWidgetItem* itm1 = new QTableWidgetItem(strFullname);
			ui->tableWidget->setItem(i, 1, itm1);
			strFullname.clear();

			QTableWidgetItem* itm2 = new QTableWidgetItem(strAddress);
			ui->tableWidget->setItem(i, 2, itm2);
			strAddress.clear();

			QTableWidgetItem* itm3 = new QTableWidgetItem(strDate);
			ui->tableWidget->setItem(i, 3, itm3);
			strDate.clear();
			
			count = i;
		}
		file.close();
		ui->tableWidget->show();
	}
}

void MainWindow::on_Sort_clicked() {
	ui->tableWidget->clearContents();
	ui->tableWidget->hide();
	list_of_elements.sort();
	list_of_complete_elements.sort();
	filltablewithlist(list_of_elements);
	ui->tableWidget->show();
}

void MainWindow::filltablewithlist(DoubleLinkedList& customerList) {
	int i = 0;
	for (const auto& it : customerList) {
		QTableWidgetItem* itm = new QTableWidgetItem(it.data->getnumber());
		ui->tableWidget->setItem(i, 0, itm);
		QTableWidgetItem* itm1 = new QTableWidgetItem(it.data->getname());
		ui->tableWidget->setItem(i, 1, itm1);
		QTableWidgetItem* itm2 = new QTableWidgetItem(it.data->getaddress());
		ui->tableWidget->setItem(i, 2, itm2);
		QTableWidgetItem* itm3 = new QTableWidgetItem(it.data->getdate());
		ui->tableWidget->setItem(i, 3, itm3);
		i++;
	}
}

void MainWindow::on_SearchByNumber_clicked() {
	ui->tableWidget->clearContents();
	ui->tableWidget->hide();
	DoubleLinkedList::searchByNumber(ui->lineEdit->text(), list_of_elements);
	filltablewithlist(list_of_elements);
	ui->tableWidget->show();
}

void MainWindow::on_SearchByDate_clicked() {
	ui->tableWidget->clearContents();
	ui->tableWidget->hide();
	list_of_elements.searchByDate(ui->lineEdit_2->text());
	filltablewithlist(list_of_elements);
	ui->tableWidget->show();
}

void MainWindow::on_SearchByName_clicked() {
	ui->tableWidget->clearContents();
	ui->tableWidget->hide();
	list_of_elements.searchByName(ui->lineEdit_5->text());
	filltablewithlist(list_of_elements);
	ui->tableWidget->show();
}

void MainWindow::on_pushButton_2_clicked() {
	ui->tableWidget->clearContents();
	ui->tableWidget->hide();
	DoubleLinkedList::searchByNumber(ui->lineEdit_6->text(), list_of_elements);
	list_of_complete_elements.copy(list_of_elements);
	filltablewithlist(list_of_complete_elements);
	ui->tableWidget->show();
}

void MainWindow::on_AddCustomer_clicked() {
	QString number, name, address, date;
	number = ui->AddNumber->text();
	name = ui->AddName->text();
	address = ui->AddAddress->text();
	date = ui->AddDate->text();
	list_of_elements.insertAtEnd(new Node(new Customer(number, name, address, date)));
	list_of_elements.save(list_of_elements, FilePath);
	filltablewithlist(list_of_elements);
	x++;

}

void MainWindow::on_pushButton_clicked() {
	ui->tableWidget->clearContents();
	ui->tableWidget->hide();
	filltablewithlist(list_of_complete_elements);
	ui->tableWidget->show();
}

