#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.Table->hide();
	ui.ShowVariables->hide();
	ui.ShowExpressions->hide();
	ui.CalculateResults->hide();
	ui.CalculateYourResult->hide();
	ui.Table2->hide();

	for (int i = 0; i < 15; i++)
	{
		ui.Table->item(i, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
	}
	for (int i = 0; i < 15; i++)
	{
		ui.Table->item(i, 6)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
	}
	expressions[0] = QString::QString("a / (b - c) * (d + e)");
	expressions[1] = QString::QString("(a + b) * (c - d) / e");
	expressions[2] = QString::QString("a - (b + c * d) / e");
	expressions[3] = QString::QString("a / b - ((c + d) * e)");
	expressions[4] = QString::QString("a * (b - c + d) / e");
	expressions[5] = QString::QString("(a + b) * (c - d) / e");
	expressions[6] = QString::QString("a * (b - c) / (d + e)");
	expressions[7] = QString::QString("a / (b * (c + d)) - e");
	expressions[8] = QString::QString("(a + (b / c - d)) * e");
	expressions[9] = QString::QString("a * (b + c) / (d - e)");
	expressions[10] = QString::QString("a - (b / c * (d + e))");
	expressions[11] = QString::QString("(a - b) / (c + d) * e");
	expressions[12] = QString::QString("a / (b + c - d * e)");
	expressions[13] = QString::QString("a * (b - c) / (d + e)");
	expressions[14] = QString::QString("(a + b * c) / (d - e)");

	variables[0][0] = "8.6"; variables[0][1] = "2.4"; variables[0][2] = "5.1"; variables[0][3] = "0.3"; variables[0][4] = "7.9";
	variables[1][0] = "7.4"; variables[1][1] = "3.6"; variables[1][2] = "2.8"; variables[1][3] = "9.5"; variables[1][4] = "0.9";
	variables[2][0] = "3.1"; variables[2][1] = "5.4"; variables[2][2] = "0.2"; variables[2][3] = "9.6"; variables[2][4] = "7.8";
	variables[3][0] = "1.2"; variables[3][1] = "0.7"; variables[3][2] = "9.3"; variables[3][3] = "6.5"; variables[3][4] = "8.4";
	variables[4][0] = "9.7"; variables[4][1] = "8.2"; variables[4][2] = "3.6"; variables[4][3] = "4.1"; variables[4][4] = "0.5";
	variables[5][0] = "0.8"; variables[5][1] = "4.1"; variables[5][2] = "7.9"; variables[5][3] = "6.2"; variables[5][4] = "3.5";
	variables[6][0] = "1.6"; variables[6][1] = "4.9"; variables[6][2] = "5.7"; variables[6][3] = "0.8"; variables[6][4] = "2.3";
	variables[7][0] = "8.5"; variables[7][1] = "0.3"; variables[7][2] = "2.4"; variables[7][3] = "7.9"; variables[7][4] = "1.6";
	variables[8][0] = "5.6"; variables[8][1] = "7.4"; variables[8][2] = "8.9"; variables[8][3] = "3.1"; variables[8][4] = "0.2";
	variables[9][0] = "0.4"; variables[9][1] = "2.3"; variables[9][2] = "6.7"; variables[9][3] = "5.8"; variables[9][4] = "9.1";
	variables[10][0] = "5.6"; variables[10][1] = "3.2"; variables[10][2] = "0.9"; variables[10][3] = "1.7"; variables[10][4] = "4.8";
	variables[11][0] = "0.3"; variables[11][1] = "6.7"; variables[11][2] = "8.4"; variables[11][3] = "9.5"; variables[11][4] = "1.2";
	variables[12][0] = "7.6"; variables[12][1] = "4.8"; variables[12][2] = "3.5"; variables[12][3] = "9.1"; variables[12][4] = "0.2";
	variables[13][0] = "0.5"; variables[13][1] = "6.1"; variables[13][2] = "8.9"; variables[13][3] = "2.4"; variables[13][4] = "7.3";
	variables[14][0] = "9.1"; variables[14][1] = "0.6"; variables[14][2] = "2.4"; variables[14][3] = "3.7"; variables[14][4] = "8.5";
}

