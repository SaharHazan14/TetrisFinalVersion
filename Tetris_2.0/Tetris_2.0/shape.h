#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"
#include "board.h"

class Shape
{
private:
	Point* points;
	double xCenter, yCenter;
	Board board;
	char boardNumber;
public:
	Shape(Point* points, double xCenter, double yCenter, Board board, char boardNumber);
	Shape(const Shape& other);
	const Shape& operator=(const Shape& other);
	~Shape();
	double getXcenter() const { return xCenter; }
	double getYcenter() const { return yCenter; }
	Point* getPoints() const { return points; }
	const Board getBoard() const { return board; }
	char getBoardNumber() const{ return boardNumber; }
	void setPoints(Point* points);
	void setBoard(Board board, char boardNumber) { this->board = board; this->boardNumber = boardNumber; }
	void print(char sign) const;
	void move(Settings::Direction key);
	bool moveDown();
	void rotate(bool clockwise);
	void removeFromBoard();
	void putOnBoard();
	bool isBomb() const;
	void preformBomb();

	int getMinX() const;
	int getMaxX() const;
};

#endif 