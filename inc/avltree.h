/*******************************************************************************
* MIT License
*
* Copyright (c) [year] [fullname]
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*******************************************************************************/


/**
 * My AVL tree implementation.
 * This tree relies on the <, >, and ==
 * operators to compare elements so these
 * operators must be defined for elements
 * in the tree.
 */

#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>

#define NULLPTR 0L

template<class T>
class AVLTree {

public:
    AVLTree();
    bool add(T);
    bool remove(T);
    void removeAll();
    void printTree();
    std::string getPosition(T);
    int size();
    bool isEmpty();
    bool contains(T);
    const T* largest();
    const T* smallest();
    ~AVLTree();

private:
    // declaration of tree node
    struct Node;

    // private member variables
    Node *treeRoot;
    int count;

    // private helper methods
    Node* newNode();
    Node* add(Node*, T);
    Node* remove(Node*, T);
    void removeAll(Node*);
    Node* largest(Node*);
    Node* smallest(Node*);
    Node* pluckLargest(Node*);
    Node* pluckSmallest(Node*);
    Node* find(Node*, T);
    Node* balanceTree(Node*);
    int balanceFactor(Node*);
    Node* rotateLeft(Node*);
    Node* rotateRight(Node*);
    void updateHeight(Node*);
    int max(int, int);
    std::string getPosition(Node*, T);

};

#endif
