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

/*-----------------------------------
 * Implementation of avltree class.
 *---------------------------------*/

#include <iostream>
#include "avltree.h"
#include "deque.h"


/******************************
 * Definition of a tree node.
 ******************************/
template<class T>
struct AVLTree<T>::Node {
    T e;
    Node *left;
    Node *right;
    int height;
};

/******************************
 * Default constructor.
 ******************************/
template<class T>
AVLTree<T>::AVLTree() {
    treeRoot = NULLPTR;
    count = 0;
}

/******************************
 * Add element e to the tree.
 ******************************/
template<class T>
bool AVLTree<T>::add(T e) {
    int prevSize = size();
    treeRoot = add(treeRoot, e);
    return prevSize != size();
}

/******************************
 * Remove element e from the
 * tree.
 ******************************/
template<class T>
bool AVLTree<T>::remove(T e) {
    int prevSize = size();
    treeRoot = remove(treeRoot, e);
    return prevSize != size();
}

/******************************
 * Remove all elements from the
 * tree.
 ******************************/
template<class T>
void AVLTree<T>::removeAll() {
    removeAll(treeRoot);
    treeRoot = NULLPTR;
}

/******************************
 * Print the tree to stdout.
 * Mainly for debugging.
 ******************************/
template<class T>
void AVLTree<T>::printTree() {
    Deque<Node*> q;
    if (treeRoot != NULLPTR) { q.addBack(treeRoot); }
    while (!q.isEmpty()) {
        Node *node = q.popFront();
        if (node->left != NULLPTR)  { q.addBack(node->left); }
        if (node->right != NULLPTR) { q.addBack(node->right); }
        std::cout << node->e << " ";
        std::cout << getPosition(node->e) << std::endl;
    }
}

/******************************
 * Find the position of e in
 * the tree rooted at root.
 * Position is specified by ()
 * for root and by the node's
 * position relative to root
 * for all other nodes
 * (e.g. (LLR) etc...).
 * If e is not in the tree it
 * returns and empty string.
 ******************************/
template<class T>
std::string AVLTree<T>::getPosition(T e) {
    return getPosition(treeRoot, e);
}

/******************************
 * Free all memory.
 ******************************/
template<class T>
AVLTree<T>::~AVLTree() {
    removeAll();
}

/******************************
 * Get the number of nodes in
 * the tree.
 ******************************/
template<class T>
int AVLTree<T>::size() {
    return count;
}

/******************************
 * Check if the tree is empty.
 ******************************/
template<class T>
bool AVLTree<T>::isEmpty() {
    return size() == 0;
}

/******************************
 * Check if the tree contains
 * element e.
 ******************************/
template<class T>
bool AVLTree<T>::contains(T e) {
    return find(treeRoot, e) != NULLPTR;
}

/******************************
 * Find the largest element
 * in the tree.
 * Returns NULLPTR if tree is
 * empty.
 ******************************/
template<class T>
const T* AVLTree<T>::largest() {
    Node *node = largest(treeRoot);
    return (node == NULLPTR) ? NULLPTR : &(node->e);
}

/******************************
 * Find the smallest element
 * in the tree.
 * Returns NULLPTR if tree is
 * empty.
 ******************************/
template<class T>
const T* AVLTree<T>::smallest() {
    Node *node = smallest(treeRoot);
    return (node == NULLPTR) ? NULLPTR : &(node->e);
}




/*-----------PRIVATE METHODS----------*/



/*
 * Private helper method for finding
 * the maximum of two integers.
 */
template<class T>
int AVLTree<T>::max(int x, int y) {
    return (x > y) ? x : y;
}

/*
 * Private helper method for creating
 * and initializing a new node.
 */
template<class T>
typename AVLTree<T>::Node* AVLTree<T>::newNode() {
    Node *node = new Node;
    node->left = NULLPTR;
    node->right = NULLPTR;
    node->height = 1;
    return node;
}

/*
 * Private helper method to add element e
 * to the tree rooted at root.
 */
template<class T>
typename AVLTree<T>::Node* AVLTree<T>::add(Node *root, T e) {
    if (root == NULLPTR) {
        Node *node = newNode();
        node->e = e;
        count++;
        return node;
    } else if (e < root->e) {
        root->left = add(root->left, e);
    } else if (e > root->e) {
        root->right = add(root->right, e);
    } else { return root; } // e is already in the tree

    updateHeight(root);
    return balanceTree(root);
}

/*
 * Private helper method to remove element e
 * from the tree rooted at root.
 */
template<class T>
typename AVLTree<T>::Node* AVLTree<T>::remove(Node *root, T e) {
    if (root == NULLPTR) {
        return NULLPTR;
    } else if (e < root->e) {
        root->left = remove(root->left, e);
    } else if (e > root->e) {
        root->right = remove(root->right, e);
    } else {
        // we found e if we reach this point
        Node *newRoot = NULLPTR;
        if (balanceFactor(root) > 0) { // left must not be empty
            newRoot = largest(root->left);
            newRoot->left = pluckLargest(root->left);
            newRoot->right = root->right;
        } else {
            newRoot = smallest(root->right);
            if (newRoot != NULLPTR) { // in case right is empty
                newRoot->right = pluckSmallest(root->right);
                newRoot->left = root->left;
            }
        }
        updateHeight(newRoot);
        delete root;
        count--;
        return balanceTree(newRoot);
    }

    updateHeight(root);
    return balanceTree(root);
}

