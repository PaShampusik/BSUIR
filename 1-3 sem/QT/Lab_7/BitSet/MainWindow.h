#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "BitSet.h"
#include<qmessagebox.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private slots:
    void on_SetBitset_clicked();
    void on_All_clicked();
    void on_Any_clicked();
    void on_None_clicked();
    void on_Set_clicked();
    void on_SetPosition_clicked();
    void on_ResetPosition_clicked();
    void on_Reset_clicked();
    void on_Flip_clicked();
    void on_FlipPosition_clicked();
    void on_To_Ullong_clicked();
    void on_GetSize_clicked();	

private:
    Ui::MainWindowClass ui;
	Bitset<32> bitset;
};
