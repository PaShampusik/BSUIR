#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Customer.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->tableWidget->hide();

	ui->List->hide();
	ui->AddNumber->setInputMask("00000000000");
	ui->AddDate->setInputMask("00.00.0000");
	ui->Sort->hide();
	ui->lineEdit->hide();
	ui->lineEdit_2->hide();
	ui->lineEdit_5->hide();
	ui->lineEdit_6->hide();
	ui->SearchByDate->hide();
	ui->SearchByName->hide();
	ui->SearchByNumber->hide();
	ui->pushButton_2->hide();
	ui->pushButton->hide();
	ui->ServedList->hide();
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
	ui->Clear->hide();
	ui->Save->hide();
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
		list_of_elements.deleteFromEnd();
	}

	ui->tableWidget->clearContents();

	std::ifstream file, file1;
	file.open(FilePath.toStdString());

	std::string buffer, Name, Group, Date, Address;
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

			strNumber = QString::fromStdString(buffer);
			getline(file, Name);
			getline(file, Address);
			getline(file, Date);
			getline(file, buffer);
			strFullname = QString::fromStdString(Name);
			strAddress = QString::fromStdString(Address);
			strDate = QString::fromStdString(Date);
			if (strNumber.length() > 10 || strDate.length() > 10 || strNumber.contains("^\d+$"))
			{
				QMessageBox::critical(this, "Error", "You choosed the wrong input file!");
				list_of_elements.clear();
				return 1;
			}

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
			i++;
		}
		file.close();
	}


	file1.open(FilePath2.toStdString());
	i = 0;
	if (file1.is_open()) {

		while (!file1.eof()) {
			getline(file1, buffer);
			while (buffer == "" && !file1.eof())
			{
				getline(file1, buffer);
			}
			if (file1.eof())
			{
				break;
			}

			strNumber = QString::fromStdString(buffer);
			getline(file1, Name);
			getline(file1, Address);
			getline(file1, Date);
			getline(file1, buffer);
			strFullname = QString::fromStdString(Name);
			strAddress = QString::fromStdString(Address);
			strDate = QString::fromStdString(Date);
			if (strNumber.length() > 10 || strDate.length() > 10 || strNumber.contains("^\d+$"))
			{
				QMessageBox::critical(this, "Error", "You choosed the wrong input file!");
				list_of_elements.clear();
				return 1;
			}

			list_of_complete_elements.insertAtEnd(new Node(new Customer(strNumber, strFullname, strAddress, strDate)));
		}
	}
	ui->tableWidget->show();
	ui->Sort->show();
	ui->lineEdit->show();
	ui->lineEdit_2->show();
	ui->lineEdit_5->show();
	ui->lineEdit_6->show();
	ui->SearchByDate->show();
	ui->SearchByName->show();
	ui->SearchByNumber->show();
	ui->pushButton_2->show();
	ui->pushButton->show();
	ui->ServedList->show();
	ui->AddCustomer_2->show();
	ui->DeleteCustomer->show();
	ui->List->show();
	ui->Clear->show();
	ui->Save->show();
	return 0;
}

void MainWindow::on_Sort_clicked() {
	ui->tableWidget->clearContents();
	ui->tableWidget->hide();
	list_of_elements.sort();
	list_of_complete_elements.sort();
	filltablewithlist(list_of_elements);
	ui->tableWidget->show();
	QMessageBox::information(this, "Notification", "Your lists are sorted!");
}

void MainWindow::filltablewithlist(DoubleLinkedList& customerList) {
	if (customerList.isEmpty())
	{
		QMessageBox::warning(this, "Warning", "Be careful, you have no such customers");
	}
	else {
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
}

void MainWindow::on_SearchByNumber_clicked() {
	ui->tableWidget->clearContents();
	ui->tableWidget->hide();
	filltablewithlist(list_of_elements.searchByNumber(ui->lineEdit->text()));
	ui->tableWidget->show();
}

void MainWindow::on_SearchByDate_clicked() {
	if (list_of_elements.searchByDate(ui->lineEdit_2->text()).isEmpty())
	{
		QMessageBox::warning(this, "Warning", "We have no such customer!");
	}
	else {

		ui->tableWidget->clearContents();
		ui->tableWidget->hide();
		//list_of_elements.searchByDate(ui->lineEdit_2->text());
		filltablewithlist(list_of_elements.searchByDate(ui->lineEdit_2->text()));
		ui->tableWidget->show();
	}
}

void MainWindow::on_SearchByName_clicked() {
	if (list_of_elements.searchByName(ui->lineEdit_5->text()).isEmpty())
	{
		QMessageBox::warning(this, "Warning", "We have no such customer!");
	}
	else {
		ui->tableWidget->clearContents();
		ui->tableWidget->hide();
		filltablewithlist(list_of_elements.searchByName(ui->lineEdit_5->text()));
		ui->tableWidget->show();

	}
}

void MainWindow::on_pushButton_2_clicked() {
	if (ui->lineEdit_6->text().isEmpty())
	{
		QMessageBox::warning(this, "Warning", "You havent entered number of customer!");
	}
	else
	{
		//searchByNumber(ui->lineEdit_6->text(), list_of_elements);
		if (list_of_elements.searchByNumber(ui->lineEdit_6->text()).isEmpty())
		{
			QMessageBox::warning(this, "Warning", "We have no such customer!");
		}
		else {

			ui->tableWidget->clearContents();
			ui->tableWidget->hide();
			list_of_complete_elements.copy(list_of_elements.searchByNumber(ui->lineEdit_6->text()));
			filltablewithlist(list_of_complete_elements);
			ui->tableWidget->show();
		}
	}
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
		list_of_elements.insertAtEnd(new Node(new Customer(number, name, address, date)));
		list_of_elements.save(list_of_elements, FilePath);
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

void MainWindow::on_pushButton_clicked() {
	ui->tableWidget->clearContents();
	ui->tableWidget->hide();
	filltablewithlist(list_of_complete_elements);
	ui->tableWidget->show();
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
		list_of_elements.deleteelementfromlist(name, number);
		ui->tableWidget->clearContents();
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

void MainWindow::on_ServedList_clicked() {
	list_of_complete_elements.save(list_of_complete_elements, FilePath2);
}

void MainWindow::on_List_clicked() {
	ui->tableWidget->clearContents();
	ui->tableWidget->hide();
	filltablewithlist(list_of_elements);
	ui->tableWidget->show();
}

void MainWindow::on_Clear_clicked() {
	list_of_complete_elements.clear();
	QMessageBox::information(this, "Success", "List of Complete customers is clear!");
}

void MainWindow::on_Save_clicked() {
	list_of_elements.save(list_of_elements, FilePath);
}