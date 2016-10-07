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


#include "avltree.h"
#include "deque.h"
#include "gtest/gtest.h"

/* Test add and remove methods */
TEST(AvlTreeTest, GeneralTests) {
    AVLTree<int> tree;
    ASSERT_EQ(tree.size(), 0);
    ASSERT_EQ(tree.contains(5), false);
    ASSERT_EQ(tree.isEmpty(), true);
    ASSERT_EQ(reinterpret_cast<const long>(tree.largest()), NULLPTR);
    ASSERT_EQ(reinterpret_cast<const long>(tree.smallest()), NULLPTR);
    // try removing element from empty tree
    ASSERT_EQ(tree.remove(1), false);
    // add integers between -5 and 5
    for (int j = -5; j <= 5; ++j) {
        ASSERT_EQ(tree.add(j), true);
    }
    ASSERT_EQ(tree.contains(5), true);
    ASSERT_EQ(tree.size(), 11);
    ASSERT_EQ(tree.isEmpty(), false);
    ASSERT_EQ(*(tree.largest()), 5);
    ASSERT_EQ(*(tree.smallest()), -5);
    // delete every other element
    for (int j = -5; j <= 5; j += 2) {
        ASSERT_EQ(tree.remove(j), true);
    }
    ASSERT_EQ(tree.contains(5), false);
    ASSERT_EQ(tree.size(), 5);
    ASSERT_EQ(*(tree.largest()), 4);
    ASSERT_EQ(*(tree.smallest()), -4);
    // try deleting non-existent element
    ASSERT_EQ(tree.remove(-20), false);
    ASSERT_EQ(tree.size(), 5);
    // try adding element already in the tree
    ASSERT_EQ(tree.add(0), false);
    ASSERT_EQ(tree.size(), 5);
    tree.removeAll();
    ASSERT_EQ(tree.size(), 0);
}

