#include <iostream>
#include "Editor.h"
#include <string>
#include "LinkedList.h"
#include <fstream>
#include <memory>

using namespace std;

int main(int argc, char* argv[]) {

	system("cls");

	Editor ourEditor(argv[1],"keywords.txt");
	//ourEditor.displayLines();
	ourEditor.run();
	
	
}