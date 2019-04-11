//
// Specification of ADT Dictionary as ADT Binary Search Tree
//    Data object: A binary search tree T that is either empty or in the form
// 	       	   root
//           //    \
//	tree left       tree right
// where tree left and tree right are binary search trees. 
// data structure: a linked binary search tree
//     operations: create, destroy
//                 search the dictionary for an item given its text
//                 insert a new item into the dictionary 
//                 remove an item from the dictionary given its text
//   associated operations: input and output
// filename binarysearchtree.cpp
// date: October 24, 2018


#include "binarysearchtree.h"
#include "treenode.h"
#include "pch.h"
#include <string>
#include <iostream>

// recursive helper functions

void changeHelpers(string myname, const char option, TreeNode*& treep, int mylevel, int myattendance, string mybook)
{
	 if (treep != nullptr)
   {
      if (myname == treep -> studentName)
      {
          if (option == 'd')
		  {
			  treep -> level = mylevel;
		  }
		  else if(option == 'e')
		  {
			  treep -> attendance = myattendance;
		  }
		  else 
			  treep -> typeOfBook = mybook;
		 
      } else if (myname < treep -> studentName) {
         changeHelpers(myname, option, treep -> leftChild, mylevel, myattendance, mybook);
      } else {
         changeHelpers(myname, option, treep -> rightChild, mylevel, myattendance, mybook);
      }
   } else {
      cout << "Student not found!" << endl;
   }
}
//Releases memory for a binary tree
//pre: treep points to the root of a binary tree
//post: releases all of the nodes in the tree pointed to by treep
//    and leaves treep empty.
//usage: destroyBST (mroot);
void destroyBST(TreeNode*& treep)
{
	if ( treep != nullptr )
	{
		destroyBST ( treep -> leftChild );
		destroyBST ( treep -> rightChild );
		delete treep;
		treep = nullptr;
	}
}

// searches for smallest element in tree
// pre: treep is pointer to binary search tree
// post: anItem gets smallest element in subtree
// usage: searchSmallestHelper(treep -> rightChild, anItem);
bool searchSmallestHelper( TreeNode* treep, string& anItem)
{
	
	if ( treep != nullptr )
	{
		bool isNull = searchSmallestHelper(treep->leftChild, anItem);
		
		if ( isNull )
			anItem = treep -> studentName;
		
		return false;
	} else
		return true;
		
}

// removes the item associated with a given text from the dictionary
// pre: targetText is assigned
// post: if BinarySearchTree object is not empty and 
//           targetText is found in Dictionary object
//           and the associated Item object (text and meaning) has been 
//           removed from the Dictionary object 
//       else throw an exception if not found or if empty
// usage: deleteHelper(targetText, root);
void deleteHelper(const string& myname, TreeNode*& treep)
{
	if (treep != nullptr)
	{
		if (myname == treep -> studentName)
		{
			if ( treep -> rightChild == nullptr and treep -> leftChild == nullptr ) {
				delete treep;
				treep = nullptr;
			}
			else if ( treep -> rightChild != nullptr and treep -> leftChild == nullptr) {
				TreeNode* deletePtr = treep;
				treep = treep -> rightChild;
				
				deletePtr -> rightChild = nullptr;
				delete deletePtr;
				deletePtr = nullptr;
			} else if ( treep -> rightChild == nullptr and treep -> leftChild != nullptr) {
				TreeNode* deletePtr = treep;
				treep = treep -> leftChild;
				
				deletePtr -> leftChild = nullptr;
				delete deletePtr;
				deletePtr = nullptr;
			} else {
				string minimumItem;
				
				searchSmallestHelper(treep -> rightChild, minimumItem);
				
				treep -> studentName = minimumItem;
				
				deleteHelper(minimumItem, treep -> rightChild);
			}
		} else if (myname < treep -> studentName) {
			deleteHelper(myname, treep -> leftChild);
		} else {
			deleteHelper(myname, treep -> rightChild);
		}
	} else {
		throw Exception("That student was not found in the report");
	}
}

// rebalances a binary tree
// pre: infile has items with keys in sorted order
// post: treep posts to a balanced BST containing items from infile
// usage: readTree(infile, root, numberOfEntries);
void readTree(istream& infile, TreeNode*& treep, int numberOfStudents) throw (Exception)
{
   if (numberOfStudents > 0)
   {
	  string myname, mybook;
	  int mylevel, myattendance, mygrades;
	  
      treep = new (nothrow) TreeNode(myname, mylevel, myattendance, mybook, mygrades, nullptr, nullptr);
	  
	  if ( treep == nullptr )
		  throw Exception("There was not enough memory to fully load tree, closing program.");
	  
      readTree(infile, treep -> leftChild, numberOfStudents / 2);
	  
      infile >> myname;
	  infile >> mylevel;
	  infile >> myattendance;
	  infile >> mybook;
	  infile >> mygrades;
	  
      readTree(infile, treep -> rightChild, (numberOfStudents - 1) / 2);
   }
}

