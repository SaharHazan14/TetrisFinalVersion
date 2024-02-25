#include "general.h"
#include "point.h"
#include "board.h"

#include <Windows.h>
#include <iostream>

void gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    std::cout.flush();
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

Settings::Direction getDirection(char key, char boardNumber) 
{
	if (boardNumber == Settings::BOARD_1)
	{
		if (key == 'a' || key == 'A')
			return Settings::Direction::LEFT;

		if (key == 'd' || key == 'D')
			return Settings::Direction::RIGHT;

		if (key == 'x' || key == 'X')
			return Settings::Direction::DROP;

		if (key == 's' || key == 'S')
			return Settings::Direction::ROTATE_CLOCKWISE;

		if (key == 'w' || key == 'W')
			return Settings::Direction::ROTATE_COUNTERCLOCKWSIE;
	}
	else
	{
		if (key == 'j' || key == 'J')
			return Settings::Direction::LEFT;

		if (key == 'l' || key == 'L')
			return Settings::Direction::RIGHT;

		if (key == 'm' || key == 'M')
			return Settings::Direction::DROP;

		if (key == 'k' || key == 'K')
			return Settings::Direction::ROTATE_CLOCKWISE;

		if (key == 'i' || key == 'I')
			return Settings::Direction::ROTATE_COUNTERCLOCKWSIE;
	}
}