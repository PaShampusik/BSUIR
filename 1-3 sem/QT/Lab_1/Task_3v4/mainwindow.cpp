#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->Table->hide();
    ui->ShowDurations->hide();
    ui->ShowIsLeap->hide();
    ui->ShowNextDays->hide();
    ui->ShowPreviousDays->hide();
    ui->ShowTillBirthday->hide();
    ui->ShowWeekNumbers->hide();
    ui->ChangeFile->hide();
    ui->label->hide();
    ui->pushButton_2->hide();
    ui->lineEdit->hide();
    ui->pushButton->hide();


}

bool MainWindow::ProverOCHKA(QString &str)
{
    QString year = str;
    year.remove(0, 6);
    while (year[0] == '0')
        year.remove(0, 1);

    QString month = str;
    month.remove(0, 3); month.remove(2, 5);
    if (month[0] == '0') month.remove(0, 1);

    QString day = str;
    day.remove(2, 8);
    if (day[0] == '0') day.remove(0, 1);

    if(str == "")
    {
        return false;
    }
    else if(year.toInt() > 9999 || year.toInt() < 1)
    {
       // QMessageBox::critical(this, "Ошибка", "Формат ввода:\ndd.mm.yyyy");
        return false;
    }
    else if(month.toInt() > 12 || month.toInt() < 1)
    {
       // QMessageBox::critical(this, "Ошибка", "Формат ввода:\ndd.mm.yyyy");
        return false;
    }
    else if(day.toInt() < 1 || day.toInt() > 31)
    {
       // QMessageBox::critical(this, "Ошибка", "Формат ввода:\ndd.mm.yyyy");
        return false;
    }

    return true;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_ChooseFile_clicked()
{
    FilePath = QFileDialog::getOpenFileName(this, "Choose text file", "D:/QT/qtProjects/Task_3v4", "Dates (*.txt);");
    if (!FilePath.isEmpty())
    {
        ui->ChooseFile->setText(FilePath);
    }
}


void MainWindow::on_Enter_clicked()
{
    ui->pushButton_2->hide();
    ui->lineEdit->hide();
    ui->pushButton->hide();
    ui->Table->resize(941, 411);
    birthday = ui->EnterBirthday->text();
    if (!ProverOCHKA(birthday) && (!birthday.isEmpty()))
    {
        QMessageBox::critical(this, "Ошибка", "Формат ввода:\ndd.mm.yyyy");
    }
    else if (FilePath.isEmpty())
    {
        ui->statusbar->showMessage("Выберите файл!");
    }
    else
    {
        if(birthday.isEmpty())
        {
            birthday = "10.03.2003";
        }
        ui->Table->show();
        ui->ShowDurations->show();
        ui->ShowIsLeap->show();
        ui->ShowNextDays->show();
        ui->ShowPreviousDays->show();
        ui->ShowTillBirthday->show();
        ui->ShowWeekNumbers->show();
        ui->ChangeFile->show();
        ui->pushButton->show();

    ui->Table->clearContents();
    std::ifstream file;

    file.open(FilePath.toStdString());

//    QTextStream stream(&file);
//    QString buffer;
    int i = 0;
    while(!file.eof()){
    //for (short i = 0; i < 4 + number_of_rows; ++i) {
        std::string str = "";
        std::getline(file, str);
        if(str == ""){

        }else{
            for(int j = 0; j < str.size(); j++){
                buffer[j] = str[j];
            }
        dates[i].setData(buffer, birthday);

        QTableWidgetItem *itm = new QTableWidgetItem(buffer);
        ui->Table->setItem(i, 0, itm);
        buffer = "";
        i++;}
    }

    file.close();
}
}

void MainWindow::on_ShowNextDays_clicked()
{
    for (short i = 0; i < 4 + number_of_rows; ++i)
        {
            buffer = dates[i].NextDay();
            QTableWidgetItem *itm = new QTableWidgetItem(buffer);
            ui->Table->setItem(i, 1, itm);
            buffer = "";
        }
}


void MainWindow::on_ShowPreviousDays_clicked()
{
    for (short i = 0; i < 4 + number_of_rows; ++i)
    {
        buffer = dates[i].PreviousDay();
        QTableWidgetItem *itm = new QTableWidgetItem(buffer);
        ui->Table->setItem(i, 2, itm);
        buffer = "";
    }
}


void MainWindow::on_ShowIsLeap_clicked()
{
    for (short i = 0; i < 4 + number_of_rows; ++i)
    {
        if(dates[i].isLeap() == true)
        {
            buffer = "Yes";
        }else
        {
            buffer = "No";
        }
        QTableWidgetItem *itm = new QTableWidgetItem(buffer);
        ui->Table->setItem(i, 3, itm);
        buffer = "";
    }
}


void MainWindow::on_ShowWeekNumbers_clicked()
{
    for (short i = 0; i < 4 + number_of_rows; ++i)
    {
        QString buffer = QString::number(dates[i].WeekNumber());
        QTableWidgetItem *itm = new QTableWidgetItem(buffer);
        ui->Table->setItem(i, 4, itm);
        buffer = "";
    }
}


void MainWindow::on_ShowTillBirthday_clicked()
{
    for (short i = 0; i < 4 + number_of_rows; ++i)
    {
        QString buffer = QString::number(dates[i].DaysTillYourBirthday(birthday));
        QTableWidgetItem *itm = new QTableWidgetItem(buffer);
        ui->Table->setItem(i, 5, itm);
        buffer = "";
    }
}


void MainWindow::on_ShowDurations_clicked()
{
    for (short i = 0; i < 4 + number_of_rows; ++i)
    {
        QString buffer = QString::number(dates[i].Duration());
        QTableWidgetItem *itm = new QTableWidgetItem(buffer);
        ui->Table->setItem(i, 6, itm);
        buffer = "";
    }
}

void MainWindow::correctData()
{
    file_wnd = new QDialog();
    file_wnd->setModal(true);
    file_wnd->resize(300, 230);
    QPushButton *edit = new QPushButton(file_wnd);
    edit->setText("Add this one");
    edit->move(110, 170);
    line = new QLineEdit(file_wnd);
    line->resize(200, 100);
    QFont font;
    font.setPointSize(18);
    line->setFont(font);
    line->move(50, 50);
    file_wnd->show();

    connect(edit, SIGNAL(clicked()), this, SLOT(ChangeFiles()));
}

void MainWindow::ChangeFiles(){

    newdate = line->text();

    if ((!ProverOCHKA(newdate) && (!newdate.isEmpty())) || newdate == "")
    {
        QMessageBox::critical(this, "Ошибка", "Формат ввода:\ndd.mm.yyyy");
    }
    else if (FilePath.isEmpty())
    {
        ui->statusbar->showMessage("Выберите файл!");
    }
    else if(newdate != "")
    {
        std::fstream file_out;
        file_out.open(FilePath.toStdString(), std::fstream::out | std::fstream::app);
        file_out << (newdate.toStdString()) << std::endl;
        number_of_rows++;
        if(number_of_rows == 5)
        {
            ui->ChangeFile->setDisabled(1);
        }
        file_out.close();
        file_wnd->close();
    }

}

void MainWindow::on_ChangeFile_clicked()
{
    correctData();
}




void MainWindow::on_pushButton_clicked()
{
    ui->label->show();
    ui->pushButton_2->show();
    ui->lineEdit->show();
    ui->Table->resize(941, 300);
}

void MainWindow::on_pushButton_2_clicked()
{
    int u = -1;

    QString buffer = ui->lineEdit->text();
    if (!ProverOCHKA(buffer) && (!buffer.isEmpty()))
    {
        QMessageBox::critical(this, "Ошибка", "Формат ввода:\ndd.mm.yyyy");
    }
    else
    {
        for(int i = 0; i < 9; i++)
        {
            if(dates[i].date == buffer)
            {
                u = i;
            }
        }
        if(u >= 0){
            for(int i = 0; i < 9; i++)
        {
            if(i >= u && i != 8){
                dates[i] = dates[i + 1];
            }
        }
        }
        std::fstream file_out;
        file_out.open(FilePath.toStdString(), std::fstream::out | std::fstream::trunc);
        file_out.close();
        file_out.open(FilePath.toStdString(), std::fstream::out | std::fstream::app);
        for(int i = 0; i < 8; i++)
        {
            file_out << dates[i].date.toStdString() << std::endl;
        }
        number_of_rows--;
        ui->statusbar->showMessage("Deleting complete!");
    }
    ui->label->hide();
    ui->pushButton_2->hide();
    ui->lineEdit->hide();
}


