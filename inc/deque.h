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


#ifndef DEQUE_H
#define DEQUE_H

/*
 * My deque class template.
 * by: Jeff Amari
 */

#ifndef NULLPTR
#define NULLPTR 0L
#endif

template <class T>
class Deque {

public:
    Deque();
    void addFront(T);
    void addBack(T);
    const T peekFront();
    const T peekBack();
    T popFront();
    T popBack();
    int size();
    bool isEmpty();
    ~Deque();

    // thrown if client attempts to
    // access elements in an empty list
    class EmptyListException {};

private:
    // declaration of a list node
    struct Node;

    // private member variables
    Node *front;
    Node *back;
    int count;

    // private helper methods
    Node *newNode(const T &e);

};









/**
 * Must include implementation in header file
 * since we cannot explicitly create a class
 * of type AVLTree<T>::Node*
 */

/******************************
 * Definition of a list node.
 ******************************/
template <class T>
struct Deque<T>::Node {
    T e;
    Node *next;
    Node *prev;
};

/**************************************
*        Implementation of Deque      *
*            Jeff Amari               *
***************************************/


// default constructor
template <class T>
Deque<T>::Deque() {
    count = 0;
    front = NULLPTR;
    back = NULLPTR;
}

// add value to front of the list
template <class T>
void Deque<T>::addFront(T e) {
    Node *tmp = front;
    front = newNode(e);
    front->next = tmp;
    if (tmp != NULLPTR) { tmp->prev = front; }
    else                { back = front;      }
    count++;
}

// add e to back of the list
template <class T>
void Deque<T>::addBack(T e) {
    Node *tmp = back;
    back = newNode(e);
    back->prev = tmp;
    if (tmp != NULLPTR) { tmp->next = back; }
    else                { front = back;     }
    count++;
}

// peek at the first element in the list
template <class T>
const T Deque<T>::peekFront() {
    if (front == NULLPTR) {
        EmptyListException emptyListException;
        throw emptyListException;
    }
    return front->e;
}

// peek at the last element in the list
template <class T>
const T Deque<T>::peekBack() {
    if (back == NULLPTR) {
        EmptyListException emptyListException;
        throw emptyListException;
    }
    return back->e;
}

// pop the first element off the list
template <class T>
T Deque<T>::popFront() {
    if (front == NULLPTR) {
        EmptyListException emptyListException;
        throw emptyListException;
    }
    T e = front->e;
    Node *tmp = front;
    front = front->next;
    if (front != NULLPTR) { front->prev = NULLPTR; }
    else                  { back = NULLPTR;        }
    delete tmp;
    count--;
    return e;
}

// pop the last element off the list
template <class T>
T Deque<T>::popBack() {
    if (back == NULLPTR) {
        EmptyListException emptyListException;
        throw emptyListException;
    }
    T e = back->e;
    Node *tmp = back;
    back = back->prev;
    if (back != NULLPTR) { back->next = NULLPTR; }
    else                 { front = NULLPTR;      }
    delete tmp;
    count--;
    return e;
}

// get the size of the list
template <class T>
int Deque<T>::size() {
    return count;
}

// check if the list is empty
template <class T>
bool Deque<T>::isEmpty() {
    return size() == 0;
}

// destructor: free all memory
template <class T>
Deque<T>::~Deque() {
    Node *nextNode = front;
    Node *prevNode = front;
    while (nextNode != NULLPTR) {
        nextNode = nextNode->next;
        delete prevNode;
        prevNode = nextNode;
    }
}


/* -----------------Private Methods------------*/

/*
 * private helper method to create a new node
 * containing e.
 */
template <class T>
typename Deque<T>::Node* Deque<T>::newNode(const T &e) {
    Node *node = new Node();
    node->e = e;
    node->next = NULLPTR;
    node->prev = NULLPTR;
    return node;
}


#endif
