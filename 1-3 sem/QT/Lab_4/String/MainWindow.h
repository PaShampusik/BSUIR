#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "MyString.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private slots:
    void on_memcpy_clicked();
	void on_memmove_clicked();
	void on_memset_clicked();
	void on_strcpy_clicked();
	void on_strncpy_clicked();
	void on_strcat_clicked();
	void on_strncat_clicked();
	void on_memcmp_clicked();
	void on_strcmp_clicked();
	void on_strncmp_clicked();
	void on_strcoll_clicked();
	void on_strxfrm_clicked();
	void on_strtok_clicked();
	void on_strlen_clicked();
	
private:
    Ui::MainWindow ui;
    MyString str = "Hello, that's my first string";
	
};
