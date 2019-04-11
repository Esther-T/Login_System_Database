//client.cpp

#include "binarysearchtree.h" 
#include "exception.h"
#include "binarytree.h"
#include <cstdlib>
#include <cstddef>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void openInputFile(ifstream& inputFile, string filename) ;
void loadItemsToTree(BinarySearchTree& mytree, int numberOfStudents, ifstream& infile);
void openOutputFile(ofstream& outputFile, string filename);
void enterInputFromUser(BinarySearchTree& mytree, ifstream& infile, ofstream& outfile);
void customerService(BinarySearchTree& mytree, ifstream& infile, ofstream& outfile, string& username, int& pinNum);
void menuOptions(BinarySearchTree& mytree, ifstream& infile, ofstream& outfile);
void performOptions(char option, BinarySearchTree& mytree, ifstream& infile, ofstream& outfile);
void printExceptionMessage(const Exception& except);
void saveToFile(BinarySearchTree& mytree, ofstream& outfile);

int main()
{
	ifstream infile;
	ofstream outfile;
	BinarySearchTree mytree;
	int numberOfStudents;
	
	loadItemsToTree(mytree, numberOfStudents, infile);
	enterInputFromUser(mytree, infile, outfile);
	cout << endl;
	cout << "Thank you and have a nice day 😀 " << endl;
	
	return 0;
}

void openInputFile(ifstream& inputFile, string filename) 
{
   inputFile.open(filename);
   if (inputFile.fail())
   {
      cout << "File failed to open!!!!" << endl;
      exit(1);
   }
}

void openOutputFile(ofstream& outputFile, string filename) 
{
   outputFile.open(filename);
   if (outputFile.fail())
   {
      cout << "File failed to open!!!!" << endl;
      exit(1);
   }
}

void loadItemsToTree(BinarySearchTree& mytree, int numberOfStudents, ifstream& infile)
{
	string myname, mybook;
	int myattendance, mylevel, pinNum;
	
	openInputFile(infile, "progress.dat");
	infile >> numberOfStudents;
	for (int i = 0; i < numberOfStudents; i++)
	{
		infile >> myname;
		infile >> mylevel;
		infile >> myattendance;
		infile >> mybook;
		infile >> pinNum;
		mytree.addNewStudent(myname, mylevel,myattendance, pinNum, mybook );
	}
	
	infile.close();
}

void enterInputFromUser(BinarySearchTree& mytree, ifstream& infile, ofstream& outfile)
{
	char newline;
	string username;
	int pinNum;
	    cout << endl;
		cout << "Enter your username > ";
		cin >> username;
		cout << endl;
		cout << "Enter your pinNumber > ";
		cin >> pinNum;
		
		cout << endl << endl;
		
		if (username == "aslanthelion" && pinNum == 888)
		{
		  menuOptions(mytree, infile, outfile);
		}
		else
		{
			customerService(mytree, infile, outfile, username, pinNum);
		}

}

void menuOptions(BinarySearchTree& mytree, ifstream& infile, ofstream& outfile)
{
	char option, newline;
	while (option != 'z')
	{
		cout << "Choose an option" << endl;
		cout << "Enter 'a' to print out full report" << endl;
		cout << "Enter 'b' to enter a new student" << endl;
		cout << "Enter 'c' to delete an existing student" << endl;
		cout << "Enter 'd' to change the level of an existing student" << endl;
		cout << "Enter 'e' to change the attendance of an existing student" << endl;
		cout << "Enter 'f' to change the book of an existing student" << endl;
		cout << "Enter 'z' to exit the program" << endl << endl;
		cin.get(newline);
		cout << "Enter your option here > ";
		
		cin.get(option);
		
		performOptions(option, mytree, infile, outfile);
		
	}
	
	
	
}

void performOptions(char option, BinarySearchTree& mytree, ifstream& infile, ofstream& outfile)
{
	string myname, mybook;
	int myattendance, myPin, mylevel;
	
	if (option == 'a')
	{
		mytree.inorderTraverse(cout);
	}
	else if (option == 'b')
	{
		cout << "Enter Student's name > ";
		cin >> myname;
		cout << endl;
		cout << "Enter Student's level > ";
		cin >> mylevel;
		cout << endl;
		cout << "Enter Student's attendance > ";
		cin >> myattendance;
		cout << endl;
		cout << "Enter Student's current book > ";
		cin >> mybook;
		cout << endl;
		cout << "Enter Student's pin Number > ";
		cin >> myPin;
		cout << endl;
		
		try
		{
			mytree.addNewStudent(myname, mylevel, myattendance, myPin, mybook );
		}
		catch (Exception except)
		{
			printExceptionMessage(except);
		}
		
		saveToFile(mytree, outfile);
	}
	
	else if (option == 'c')
	{
		cout << "Enter Student's name > ";
		cin >> myname;
		cout << endl;
		mytree.deleteStudent(myname);
		saveToFile(mytree, outfile);
	}
	
	else if(option == 'd')
	{
		cout << "Enter student's name > ";
		cin >> myname;
		cout << "Enter student's new level > ";
		cin >> mylevel;
		mytree.changeLevel(option, myname, mylevel);
		saveToFile(mytree, outfile);
	}
	
	else if(option == 'e')
	{
		cout << "Enter student's name > ";
		cin >> myname;
		cout << "Enter student's new attendance > ";
		cin >> myattendance;
		mytree.changeAttendance(option, myname, myattendance);
		saveToFile(mytree, outfile);
	}
	
	else if(option == 'f')
	{
		cout << "Enter student's name > ";
		cin >> myname;
		cout << "Enter student's new book > ";
		cin >> mybook;
		mytree.changeBook(option, myname, mybook);
		saveToFile(mytree, outfile);
	}
}


void customerService(BinarySearchTree& mytree, ifstream& infile, ofstream& outfile, string& username, int& pinNum)
{
	mytree.printSingleStudent(cout, username, pinNum);
}

void printExceptionMessage(const Exception& except)
{
   cout << endl << endl;
   cout << except.what();
   cout << endl << endl;
}

void saveToFile(BinarySearchTree& mytree, ofstream& outfile)
{
	openOutputFile(outfile, "progress.dat");
	mytree.printToFile(outfile);
	outfile.close();
}

