//file binarytree.cpp
//author Dr. Y 
//date October 23, 2018   caveat: try it with your client program of PA6 to test it

// Implementation of ADT Binary Tree
//    Data object: A binary tree T that is either empty or in the form
//                      r
//                   /     \
//                 TL      TR
// where TL and TR are binary trees.
//data structure: a linked binary tree
//operations: create, destroy, copy/create, copy, preorder traversal, inorder traversal,
//            postorder traversal, make a full tree of height 2, make a complete tree of height 3

#include "binarytree.h"
#include "pch.h"
#include <iostream>
using namespace std;

// ***************** recursive helpers *****************

//Copies one binary tree to another
//pre oldtreep points to the root of a binary tree
//post: newtreep points to the root of a binary tree
//  that has copies of the nodes of oldtreep's tree
//usage: copyTree (newptr, oldptr);
void copyTree (TreeNode*& newtreep, TreeNode* oldtreep) throw (Exception)
{
   if (oldtreep == nullptr)
   {
	   newtreep = nullptr;
   } else {
	  // newtreep = new (nothrow) TreeNode(oldtreep -> item, nullptr, nullptr);
	   if (newtreep == nullptr)
	   {
		   throw Exception("BinaryTree: no room in the heap for a node");
	   }
	   copyTree(newtreep -> leftChild, oldtreep -> leftChild);
	   copyTree(newtreep -> rightChild, oldtreep -> rightChild);
   }
}

//Releases memory for a binary tree
//pre: treep points to the root of a binary tree
//post: releases all of the nodes in the tree pointed to by treep
//    and leaves treep empty.
//usage: destroyTree (mroot);
void destroyTree (TreeNode*& treep)
{
   if (treep != nullptr)
   {
	   destroyTree(treep -> leftChild);
	   destroyTree(treep -> rightChild);
	   delete treep;
	   treep = nullptr;
   }
}

// recursive helper for prettyDisplay.
// pre: treep is assigned a pointer into a binary tree and level >= 1
// post: prints the tree in a user-friendly fashion as a binary tree
//       rotated 90 degrees
void writePretty (TreeNode* treep, int level)
{
	// waiting for the best one
}

// ********** recursive helpers for the traversals ****************
//pre: treep points to the root of a binary tree to be traversed
//post: prints the item objects in the nodes on the screen in the 
//     specified order. the items are separated by commas
//usage: preorder (mroot);   
//       similarly for the others
/*void preorder (TreeNode* treep)
{
	if (treep != nullptr)
	{
		cout << treep -> item << ", ";
		preorder(treep -> leftChild);
		preorder(treep -> rightChild);
	}
}

void inorder (TreeNode* treep)
{
	if (treep != nullptr)
	{
		inorder(treep -> leftChild);
		cout << treep -> item << ", ";
		inorder(treep -> rightChild);
	}
}

void postorder (TreeNode* treep)
{
	if (treep != nullptr)
	{
		postorder(treep -> leftChild);
		postorder(treep -> rightChild);
		cout << treep -> item << ", ";
	}
}
*/
// **************************public methods************************


//creates an empty binary tree
//post: object is an empty binary tree
//usage: BinaryTree zags;
BinaryTree::BinaryTree()
{
   root = nullptr;
}

//creates a new binary tree that is a copy of an existing tree
//post: object is a copy of rightHandSideTree
//throws an exception if there is not enough room in the
//       heap to make the copied tree
//usage: BinaryTree zags (bulldog);
BinaryTree::BinaryTree(const BinaryTree& rightHandSideTree) throw (Exception)
{
   root = nullptr;
   copyTree(root, rightHandSideTree.root);
}

//releases the memory of a binary tree
//pre: object exists
//post: memory for the object has been released. object theoretically does not exist
//       but in practice, it is empty.
BinaryTree::~BinaryTree()
{
   destroyTree(root);
}

// ******************** member functions ********************************************
//@pre: binary tree object exists
// **********************************************************************************

//checks for an empty tree
//post: returns true if the object is empty; else returns false
//usage: if (tree.isEmpty())
bool BinaryTree::isEmpty() const
{
   return (root == nullptr);
}

//copies one tree to another
//pre: rightHandSideTree is an assigned tree.
//post: object is a copy of rightHandSideTree
//throws an exception if there is not enough room in the
//       heap to make the copied tree
//usage: atree = btree = ctree;
BinaryTree& BinaryTree::operator=(const BinaryTree& rightHandSideTree) throw (Exception)
{
   if (this != &rightHandSideTree)
   {
	   destroyTree(root);
	   copyTree(root, rightHandSideTree.root);
   }
   return *this;
}

//prints the tree to look like a computer science tree
//post: outputs the tree as in the example below
//
//                        bar
//                  foo
//                        geeU
//  root ->  queue
//                        stack
//                  list
//                        array
//nodes at the same level are indented the same.
//Viewer must rotate head 90 degrees in order to look like a cs tree
//usage: tree.prettyDisplay();
void BinaryTree::prettyDisplay()
{
	writePretty(root, 1);
}

// *************** on the following traversals

//post: prints the objects in the tree in order specified
//usage: tree.preorderTraverse();  
//similarly for the other traversals
// *****************************************************




BinaryTree::BinaryTree()
{
}


BinaryTree::~BinaryTree()
{
}