/* Test print method and tree structure */
TEST(AvlTreeTest, AddRemoveStructureTest) {
    AVLTree<int> tree;
    // try getting position of non-existent element

    /*---------------ADD TESTING-------------*/

    ASSERT_EQ(tree.getPosition(5), "");
    tree.add(5);
    ASSERT_EQ(tree.getPosition(5), "()");
    tree.add(4);
    ASSERT_EQ(tree.getPosition(5), "()");
    ASSERT_EQ(tree.getPosition(4), "(L)");
    tree.add(3);
    ASSERT_EQ(tree.getPosition(5), "(R)");
    ASSERT_EQ(tree.getPosition(4), "()");
    ASSERT_EQ(tree.getPosition(3), "(L)");
    tree.add(2);
    ASSERT_EQ(tree.getPosition(5), "(R)");
    ASSERT_EQ(tree.getPosition(4), "()");
    ASSERT_EQ(tree.getPosition(3), "(L)");
    ASSERT_EQ(tree.getPosition(2), "(LL)");
    tree.add(1);
    ASSERT_EQ(tree.getPosition(5), "(R)");
    ASSERT_EQ(tree.getPosition(4), "()");
    ASSERT_EQ(tree.getPosition(3), "(LR)");
    ASSERT_EQ(tree.getPosition(2), "(L)");
    ASSERT_EQ(tree.getPosition(1), "(LL)");
    tree.add(6);
    ASSERT_EQ(tree.getPosition(5), "(R)");
    ASSERT_EQ(tree.getPosition(4), "()");
    ASSERT_EQ(tree.getPosition(3), "(LR)");
    ASSERT_EQ(tree.getPosition(2), "(L)");
    ASSERT_EQ(tree.getPosition(1), "(LL)");
    ASSERT_EQ(tree.getPosition(6), "(RR)");
    tree.add(7);
    ASSERT_EQ(tree.getPosition(5), "(RL)");
    ASSERT_EQ(tree.getPosition(4), "()");
    ASSERT_EQ(tree.getPosition(3), "(LR)");
    ASSERT_EQ(tree.getPosition(2), "(L)");
    ASSERT_EQ(tree.getPosition(1), "(LL)");
    ASSERT_EQ(tree.getPosition(6), "(R)");
    ASSERT_EQ(tree.getPosition(7), "(RR)");
    tree.add(8);
    ASSERT_EQ(tree.getPosition(5), "(RL)");
    ASSERT_EQ(tree.getPosition(4), "()");
    ASSERT_EQ(tree.getPosition(3), "(LR)");
    ASSERT_EQ(tree.getPosition(2), "(L)");
    ASSERT_EQ(tree.getPosition(1), "(LL)");
    ASSERT_EQ(tree.getPosition(6), "(R)");
    ASSERT_EQ(tree.getPosition(7), "(RR)");
    ASSERT_EQ(tree.getPosition(8), "(RRR)");
    tree.add(9);
    ASSERT_EQ(tree.getPosition(5), "(RL)");
    ASSERT_EQ(tree.getPosition(4), "()");
    ASSERT_EQ(tree.getPosition(3), "(LR)");
    ASSERT_EQ(tree.getPosition(2), "(L)");
    ASSERT_EQ(tree.getPosition(1), "(LL)");
    ASSERT_EQ(tree.getPosition(6), "(R)");
    ASSERT_EQ(tree.getPosition(7), "(RRL)");
    ASSERT_EQ(tree.getPosition(8), "(RR)");
    ASSERT_EQ(tree.getPosition(9), "(RRR)");
    tree.add(10);
    ASSERT_EQ(tree.getPosition(5), "(RLL)");
    ASSERT_EQ(tree.getPosition(4), "()");
    ASSERT_EQ(tree.getPosition(3), "(LR)");
    ASSERT_EQ(tree.getPosition(2), "(L)");
    ASSERT_EQ(tree.getPosition(1), "(LL)");
    ASSERT_EQ(tree.getPosition(6), "(RL)");
    ASSERT_EQ(tree.getPosition(7), "(RLR)");
    ASSERT_EQ(tree.getPosition(8), "(R)");
    ASSERT_EQ(tree.getPosition(9), "(RR)");
    ASSERT_EQ(tree.getPosition(10), "(RRR)");
    tree.add(11);
    ASSERT_EQ(tree.getPosition(5), "(RLL)");
    ASSERT_EQ(tree.getPosition(4), "()");
    ASSERT_EQ(tree.getPosition(3), "(LR)");
    ASSERT_EQ(tree.getPosition(2), "(L)");
    ASSERT_EQ(tree.getPosition(1), "(LL)");
    ASSERT_EQ(tree.getPosition(6), "(RL)");
    ASSERT_EQ(tree.getPosition(7), "(RLR)");
    ASSERT_EQ(tree.getPosition(8), "(R)");
    ASSERT_EQ(tree.getPosition(9), "(RRL)");
    ASSERT_EQ(tree.getPosition(10), "(RR)");
    ASSERT_EQ(tree.getPosition(11), "(RRR)");
    tree.add(12);
    ASSERT_EQ(tree.getPosition(5), "(LRL)");
    ASSERT_EQ(tree.getPosition(4), "(L)");
    ASSERT_EQ(tree.getPosition(3), "(LLR)");
    ASSERT_EQ(tree.getPosition(2), "(LL)");
    ASSERT_EQ(tree.getPosition(1), "(LLL)");
    ASSERT_EQ(tree.getPosition(6), "(LR)");
    ASSERT_EQ(tree.getPosition(7), "(LRR)");
    ASSERT_EQ(tree.getPosition(8), "()");
    ASSERT_EQ(tree.getPosition(9), "(RL)");
    ASSERT_EQ(tree.getPosition(10), "(R)");
    ASSERT_EQ(tree.getPosition(11), "(RR)");
    ASSERT_EQ(tree.getPosition(12), "(RRR)");

    /*---------------REMOVE TESTING-------------*/

    // removing non-existent element should
    // leave the tree unchanged
    tree.remove(20);
    ASSERT_EQ(tree.getPosition(5), "(LRL)");
    ASSERT_EQ(tree.getPosition(4), "(L)");
    ASSERT_EQ(tree.getPosition(3), "(LLR)");
    ASSERT_EQ(tree.getPosition(2), "(LL)");
    ASSERT_EQ(tree.getPosition(1), "(LLL)");
    ASSERT_EQ(tree.getPosition(6), "(LR)");
    ASSERT_EQ(tree.getPosition(7), "(LRR)");
    ASSERT_EQ(tree.getPosition(8), "()");
    ASSERT_EQ(tree.getPosition(9), "(RL)");
    ASSERT_EQ(tree.getPosition(10), "(R)");
    ASSERT_EQ(tree.getPosition(11), "(RR)");
    ASSERT_EQ(tree.getPosition(12), "(RRR)");
    tree.remove(8);
    ASSERT_EQ(tree.getPosition(5), "(LRL)");
    ASSERT_EQ(tree.getPosition(4), "(L)");
    ASSERT_EQ(tree.getPosition(3), "(LLR)");
    ASSERT_EQ(tree.getPosition(2), "(LL)");
    ASSERT_EQ(tree.getPosition(1), "(LLL)");
    ASSERT_EQ(tree.getPosition(6), "(LR)");
    ASSERT_EQ(tree.getPosition(7), "(LRR)");
    ASSERT_EQ(tree.getPosition(8), "");
    ASSERT_EQ(tree.getPosition(9), "()");
    ASSERT_EQ(tree.getPosition(10), "(RL)");
    ASSERT_EQ(tree.getPosition(11), "(R)");
    ASSERT_EQ(tree.getPosition(12), "(RR)");
    tree.remove(9);
    ASSERT_EQ(tree.getPosition(5), "(LRL)");
    ASSERT_EQ(tree.getPosition(4), "(L)");
    ASSERT_EQ(tree.getPosition(3), "(LLR)");
    ASSERT_EQ(tree.getPosition(2), "(LL)");
    ASSERT_EQ(tree.getPosition(1), "(LLL)");
    ASSERT_EQ(tree.getPosition(6), "(LR)");
    ASSERT_EQ(tree.getPosition(7), "()");
    ASSERT_EQ(tree.getPosition(8), "");
    ASSERT_EQ(tree.getPosition(9), "");
    ASSERT_EQ(tree.getPosition(10), "(RL)");
    ASSERT_EQ(tree.getPosition(11), "(R)");
    ASSERT_EQ(tree.getPosition(12), "(RR)");
    tree.remove(11);
    ASSERT_EQ(tree.getPosition(5), "(LRL)");
    ASSERT_EQ(tree.getPosition(4), "(L)");
    ASSERT_EQ(tree.getPosition(3), "(LLR)");
    ASSERT_EQ(tree.getPosition(2), "(LL)");
    ASSERT_EQ(tree.getPosition(1), "(LLL)");
    ASSERT_EQ(tree.getPosition(6), "(LR)");
    ASSERT_EQ(tree.getPosition(7), "()");
    ASSERT_EQ(tree.getPosition(8), "");
    ASSERT_EQ(tree.getPosition(9), "");
    ASSERT_EQ(tree.getPosition(10), "(RL)");
    ASSERT_EQ(tree.getPosition(11), "");
    ASSERT_EQ(tree.getPosition(12), "(R)");
    tree.remove(12);
    ASSERT_EQ(tree.getPosition(5), "(RLL)");
    ASSERT_EQ(tree.getPosition(4), "()");
    ASSERT_EQ(tree.getPosition(3), "(LR)");
    ASSERT_EQ(tree.getPosition(2), "(L)");
    ASSERT_EQ(tree.getPosition(1), "(LL)");
    ASSERT_EQ(tree.getPosition(6), "(RL)");
    ASSERT_EQ(tree.getPosition(7), "(R)");
    ASSERT_EQ(tree.getPosition(8), "");
    ASSERT_EQ(tree.getPosition(9), "");
    ASSERT_EQ(tree.getPosition(10), "(RR)");
    ASSERT_EQ(tree.getPosition(11), "");
    ASSERT_EQ(tree.getPosition(12), "");
}