// prints out the list in order
// pre: treep is assigned assigned a pointer to a root node of a binary search tree
// post: the tree is displayed on screen or saved to file depending on output
// usage: inorderHelper(output, root);

void inorderHelper(ostream& output, TreeNode* treep)
{	
	if (treep != nullptr)
	{
		inorderHelper(output, treep -> leftChild);
		output << treep -> studentName << "   			";
		output << treep -> level << "   		";
		output << treep -> attendance << "   		";
		output << treep -> typeOfBook << "    		";
		output << treep -> grade << " ";
		output << endl;
		inorderHelper(output, treep -> rightChild);
	}
}

// searches a binary search tree for a certain text
// pre: treep is assigned a pointer to a root node of a binary search tree
//      targetText is assigned
// post: if targetText is found in the tree whose root node is treep
//          then the item in the root node is copied into anItem and
//          returns true; otherwise, returns false
// usage: isFound = searchHelper(root, targetText, anItem);
bool searchHelper(TreeNode* treep, string& myname, int& mylevel, int& myattendance, int& mygrades, string& mybook,  bool& isFound)
{
   if (treep != nullptr)
   {
      if (myname == treep -> studentName && mygrades == treep -> grade)
      {
          myname = treep -> studentName;
		  mylevel = treep -> level;
		  myattendance = treep -> attendance;
		  mygrades = treep -> grade;
		  mybook = treep -> typeOfBook;
         return true;
		 
      } else if (myname < treep -> studentName) {
         return searchHelper(treep -> leftChild, myname, mylevel, myattendance, mygrades, mybook, isFound);
      } else {
         return searchHelper(treep -> rightChild, myname, mylevel, myattendance, mygrades, mybook, isFound);
      }
   } else {
      return false;
   }
}

// recursive helper for addNewEntry
// pre: newItem has been assigned
// post: if there is room in the BinarySearchTree object and newItem's text
//            is not already there then newItem is appropriately added
//       else it throws an exception for either a full dictionary or
//            a message that it is already there
// usage: myDictionary.addNewEntry(myItem, isFull, isAlreadyThere);
void addHelper(TreeNode*& treep, const string& myname, const int& mylevel, const int& myattendance, const int& mygrades, const string& mybook ) throw (Exception)
{
	if (treep != nullptr)
	{
		if (myname == treep -> studentName)
		{
			throw Exception("Student already exists");
		} else if ( myname < treep -> studentName) {
			addHelper(treep -> leftChild, myname, mylevel, myattendance, mygrades, mybook );
		} else {
			addHelper(treep -> rightChild, myname, mylevel, myattendance, mygrades, mybook );
		}
	} else {
		treep = new (nothrow) TreeNode(myname, mylevel, myattendance, mybook, mygrades, nullptr, nullptr);
   } 
   
   if ( treep == nullptr )
	   throw Exception("There was not enough memory to add a new student.");
}

void printToFileHelper(ostream& output, TreeNode*& treep)
{
	if (treep != nullptr)
	{
		printToFileHelper(output, treep -> leftChild);
		output << treep -> studentName << endl;
		output << treep -> level << endl;
		output << treep -> attendance << endl;
		output << treep -> typeOfBook << endl;
		output << treep -> grade << endl;
		output << endl;
		printToFileHelper(output, treep -> rightChild);
	}
}

// displays dictionary onscreen or inputs
// 		into a file depending on output
// pre: output has been opened if it is a file
//      rightHandSideDictionary has been assigned items
// post: output contains each item on a separate line in the format
//		1
//		brb be right back
// usage: outfile << myDictionary;  
//
// Know it is not necessary, I just like the completeness it provides.  
/*ostream& operator<< (ostream& output)
{
	return output;
}*/

// inputs items into a dictionary
// pre: input has been opened if it is a file
//      items are arranged in the following format
//      2
//      lol
//      laugh out loud
//      ttyl
//      talk to you later
// post: if there is room, 
//       all items in the input have been stored in rightHandSideDictionary
// usage: infile >> myDictionary;
istream& operator>> (istream& input, BinarySearchTree& rightHandSideDictionary) throw (Exception)
{
	char newline;
	
	// If tree already exists, destroy the tree to prevent memory leak
	if ( rightHandSideDictionary.root != nullptr )
	{
		destroyBST( rightHandSideDictionary.root );
	}
		
	input >> rightHandSideDictionary.numberOfStudents;
	input.get(newline);
		
	readTree(input, rightHandSideDictionary.root, rightHandSideDictionary.numberOfStudents);

	return input;
}

