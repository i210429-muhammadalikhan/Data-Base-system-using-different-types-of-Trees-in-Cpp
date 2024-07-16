#pragma once
#pragma once

#include<iostream>
#include <filesystem>

#include "SLinkedList.h"

using namespace std;

//template <class T> 
template <class T> class Node {

public:
	T data;
	SLinkedList<string> list;
	int Height;
	Node* left;
	Node* right;

	Node() {
		data = T();
		this->left = NULL;
		this->right = NULL;
	}

};


//template <class T>

template <class T> class bst {

	//private:

public:

	Node<T>* root;
	//int Height();
	bst()
	{
		root = NULL;
		//this->left = NULL;
		//data = 0;
		//this->left = NULL;
		//this->right = NULL;
	}

	int Height(Node<T>* ptr)
	{
		ptr == root;
		if (ptr == NULL)
		{
			return -1;
		}

		else if (ptr != NULL)
		{
			return ptr->Height;
		}
	}

	Node<T>* Insert(T val, Node<T>* ptr)
	{
		ptr = root;
		if (ptr == NULL)
		{
			ptr = new Node<T>;
			ptr->data = val;
			ptr->left = NULL;
			ptr->right = NULL;
		}

		else if (val < ptr->data)
		{
			ptr->left = Insert(val, ptr->left);
			if (Height(ptr->left)) - (Height(ptr->right) == 2);
			{
				if (val < ptr->left->data) {
					ptr = RR(ptr);
				}
				else {
					ptr = RL(ptr);
				}
			}
		}

		else if (val > ptr->data)
		{
			ptr->left = Insert(val, ptr->left);
			if (Height(ptr->left)) - (Height(ptr->right) == 2);
			{
				if (val > ptr->left->data) {
					ptr = LL(ptr);
				}
				else {
					ptr = LR(ptr);
				}
			}
		}

		ptr->Height = Max(Height(ptr->left), Height(ptr->right)) + 1;
		return ptr;
	}

	int Max(int var1, int var2)
	{
		if (var1 > var2)
		{
			return var1;
		}

		else
		{
			return var2;
		}
	}

	Node<T>* LL(Node<T>* ptr) {

		Node<T>* anptr;
		anptr = ptr->right;
		ptr->right = anptr->left;
		anptr->left = ptr;

		ptr->Height = Max(Height(ptr->left), Height(ptr->right) + 1);
		anptr->Height = Max(Height(anptr->left), ptr->Height + 1);
		return anptr;
	}

	Node<T>* RR(Node<T>* ptr) {

		Node<T>* anptr;
		anptr = ptr->left;
		ptr->left = anptr->right;
		anptr->right = ptr;

		ptr->Height = Max(Height(ptr->left), Height(ptr->right) + 1);
		anptr->Height = Max(Height(anptr->left), ptr->Height + 1);
		return anptr;
	}



	Node<T>* LR(Node<T>* ptr)
	{
		ptr->right = RR(ptr->right);
		return LL(ptr);
	}


	Node<T>* RL(Node<T>* ptr)
	{
		ptr->left = LL(ptr->left);
		return RR(ptr);
	}



	//void insert(T val)
	void insert(T val, string fileName, string lineNo)
	{
		Node<T>* newnode;
		Node<T>* ptr;

		newnode = new Node<T>;
		newnode->data = val;
		newnode->list.insert(fileName, lineNo);

		newnode->left = NULL;
		newnode->right = NULL;


		if (root == NULL)
		{
			root = newnode;
		}

		else if (root != NULL)
		{
			ptr = root;

			while (ptr != NULL)
			{
				if (val < ptr->data)
				{
					if (ptr->left != NULL)
					{
						ptr = ptr->left;
					}
					else {
						ptr->left = newnode;
						break;
					}
				}

				else if (val > ptr->data) {

					if (ptr->right != NULL)
					{
						ptr = ptr->right;
					}

					else {
						ptr->right = newnode;
						break;
					}
				}
				else if (val == ptr->data) {
					// add data to ptr linked list
					ptr->list.insert(fileName, lineNo);
					//cout << "*** add data to ptr linked list *** \n";
					break;
				}
				else {
					cout << "*** DUPLICATE VALUE *** \n";
					break;
				}
			}
		}
	}

	void inOrderTraversal(Node<T>* ins)
	{

		if (ins != NULL)
		{
			inOrderTraversal(ins->left);
			cout << ins->data << endl;
			ins->list.printFileInfo();
			inOrderTraversal(ins->right);

		}
	}

	// NEW 	inOrderTraversal
	void inOrderTraversalWithFileHandling(Node<T>* ins)
	{
		if (ins != NULL)
		{
			inOrderTraversalWithFileHandling(ins->left);
			//cout << ins->data << endl;

			// converting ins->data to string
			stringstream ss;
			ss << "" << ins->data;
			string data = ss.str();
			if (data.find(",") != std::string::npos) {
				data = '"' + data + '"';
			}

			ins->list.writeAVLIndexToFile(data);
			inOrderTraversalWithFileHandling(ins->right);

		}
	}

	void PreOrderTraversal(Node<T>* ins)
	{
		if (ins == NULL)
		{
			//return
			cout << "POINTER SENT IN THE FUNTION IS EMPTY !" << endl;
		}

		else
		{
			cout << ins->data << endl;
			inOrderTraversal(ins->left);
			inOrderTraversal(ins->right);

		}
	}

	void PostOrderTraversal(Node<T>* ins)
	{
		if (ins == NULL)
		{
			//return
			cout << "POINTER SENT IN THE FUNTION IS EMPTY !" << endl;
		}

		else
		{
			inOrderTraversal(ins->left);
			inOrderTraversal(ins->right);
			cout << ins->data << endl;
		}
	}

};