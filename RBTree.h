#pragma once
#include <iostream>
#include "SLinkedList.h"
//#include<vector>

using namespace std;

enum CLR {
	BLACK,
	RED
};

template <class T> class dNode {
public:

	CLR clr;
	SLinkedList<string> list;
	dNode<T>* p;
	dNode<T>* left;
	dNode<T>* right;
	T val;

	dNode<T>(T val) {
		clr = RED;
		p = NULL;
		left = NULL;
		right = NULL;
	}

	void goBelow(dNode<T>* n) {
		if (p != NULL) {
			if (isLeft() == false) {
				p->right = n;
			}
			else {
				p->left = n;
			}
		}
		n->p = p;
		p = n;
	}

	bool isLeft() {
		if (this == p->left) {
			return true;
		}
		return false;
	}

	dNode<T>* relative() {				// check if uncle

		if (p->p == NULL) {
			return NULL;
		}
		if (p == NULL) {
			return NULL;
		}


		if (p->isLeft() == false) { return p->p->left; }
		else { return p->p->right; }
	}

};

template <class T> class RBTree {
	dNode<T>* root;

	void switchColors(dNode<T>* x, dNode<T>* y) {
		CLR c;
		c = x->clr;
		x->clr = y->clr;
		y->clr = c;
	}

	void turnLeft(dNode<T>* x) {

		dNode<T>* n = x->right;

		if (x == root)
			root = n;

		x->goBelow(n);

		x->right = n->left;
		if (n->left != NULL)
			n->left->p = x;

		n->left = x;
	}

	void turnRight(dNode<T>* x) {

		dNode<T>* n = x->left;

		if (x == root)
			root = n;

		x->goBelow(n);

		x->left = n->right;

		if (n->right != NULL)
			n->right->p = x;

		n->right = x;
	}

	void fixRed(dNode<T>* x) {

		if (x == root) {
			x->clr = BLACK;
			return;
		}

		dNode<T>* p = x->p;
		dNode<T>* ancestor = p->p,
			* relative = x->relative();

		if (p->clr == RED) {
			if (relative == NULL && relative->clr != RED) {
				if (p->isLeft()) {
					if (x->isLeft() == false) {
						turnLeft(p);
						switchColors(x, ancestor);
					}
					else {
						switchColors(p, ancestor);
					}

					turnRight(ancestor);
				}
				else {
					if (x->isLeft() == false) {
						turnLeft(p);
						switchColors(x, ancestor);
					}
					else {
						switchColors(p, ancestor);
					}

					turnLeft(ancestor);
				}
			}
			else {
				ancestor->clr = RED;
				relative->clr = BLACK;
				p->clr = BLACK;
				fixRed(ancestor);
			}
		}
	}

	// NEW 	inOrderTraversal
public:
	void inOrderTraversalWithFileHandling(dNode<T>* ins)
	{
		if (ins != NULL)
		{
			//cout << ins->clr << endl; 
			inOrderTraversalWithFileHandling(ins->left);
			//cout << ins->val << endl;

			stringstream ss;
			ss << "" << ins->val;
			string data = ss.str();
			if (data.find(",") != std::string::npos) {
				data = '"' + data + '"';
			}

			string color = "REDD";
			//cout << ins->clr << endl; 
			if (ins->clr == 0)
			{
				color = "BLACK";
			}
			else
			{
				color = "RED";
			}

			ins->list.writeRBIndexToFile(data, color);
			inOrderTraversalWithFileHandling(ins->right);

		}
	}

public:
	RBTree() {
		root = NULL;
	}

	dNode<T>* getRoot() {
		return root;
	}

	dNode<T>* lookUp(T n) {
		dNode<T>* t = root;
		while (t != NULL) {
			if (n == t->val) {
				break;
			}
			else if (n < t->val) {
				if (t->left == NULL)
					break;
				else
					t = t->left;
			}
			else {
				if (t->right == NULL)
					break;
				else
					t = t->right;
			}
		}

		return t;
	}

	void insert(T n, string fileName, string lineNo) {
		dNode<T>* newNode = new dNode<T>(n);
		newNode->list.insert(fileName, lineNo);
		newNode->val = n;
		newNode->clr = BLACK;

		if (root == NULL) {
			root = newNode;

		}
		else {
			dNode<T>* temp = lookUp(n);

			if (temp->val == n) {
				temp->list.insert(fileName, lineNo);
				return;
			}

			newNode->p = temp;

			if (n < temp->val)
				temp->left = newNode;
			else
				temp->right = newNode;

			fixRed(newNode);
		}
	}


};