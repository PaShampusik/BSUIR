#include "parser.h"

Parser::Parser(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

}

void Parser::on_OpenFile_clicked()
{
	ui.plainTextEdit->clear();
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open a cpp file"), "D:/BSUIR/QT/Lab 4/Parser", tr("Text File (*.cpp)"));
	QFile file(fileName);
	QString line;

	if (fileName.isEmpty())
	{
		QMessageBox::information(this, "Error!", "File is Empty");
		return;
	}

	if (!file.open(QIODevice::ReadWrite)) {
		QMessageBox::information(this, tr("Unable to open file"), file.errorString());
		return;
	}
	else {
		QTextStream stream(&file);

		while (!stream.atEnd()) {
			line = stream.readLine();
			ui.plainTextEdit->appendPlainText(line);
		}
		file.close();
	}

}

void Parser::on_pushButton_clicked()
{
	ui.plainTextEdit_2->clear();
	QString plText = ui.plainTextEdit->toPlainText();
	if (plText == "")
	{
		QMessageBox::warning(this, "Error!", "File is Empty");
		return;
	}
	QStringList strList;
	strList = ui.plainTextEdit->toPlainText().split("\n");

	int Count = 0;
	std::string str = "";
	std::string s = "";
	for (int i = 0; i < strList.size(); i++) {
		std::string str = strList[i].toStdString();
		std::cmatch result;
		std::cmatch resultInit;

		std::regex regularForVar(
			"(int|double|long|size_t|std::string|float|bool|char|char\\*|short|long long|void)"
			"(( )*\\**( )*([\\w-]+)((,)|(;)))+"
		);

		std::regex regularForVarInit(
			"(int|double|long|size_t|std::string|float|bool|char|char\\*|short|long long|void)"
			"(( )*\\**( )*([\\w-]+)((\\s*=\\s*&*[\\w]+)|(\\(\\s*[0-9]+\\s*\\)))(\\[\\w\\])*(,)*)+"
		);


		if (std::regex_search(str.c_str(), result, regularForVar)) {
			Count++;
			s += result[0];
			s += "\n";
		}
		if (std::regex_search(str.c_str(), resultInit, regularForVarInit)) {
			Count++;
			s += resultInit[0];
			s += "\n";
		}
		const char* y = s.c_str();
		str = y;
	}
	ui.plainTextEdit_2->appendPlainText("Variables: \n" + QString::fromStdString(s) + "\nCount of variables: " + QString::number(Count));

	int classesCount = 0;
	int objCount = 0;
	std::vector<std::string> classesVect;
	for (int i = 0; i < strList.size(); i++) {
		std::string str = strList[i].toStdString();
		std::cmatch resultClass;
		std::regex regularForClass(
			"(class)"
			"(\\s)"
			"([\\w-]+)"
		);
		if (std::regex_search(str.c_str(), resultClass, regularForClass)) {
			classesVect.push_back(resultClass[3]);
			classesCount++;
		}
	}

	ui.plainTextEdit_2->appendPlainText("Classes Count: " + QString::number(classesCount));


	int structsCount = 0;
	int objStructsCount = 0;
	std::vector<std::string> structsVect;
	for (int i = 0; i < strList.size(); i++) {
		std::string str = strList[i].toStdString();
		std::cmatch resultStruct;
		std::regex regularForStruct(
			"(struct)"
			"(\\s)"
			"([\\w-]+)"
		);
		if (std::regex_search(str.c_str(), resultStruct, regularForStruct)) {
			structsVect.push_back(resultStruct[3]);
			structsCount++;
		}
	}

	ui.plainTextEdit_2->appendPlainText("Structs Count: " + QString::number(structsCount));


	int arrsCount = 0;
	for (int i = 0; i < strList.size(); i++) {
		std::string str = strList[i].toStdString();

		std::regex regularForStruct(
			"(int|double|long|size_t|std::string|float|bool|char|char\\*|short|long long)"
			"(\\s)+"
			"([\\w-]+)"
			"(\\s*)"
			"\\[\\s*\\d*\\s*\\]"
		);
		if (std::regex_search(str.c_str(), regularForStruct)) {
			arrsCount++;
		}
	}
	ui.plainTextEdit_2->appendPlainText("Arrays Count: " + QString::number(arrsCount));

	s = "";
	str = "";
	for (int i = 0; i < strList.size(); i++) {
		std::string str = strList[i].toStdString();
		std::cmatch resultPrototypeFunction;
		std::regex regularForPrototype(
			"(int|double|long|size_t|std::string|float|bool|char|char\\*|short|long long|void)"
			"(\\s*\\**\\s*)"
			"([\\w-]+)"
			"(( )*)"
			"(\\()"
			"(( )*(int|double|long|size_t|std::string|float|bool|char|char\\*|short|long long|void)(( )*\\**( )*([\\w-])*)*(,)*)*"
			"(\\))"
		);
		if (std::regex_search(str.c_str(), resultPrototypeFunction, regularForPrototype)) {
			s += resultPrototypeFunction[0];
			s += ";\n";
		}
	}
	const char* y = s.c_str();
	str = y;
	ui.plainTextEdit_2->appendPlainText("Function prototypes: \n" + QString::fromStdString(s));

	s = "";
	MyString string;
	for (int i = 0; i < strList.size(); i++) {
		std::string str = strList[i].toStdString();

		std::regex regularVarChanged(
			"(\\**([\\w-]+)(\\[(\\w)*\\])*)"
			"(\\s*=\\s*&*[\\w]+)"
		);
		if (std::regex_search(str.c_str(), regularVarChanged)) {

			s += "Row: " + std::to_string(i);

			s += ",\n";
		}
	}
	y = s.c_str();
	string = y;
	ui.plainTextEdit_2->appendPlainText("Changing of variables coordinates:\n" + QString::fromStdString(s));

	int localVarsCount = 0;
	string = "";
	s = "";
	Stack stack;

	for (int i = 0; i < strList.size(); i++) {
		std::string str = strList[i].toStdString();
		for (char c : str) {
			switch (c) {
			case '{':
			{
				stack.push('{');
				if (!stack.isEmpty()) {
					std::regex regularForVar(
						"(int|double|long|size_t|std::string|float|bool|char|char\\*|short|long long|void)"
						"(( )*\\**( )*([\\w-]+)((,)|(;)))+"
					);
					
					std::regex regularForVarInit(
						"(int|double|long|size_t|std::string|float|bool|char|char\\*|short|long long|void)"
						"(( )*\\**( )*([\\w-]+)((\\s*=\\s*&*[\\w]+)|(\\(\\s*[0-9]+\\s*\\)))(\\[\\w\\])*(,)*)+"
					);


					if (std::regex_search(str.c_str(), regularForVar)) {
						localVarsCount++;
						s += "Row: " + std::to_string(i);
						s += "\n";
					}
					if (std::regex_search(str.c_str(), regularForVarInit)) {
						localVarsCount++;
						s += "Row: " + std::to_string(i);
						s += "\n";
					}
				}
			}
			break;
			case '}':
			{
				if (!stack.isEmpty()) {
					stack.pop();
				}
			}
			break;
			default:
				break;
			}
		}
		if (!stack.isEmpty()) {
			std::cmatch result;
			std::cmatch resultInit;
			std::regex regularForVar(
				"(int|double|long|size_t|std::string|float|bool|char|char\\*|short|long long|void)"
				"(( )*\\**( )*([\\w-]+)((,)|(;)))+"
			);

			std::regex regularForVarInit(
				"(int|double|long|size_t|std::string|float|bool|char|char\\*|short|long long|void)"
				"(( )*\\**( )*([\\w-]+)((\\s*=\\s*&*[\\w]+)|(\\(\\s*[0-9]+\\s*\\)))(\\[\\w\\])*(,)*)+"
			);


			if (std::regex_search(str.c_str(), result, regularForVar)) {
				localVarsCount++;
				s += "Row: " + std::to_string(i);
				s += "\n";
			}
			if (std::regex_search(str.c_str(), resultInit, regularForVarInit)) {
				localVarsCount++;
				s += "Row: " + std::to_string(i);
				s += "\n";
			}
		}



	}
	y = s.c_str();
	string = y;
	ui.plainTextEdit_2->appendPlainText("Local variables: \n" + QString::fromStdString(s) + "\nNumber of local variables: " + QString::number(localVarsCount));
	//}

	//if (ui.comboBox->currentText() == "Overrided functions") {
	s = "";
	string = "";
	std::vector<std::string> fList;
	std::vector<std::string> nameFuncList;
	std::vector<int> rowFuncList;

	for (int i = 0; i < strList.size(); i++) {
		std::string str = strList[i].toStdString();
		std::cmatch resultPrototypeFunction;
		std::regex regularForPrototype(
			"(int|double|long|size_t|std::string|float|bool|char|char\\*|short|long long|void)"
			"(\\s*\\**\\s*)"
			"([\\w-]+)"
			"(( )*)"
			"(\\()"
			"(( )*(int|double|long|size_t|std::string|float|bool|char|char\\*|short|long long|void)(( )*\\**( )*([\\w-])*)*(,)*)*"
			"(\\))"
		);
		if (std::regex_search(str.c_str(), resultPrototypeFunction, regularForPrototype)) {
			fList.push_back(resultPrototypeFunction[0]);
			nameFuncList.push_back(resultPrototypeFunction[3]);
			rowFuncList.push_back(i);
		}
	}
	int overrideCount = 0;
	int ind = 0;
	while (ind < fList.size())
	{
		bool isExist = false;
		int ind2 = 0;
		while (ind2 < fList.size()) {
			if (nameFuncList[ind] == nameFuncList[ind2] && ind != ind2 && fList[ind] != fList[ind2]) {
				s += "Row: " + std::to_string(rowFuncList[ind2]);
				s += "\n";
				isExist = true;
				fList.erase(fList.begin() + ind2);
				nameFuncList.erase(nameFuncList.begin() + ind2);
				rowFuncList.erase(rowFuncList.begin() + ind2);
			}
			else {
				ind2++;
			}
		}
		if (isExist) {
			s += "Row: " + std::to_string(rowFuncList[ind]);
			s += "\n";
			fList.erase(fList.begin() + ind);
			nameFuncList.erase(nameFuncList.begin() + ind);
			rowFuncList.erase(rowFuncList.begin() + ind);
			overrideCount++;
		}
		else {
			ind++;
		}
	}
	y = s.c_str();
	string = y;
	ui.plainTextEdit_2->appendPlainText("Override functions: \n" + QString::fromStdString(s));
	ui.plainTextEdit_2->appendPlainText("Count of override functions: \n" + QString::number(overrideCount));

	QString spare = "";

	std::string temp = ui.plainTextEdit->toPlainText().toStdString();
	QStringList list = ui.plainTextEdit->toPlainText().split("\n");
	std::vector<int> depth;
	int amount = 0;
	Stack pos;

	for (size_t i = 0; i < temp.size() - 5; ++i)
	{
		if (temp[i] != 'e' && temp[i + 1] != 'l' && temp[i + 2] != 's' && temp[i + 3] != 'e' && temp[i] == 'i' && temp[i + 1] == 'f')
		{
			++amount;
			pos.push('{');
		}
		if (temp[i] == 'e' && temp[i + 1] == 'l' && temp[i + 2] == 's' && temp[i + 3] == 'e' && temp[i + 4] == 'i' && temp[i + 5] == 'f')
		{
			pos.push('{');
		}
		if (!pos.isEmpty() && temp[i] == '}')
		{
			depth.push_back(amount);
			--amount;
			pos.pop();
		}
	}

	for (size_t i = 0; i < depth.size() - depth.size() / 3; ++i)
	{
		spare += QString::number(depth[i]) + "\n";
	}
	ui.plainTextEdit_2->appendPlainText("If Else depths: " + spare + "\n");


	
	s = "";
	for (int i = 0; i < strList.size(); i++) {
		std::string str = strList[i].toStdString();

		std::regex regularForLogicalMistakes(
			"(\\s*while\\s*\\(\\s*false\\s*\\))|(\\s*if\\s*\\(\\s*false\\s*\\))|(\\s*if\\s*\\(\\s*true\\s*\\))|(\\s*while\\(\\s*true\\s*\\)\\s*\\{\\s*\\})|(\\s*if\\(\\s*\\))"
		);
		std::regex regularForWhileTrueEmpty();
		std::cmatch result;
		if (std::regex_search(str.c_str(), result, regularForLogicalMistakes)) {
			s += result[0];
			s += "\nRow: " + std::to_string(i);
			s += "\n\n";
		}
	}
	ui.plainTextEdit_2->appendPlainText(QString::fromStdString(s));
}
