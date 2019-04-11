// Implementation of ADT TreeNode

#include "treenode.h"
#include "pch.h"

TreeNode::TreeNode()
{
   leftChild = nullptr;
   rightChild = nullptr;
}

TreeNode::TreeNode(const string& myname, const int& mylevel, const int& myattendance, const string& book, const int& mygrade, TreeNode* theLeft, TreeNode* theRight)

{
   studentName = myname;
   level = mylevel;
   attendance = myattendance;
   typeOfBook = book;
   grade = mygrade;
   
   leftChild = theLeft;
   rightChild = theRight;
}


TreeNode::TreeNode()
{
}


TreeNode::~TreeNode()
{
}
