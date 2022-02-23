#include <iostream>
#include "Editor.h"
#include "windows.h"
#include "Position.h"
#include <string>
#include <fstream>
#include "LinkedList.h"
#include <conio.h>
#include <memory>
#include <stdlib.h>

#define ARROWDOWN 80 
#define ARROWUP 72
#define ARROWLEFT 75
#define ARROWRIGHT 77



template <typename ITEMTYPE> int binarySearch(const ITEMTYPE*, int, int, ITEMTYPE);

void colorText(int);

template<class ItemType> void bubbleSort(ItemType*, int);

using namespace std;



//function place cursor at the specified coordinates/position
void placeCursorAt(Position coordinate) {

	COORD coord;

	coord.X = coordinate.getX();

	coord.Y = coordinate.getY();

	SetConsoleCursorPosition(

		GetStdHandle(STD_OUTPUT_HANDLE),

		coord);

}
//default constructor
Editor::Editor() {

}

//default 
Editor::Editor(char* fileName, string keywordFile){

	//opening file to read from and storing in inFile
	fstream inFile;
	inFile.open(fileName);
	fileLabel = fileName;


	//checking to make sure the file was open, quitting the program if not
	if (!inFile.is_open()) {
		cout << "The file failed to open.\n";
		return;
	}

	//string variables line and word to hold a line or word from the file
	string line;
	string word;
	int counter = 1;
	//adding each line from the file to a linked list
	while (!inFile.eof()) {
		getline(inFile, line);  //>>
		fileLines.insert(counter, line);
		counter++;
	}
	inFile.close();

	inFile.open("keywords.txt");
	//checking to make sure the file was open, quitting the program if not
	if (!inFile.is_open()) {
		cout << "The file failed to open.\n";
		return;
	}

	counter = 0;
	while (inFile>>word) {
		/*keyWords[counter] = line;
		counter++;   */
		//add each word from the keywords file to the binary search tree
		keywordTree.add(word);
	}

	//bubbleSort(keyWords,60); Sorting line from the 3rd iteration

	
}


void Editor::displayLines()
{
	system("CLS");
	int position;
	string nextLine, nextWord, line;


	// goes through each line in the linked list 
	for (position = 1; position <= fileLines.getLength(); position++)
	{
		nextLine = fileLines.getEntry(position);

		int i = 0;
		while (i < nextLine.length()) {
			string word;
			// isolate a word at a time (can contain underscores)
			if (isalpha(nextLine[i])) {
				while (isalpha(nextLine[i]) || nextLine[i] == '_') {
					word += nextLine[i];
					i++;
				}
				/*int numKeywords = 0;
				for (int i = 0; i < 60; i++) {
					if (keyWords[i] != "") {
						numKeywords++;
					}
				}
				if (binarySearch <string> (keyWords, 0, numKeywords - 1, word) != -1)  //found */
				if(keywordTree.contains(word))
					colorText(1);
				else
					colorText(0);
				cout << word;
			}

			else {
colorText(0);
cout << nextLine[i];
i++;
			}

		}

		cout << endl;
	}
	placeCursorAt(p);
} // end displayLines

//deletes character at the current position
void Editor::deleteCurrentChar() {

	//variable to hold the string we want to delete a character from
	string replacementLine = fileLines.getEntry(p.getY() + 1);

	//create a command object "hold" and place it into the stack for if undo is needed"
	Command hold(Position(p.getX(), p.getY()), 'x', replacementLine[p.getX()]);
	commandStack.push(hold);

	//deleting the character from our replacement string and replacing the original string
	replacementLine.erase(replacementLine.begin() + p.getX());
	fileLines.replace(p.getY() + 1, replacementLine);

	//show our updated result 
	displayLines();

	//set "changes" to true so we know changes have been made
	changes = true;
}

//deletes the line our cursor is on
void Editor::deleteCurrentLine() {

	//create a command object "hold" and place it into the stack for if undo is needed"
	Command hold(Position(p.getX(), p.getY()), fileLines.getEntry(p.getY() + 1), 'd');
	commandStack.push(hold);


	fileLines.remove(p.getY() + 1);
	if (p.getY() > 0) {
		p.setY(p.getY() - 1);
		p.setX(fileLines.getEntry(p.getY() + 1).length() - 1);
	}
	p.setX(0);
	placeCursorAt(p);
	displayLines();

	//set "changes" to true so we know changes have been made
	changes = true;
}

