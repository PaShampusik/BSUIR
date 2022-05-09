#include "mainwindow.h"

mainwindow::mainwindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.lineEdit, &QLineEdit::textChanged, this, &mainwindow::lineEditChange);
}

void mainwindow::lineEditChange()
{
	ui.pushButton->setDisabled(0);
}

void mainwindow::on_pushButton_clicked()
{
	ui.lineEdit_2->clear();
	ui.pushButton->setDisabled(1);
	if (ui.lineEdit->text().isEmpty())
	{
		QMessageBox::warning(this, "Error!", "Incorrect input!");
		return;
	}
	QString str = ui.lineEdit->text();
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			QMessageBox::warning(this, "Error!", "Incorrect input!");
			return;
		}
	}
	int number = ui.lineEdit->text().toInt();
	if (number < 1 || number > 10000)
	{
		QMessageBox::warning(this, "Error!", "Incorrect input!");
		return;
	}
	decimal(number);


}
int validLength(const std::string& a)
{
	int length = 0;
	for (; a[length] != '\0'; length++);
	return(length);
}


bool search_for_bit(std::string number, int k)
{
	int bit, i = 0;
	int str_length = validLength(number);
	for (; i != (k); i++)
	{
		bit = (number[str_length - 1] - '0') % 2;
		number[str_length - 1] = number[str_length - 1] - bit;
		for (int j = str_length - 1; j >= 0; j--)
		{
			if ((number[j] - '0') % 2 == 0)
			{
				number[j] = (number[j] - '0') / 2 + '0';
			}
			else
			{
				number[j] = (number[j] - '0') / 2 + '0';
				if (j != str_length - 1)
				{
					number[j + 1] = number[j + 1] + 5;
				}
			}
		}
	}
	return(bit);
}



std::string pow_number(const std::string& data, int k)
{
	std::string new_data = "1";
	if (k == 0)
	{
		return("1");
	}
	for (int i = 0; i < k; i++)
	{
		new_data += '0';
	}
	for (int i = validLength(new_data) - 1, j = validLength(data) - 1; i >= 0 && j >= 0; i--, j--)
	{
		new_data[i] = data[j];
	}
	return(new_data);
}


void mainwindow::decimal(int n)
{
	std::string* first = new std::string[10000];
	std::string* second = new std::string[10000];
	first[0] = "0";
	int counterB = 0, counterA = 1, k = 1, counterBIN = 1, tmp;
	while (n >= counterBIN)
	{
		tmp = counterB = 0;
		for (int i = 0; i < counterA; i++)
		{
			if (!search_for_bit(first[i], k))
			{
				first[tmp] = first[i];
				tmp++;
			}
		}
		counterA = tmp;
		for (int i = 0; i < counterA; i++)
		{
			second[i] = pow_number(first[i], k - 1);
			counterB++;
		}
		for (int i = 0; i < counterB; i++)
		{
			first[counterA] = second[i];
			counterA++;
		}
		counterBIN += counterB;
		k++;
	}
	ui.lineEdit_2->insert(QString::fromStdString(second[counterB - (counterBIN - n)]));

	//std::cout << B[counterB - (counterBIN - n)];
	delete[] first;
	delete[] second;
}