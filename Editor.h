//Reese Ganaway, Aaron Aviles, Andrew Li

#ifndef _Editor
#define _Editor
	

#include <string>
#include "LinkedList.h"
#include "ListInterface.h"
#include <iostream>
#include "Position.h"
#include "LinkedStack.h"
#include "Command.h" 
#include <memory>
#include "BinarySearchTree.h"



class Editor {

private:

	//Linked List to hold the lines from the file
	LinkedList<string> fileLines;
	Position p;

	
	//holds entered commands. Most recent command will be at the top of the stack
	LinkedStack<Command> commandStack;

	//Holds the name of the file for future use
	char* fileLabel;

	//bool variable to indicate whether or not changes have been made to the file
	bool changes=false;


	//string keyWords[60];
	//^array for iteration 3

	//Binary search tree that will hold our key words
	BinarySearchTree<string> keywordTree;

public:

	//default constructor
	Editor();

	//parameterized constructor
	Editor(char*,string);

	//displays the lined in our LinkedList fileLines
	void displayLines();

	//deletes the caracter at the cursors position
	void deleteCurrentChar();

	void deleteCurrentLine();

	//function that runs the editor
	void run();

	//function to save changes to file
	void writeToFile();

	//function for handling commands given by user
	void commandCases(char);

	void undo();
};


#endif