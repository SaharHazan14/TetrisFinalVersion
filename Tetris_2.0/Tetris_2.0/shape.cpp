#include "shape.h"

Shape::Shape(Point* points, double xCenter, double yCenter, Board board, char boardNumber)
{
	this->points = new Point[4];
	for (int i = 0; i < 4; i++)
		this->points[i] = points[i];

	this->xCenter = xCenter;
	this->yCenter = yCenter;

	this->board = board;
	this->boardNumber = boardNumber;
}

Shape::Shape(const Shape& other)
{
	points = new Point[4];
	for (int i = 0; i < 4; i++)
		points[i] = other.points[i];

	xCenter = other.xCenter;
	yCenter = other.yCenter;

	board = other.board;
	boardNumber = other.boardNumber;
}

const Shape& Shape::operator=(const Shape& other)
{
	for (int i = 0; i < 4; i++)
		points[i] = other.points[i];

	xCenter = other.xCenter;
	yCenter = other.yCenter;

	board = other.board;
	boardNumber = other.boardNumber;

	return *this;
}

Shape::~Shape()
{
	delete[] points;
}

void Shape::setPoints(Point* points)
{
	for (int i = 0; i < 4; i++)
		this->points[i] = points[i];
}

void Shape::print(char sign) const
{
	for (int i = 0; i < 4; i++)
		points[i].print(sign);
}

void Shape::move(Settings::Direction key)
{
	switch (key)
	{
	case Settings::Direction::LEFT:
		for (int i = 0; i < 4; i++)
			if (!points[i].canMove(Settings::Direction::LEFT))
				return;
		for (int i = 0; i < 4; i++)
			points[i].setX(points[i].getX() - 1);
		xCenter = xCenter - 1;
		break;
	
	case Settings::Direction::RIGHT:
		for (int i = 0; i < 4; i++)
			if (!points[i].canMove(Settings::Direction::RIGHT))
				return;
		for (int i = 0; i < 4; i++)
			points[i].setX(points[i].getX() + 1);
		xCenter = xCenter + 1;
		break;
	
	case Settings::Direction::DROP:
		while (true)
		{
			for (int i = 0; i < 4; i++)
				if (!points[i].canMove(Settings::Direction::DOWN))
					return;
			for (int i = 0; i < 4; i++)
				points[i].setY(points[i].getY() + 1);
			yCenter = yCenter + 1;
		}
		break;
	
	case Settings::Direction::ROTATE_CLOCKWISE:
		rotate(true);
		break;
	
	case Settings::Direction::ROTATE_COUNTERCLOCKWSIE:
		rotate(false);
		break;
	}
}

bool Shape::moveDown()
{
	for (int i = 0; i < 4; i++)
		if (!points[i].canMove(Settings::Direction::DOWN))
			return false;

	for (int i = 0; i < 4; i++)
		points[i].setY(points[i].getY() + 1);

	yCenter = yCenter + 1;

	return true;
}

void Shape::rotate(bool clockwise)
{
	if (isBomb())
		return;

	int direction = clockwise ? 1 : -1;

	for (int i = 0; i < 4; i++)
	{
		double relativeX = points[i].getX() - xCenter;
		double relativeY = points[i].getY() - yCenter;

		double rotatedX = -relativeY * direction;
		double rotatedY = relativeX * direction;

		if (!isValidCoord(int(rotatedX + xCenter), int(rotatedY + yCenter)))
			return;
	}

	for (int i = 0; i < 4; i++)
	{
		double relativeX = points[i].getX() - xCenter;
		double relativeY = points[i].getY() - yCenter;

		double rotatedX = -relativeY * direction;
		double rotatedY = relativeX * direction;

		points[i].setX(int(rotatedX + xCenter));
		points[i].setY(int(rotatedY + yCenter));
	}
}

void Shape::removeFromBoard()
{
	for (int i = 0; i < 4; i++)
		board[points[i].getY()][points[i].getX()] = ' ';
}

void Shape::putOnBoard()
{
	for (int i = 0; i < 4; i++)
		board[points[i].getY()][points[i].getX()] = 219; 
}

bool Shape::isBomb() const
{
	if ((points[0].getX() == points[1].getX()) && points[0].getY() == points[1].getY()) 
		return true;

	return false;
}

void Shape::preformBomb()
{
	int x = points[0].getX();
	int y = points[0].getY();
	int right = 0, left = 0, up = 0, down = 0;

	for (int i = 1; i <= 4; i++)
	{
		if (x + i < Settings::BOARD_WIDTH)
			right++;

		if (x - i >= 0)
			left++;

		if (y + i < Settings::BOARD_HEIGHT)
			down++;

		if (y - i >= 0)
			up++;
	}

	for(int i = x - left; i <= x + right; i++)
		for (int j = y - up; j <= y + down; j++)
		{
			board[j][i] = ' ';
		}
}

int Shape::getMinX() const
{
	int min = points[0].getX();
	int curr;

	for (int i = 1; i < 4; i++)
	{
		curr = points[i].getX();

		if (curr < min)
			min = curr;
	}

	return min;
}

int Shape::getMaxX() const
{
	int max = points[0].getX();
	int curr;

	for (int i = 1; i < 4; i++)
	{
		curr = points[i].getX();

		if (curr > max)
			max = curr;
	}

	return max;
}