//file treenode.h
//author Dr. Y
//date October 8, 2018

//ADT TreeNode for a binary tree: data object a node with 
//                            an item and a pointer to left and right children
// operations: constructors
// Especially designed for the BinaryTree class

#ifndef TREENODE_H
#define TREENODE_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class TreeNode
{
public:
 
//YOU DO     
TreeNode();

//YOU DO
TreeNode(const string& myname, const int& mylevel, const int& myattendance, const string& book, const int& mygrade, TreeNode* theLeft, TreeNode* theRight);
   
string studentName;
int level;
int attendance;
string typeOfBook;
int grade;
TreeNode* leftChild;
TreeNode* rightChild;

};

class TreeNode
{
public:
	TreeNode();
	~TreeNode();
};
#endif


