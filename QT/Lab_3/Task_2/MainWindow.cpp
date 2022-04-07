#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);
}


void MainWindow::on_ChooseFile_clicked() {
	QString fileName = QFileDialog::getOpenFileName(this,
													tr("Open File"), "",
													tr("Text Files (*.txt)"));
	if (!fileName.isEmpty()) {
		ui->ChooseFile->setText(fileName);
	}
}


void MainWindow::on_CheckFile_clicked() {
	QString fileName = ui->ChooseFile->text();
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::information(this, tr("Unable to open file"),
			file.errorString());
		return;
	}
	QTextStream in(&file);
	QString line;
	bool x = 0;
	int count = 0;
	while (!in.atEnd()) {
		line = in.readLine();
		std::string temp = line.toStdString();
		for (int i = 0; i < line.length(); i++)
		{
			if (temp[i] == '(' || temp[i] == '[' || temp[i] == '{')
			{
				//add element to stack
				Stack.push(temp[i]);
			}
			//if we meet it first time, it is mistake
			else if (temp[i] == ')' || temp[i] == ']' || temp[i] == '}')
			{
				if (Stack.isEmpty())
				{
					x = 1;
					QMessageBox::critical(this, tr("Error"), tr("Mistake in line ") + QString::number(count + 1) + tr(" in symbol ") + QString(temp[i]));
					break;
				}
				else
				{
					//if we meet it second time, it is mistake
					if (Stack.gettop() == '(' && temp[i] == ')')
					{
						Stack.pop();
					}
					else if (Stack.gettop() == '[' && temp[i] == ']')
					{
						Stack.pop();
					}
					else if (Stack.gettop() == '{' && temp[i] == '}')
					{
						Stack.pop();
					}
					else
					{
						x = 1;
						QMessageBox::critical(this, tr("Error!"), tr("Mistake in line ") + QString::number(count + 1) + tr(" in symbol ") + QString(i);
						break;
					}
				}
			}
			count++;
		}
	}
	if (!x)
	{
		QMessageBox::information(this, tr("Success!"), tr("Text has been successfully validated!"));
	}
	file.close();
	
}

void MainWindow::on_CheckHandwriting_clicked() {
	if (auto x)
	{

	}
}
