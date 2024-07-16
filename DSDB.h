#pragma once
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

#include "AVL.h"
//#include "AVLTreeState.h"

#include "Common.h"

using namespace std;

class DSDB {

public:
	string systemName;
	int menuOption;
	int key;
	int treeType;
	Common common;

public:
	DSDB() {
		systemName = "Database System - DSDB";
		key = 1;	// ID
		treeType = 1;	// AVL
	}

	void run() {
		system("cls");
		cout << "*************************************************************************************************************************************************************" << endl;
		cout << systemName + " " + "Version 1.0" << endl;
		cout << systemName + " " + "Initializing . . ." << endl;
		cout << "*************************************************************************************************************************************************************" << endl;

		// create indexes
		//createAVLTreeIndex();	// AVL
		//createBtreeIndex(); 	// BTree
		//createRBtreeIndex(); // RBTree

		do {
			//system("cls");
			showMenu();
			menuOption = getMenuOption();
			switch (menuOption) {
			case 1:
				createIndex();
				system("PAUSE");
				break;
			case 2:
				pointSearch();
				system("PAUSE");
				break;
			case 3:
				rangeSearch();
				system("PAUSE");
				break;
			case 4:
				updateRecord();
				system("PAUSE");
				break;
			case 5:
				deleteKey();
				system("PAUSE");
				break;
			case 6:
				whereOperation();
				system("PAUSE");
				break;
			default:
				break;
			}
		} while (menuOption != 0);
	}

	int getMenuOption() {
		cin >> menuOption;
		return menuOption;
	}

	void showMenu()
	{

		//cout << "System State" << endl;
		//cout << "AVL Index Created Using Field: " << key << endl;

		cout << "Choose Menu\n";
		cout << "Please make your selection\n";
		cout << "1 - Create Index \n";
		cout << "2 - Point Search \n";
		cout << "3 - Range Search \n";
		cout << "4 - Update Key-Data \n";
		cout << "5 - Delete Key \n";
		cout << "6 - Where Operation \n";
		cout << "0 - Quit\n";
		cout << "Selection: ";

	};

	void createIndex() {

		cout << "Choose Tree Type\n";
		cout << "1 - AVL Tree Index \n";
		cout << "2 - B-Tree Index \n";
		cout << "3 - Red-Black Tree Index \n";
		cout << "Selection: ";

		int tree;
		cin >> tree;

		cout << "Choose Data Key\n";
		cout << "1 - ID \n";
		cout << "2 - Year \n";
		cout << "3 - Cause Name \n";
		cout << "4 - State \n";
		cout << "5 - Deaths \n";
		cout << "6 - Age-adjusted Death Rate \n";
		cout << "Selection: ";

		int dataField;
		cin >> dataField;

		//cout << treeType << " " << key << endl;
		if (tree != treeType || dataField != key) {
			treeType = tree;
			key = dataField;
			createNewIndexUsingDefaultKeyAndTree(3, true);
		}
		else if (key == 1 && treeType == 1) {				// This is default
			createNewIndexUsingDefaultKeyAndTree(3, true);
		}
		else {
			cout << "****************************************************************************" << endl;
			cout << "Index Already Exists . . ." << endl;
			cout << "****************************************************************************" << endl;
		}

		// CREATE INDEX IF PREVIOUSLY DIFFERENT (tree or data field)
	}

	void createNewIndexUsingDefaultKeyAndTree(int i, bool isNew) {
		switch (treeType)
		{
		case 1: {
			cout << "****************************************************************************" << endl;
			cout << "Creating Index . . ." << endl;
			createAVLTreeIndex();
			break;
		}
		case 2: {
			if (isNew == true) {
				cout << "Enter Degree For New Btree Index: ";
				int d;
				cin >> d;
				cout << "****************************************************************************" << endl;
				cout << "Creating Index . . ." << endl;
				createBtreeIndex(d);
			}
			else {
				createBtreeIndex(i);
			}
			break;
		}
		case 3: {
			cout << "****************************************************************************" << endl;
			cout << "Creating Index . . ." << endl;
			createRBtreeIndex();
			break;
		}
		}
	}

	void pointSearch() {
		string userInput;
		cout << "Enter Key Value: ";
		std::getline(std::cin >> std::ws, userInput);
		//cout << userInput << endl;
		RecordLinkedList<string> list = common.getAVLIndexBasedRecordsWrtUserInput(key, treeType, userInput);
		if (list.head == NULL)
		{
			cout << "****************************************************************************" << endl;
			cout << "No Matching Records Found . . ." << endl;
			cout << "****************************************************************************" << endl;
		}
		else {
			list.printRecords();
		}
	}

