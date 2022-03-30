#include "MainWindow.h"

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
    ui->tableWidget->clearContents();
    if (FilePath.isEmpty())
    {
        ui->statusBar->showMessage("Âûבונטעו פאיכ!");
    }
    if (!FilePath.isEmpty()) {
        ui->tableWidget->show();
        ui->AddItem->show();
        ui->SearchByName->show();
        ui->SearchByGroup->show();
        ui->SearchByNameAndGroup->show();
        ui->SortByPrice->show();
        ui->pushButton_2->show();

        QFile file(FilePath);

        file.open(QFile::ReadOnly);

        QTextStream stream(&file);



        for (int i = 0; i < 8 + newitems; i++) {

            strName = stream.readLine();
            items[i].name = strName;

            QTableWidgetItem* itm = new QTableWidgetItem(strName);
            ui->tableWidget->setItem(i, 0, itm);
            strName = "";

            amount = stream.readLine();
            Amount = amount.toInt();
            items[i].amount = Amount;

            QTableWidgetItem* itm2 = new QTableWidgetItem(amount);
            ui->tableWidget->setItem(i, 1, itm2);
            amount = "";

            items[i].group = stream.readLine();
            //items[i].group = strGroup;

            QTableWidgetItem* itm1 = new QTableWidgetItem(items[i].group);
            ui->tableWidget->setItem(i, 2, itm1);
            // strGroup = "";

            price = stream.readLine();
            Price = price.toInt();
            items[i].price = Price;

            QTableWidgetItem* itm3 = new QTableWidgetItem(price);
            ui->tableWidget->setItem(i, 3, itm3);
            price = "";

            onstock = stream.readLine();
            OnStock = onstock.toInt();
            items[i].onstock = OnStock;

            if (OnStock == 0)
            {
                onstock = "No";
            }
            else
            {
                onstock = "Yes";
            }

            QTableWidgetItem* itm4 = new QTableWidgetItem(items[i].Onstock());
            ui->tableWidget->setItem(i, 4, itm4);
            price = "";
}