/*
 * Private helper method to remove the
 * node containing the largest element
 * in the tree rooted at root.
 */
template<class T>
typename AVLTree<T>::Node* AVLTree<T>::pluckLargest(Node *root) {
    if (root == NULLPTR)
        return NULLPTR;
    else if (root->right == NULLPTR)
        return root->left;
    else
        root->right = pluckLargest(root->right);

    updateHeight(root); // required
    return balanceTree(root);
}

/*
 * Private helper method to remove the
 * node containing the smallest element
 * in the tree rooted at root.
 */
template<class T>
typename AVLTree<T>::Node* AVLTree<T>::pluckSmallest(Node *root) {
    if (root == NULLPTR)
        return NULLPTR;
    else if (root->left == NULLPTR)
        return root->right;
    else
        root->left = pluckSmallest(root->left);

    updateHeight(root); // required
    return balanceTree(root);
}

/*
 * Private helper method to get the node
 * containing the largest element in the
 * tree rooted at root.
 */
template<class T>
typename AVLTree<T>::Node* AVLTree<T>::largest(Node *root) {
    if (root == NULLPTR) { return NULLPTR; }
    while (root->right != NULLPTR)
        root = root->right;
    return root;
}

/*
 * Private helper method to get the node
 * containing the smallest element in the
 * tree rooted at root.
 */
template<class T>
typename AVLTree<T>::Node* AVLTree<T>::smallest(Node *root) {
    if (root == NULLPTR) { return NULLPTR; }
    while (root->left != NULLPTR)
        root = root->left;
    return root;
}

/*
 * Private helper method to find the node
 * containing element e in the tree rooted
 * at root.
 */
template<class T>
typename AVLTree<T>::Node* AVLTree<T>::find(Node *root, T e) {
    if (root == NULLPTR)
        return NULLPTR;
    else if (e < root->e)
        return find(root->left, e);
    else if (e > root->e)
        return find(root->right, e);
    else
        return root;
}

/*
 * Private helper method for balancing the
 * tree rooted at root.
 */
template<class T>
typename AVLTree<T>::Node* AVLTree<T>::balanceTree(Node *root) {
    if (root == NULLPTR) { return NULLPTR; }
    int bf = balanceFactor(root);
    if (bf < -1) {
        if (balanceFactor(root->right) > 0)
            root->right = rotateRight(root->right);
        return rotateLeft(root);
    } else if (bf > 1) {
        if (balanceFactor(root->left) < 0)
            root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    return root;
}

/*
 * Private helper method for checking
 * the balance factor of a given node.
 */
template<class T>
int AVLTree<T>::balanceFactor(Node *node) {
    if (node == NULLPTR) { return 0; }
    return ((node->left == NULLPTR) ? 0 : (node->left)->height) -
            ((node->right == NULLPTR) ? 0 : (node->right)->height);
}

/*
 * Private helper method to rotate the tree
 * rooted at root to the left.
 */
template<class T>
typename AVLTree<T>::Node* AVLTree<T>::rotateLeft(Node *root) {
    Node *newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

/*
 * Private helper method to rotate the tree
 * rooted at root to the right.
 */
template<class T>
typename AVLTree<T>::Node* AVLTree<T>::rotateRight(Node *root) {
    Node *newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

/*
 * Private helper method to update the height
 * of the tree rooted at root.
 */
template<class T>
void AVLTree<T>::updateHeight(Node *root) {
    if (root != NULLPTR) {
        int lHeight = (root->left == NULLPTR) ? 0 : (root->left)->height;
        int rHeight = (root->right == NULLPTR) ? 0 : (root->right)->height;
        root->height = max(rHeight, lHeight) + 1;
    }
}

/*
 * Private helper method to find the position of e
 * in the tree rooted at root.
 */
template<class T>
std::string AVLTree<T>::getPosition(Node *root, T e) {
    std::string pos;
    pos.push_back('(');
    while (root != NULLPTR && root->e != e) {
        if (e < root->e) {
            root = root->left;
            pos.push_back('L');
        } else if (e > root->e) {
            root = root->right;
            pos.push_back('R');
        }
    }
    pos.push_back(')');
    if (root == NULLPTR) { pos.clear(); }
    return pos;
}

/*
 * Private helper method to remove all nodes from
 * the tree rooted at root and free allocated memory.
 */
template<class T>
void AVLTree<T>::removeAll(Node *root) {
    Deque<Node*> q;
    if (root != NULLPTR) { q.addBack(root); }
    while (!q.isEmpty()) {
        Node *node = q.popFront();
        if (node->left != NULLPTR)  { q.addBack(node->left);  }
        if (node->right != NULLPTR) { q.addBack(node->right); }
        delete node;
        count--;
    }
}


/*
 * explicit class template instantiations.
 */
#include "avltreetemplates.h"