/* Test any special cases */
TEST(AvlTreeTest, SpecialCasesTest) {
    AVLTree<int> tree;
    tree.add(5);
    tree.add(4);
    tree.add(3);
    tree.add(2);
    tree.add(1);
    tree.add(6);
    tree.add(7);
    tree.add(8);
    tree.add(9);
    tree.add(10);
    tree.add(11);
    tree.add(12);
    tree.remove(8);
    tree.remove(9);
    tree.remove(11);
    ASSERT_EQ(tree.getPosition(5), "(LRL)");
    ASSERT_EQ(tree.getPosition(4), "(L)");
    ASSERT_EQ(tree.getPosition(3), "(LLR)");
    ASSERT_EQ(tree.getPosition(2), "(LL)");
    ASSERT_EQ(tree.getPosition(1), "(LLL)");
    ASSERT_EQ(tree.getPosition(6), "(LR)");
    ASSERT_EQ(tree.getPosition(7), "()");
    ASSERT_EQ(tree.getPosition(8), "");
    ASSERT_EQ(tree.getPosition(9), "");
    ASSERT_EQ(tree.getPosition(10), "(RL)");
    ASSERT_EQ(tree.getPosition(11), "");
    ASSERT_EQ(tree.getPosition(12), "(R)");
    tree.remove(7);
    ASSERT_EQ(tree.getPosition(5), "(LR)");
    ASSERT_EQ(tree.getPosition(4), "(L)");
    ASSERT_EQ(tree.getPosition(3), "(LLR)");
    ASSERT_EQ(tree.getPosition(2), "(LL)");
    ASSERT_EQ(tree.getPosition(1), "(LLL)");
    ASSERT_EQ(tree.getPosition(6), "()");
    ASSERT_EQ(tree.getPosition(7), "");
    ASSERT_EQ(tree.getPosition(8), "");
    ASSERT_EQ(tree.getPosition(9), "");
    ASSERT_EQ(tree.getPosition(10), "(RL)");
    ASSERT_EQ(tree.getPosition(11), "");
    ASSERT_EQ(tree.getPosition(12), "(R)");
    tree.removeAll();
    ASSERT_EQ(tree.size(), 0);
    tree.add(7);
    tree.add(4);
    tree.add(12);
    tree.add(2);
    tree.add(10);
    tree.add(13);
    tree.add(11);
    ASSERT_EQ(tree.getPosition(4), "(L)");
    ASSERT_EQ(tree.getPosition(2), "(LL)");
    ASSERT_EQ(tree.getPosition(7), "()");
    ASSERT_EQ(tree.getPosition(13), "(RR)");
    ASSERT_EQ(tree.getPosition(10), "(RL)");
    ASSERT_EQ(tree.getPosition(11), "(RLR)");
    ASSERT_EQ(tree.getPosition(12), "(R)");
    tree.remove(7);
    ASSERT_EQ(tree.getPosition(4), "(L)");
    ASSERT_EQ(tree.getPosition(2), "(LL)");
    ASSERT_EQ(tree.getPosition(7), "");
    ASSERT_EQ(tree.getPosition(13), "(RR)");
    ASSERT_EQ(tree.getPosition(10), "()");
    ASSERT_EQ(tree.getPosition(11), "(RL)");
    ASSERT_EQ(tree.getPosition(12), "(R)");
}


