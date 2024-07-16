#pragma once
#include <iostream>
#include <filesystem>
//#include<vector>

using namespace std;

template <class T> class cNode {

public:

    int t;
    int n;
    cNode** N;    // array for pointing to child pointers
    string fileName[10000] = { "" };
    string lineNo[10000] = { "" };
    bool leaf;
    T* elements;

    cNode(int t1, bool l) {

        t = t1;
        leaf = l;
        n = 0;
        elements = new T[2 * t - 1];
        N = new cNode * [2 * t];

    }

    // New Traversal
    void traversalWithFileHandling() {
        int i;
        for (i = 0; i < n; i++) {
            if (leaf == false)
                N[i]->traversalWithFileHandling();
            //cout << " " << elements[i] << " " << fileName[i] << " " << lineNo[i] << endl;
            writeBtreeIndexToFile(fileName[i], lineNo[i], elements[i]);
        }

        if (leaf == false)
            N[i]->traversalWithFileHandling();
    }

    void writeBtreeIndexToFile(string fileN, string lineN, T data) {
        string indexFile = "data/indexes/BtreeIndex.csv";

        ofstream file;
        file.open(indexFile, fstream::app);
        file << "\n" << data << "," << fileN << "," << lineN;
        file.close();
    }


    void splitChild(int i, cNode* y) {
        cNode* z = new cNode<T>(y->t, y->leaf);
        z->n = t - 1;

        for (int m = 0; m < t - 1; m++) {
            z->fileName[m] = y->fileName[m + t];
            z->elements[m] = y->elements[m + t];
            z->lineNo[m] = y->lineNo[m + t];
        }


        if (y->leaf == false) {
            for (int m = 0; m < t; m++)
                z->N[m] = y->N[m + t];
        }

        y->n = t - 1;
        for (int m = n; m >= i + 1; m--)
            N[m + 1] = N[m];

        N[i + 1] = z;

        for (int m = n - 1; m >= i; m--) {
            fileName[m + 1] = fileName[m];
            elements[m + 1] = elements[m];
            lineNo[m + 1] = lineNo[m];
        }

        fileName[i] = y->fileName[t - 1];
        elements[i] = y->elements[t - 1];
        lineNo[i] = y->lineNo[t - 1];

        n = n + 1;
    }

    // Insert non full condition
    void insertNonFull(string f, string l, T k) {
        int i = n - 1;

        if (leaf == false) {
            while (i >= 0 && elements[i] >= k) {
                //if(elements[i] == k) {
                    //cout << "duplicate - 2" << endl;
                //}
                i--;
            }

            if (N[i + 1]->n == 2 * t - 1) {
                splitChild(i + 1, N[i + 1]);

                if (elements[i + 1] < k)
                    i++;
            }
            // N[i + 1]->fileName = fileName;
            // N[i + 1]->lineNo = lineNo;
            N[i + 1]->insertNonFull(f, l, k);

        }
        else {
            while (i >= 0 && elements[i] >= k) {
                //if(elements[i] == k) {
                    //cout << "duplicate - 1" << endl;
                //}
                fileName[i + 1] = fileName[i];
                elements[i + 1] = elements[i];
                lineNo[i + 1] = lineNo[i];
                i--;
            }

            fileName[i + 1] = f;
            elements[i + 1] = k;
            lineNo[i + 1] = l;
            //cout << "inserted: " << k << " at " << i + 1<< endl;
            n = n + 1;
        }
    }

};

template <class T> class BTree {
    int t;    // degree
    cNode<T>* root;

public:
    BTree(int b) {
        root = NULL;
        t = b;
    }

    void traversalWithFileHandling() {
        if (root != NULL)
            root->traversalWithFileHandling();
    }

    // Insert the cNode
    void insert(string f, string l, T k) {
        //cout << k << " " << f << " " << t << "\n";	
        if (root == NULL) {
            root = new cNode<T>(t, true);
            //cout << "inserted: " << k << " at 0" << endl;
            root->elements[0] = k;
            root->fileName[0] = f;
            root->lineNo[0] = l;
            // root->fileName[0] = fileName;
            // root->lineNo[0] = lineNo;
            root->n = 1;
        }
        else {
            if (root->n != 2 * t - 1) {
                //cout << "inserting--: " << k << endl;

                // if (root->elements[0] == k) {
                //     cout << "duplicate" << " " << k << endl;
                // }

                // int i = root->n - 1;
                // while (i >= 0 && root->elements[i] >= k) {
                //     if(root->elements[i] == k) {
                //         cout << "duplicate--- " << k << endl;
                //     } 
                //     i--;
                // }

                root->insertNonFull(f, l, k);

            }
            else {
                cNode<T>* s = new cNode<T>(t, false);

                s->N[0] = root;
                s->splitChild(0, root);

                int i = 0;
                if (s->elements[0] < k) {
                    i++;
                }


                // s->N[i]->fileName[i] = f;
                // s->N[i]->lineNo[i] = l;
                s->N[i]->insertNonFull(f, l, k);
                //cout << "insert: " << k << endl;
                root = s;
            }
        }
    }
};