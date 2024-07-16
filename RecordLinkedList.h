#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <filesystem>

#include <stdlib.h>
#include <conio.h>
#include "Record.h"

using namespace std;
template <class T>

class bNode
{
public:
	T data;
	Record r;
	bNode* next;

	bNode()
	{
		this->data = 0;
		this->next = NULL;
	}

	bNode(Record r)
	{
		this->r = r;
		this->next = NULL;
	}

};

template <class T> class RecordLinkedList {

public:
	bNode<T>* head;
	const char separator = ' ';
	const int stringColumnWidth = 15;
	const int intColumnWidth = 8;

	RecordLinkedList()
	{
		head = NULL;
	}

	void insert(T x, Record r)
	{

		bNode<T>* n = new bNode <T>(r);
		n->next = NULL;

		if (head == NULL)
		{
			head = n;
		}

		else
		{
			bNode<T>* temp = head;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = n;
		}

	}

	void printRecords() {
		bNode<T>* ptr = head;

		cout << "*************************************************************************************************************************************************************************************" << endl;
		printPrettyTable("ID", stringColumnWidth);
		printPrettyTable("YEAR", stringColumnWidth);
		printPrettyTable("CAUSE NAME 113", stringColumnWidth * 5);
		printPrettyTable("CAUSE NAME", stringColumnWidth * 2);
		printPrettyTable("STATE", stringColumnWidth * 2);
		printPrettyTable("DEATHS", stringColumnWidth);
		printPrettyTable("RATE", stringColumnWidth);
		cout << endl;
		cout << "*************************************************************************************************************************************************************************************" << endl;

		//cout << ptr->r.getId() << " " << ptr->r.getCauseName113() << endl;
		printPrettyTable(ptr->r.getId(), this->stringColumnWidth);
		printPrettyTable(ptr->r.getYear(), this->stringColumnWidth);

		ptr->r.getCauseName113() = regex_replace(ptr->r.getCauseName113(), std::regex(" +"), " ");
		printPrettyTable(ptr->r.getCauseName113(), this->stringColumnWidth * 5);

		ptr->r.getCauseName() = regex_replace(ptr->r.getCauseName(), std::regex(" +"), " ");
		printPrettyTable(ptr->r.getCauseName(), this->stringColumnWidth * 2);

		printPrettyTable(ptr->r.getState(), this->stringColumnWidth * 2);
		printPrettyTable(ptr->r.getDeaths(), this->stringColumnWidth);
		printPrettyTable(ptr->r.getRate(), this->stringColumnWidth);
		cout << endl;

		while (ptr->next != NULL)
		{
			ptr = ptr->next;
			//cout << ptr->r.getId() << " " << ptr->r.getCauseName113() << endl;
			printPrettyTable(ptr->r.getId(), this->stringColumnWidth);
			printPrettyTable(ptr->r.getYear(), this->stringColumnWidth);

			ptr->r.getCauseName113() = regex_replace(ptr->r.getCauseName113(), std::regex(" +"), " ");
			printPrettyTable(ptr->r.getCauseName113(), this->stringColumnWidth * 5);

			ptr->r.getCauseName() = regex_replace(ptr->r.getCauseName(), std::regex(" +"), " ");
			printPrettyTable(ptr->r.getCauseName(), this->stringColumnWidth * 2);

			printPrettyTable(ptr->r.getState(), this->stringColumnWidth * 2);
			printPrettyTable(ptr->r.getDeaths(), this->stringColumnWidth);
			printPrettyTable(ptr->r.getRate(), this->stringColumnWidth);
			cout << endl;
		}

		// cout << ptr->r.getId() << " " << ptr->r.getCauseName113() << endl;
		// cout << endl;
		// printPrettyTable(ptr->r.getId(), this->stringColumnWidth);
		// printPrettyTable(ptr->r.getYear(), this->stringColumnWidth);
		// printPrettyTable(ptr->r.getCauseName113(), this->stringColumnWidth * 4);
		// printPrettyTable(ptr->r.getCauseName(), this->stringColumnWidth * 3);
		// printPrettyTable(ptr->r.getState(), this->stringColumnWidth);
		// printPrettyTable(ptr->r.getDeaths(), this->stringColumnWidth);
		// printPrettyTable(ptr->r.getRate(), this->stringColumnWidth);
		cout << endl;
		cout << "*************************************************************************************************************************************************************************************" << endl;
	}

	template<typename U> void printPrettyTable(U t, const int& width) {
		cout << left << setw(width) << setfill(separator) << t;
	}
};