/*----------------------DEQUE TESTS-----------------*/

/* Test all methods */
TEST(DequeTests, ComprehensiveTests) {
    Deque<int> deq;
    ASSERT_EQ(deq.size(), 0);
    ASSERT_EQ(deq.isEmpty(), true);
    deq.addFront(1);
    ASSERT_EQ(deq.size(), 1);
    ASSERT_EQ(deq.peekFront(), 1);
    ASSERT_EQ(deq.peekBack(), 1);
    ASSERT_EQ(deq.isEmpty(), false);
    deq.addFront(-5);
    ASSERT_EQ(deq.size(), 2);
    ASSERT_EQ(deq.peekFront(), -5);
    ASSERT_EQ(deq.peekBack(), 1);

    ASSERT_EQ(deq.popFront(), -5);

    ASSERT_EQ(deq.size(), 1);
    ASSERT_EQ(deq.peekFront(), 1);
    ASSERT_EQ(deq.peekBack(), 1);

    deq.addBack(10);
    ASSERT_EQ(deq.size(), 2);
    ASSERT_EQ(deq.peekFront(), 1);
    ASSERT_EQ(deq.peekBack(), 10);

    ASSERT_EQ(deq.popBack(), 10);

    ASSERT_EQ(deq.size(), 1);
    ASSERT_EQ(deq.peekFront(), 1);
    ASSERT_EQ(deq.peekBack(), 1);

    ASSERT_EQ(deq.popBack(), 1);

    ASSERT_EQ(deq.size(), 0);
    ASSERT_EQ(deq.isEmpty(), true);
    ASSERT_THROW(deq.peekFront(), Deque<int>::EmptyListException);
    ASSERT_THROW(deq.peekBack(), Deque<int>::EmptyListException);
    ASSERT_THROW(deq.popFront(), Deque<int>::EmptyListException);
    ASSERT_THROW(deq.popBack(), Deque<int>::EmptyListException);
}

