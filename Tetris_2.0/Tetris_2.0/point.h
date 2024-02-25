#ifndef POINT_H
#define POINT_H

#include "board.h"

class Point
{
private:
	int x, y;
	Board board;
	char boardNumber;
public:
	Point(int x, int y, Board board, char boardNumber);
	Point();
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void setCoord(int x, int y) { this->x = x; this->y = y; }
	void print(char sign) const;
	bool canMove(Settings::Direction key) const;
};

#endif