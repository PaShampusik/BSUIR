#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->tableWidget->hide();
    ui->AddItem->hide();
    ui->SearchByName->hide();
    ui->SearchByGroup->hide();
    ui->SearchByNameAndGroup->hide();
    ui->SortByPrice->hide();
    ui->AddAmount->hide();
    ui->AddPrice->hide();
    ui->AddGroup->hide();
    ui->AddName->hide();
    ui->AddStock->hide();
    ui->addname->hide();
    ui->addamount->hide();
    ui->addgroup->hide();
    ui->addprice->hide();
    ui->addstock->hide();
    ui->AddButton->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->pushButton->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->AddAmount->setInputMask("0000000000000000000000000000000000000000000000000000");
    ui->AddName->setInputMask("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    ui->AddGroup->setInputMask("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    ui->AddPrice->setInputMask("000000000000000000000000000000000000000000000000000000000");
    ui->AddStock->setInputMask("B");
    ui->lineEdit_2->setInputMask("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    ui->lineEdit->setInputMask("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->pushButton_3->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->pushButton_2->hide();
    ui->lineEdit_3->setInputMask("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    ui->lineEdit_4->setInputMask("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

  //  Items *items = new Items[8];



}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_ChooseFile_clicked()
{
    FilePath = QFileDialog::getOpenFileName(this, "Choose text file", "D:/QT/qtProjects/Details(task_4)", "Input (*.txt);");
    FilePath2 = QFileDialog::getOpenFileName(this, "Choose text file", "D:/QT/qtProjects/Details(task_4)", "Output (*.txt);");
    if (!FilePath.isEmpty())
    {
        ui->ChooseFile->setText(FilePath);
    }
}



void MainWindow::on_ShowTable_clicked()
{   ui->tableWidget->clearContents();
    if (FilePath.isEmpty())
    {
        ui->statusbar->showMessage("Выберите файл!");
    }
    if(!FilePath.isEmpty()){
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



    for(int i = 0; i < 8 + newitems; i++){

        strName = stream.readLine();
        items[i].name = strName;

        QTableWidgetItem *itm = new QTableWidgetItem(strName);
        ui->tableWidget->setItem(i, 0, itm);
        strName = "";

        amount = stream.readLine();
        Amount = amount.toInt();
        items[i].amount = Amount;

        QTableWidgetItem *itm2 = new QTableWidgetItem(amount);
        ui->tableWidget->setItem(i, 1, itm2);
        amount = "";

        items[i].group = stream.readLine();
        //items[i].group = strGroup;

        QTableWidgetItem *itm1 = new QTableWidgetItem(items[i].group);
        ui->tableWidget->setItem(i, 2, itm1);
       // strGroup = "";

        price = stream.readLine();
        Price = price.toInt();
        items[i].price = Price;

        QTableWidgetItem *itm3 = new QTableWidgetItem(price);
        ui->tableWidget->setItem(i, 3, itm3);
        price = "";

        onstock = stream.readLine();
        OnStock = onstock.toInt();
        items[i].onstock = OnStock;

        if(OnStock == 0)
        {
            onstock = "No";
        }else
        {
            onstock = "Yes";
        }

        QTableWidgetItem *itm4 = new QTableWidgetItem(items[i].Onstock());
        ui->tableWidget->setItem(i, 4, itm4);
        price = "";

     //   oof = stream.readLine();

    }
}
    if(newitems == 10)
    {
        ui->AddItem->setDisabled(1);
    }
}




void MainWindow::on_SortByPrice_clicked()
{
    Items temp;
        for (int i = 0; i < 8  + newitems - 1; i++)
        {
            for (int j = 0; j < 8 - i - 1 + newitems; j++)
            {
                if (items[j].price < items[j + 1].price)
                {
                    temp = items[j];
                    items[j] = items[j + 1];
                    items[j + 1] = temp;
                }
            }
        }
        ui->tableWidget->clearContents();
        for(int i = 8 + newitems - 1, k = 0; i >= 0; i--, k++){



            QTableWidgetItem *itm = new QTableWidgetItem(items[i].name);
            ui->tableWidget->setItem(k, 0, itm);

            QTableWidgetItem *itm1 = new QTableWidgetItem(items[i].group);
            ui->tableWidget->setItem(k, 1, itm1);

            QTableWidgetItem *itm2 = new QTableWidgetItem(items[i].Amount());
            ui->tableWidget->setItem(k, 2, itm2);

            QTableWidgetItem *itm3 = new QTableWidgetItem(items[i].Price());
            ui->tableWidget->setItem(k, 3, itm3);

            OnStock = items[i].Onstock().toInt();

            if(OnStock == 0)
            {
                onstock = "No";
            }else
            {
                onstock = "Yes";
            }

            QTableWidgetItem *itm4 = new QTableWidgetItem(items[i].Onstock());
            ui->tableWidget->setItem(i, 4, itm4);
            price = "";

        }
}

void MainWindow::on_SearchByName_clicked()
{
    name_wnd = new QDialog();
    name_wnd->setModal(true);
    name_wnd->resize(300, 230);
    QPushButton *edit = new QPushButton(name_wnd);
    edit->setText("Search this one");
    edit->move(95, 170);
    line = new QLineEdit(name_wnd);
    line->resize(200, 100);
    QFont font;
    font.setPointSize(18);
    line->setFont(font);
    line->move(50, 50);
    name_wnd->show();

    connect(edit, SIGNAL(clicked()), this, SLOT(name()));

}

void MainWindow::name()
{
    ui->tableWidget->clearContents();
    QString newname = line->text();
    int u = 0;


    for (int i = 0; i < 8 + newitems; i++)
    {
        if(items[i].name == newname)
        {
            QTableWidgetItem *itm = new QTableWidgetItem(items[i].name);
            ui->tableWidget->setItem(u, 0, itm);
            QTableWidgetItem *itm1 = new QTableWidgetItem(items[i].Amount());
            ui->tableWidget->setItem(u, 1, itm1);
            QTableWidgetItem *itm2 = new QTableWidgetItem(items[i].Group());
            ui->tableWidget->setItem(u, 2, itm2);
            QTableWidgetItem *itm3 = new QTableWidgetItem(items[i].Price());
            ui->tableWidget->setItem(u, 3, itm3);
            QTableWidgetItem *itm4 = new QTableWidgetItem(items[i].Onstock());
            ui->tableWidget->setItem(u, 4, itm4);
        }
    }
    if(u == 0)
    {
        QMessageBox::critical(this, "Error", "Are you from BNTU? Learn to write..");
    }

}


void MainWindow::on_AddItem_clicked()
{
    ui->tableWidget->resize(721, 381);
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->pushButton->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->AddAmount->show();
    ui->AddPrice->show();
    ui->AddGroup->show();
    ui->AddName->show();
    ui->AddStock->show();
    ui->addname->show();
    ui->addamount->show();
    ui->addgroup->show();
    ui->addprice->show();
    ui->addstock->show();
    ui->AddButton->show();

}

void MainWindow::on_AddButton_clicked()
{
    items = AddMemory(items, 8 + newitems);

    newitems++;

    QString addname = ui->AddName->text();
    items[8 + newitems - 1].name = addname;

    QString addgroup = ui->AddGroup->text();
    items[8 + newitems - 1].group = addgroup;

    QString addamount = ui->AddAmount->text();
    items[8 + newitems - 1].amount = addamount.toInt();

    QString addprice = ui->AddPrice->text();
    items[8 + newitems - 1].price = addprice.toInt();

    QString addonstock = ui->AddStock->text();
    items[8 + newitems - 1].onstock = addonstock.toInt();

    if(!addname.isEmpty() && !addamount.isEmpty() && !addgroup.isEmpty() && !addprice.isEmpty() && !addonstock.isEmpty()){
    std::fstream file_out;

    file_out.open(FilePath.toStdString(), std::fstream::out | std::fstream::app);

    file_out << items[8 + newitems - 1].Name().toStdString()<< std::endl;
    file_out << (items[8 + newitems - 1].Amount().toStdString()) << std::endl;
    file_out << (items[8 + newitems - 1].Group().toStdString()) << std::endl;
    file_out << (items[8 + newitems - 1].Price().toStdString()) << std::endl;
    file_out << (items[8 + newitems - 1].onstock) << std::endl;

    ui->statusbar->showMessage("Item successfully added to the list!");

    ui->AddAmount->clear();
    ui->AddPrice->clear();
    ui->AddGroup->clear();
    ui->AddName->clear();
    ui->AddStock->clear();
    ui->addname->hide();
    ui->addamount->hide();
    ui->addgroup->hide();
    ui->addprice->hide();
    ui->addstock->hide();
    ui->AddButton->hide();
    ui->AddAmount->hide();
    ui->AddPrice->hide();
    ui->AddGroup->hide();
    ui->AddName->hide();
    ui->AddStock->hide();

    file_out.close();
}else
    {
        QMessageBox::critical(this, "Error", "Are you from BNTU?");
    }


}

void MainWindow::on_SearchByGroup_clicked()
{
    name_wnd = new QDialog();
    name_wnd->setModal(true);
    name_wnd->resize(300, 230);
    QPushButton *edit = new QPushButton(name_wnd);
    edit->setText("Search by this GROUP");
    edit->move(85, 170);
    line = new QLineEdit(name_wnd);
    line->resize(200, 100);
    QFont font;
    font.setPointSize(18);
    line->setFont(font);
    line->move(50, 50);
    name_wnd->show();

    connect(edit, SIGNAL(clicked()), this, SLOT(group()));

}

void MainWindow::group()
{
    ui->tableWidget->clearContents();
    QString group = line->text();
    int u = 0;


    for (int i = 0; i < 8 + newitems; i++)
    {
        if(items[i].Group() == group)
        {
            QTableWidgetItem *itm = new QTableWidgetItem(items[i].name);
            ui->tableWidget->setItem(u, 0, itm);
            QTableWidgetItem *itm1 = new QTableWidgetItem(items[i].Amount());
            ui->tableWidget->setItem(u, 1, itm1);
            QTableWidgetItem *itm2 = new QTableWidgetItem(items[i].Group());
            ui->tableWidget->setItem(u, 2, itm2);
            QTableWidgetItem *itm3 = new QTableWidgetItem(items[i].Price());
            ui->tableWidget->setItem(u, 3, itm3);
            QTableWidgetItem *itm4 = new QTableWidgetItem(items[i].Onstock());
            ui->tableWidget->setItem(u, 4, itm4);
            u++;
        }
    }
    if(u == 0)
    {
        QMessageBox::critical(this, "Error", "Are you from BNTU? Learn to write..");
    }

}

Items* MainWindow::AddMemory(Items *items, int num)
{
    Items *items_temp = new Items[num + 1];

    for (int i = 0; i < num; i++)
    {
        items_temp[i] = items[i];
    }
    delete [] items;
    items = items_temp;

    return items;
}

Items* MainWindow::LessMemory(Items *items, int num)
{
    Items *items_temp = new Items[num - 1];

    for (int i = 0; i < num - 1; i++)
    {
        items_temp[i] = items[i];
    }
    delete [] items;
    items = items_temp;

    return items;
}




void MainWindow::on_SearchByNameAndGroup_clicked()
{
    ui->tableWidget->resize(721, 281);
    ui->AddAmount->hide();
    ui->AddPrice->hide();
    ui->AddGroup->hide();
    ui->AddName->hide();
    ui->AddStock->hide();
    ui->addname->hide();
    ui->addamount->hide();
    ui->addgroup->hide();
    ui->addprice->hide();
    ui->addstock->hide();
    ui->AddButton->hide();
    ui->lineEdit->show();
    ui->lineEdit_2->show();
    ui->pushButton->show();
    ui->label->show();
    ui->label_2->show();
}


void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->clearContents();
    QString name = ui->lineEdit->text();
    QString group = ui->lineEdit_2->text();

    int u = 0;


    for (int i = 0; i < 8 + newitems; i++)
    {
        if(items[i].Group() == group && items[i].Name() == name)
        {
            QTableWidgetItem *itm = new QTableWidgetItem(items[i].name);
            ui->tableWidget->setItem(u, 0, itm);
            QTableWidgetItem *itm1 = new QTableWidgetItem(items[i].Amount());
            ui->tableWidget->setItem(u, 1, itm1);
            QTableWidgetItem *itm2 = new QTableWidgetItem(items[i].Group());
            ui->tableWidget->setItem(u, 2, itm2);
            QTableWidgetItem *itm3 = new QTableWidgetItem(items[i].Price());
            ui->tableWidget->setItem(u, 3, itm3);
            QTableWidgetItem *itm4 = new QTableWidgetItem(items[i].Onstock());
            ui->tableWidget->setItem(u, 4, itm4);
            u++;
        }
    }
    if(u == 0)
    {
        QMessageBox::critical(this, "Error", "Are you from BNTU? Learn to write..");
    }
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->pushButton->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->tableWidget->resize(721, 381);

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit_3->show();
    ui->lineEdit_4->show();
    ui->pushButton_3->show();
    ui->label_3->show();
    ui->label_4->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    int k = -1;
    for(int i = 0; i < 8 + newitems; i++)
    {
        if (items[i].Name() == ui->lineEdit_3->text() && items[i].Group() == ui->lineEdit_4->text()){
            g = i;
            k++;
        }
    }
    if(k < 0){
        QMessageBox::critical(this, "Error", "Are you from BNTU? Learn to write..");
    }


    std::fstream fin;
    fin.open(FilePath.toStdString());
    std::fstream temp;
    temp.open(FilePath2.toStdString());




    while(!fin.eof()){
    //for (short i = 0; i < 4 + number_of_rows; ++i) {
        std::string str1 = "";
        std::string str2 = "";
        std::string str3 = "";
        std::string str4 = "";
        std::string str5 = "";
  //      std::string str6 = "";

        std::getline(fin, str1);
        std::getline(fin, str2);
        std::getline(fin, str3);
        std::getline(fin, str4);
        std::getline(fin, str5);
 //       std::getline(fin, str6);

        if(items[g].name.toStdString() == str1 && items[g].group.toStdString() == str3)
        {

        }else
        {
            temp << str1 << std::endl;
            temp << str2 << std::endl;
            temp << str3 << std::endl;
            temp << str4 << std::endl;
            temp << str5 << std::endl;
        }
    }
    fin.close();
    fin.open(FilePath.toStdString(), std::fstream::out | std::fstream::trunc);
    fin.close();
    fin.open(FilePath.toStdString());
    temp.seekg(0);
    fin.seekp(0);
    while(!temp.eof()){
        std::string str1 = "";
        std::getline(temp, str1);
            fin << str1 << std::endl;

   }
    fin.close();
    temp.close();
    temp.open(FilePath2.toStdString(), std::fstream::out | std::fstream::trunc);
    temp.close();
    newitems--;
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->pushButton_3->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->statusbar->showMessage("Deleting is complete!");
    items = LessMemory(items, 8 + newitems);

}
