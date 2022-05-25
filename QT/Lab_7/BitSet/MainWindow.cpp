#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void MainWindow::on_All_clicked() {
    if (bitset.all())
    {
        QMessageBox::information(this, "Info", "All bites are 1");
    }
    else {
		QMessageBox::warning(this, "Info", "Not All bites are 1");
    }
}
void MainWindow::on_Any_clicked() {
    if (bitset.any())
    {
        QMessageBox::information(this, "Info", "Bitset includes at least one 1");
    }
    else {
        QMessageBox::warning(this, "Info", "Not All bites are 0");
    }
}
void MainWindow::on_None_clicked() {
    if (bitset.none())
    {
        QMessageBox::information(this, "Info", "All bites are 0");
    }
    else {
        QMessageBox::warning(this, "Info", "Not All bites are 0");
    }
}
void MainWindow::on_Flip_clicked() {
    bitset.flip();
    ui.BitSet->setText(QString::fromStdString(bitset.to_string()));
}
void MainWindow::on_FlipPosition_clicked() {
    int pos = ui.FlipPositionLine->text().toInt();
    bitset.flip(pos - 1);
    ui.BitSet->setText(QString::fromStdString(bitset.to_string()));
}
void MainWindow::on_Set_clicked() {
    bitset.set();
    ui.BitSet->setText(QString::fromStdString(bitset.to_string()));
}
void MainWindow::on_SetPosition_clicked() {
    int pos = ui.SetPositionLine->text().toInt();
    bitset.set(pos - 1);
    ui.BitSet->setText(QString::fromStdString(bitset.to_string()));
}
void MainWindow::on_Reset_clicked() {
    bitset.reset();
    ui.BitSet->setText(QString::fromStdString(bitset.to_string()));
}
void MainWindow::on_ResetPosition_clicked() {
    int pos = ui.ResetPositionLine->text().toInt();
	bitset.reset(pos - 1);
	ui.BitSet->setText(QString::fromStdString(bitset.to_string()));
}
void MainWindow::on_GetSize_clicked() {
    ui.GetSizeLine->setText(QString::number(bitset.get_size()));
}
void MainWindow::on_To_Ullong_clicked() {
    ui.To_UllongLine->setText(QString::number(bitset.to_ullong()));
}

void MainWindow::on_SetBitset_clicked() {
    QString temp = ui.SetBitsetLine->text();
    bitset = temp.toInt();
    ui.BitSet->setText(QString::fromStdString(bitset.to_string()));	
}