void MainWindow::on_ShowTable_clicked() {
	ui.ShowTable->setDisabled(1);
	ui.Table->show();
	ui.ShowExpressions->show();
}

void MainWindow::on_ShowExpressions_clicked() {
	ui.ShowExpressions->setDisabled(1);
	ui.ShowVariables->show();

	for (int i = 0; i < 15; i++)
	{
		QTableWidgetItem* itm = new QTableWidgetItem(expressions[i]);
		ui.Table->setItem(i, 0, itm);
	}
}

void MainWindow::on_ShowVariables_clicked() {
	ui.ShowVariables->setDisabled(1);
	ui.CalculateResults->show();
	for (int i = 0; i < 15; i++)
	{
		for (int j = 1; j < 6; j++)
		{
			QTableWidgetItem* itm = new QTableWidgetItem(variables[i][j - 1]);
			ui.Table->setItem(i, j, itm);
		}
	}

}

void MainWindow::on_CalculateResults_clicked() {
	//ui.CalculateResults->setDisabled(1);
	QString buffer;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 1; j < 6; j++)
		{
			buffer = ui.Table->item(i, j)->text();
			variables[i][j - 1] = buffer;
		}
	}
	for (int i = 0; i < 15; i++)
	{
		double result = calculate(expressions[i], variables[i]);
		Stack.clear();
		Queue.clear();
		QTableWidgetItem* itm = new QTableWidgetItem(QString::QString::number(result));
		ui.Table->setItem(i, 6, itm);
	}
	ui.CalculateYourResult->show();
	ui.Table2->show();
}

double MainWindow::calculate(QString expression, QString variables[]) {
	double result = 0;
	std::string oof;
	std::string line = expression.toStdString();
	for (int i = 0; i < line.length(); i++)
	{

		oof = line[i];
		if (oof == " ")
		{
			continue;
		}
		if (line[i] == 'a' || line[i] == 'b' || line[i] == 'c' || line[i] == 'd' || line[i] == 'e')
		{
			Queue.enqueue(QString::QString(line[i]));
		}
		/*else if (line[i] == 'b')
		{
			Queue.enqueue(variables[1]);
		}
		else if (line[i] == 'c')
		{
			Queue.enqueue(variables[2]);
		}
		else if (line[i] == 'd')
		{
			Queue.enqueue(variables[3]);
		}
		else if (line[i] == 'e')
		{
			Queue.enqueue(variables[4]);
		}*/
		if (line[i] == '+' || line[i] == '-' || line[i] == '/' || line[i] == '*')
		{
			if (Stack.isEmpty() || (!(Stack.isEmpty()) && Stack.gettop() == '('))
			{
				Stack.push(QString::QString(line[i]));
			}
			else if (!Stack.isEmpty() && CompareValues(oof, Stack.gettop().toStdString()) == 1)
			{
				Stack.push(QString::fromStdString(oof));
			}
			else if (!Stack.isEmpty() && CompareValues(oof, Stack.gettop().toStdString()) == 0)
			{
				while (!Stack.isEmpty() && (CompareValues(oof, Stack.gettop().toStdString()) == 0 || Stack.gettop() != "("))
				{
					Queue.enqueue(Stack.pop());
				}
				Stack.push(QString::fromStdString(oof));
			}
		}
		if (line[i] == '(')
		{
			Stack.push(QString::fromStdString(oof));
		}
		if (line[i] == ')')
		{
			while (!Stack.isEmpty() && Stack.gettop() != '(') {
				Queue.enqueue(Stack.pop());
			}
			Stack.pop();
		}
	}
	while (!Stack.isEmpty()) {
		Queue.enqueue(Stack.pop());
	}
	oof = "";
	while (!Queue.isEmpty()) {
		oof.append(Queue.dequeue());
	}
	double Result = 0;
	for (int i = 0; i < oof.length(); i++)
	{
		if (oof[i] == 'a')
		{
			Stack.push(QString::QString(variables[0]));
		}

		else if (oof[i] == 'b')
		{
			Stack.push(QString::QString(variables[1]));
		}
		else if (oof[i] == 'c')
		{
			Stack.push(QString::QString(variables[2]));
		}
		else if (oof[i] == 'd')
		{
			Stack.push(QString::QString(variables[3]));
		}
		else if (oof[i] == 'e')
		{
			Stack.push(QString::QString(variables[4]));
		}
		if (oof[i] == '*' || oof[i] == '/' || oof[i] == '+' || oof[i] == '-')
		{
			QString num1 = Stack.pop();
			QString num2 = Stack.pop();


			if (oof[i] == '*')
			{
				result = num1.toDouble() * num2.toDouble();
				Stack.push(QString::number(result));
			}
			else if (oof[i] == '/')
			{
				result = num2.toDouble() / num1.toDouble();
				Stack.push(QString::number(result));
			}
			else if (oof[i] == '+')
			{
				result = num1.toDouble() + num2.toDouble();
				Stack.push(QString::number(result));
			}
			else if (oof[i] == '-')
			{
				result = num2.toDouble() - num1.toDouble();
				Stack.push(QString::number(result));
			}
		}
	}

	return Stack.pop().toDouble();

}

