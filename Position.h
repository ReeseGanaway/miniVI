//Position.h
//Reese Ganaway, Aaron Aviles, Andrew Li

#ifndef _POSITION
#define _POSITION



#include<iostream>
#include<cstdlib>
#include<cmath>

using namespace std;

class Position {

private:

	int x, y;


public:

	//default constructor
	Position();

	//parameterized constructor
	Position(int, int);


	//setter functions
	void setX(int);
	void setY(int);


	//getter functions
	int getY();
	int getX();

	//function to calculate the distance between this point and another
	double distance(Position);

	//Both positions must be initialized 
	//Returns true if positions are equal, false if not
	bool operator==(Position pointTwo) const;
};
#endif // !