	void rangeSearch() {
		int startingRange;
		int endingRange;
		if (key == 1 || key == 2 || key == 5 || key == 6) {
			cout << "Enter Starting Range For " << key << " : ";
			cin >> startingRange;
			cout << "Enter Ending Range For " << key << " : ";
			cin >> endingRange;

			RecordLinkedList<string> list = common.getAVLIndexBasedRecordsWrtUserInputRange(treeType, startingRange, endingRange);
			list.printRecords();
		}
		else {
			cout << "****************************************************************************" << endl;
			cout << "Feature Not Applicable On String Keys . . ." << endl;
			cout << "****************************************************************************" << endl;
		}
	}

	void updateRecord() {
		string keyValue;
		cout << "Enter Key Value: ";
		std::getline(std::cin >> std::ws, keyValue);

		cout << "Choose Field\n";
		cout << "1 - ID \n";
		cout << "2 - Year \n";
		cout << "3 - Cause Name \n";
		cout << "4 - State \n";
		cout << "5 - Deaths \n";
		cout << "6 - Age-adjusted Death Rate \n";
		cout << "Selection: ";

		int dataField;
		cin >> dataField;

		string oldValue;
		cout << "Enter Old Value: ";
		std::getline(std::cin >> std::ws, oldValue);

		string newValue;
		cout << "Enter New Value: ";
		std::getline(std::cin >> std::ws, newValue);

		bool isUpdated = common.update(key, keyValue, dataField, oldValue, newValue);
		if (isUpdated) {
			cout << "****************************************************************************" << endl;
			cout << "Record(s) Updated . . ." << endl;
			cout << "****************************************************************************" << endl;

			if (key == dataField) {
				// INDEX needs to be updated
				createNewIndexUsingDefaultKeyAndTree(3, false);
			}
		}
	}

	void deleteKey() {
		string userInput;
		cout << "Enter Key Value: ";
		std::getline(std::cin >> std::ws, userInput);
		//key = "STATE";
		bool isDeleted = common.deleteKey(key, userInput);
		if (isDeleted) {
			cout << "****************************************************************************" << endl;
			cout << "Record(s) Deleted . . ." << endl;
			cout << "****************************************************************************" << endl;
			createNewIndexUsingDefaultKeyAndTree(3, false);
		}
	}

	void whereOperation() {
		cout << "****************************************************************************" << endl;
		cout << "Samples Queries/Commands . . ." << endl;
		cout << "****************************************************************************" << endl;
		cout << "Using YEAR As Key:" << endl;
		cout << "SEARCH WHERE YEAR = 2016;" << endl;
		cout << "DELETE 2016 WHERE STATE = Alabama;" << endl;
		cout << endl;
		cout << "Using ID As Key:" << endl;
		cout << "SEARCH WHERE ID = 790;" << endl;
		cout << "DELETE 2062 WHERE STATE = Delaware;" << endl;
		cout << "****************************************************************************" << endl;

		string str;
		cout << "Enter Command: ";
		std::getline(std::cin >> std::ws, str);

		if (str.find("SEARCH") != std::string::npos) {
			cout << "SEARCH" << endl;
			//common.searchWrtWhereClause(key, str);

			unsigned first = str.find("DELETE");
			unsigned last = str.find("WHERE");

			first = str.find("=");
			last = str.find(";");
			string strNew = str.substr(first, last - first);
			strNew = strNew.substr(1);
			string fieldValue = regex_replace(strNew, std::regex("^ +| +$|( ) +"), "$1");
			cout << fieldValue << endl;

			RecordLinkedList<string> list = common.getAVLIndexBasedRecordsWrtUserInput(key, treeType, fieldValue);
			if (list.head == NULL)
			{
				cout << "****************************************************************************" << endl;
				cout << "No Matching Records Found . . ." << endl;
				cout << "****************************************************************************" << endl;
			}
			else {
				list.printRecords();
			}

		}
		else if (str.find("DELETE") != std::string::npos) {
			bool isDeleted = common.deleteWrtWhereClause(key, str);
			if (isDeleted) {
				cout << "****************************************************************************" << endl;
				cout << "Record(s) Deleted . . ." << endl;
				cout << "****************************************************************************" << endl;
				createNewIndexUsingDefaultKeyAndTree(3, false);
			}
		}

	}

