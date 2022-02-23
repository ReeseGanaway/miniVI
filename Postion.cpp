#include "Position.h"

using namespace std;

Position::Position() {
	x = 0;
	y = 0;
}

Position::Position(int xCoord, int yCoord) {
	x = xCoord;
	y = yCoord;
}

void Position::setX(int xCoord) {
	x = xCoord;
}

void Position::setY(int yCoord) {
	y = yCoord;
}

int Position::getX(){
	return x;
}

int Position::getY() {
	return y;
}

double Position::distance(Position positionTwo) {
	return sqrt(pow(positionTwo.getX() - getX(), 2) + (pow(positionTwo.getY() - getY(), 2)));
}

bool Position::operator==(Position pointTwo) const 
{
	if ((x == pointTwo.x) && (y == pointTwo.y)) {
		return true;
	}
	else {
		return false;
	}
}




