#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDateTime>
#include <QDate>
#include <QMessageBox>
#include <QTextStream>
#include <QTextDecoder>
#include <QTextEdit>
#include <QLineEdit>
#include <fstream>
#include <iostream>
#include <string>
#include "date.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    void FindFile();
    void correctData();

    ~MainWindow();

private slots:

    void on_ChooseFile_clicked();
    void on_Enter_clicked();
    void on_ShowNextDays_clicked();
    void on_ShowPreviousDays_clicked();
    void on_ShowIsLeap_clicked();
    void on_ShowWeekNumbers_clicked();
    void on_ShowTillBirthday_clicked();
    void on_ShowDurations_clicked();
    void on_ChangeFile_clicked();
    void ChangeFiles();
    bool ProverOCHKA(QString &str);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:

    int number_of_rows = 0;
    QString buffer;
    Date *dates = new Date[9];
    Ui::MainWindow *ui;
    QString FilePath;
    QString birthday;
    QDialog *file_wnd;
    QString read_buffer;
    QTextEdit *input_here;
    QString newdate;
    QLineEdit *line;
    QString our_buffer;
};

#endif // MAINWINDOW_H
