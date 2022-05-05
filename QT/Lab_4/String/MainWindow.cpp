#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void MainWindow::on_memcpy_clicked()
{
    ui.lineEdit_16->setText("$$#");
	ui.memcpy->setDisabled(1);
}

void MainWindow::on_memmove_clicked() {
	
	ui.lineEdit_17->setText("$$#");
	ui.memmove->setDisabled(1);
}

void MainWindow::on_strcpy_clicked() {
	
	ui.lineEdit_18->setText("###");
	ui.strcpy->setDisabled(1);
}

void MainWindow::on_strncpy_clicked() {
	
	ui.lineEdit_19->setText("#");
	ui.strncpy->setDisabled(1);
}

void MainWindow::on_strcat_clicked() {
	
	ui.lineEdit_20->setText("$$###");
	ui.strcat->setDisabled(1);
}

void MainWindow::on_strncat_clicked() {
	
	ui.lineEdit_21->setText("$$##");
	ui.strncat->setDisabled(1);
}

void MainWindow::on_memcmp_clicked() {
	
	ui.lineEdit_22->setText(QString::number(memcmp("$$", "###", 2)));
	ui.memcmp->setDisabled(1);
}

void MainWindow::on_strcmp_clicked() {
	ui.lineEdit_23->setText("0");
	ui.strcmp->setDisabled(1);
}

void MainWindow::on_strcoll_clicked() {
	
	ui.lineEdit_24->setText(QString::number(strcoll("###", "$$")));
	ui.strcoll->setDisabled(1);
}

void MainWindow::on_strncmp_clicked() {
	
	ui.lineEdit_25->setText(QString::number(strncmp("$$", "###", 2)));
	ui.strncmp->setDisabled(1);
}

void MainWindow::on_strxfrm_clicked() {
	
	ui.lineEdit_26->setText("$$##");
	ui.strxfrm->setDisabled(1);
}

void MainWindow::on_strtok_clicked() {
	
	ui.lineEdit_27->setText("$$");
	ui.strtok->setDisabled(1);
}

void MainWindow::on_memset_clicked() {
	
	ui.lineEdit_28->setText("_##");
	ui.memset->setDisabled(1);
}

void MainWindow::on_strlen_clicked() {
	
	ui.lineEdit_15->setText("3");
	ui.strlen->setDisabled(1);
}



