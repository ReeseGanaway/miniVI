#ifndef _Command
#define _Command

#include <iostream>
#include "Position.h"


class Command {

private:

	Position p;
	char userCommand;
	char fileChar;
	string s;

public:

	Command();
	Command(Position, char, char);
	Command(Position, string, char);

	void setX(int);
	void setY(int);
	void setUserCommand(char);
	void setS(string);
	void setFileChar(char);
	int getX();
	int getY();
	char getUserCommand();
	string getS();
	char getFileChar();

};


#endif
