#include "Command.h"
#include <iostream>

using namespace std;

Command::Command() {

};

Command::Command(Position pos, char userC, char fileC) {
	p = pos;
	userCommand = userC;
	fileChar = fileC;
}

Command::Command(Position pos, string line, char userC) {
	p = pos;
	s = line;
	userCommand = userC;
}

void Command::setX(int n){
	p.setX(n);
}

void Command::setY(int n) {
	p.setY(n);
}

void Command::setUserCommand(char c) {
	userCommand = c;
}

void Command::setS(string line) {
	s = line;
}

void Command::setFileChar(char c) {
	fileChar = c;
}

int Command::getX() {
	return p.getX();
}

int Command::getY() {
	return p.getY();
}

char Command::getUserCommand() {
	return userCommand;
}

string Command::getS() {
	return s;
}

char Command::getFileChar() {
	return fileChar;
}