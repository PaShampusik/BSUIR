#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void MainWindow::on_All_clicked() {
	
}
void MainWindow::on_Any_clicked() {

}
void MainWindow::on_None_clicked() {

}
void MainWindow::on_Flip_clicked() {
    bitset.flip();
    ui.BitSet->setText(QString::fromStdString(bitset.to_string()));
}
void MainWindow::on_FlipPosition_clicked() {
    int pos = ui.FlipPositionLine->text().toInt();
    bitset.flip(pos);
    ui.BitSet->setText(QString::fromStdString(bitset.to_string()));
}
void MainWindow::on_Set_clicked() {
    bitset.set();
    ui.BitSet->setText(QString::fromStdString(bitset.to_string()));
}
void MainWindow::on_SetPosition_clicked() {
    int pos = ui.SetPositionLine->text().toInt();
    bitset.set(pos);
    ui.BitSet->setText(QString::fromStdString(bitset.to_string()));
}
void MainWindow::on_Reset_clicked() {
    bitset.reset();
    ui.BitSet->setText(QString::fromStdString(bitset.to_string()));
}
void MainWindow::on_ResetPosition_clicked() {
    int pos = ui.ResetPositionLine->text().toInt();
	bitset.reset(pos);
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