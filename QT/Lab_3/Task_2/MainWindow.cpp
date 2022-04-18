#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui->setupUi(this);
	this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

MainWindow::~MainWindow() {
	
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
	Stack.clear();
	QString fileName = ui->ChooseFile->text();
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::information(this, tr("Unable to open file"),
			file.errorString());
		return;
	}
	QTextStream in(&file);
	QString line;
	bool x = 0, y = 0;
	int count = 0;
	while (!in.atEnd()) {
		line = in.readLine();
		ui->File->appendPlainText(line);
		std::string temp = line.toStdString();
		for (int i = 0; i < line.length(); i++)
		{
			if (temp[i] == '(' || temp[i] == '[' || temp[i] == '{')
			{
				//add element to stack
				Stack.push(count, i, temp[i]);
			}
			//if we meet it first time, it is mistake
			else if (temp[i] == ')' || temp[i] == ']' || temp[i] == '}')
			{
				if (Stack.isEmpty())
				{
					y = 0;
					x = 1;
					QMessageBox::critical(this, tr("Error"), tr("Mistake in line ") + QString::number(count + 1) + tr(" in symbol ") + QString::number(i + 1));
					break;
				}
				else
				{
					y = 1;
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
					/*else if (((Stack.gettop() == '(' || Stack.gettop() == '[') && temp[i] == '}') || ((Stack.gettop() == '(' || Stack.gettop() == '{') && temp[i] == ']') || ((Stack.gettop() == '{' || Stack.gettop() == '[') && temp[i] == ')'))
					{
						QMessageBox::critical(this, tr("Error"), tr("Mistake in line ") + QString::number(Stack.gettopline() + 1) + tr(" in symbol ") + QString::number(Stack.gettopcolumn() + 1));
					}*/
					else
					{
						x = 1;
						QMessageBox::critical(this, tr("Error!"), tr("Mistake in line ") + QString::number(count + 1) + tr(" in symbol ") + QString::number(i + 1));
						y = 0;
						break;
					}
				}
			}
		}
		if (x)
		{
			break;
		}
		count++;
	}
	
	if(!Stack.isEmpty() && y)
	{
		QMessageBox::critical(this, tr("Error"), tr("Mistake in line ") + QString::number(Stack.gettopline() + 1) + tr(" in symbol ") + QString::number(Stack.gettopcolumn() + 1));
		x = 1;
	}	
	
	if (!x)
	{
		QMessageBox::information(this, tr("Success!"), tr("Text has been successfully validated!"));
	}
	if (file.isOpen())
	{
		file.close();
	}
	
}

void MainWindow::on_CheckHandwriting_clicked() {
	
	Stack.clear();
	
	QString text;
	QStringList list_of_strings;
	QString line;
	bool x = 0, y = 0;
	int count = 0;
	text = ui->Handwriting->toPlainText();
	list_of_strings = text.split('\n');
	for (int i = 0; i < list_of_strings.size(); i++)
	{
		line = list_of_strings[i];
		std::string temp = line.toStdString();
		for (int i = 0; i < line.length(); i++)
		{
			if (temp[i] == '(' || temp[i] == '[' || temp[i] == '{')
			{
				//add element to stack
				y = 1;
				Stack.push(count, i, temp[i]);
			}
			//if we meet it first time, it is mistake
			else if (temp[i] == ')' || temp[i] == ']' || temp[i] == '}')
			{
				if (Stack.isEmpty())
				{
					y = 0;
					x = 1;
					QMessageBox::critical(this, tr("Error"), tr("Mistake in line ") + QString::number(count + 1) + tr(" in symbol ") + QString::number(i + 1));
					break;
				}
				else
				{
					y = 1;
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
					/*else if (((Stack.gettop() == '(' || Stack.gettop() == '[') && temp[i] == '}') || ((Stack.gettop() == '(' || Stack.gettop() == '{') && temp[i] == ']') || ((Stack.gettop() == '{' || Stack.gettop() == '[') && temp[i] == ')'))
					{
						QMessageBox::critical(this, tr("Error"), tr("Mistake in line ") + QString::number(Stack.gettopline() + 1) + tr(" in symbol ") + QString::number(Stack.gettopcolumn() + 1));
					}*/
					else
					{
						x = 1;
						QMessageBox::critical(this, tr("Error!"), tr("Mistake in line ") + QString::number(count + 1) + tr(" in symbol ") + QString::number(i + 1));
						y = 0;
						break;
					}
				}
			}
		}
		if (x)
		{
			break;
		}
		count++;
	}

	if (!Stack.isEmpty() && y)
	{
		QMessageBox::critical(this, tr("Error"), tr("Mistake in line ") + QString::number(Stack.gettopline() + 1) + tr(" in symbol ") + QString::number(Stack.gettopcolumn() + 1));
		x = 1;
	}

	if (!x)
	{
		QMessageBox::information(this, tr("Success!"), tr("Text has been successfully validated!"));
	}
}


void MainWindow::on_Quit_clicked() {
	
	QApplication::quit();
}