//function to run the editor
void Editor::run() {

	//initialze character variable to hold the user commands
	char userCommand = ' ';
	displayLines();

	commandCases(userCommand);
	return;
}

//function for handling commands given by user
void Editor::commandCases(char userCommand) {

	string longCommand;
	//while the user isnt trying to quit
	while (userCommand != 'q') {

		//get user command, do not echo
		userCommand = _getch();

		//switch statement for all possible commands
		switch (userCommand) {

			//if user enters 'x'
		case 'x':
			deleteCurrentChar();
			break;

			//if user enters 'j' or down key
		case 'j':
		case ARROWDOWN:
			//if we arent yet at the bottom of the text file
			if (p.getY() < fileLines.getLength() - 1) {
				//if the current line is longer than the line below, set the x coordinate to the end 
				//of the shorter line
				if (p.getX() > fileLines.getEntry(p.getY() + 2).length() - 1) {
					p.setX(fileLines.getEntry(p.getY() + 2).length() - 1);
				}
				if (fileLines.getEntry(p.getY() + 2).empty()){
					p.setX(0);
				}
					p.setY(p.getY() + 1);
					
					placeCursorAt(p);
					
				}
				break;

			//if user enters 'k' or up key
			case 'k':
			case ARROWUP:
				//check to see if we are already at the top of the file
				if (p.getY() > 0) {
					//if the current line is longer than the above line, set the x coordinate to the end 
					//of the shorter line
					if (fileLines.getEntry(p.getY()).length()-1 < p.getX()) {
						p.setX(fileLines.getEntry(p.getY()).length() - 1);
					}
					if (fileLines.getEntry(p.getY()).empty()) {
						p.setX(0);
					}
					p.setY(p.getY() - 1);
					placeCursorAt(p);
				}
				break;

			//if user enters 'h' or left key
			case 'h':
			case ARROWLEFT:
				//if we aren't already at the beginning of the line
				if (p.getX() > 0) {
					if (!fileLines.getEntry(p.getY() + 1).empty()) {
						p.setX(p.getX() - 1);
						placeCursorAt(p);
					}
				}
				break;

			//if user enters 'l' or right key
			case 'l':
			case ARROWRIGHT:
				//if we aren't at the end of the line
				if (p.getX() < fileLines.getEntry(p.getY()+1).length() - 1) {
					if (!fileLines.getEntry(p.getY() + 1).empty()) {
						p.setX(p.getX() + 1);
						placeCursorAt(p);
					}
				}
				break;

			//case for deleting a whole line
			case 'd':
				userCommand = _getch();
				if (userCommand == 'd') {
					deleteCurrentLine();

				}
				break;
			
			case 'q':
				userCommand = ' ';
				break;

			case 'u':
				undo();
				break;

			//if user enters ':'
			case ':':
				//put cursor at the bottom of the editor
				placeCursorAt(Position(0, fileLines.getLength()));
				cout << "\n\n\n:";

				cin >> longCommand;

				//if the user entered w
				if (longCommand == "w") {
					writeToFile();
					changes = false;
					break;

				}
				//if changes were made to the file and the user tries to quit without saving
				else if (longCommand == "q") {
					if (changes == true) {
						char response;
						cout << "You have not saved your changes. Are you sure you would like to quit?\n"
							<< "Press 'q' to quit, or 'w' to save.";
						cin >> response;
						if (response == 'q') {
							return;
						}
						else if (response == 'w') {
							writeToFile();
							changes = false;
							break;
						}
					}
					else if(changes==false) {
						return;
					}
				}
				else if (longCommand == "q!") {
					return;
				}
			}





		}
		return;
	}


