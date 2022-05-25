#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include"Map.h"
#include"Set.h"
#include"Unordered_map.h"
#include <qmessagebox.h>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
	void AddMapWidget(QTreeWidgetItem* oof, Map<int, int>::Node* root);
	void AddSetWidget(QTreeWidgetItem* oof, Set<int>::Node* root);

	
private slots:
	void on_AddMapElement_clicked();
	void on_AddSetElement_clicked();
	void on_AddUnorderedMapElement_clicked();
	void on_FindMapElement_clicked();
	void on_FindSetElement_clicked();
	void on_FindUnorderedMapElement_clicked();
	void on_RemoveMapElement_clicked();
	void on_RemoveSetElement_clicked();
	void on_RemoveUnorderedMapElement_clicked();
	

private:
    Ui::MainWindowClass ui;
	Map<int, int> map = Map<int, int>();
	Set<int> set = Set<int>();
	HashTable<int, int> unordered_map = HashTable<int, int>();
};
