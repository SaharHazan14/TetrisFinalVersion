#include "point.h"
#include "general.h"

#include <iostream>

Point::Point(int x, int y, Board board, char boardNumber)
{
	this->x = x;
	this->y = y;
	this->board = board;
	this->boardNumber = boardNumber;
}

Point::Point()
{
	x = y = 0; 
	board = nullptr; 
	boardNumber = '0';
}

void Point::print(char sign) const
{
	if (boardNumber == Settings::BOARD_1)
	{
		gotoxy(x + 1 + Settings::B1_MINX, y + 1 + Settings::B1_MINY);
		std::cout << sign;
	}
	else
	{
		gotoxy(x + 1 + Settings::B2_MINX, y + 1 + Settings::B2_MINY);
		std::cout << sign;
	}
}

bool Point::canMove(Settings::Direction key) const
{
	if (key == Settings::Direction::LEFT)
	{
		if ((x > 0) && (board[y][x - 1] == ' ')) 
			return true;
	}
	else if (key == Settings::Direction::RIGHT)
	{
		if ((x < Settings::BOARD_WIDTH) && (board[y][x + 1] == ' '))
			return true;
	}
	else if (key == Settings::Direction::DOWN)
	{
		if (y != (Settings::BOARD_HEIGHT - 1) && board[y + 1][x] == ' ')
			return true;
	}

	return false;
}