// creates a new binary search tree
// post: BinarySearchTree object exists but is empty
// usage: BinarySearchTree myDictionary;	
BinarySearchTree::BinarySearchTree()
{
	numberOfStudents = 0;
}

// destroys a binary search tree
// pre: BinarySearchTree object exists
// post: all memory for BinarySearchTree object has been freed
// usage: automatically done at the end of scope
BinarySearchTree::~BinarySearchTree()
{
	
}

// searchs for a meaning with a given text
// pre targetText has been assigned a value not already in the hash table
// post if an item with texting abbreviationthe same as targetText is found then
//          isFound is true and theItem is that item
//       else isFound is false
// usage  myDictionary.searchForMeaning(targetText, anItem, isFound);
void BinarySearchTree::searchForStudent(string& myname, int& mylevel, int& myattendance, int& mygrades, string& mybook,  bool& isFound)
{
	isFound = searchHelper(root, myname, mylevel, myattendance, mygrades, mybook, isFound);
}

// inserts a new text' item into the dictionary
// pre: newItem has been assigned
// post: if there is room in the BinarySearchTree object and newItem's text
//            is not already there then newItem is appropriately added
//       else it throws an exception for either a full dictionary or
//            a message that it is already there
// usage: myDictionary.addNewEntry(myItem, isFull, isAlreadyThere);
void BinarySearchTree::addNewStudent(const string& myname, const int& mylevel, const int& myattendance, const int& mygrades, const string& mybook ) throw (Exception)
{
	addHelper(root, myname, mylevel, myattendance, mygrades, mybook );
	numberOfStudents++;
}

// removes the item associated with a given text from the dictionary
// pre: targetText is assigned
// post: if BinarySearchTree object is not empty and 
//           targetText is found in Dictionary object
//           and the associated Item object (text and meaning) has been 
//           removed from the Dictionary object 
//       else throw an exception if not found or if empty
// usage: myDictionary.deleteEntry(targetText);
void BinarySearchTree::deleteStudent(const string& myname) throw (Exception)
{
	deleteHelper(myname, root);
	numberOfStudents--;
}

// prints out on screen or to file the BST in alphabetical order
// pre: tree exists
// post: prints out on screen or to file number of items followed by
//		the tree in alphabetical order, formatted 
//		2
//		afk away from keyboard
// 		brb be right back
//usage: tree.inorderTraverse(cout);  
// *****************************************************
void BinarySearchTree::inorderTraverse(ostream& output) const
{
	cout << endl;
	output << "Number of students: " << numberOfStudents << endl;
	output << "|Student's Name| ";
	output << "Student's level| ";
	output << "Student's attendance| ";
	output << "Student's current book| ";
	output << "Student's pin number| ";
	output << endl;
	inorderHelper(output, root);
	cout << endl;
}

void BinarySearchTree::printSingleStudent(ostream& output, string& myname, int& myPin)
{
	cout << endl;
	int myattendance, mylevel;
	string mybook;
	bool isFound = searchHelper(root, myname, mylevel, myattendance, myPin, mybook, isFound);
	if (isFound)
	{
		cout << "Student's name: " << myname << endl;
		cout << "Level: " << mylevel << endl;
		cout << "Attendance: " << myattendance << endl;
		cout << "Currently reading book: " << mybook << endl;
		cout << "Pin Number: " << myPin << endl;
		cout << endl;
	}
	else
		cout << "Student not found" << endl;
}

void BinarySearchTree::printToFile(ostream& output)
{
	output << numberOfStudents << endl;
	printToFileHelper(output, root);
}

void BinarySearchTree::changeLevel(const char option, string myname, int mylevel)
{
	int myattendance;
	string mybook;
	changeHelpers(myname, option, root, mylevel, myattendance, mybook);
}

void BinarySearchTree::changeAttendance(const char option, string myname, int myattendance)
{
	int mylevel;
	string mybook;
	changeHelpers(myname, option, root, mylevel, myattendance, mybook);
}

void BinarySearchTree::changeBook(const char option, string myname, string mybook)
{
	int mylevel, myattendance;
	changeHelpers(myname, option, root, mylevel, myattendance, mybook);
}




BinarySearchTree::BinarySearchTree()
{
}


BinarySearchTree::~BinarySearchTree()
{
}
