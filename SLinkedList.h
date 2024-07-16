#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include <stdlib.h>
#include<conio.h>

using namespace std;
template <class T> class aNode {
public:
	T data;
	T fileName;
	T lineNo;
	aNode* next;

	aNode()
	{
		this->data = 0;
		this->next = NULL;
	}

	aNode(T fileName, T lineNo)
	{
		this->fileName = fileName;
		this->lineNo = lineNo;
		this->next = NULL;
	}

};

template <class T> class SLinkedList {

public:

	aNode<T>* head;

	SLinkedList()
	{
		head = NULL;
	}

	void insert(T x, T y)
	{

		aNode<T>* n = new aNode <T>(x, y);
		n->next = NULL;

		if (head == NULL)
		{
			head = n;
		}

		else
		{
			aNode<T>* temp = head;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = n;
		}

	}

	void printFileInfo() {
		aNode<T>* ptr = head;
		//cout << "here" << endl;
		//cout << ptr->data;
		//cout << ptr->fileName << " " << ptr->lineNo << endl;
		while (ptr->next != NULL) {
			//cout << ptr->fileName << " " << ptr->lineNo << endl;
			ptr = ptr->next;
		}
		//cout << "here" << endl;
		//cout << ptr->data;
		//cout << ptr->fileName << " " << ptr->lineNo << endl;
	}

	void writeAVLIndexToFile(string data) {
		string indexFile = "data/indexes/AVLIndex.csv";

		aNode<T>* ptr = head;
		ofstream file;
		if (ptr->next != NULL) {

			file.open(indexFile, fstream::app);
			while (ptr->next != NULL)
			{
				//cout << ptr->fileName << " " << ptr->lineNo << endl;
				file << "\n" << data << "," << ptr->fileName << "," << ptr->lineNo;
				ptr = ptr->next;
			}
			file.close();
		}

		file.open(indexFile, fstream::app);
		file << "\n" << data << "," << ptr->fileName << "," << ptr->lineNo;
		file.close();

	}

	// void writeRBIndexToFile(string data) {
	// 	string indexFile = "data/indexes/RBtreeIndex.csv";

	// 	aNode<T>* ptr = head;
	// 	ofstream file;		
	// 	if(ptr->next != NULL) {

	// 		file.open (indexFile, fstream::app);
	// 		while (ptr->next != NULL)
	// 		{
	// 			//cout << ptr->fileName << " " << ptr->lineNo << endl;
	// 			file << "\n" << data << "," <<ptr->fileName << ","<<ptr->lineNo;
	// 			ptr = ptr->next;
	// 		}	
	//    		file.close();			
	// 	} 

	// 	file.open (indexFile, fstream::app);
	// 	file << "\n" << data << "," <<ptr->fileName << ","<<ptr->lineNo;
	// 	file.close();			

	// }

	void writeRBIndexToFile(string data, string color) {
		string indexFile = "data/indexes/RBtreeIndex.csv";

		aNode<T>* ptr = head;
		ofstream file;
		if (ptr->next != NULL) {

			file.open(indexFile, fstream::app);
			while (ptr->next != NULL)
			{
				//cout << ptr->fileName << " " << ptr->lineNo << endl;
				file << "\n" << data << "," << ptr->fileName << "," << ptr->lineNo << "," << color;
				ptr = ptr->next;
			}
			file.close();
		}

		file.open(indexFile, fstream::app);
		file << "\n" << data << "," << ptr->fileName << "," << ptr->lineNo << "," << color;
		file.close();

	}
};
