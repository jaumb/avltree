
/**
 * List of explicit class tempate instantiations.
 * This is one method of avoiding including the class
 * template definition in the header file.
 * This file is #include'ed at the bottom of
 * the class definition file.
 */

#ifndef AVLTREE_TEMPLATES_H
#define AVLTREE_TEMPLATES_H

#include <string>

template class AVLTree<int>;
template class AVLTree<std::string>;

#endif