	void createAVLTreeIndex() {
		// remove existing index
		removeIndexFiles();

		// create new index
		switch (key)
		{
		case 1:
		{
			bst<int> obj1 = common.loadIntDataInAvlTree(1);
			obj1.inOrderTraversalWithFileHandling(obj1.root);
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 2:
		{
			bst<int> obj2 = common.loadIntDataInAvlTree(2);
			obj2.inOrderTraversalWithFileHandling(obj2.root);
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 3:
		{
			bst<string> obj3 = common.loadStringDataInAvlTree(3);
			obj3.inOrderTraversalWithFileHandling(obj3.root);
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 4:
		{
			bst<string> obj4 = common.loadStringDataInAvlTree(4);
			obj4.inOrderTraversalWithFileHandling(obj4.root);
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 5:
		{
			bst<int> obj5 = common.loadIntDataInAvlTree(5);
			obj5.inOrderTraversalWithFileHandling(obj5.root);
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 6:
		{
			bst<int> obj6 = common.loadIntDataInAvlTree(6);
			obj6.inOrderTraversalWithFileHandling(obj6.root);
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		// default:
		// 	break;
		}
		//bst<int> obj = common.loadIntDataInAvlTree(1);	
		//bst<string> obj = common.loadStringDataInAvlTree(3);	
	}

	void removeIndexFiles() {
		string avlFile = "data/indexes/AVLIndex.csv";
		string btreeFile = "data/indexes/BtreeIndex.csv";
		string rbtreeFile = "data/indexes/RBtreeIndex.csv";
		try {
			std::filesystem::remove(avlFile);
		}
		catch (const std::exception& e) {
			cout << "File already deleted" << endl;
		}
		try {
			std::filesystem::remove(btreeFile);
		}
		catch (const std::exception& e) {
			cout << "File already deleted" << endl;
		}
		try {
			std::filesystem::remove(rbtreeFile);
		}
		catch (const std::exception& e) {
			cout << "File already deleted" << endl;
		}
	}

	void createBtreeIndex(int d) {
		// remove existing index
		removeIndexFiles();

		// create new index
		//BTree<int> obj = common.loadIntDataInBTree(1);	
		//BTree<string> obj = common.loadStringDataInBTree(3);	
		//obj.traversalWithFileHandling();

		// create new index
		switch (key)
		{
		case 1:
		{
			BTree<int> obj1 = common.loadIntDataInBTree(1, d);
			obj1.traversalWithFileHandling();
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 2:
		{
			BTree<int> obj2 = common.loadIntDataInBTree(2, d);
			obj2.traversalWithFileHandling();
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 3:
		{
			BTree<string> obj3 = common.loadStringDataInBTree(3, d);
			obj3.traversalWithFileHandling();
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 4:
		{
			BTree<string> obj4 = common.loadStringDataInBTree(4, d);
			obj4.traversalWithFileHandling();
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 5:
		{
			BTree<int> obj5 = common.loadIntDataInBTree(5, d);
			obj5.traversalWithFileHandling();
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 6:
		{
			BTree<int> obj6 = common.loadIntDataInBTree(6, d);
			obj6.traversalWithFileHandling();
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		}
	}


	void createRBtreeIndex() {
		// remove existing index
		removeIndexFiles();

		switch (key)
		{
		case 1:
		{
			RBTree<int> obj1 = common.loadIntDataInRBTree(1);
			obj1.inOrderTraversalWithFileHandling(obj1.getRoot());
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 2:
		{
			RBTree<int> obj2 = common.loadIntDataInRBTree(2);
			obj2.inOrderTraversalWithFileHandling(obj2.getRoot());
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 3:
		{
			RBTree<string> obj3 = common.loadStringDataInRBTree(3);
			obj3.inOrderTraversalWithFileHandling(obj3.getRoot());
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 4:
		{
			RBTree<string> obj4 = common.loadStringDataInRBTree(4);
			obj4.inOrderTraversalWithFileHandling(obj4.getRoot());
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 5:
		{
			RBTree<int> obj5 = common.loadIntDataInRBTree(5);
			obj5.inOrderTraversalWithFileHandling(obj5.getRoot());
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		case 6:
		{
			RBTree<int> obj6 = common.loadIntDataInRBTree(6);
			obj6.inOrderTraversalWithFileHandling(obj6.getRoot());
			cout << "****************************************************************************" << endl;
			cout << "Index Created . . ." << endl;
			cout << "****************************************************************************" << endl;
			break;
		}
		}
	}
};