int MainWindow::CompareValues(std::string char1, std::string char2) {
	int value1 = 5;
	int value2 = 5;

	if (char1 == "*" || char1 == "/")
	{
		value1 = 2;
	}
	else if (char1 == "+" || char1 == "-")
	{
		value1 = 1;
	}
	if (char2 == "*" || char2 == "/")
	{
		value2 = 2;
	}
	else if (char2 == "+" || char2 == "-")
	{
		value2 = 1;
	}
	else if (char2 == "(")
	{
		value2 = 0;
	}
	int res = value1 - value2;
	if (res > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

void MainWindow::on_CalculateYourResult_clicked() {
	if (!ui.Table2->item(0, 0)->text().contains("[a-z]"))
	{
		QMessageBox::critical(this, tr("Error"), tr("You havent entered an expression!"));
	}
	else {
		if (Check(ui.Table2->item(0, 0)->text()))
		{
			QString variable[5];
			double result = 0;
			QString oof = "";
			for (int i = 0; i < 5; i++)
			{
				if (ui.Table2->item(0, i + 1)->text() == "")
				{
					variable[i] = "0";
				}
				else {
					variable[i] = ui.Table2->item(0, i + 1)->text();
				}
			}
			oof = ui.Table2->item(0, 0)->text();
			result = calculate(oof, variable);
			QTableWidgetItem* itm = new QTableWidgetItem(QString::number(result));
			ui.Table2->setItem(0, 6, itm);
		}
	}
}


int MainWindow::Check(QString expression) {

	Stack.clear();

	QString text;
	QStringList list_of_strings;
	std::string temp = expression.toStdString();
	int y = 1, x = 0;

	if (expression[0] == '-' || expression[0] == '+' || expression[0] == '*' || expression[0] == '/' || expression[0] == '=')
	{
		QMessageBox::critical(this, tr("Error"), tr("Mistake in input!"));
		return 0;
	}
	else if (expression[expression.length() - 1] == '-' || expression[expression.length() - 1] == '*' || expression[expression.length() - 1] == '/' || expression[expression.length() - 1] == '+')
	{
		QMessageBox::critical(this, tr("Error"), tr("Mistake in input!"));
		return 0;
	}

	for (int i = 0; i < expression.length(); i++)
	{
		if (temp[i] == '(')
		{
			//add element to stack
			y = 1;
			Stack.push(QString::QString(temp[i]));
		}
		//if we meet it first time, it is mistake
		else if (temp[i] == ')')
		{
			if (Stack.isEmpty())
			{
				y = 0;
				x = 1;
				QMessageBox::critical(this, tr("Error"), tr("Mistake in input!"));
				return 0;
			}
			else
			{
				y = 1;
				//if we meet it second time, it is mistake
				if (Stack.gettop() == '(' && temp[i] == ')')
				{
					Stack.pop();
				}
				else
				{
					x = 1;
					QMessageBox::critical(this, tr("Error!"), tr("Mistake in input!"));
					y = 0;
					return 0;
				}
			}
		}
	}

	if (!Stack.isEmpty() && y)
	{
		QMessageBox::critical(this, tr("Error"), tr("Mistake in input!"));
		x = 1;
	}

	if (!x)
	{
		return 1;
	}
	return 1;
}




