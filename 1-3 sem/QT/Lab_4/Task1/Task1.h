#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Task1.h"

class Task1 : public QMainWindow
{
    Q_OBJECT

public:
    Task1(QWidget *parent = Q_NULLPTR);

private:
    Ui::Task1Class ui;
};