//function for saving changes to the file
void Editor::writeToFile() {
		//open file to write to and storing in outfile
		ofstream outFile;
		outFile.open(fileLabel);


		//check to make sure file opened properly
		if (!outFile.is_open()) {
			cout << "The file failed to open.\n";
			return;
		}

		//loop to write the items in our linked list to the file
		for (int i = 1; i <= fileLines.getLength(); i++) {
			outFile << fileLines.getEntry(i);
			outFile << '\n';
		}
		outFile.close();

		//bring the cursor back to the original spot
		placeCursorAt(p);
	}

//function for undoing the last command ordered by the user
void Editor::undo() {

	//check if there is a command that has not yet been undone
	if (commandStack.isEmpty()) {
			return;
		}

	Command hold = commandStack.peek();
	//if the last command was to delete a single character
	if (hold.getUserCommand() == 'x') {
		
		//get the coordinates at the time the last change was made
		p.setX(hold.getX());
		p.setY(hold.getY());
		commandStack.pop();

		//save the current line into a temporary variable
		string replacementLine = fileLines.getEntry(p.getY() + 1);

		//insert the last deleted character back into the line
		replacementLine.insert(replacementLine.begin() + p.getX(), hold.getFileChar());
		fileLines.replace(p.getY() + 1, replacementLine);

	}

	//if the last command was to delete a whole line
	else if (hold.getUserCommand() == 'd') {
		
		//get the coordinates at the time the last change was made
		p.setX(hold.getX());
		p.setY(hold.getY());

		//insert the last deleted line back into the file
		fileLines.insert(p.getY() + 1, hold.getS());

		//remove the formerly deleted line and last command from the stack
		commandStack.pop();


	}

	//show the updates lines
	displayLines();
	placeCursorAt(p);

}

//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** Searches the array anArray[first] through anArray[last]
	for a given value by using a binary search.
 @pre  0 <= first, last <= SIZE - 1, where SIZE is the
	maximum size of the array, and anArray[first] <=
	anArray[first + 1] <= ... <= anArray[last].
 @post  anArray is unchanged and either anArray[index] contains
	the given value or index == -1.
 @param anArray  The array to search.
 @param first  The low index to start searching from.
 @param last  The high index to stop searching at.
 @param target  The search key.
 @return  Either index, such that anArray[index] == target, or -1.
*/
template <typename ITEMTYPE> int binarySearch(const ITEMTYPE anArray[], int first, int last, ITEMTYPE target)
{
	int index;
	if (first > last)
		index = -1; // target not in original array
	else
	{
		// If target is in anArray, anArray[first] <= target <= anArray[last]
		int mid = first + (last - first) / 2;
		if (target == anArray[mid])
			index = mid; // target found at anArray[mid]
		else if (target < anArray[mid])
			// Point X
			index = binarySearch(anArray, first, mid - 1, target);
		else
			// Point Y
			index = binarySearch(anArray, mid + 1, last, target);
	}  // end if

	return index;
}  // end binarySearch

void colorText(int value) {

	COORD coord;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	FlushConsoleInputBuffer(hConsole);

	SetConsoleTextAttribute(hConsole, value + 240);

}

//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2016 __Pearson Education__. All rights reserved.

// Listing 11-2.

#include <iostream>
#include <string>

/** Sorts the items in an array into ascending order.
 @pre  None.
 @post  theArray is sorted into ascending order; n is unchanged.
 @param theArray  The given array.
 @param n  The size of theArray. */
template<class ItemType>
void bubbleSort(ItemType theArray[], int n)
{
	bool sorted = false; // False when swaps occur
	int pass = 1;
	while (!sorted && (pass < n))
	{
		// At this point, theArray[n+1-pass..n-1] is sorted
		// and all of its entries are > the entries in theArray[0..n-pass]
		sorted = true; // Assume sorted
		for (int index = 0; index < n - pass; index++)
		{
			// At this point, all entries in theArray[0..index-1]
			// are <= theArray[index]
			int nextIndex = index + 1;
			if (theArray[index] > theArray[nextIndex])
			{
				// Exchange entries
				std::swap(theArray[index], theArray[nextIndex]);
				sorted = false; // Signal exchange
			} // end if
		}  // end for
		// Assertion: theArray[0..n-pass-1] < theArray[n-pass]

		pass++;
	}  // end while
}  // end bubbleSort


