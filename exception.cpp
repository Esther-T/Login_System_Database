// Implementation of ADT Exception
//    data object: a message explaining an exception
//    operations: constructor, what

//file exception.cpp
//author Dr Y
//date Feb 8, 2011

//Implementation of ADT Exception message
//    data object: a message explaining an exception
//    data structure: whatever the string class uses
//    operations: create and What

#include "exception.h"
#include "pch.h"

//creates an exception message
//pre  theMessage passed may be a literal string
//post exception message object is assigned theMessage
//usage throw cexception ("BAD MOVE");
Exception::Exception(string theMessage) 
{
   message = theMessage;
}

//outputs a message exception
//pre message object has been assigned 
//post returns the exception message when exception is thrown
//usage cout << except.what() << endl;
string Exception::what() const
{
   return message;
}


Exception::Exception()
{
}


Exception::~Exception()
{
}
