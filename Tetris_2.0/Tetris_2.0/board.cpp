#include "board.h"
#include "general.h"

#include <iostream>

Board createEmptyBoard()
{
	char** res = new char* [Settings::BOARD_HEIGHT];

	for (int i = 0; i < Settings::BOARD_HEIGHT; i++)
		res[i] = new char[Settings::BOARD_WIDTH];

	for (int i = 0; i < Settings::BOARD_HEIGHT; i++)
		for (int j = 0; j < Settings::BOARD_WIDTH; j++)
			res[i][j] = ' ';

	return res;
}

void freeBoard(Board board)
{
	for (int i = 0; i < Settings::BOARD_HEIGHT; i++)
		delete[] board[i];
	delete[] board;
}

void printBorder(int x, int y)
{
	for (int col = x; col <= x + Settings::BOARD_WIDTH + 1; col++)
	{
		gotoxy(col, y);
		std::cout << '-';

		gotoxy(col, y + Settings::BOARD_HEIGHT + 1);
		std::cout << '-';
	}

	for (int row = y; row <= y + Settings::BOARD_HEIGHT + 1; row++)
	{
		gotoxy(x, row);
		std::cout << '|';

		gotoxy(x + Settings::BOARD_WIDTH + 1, row);
		std::cout << '|';
	}
}

void printBoard(Board board, int x, int y)
{
	printBorder(x, y);

	for (int i = 0; i < Settings::BOARD_HEIGHT; i++)
	{
		gotoxy(x + 1, y + 1 + i);

		for (int j = 0; j < Settings::BOARD_WIDTH; j++)
			std::cout << board[i][j];
	}
}

int checkBoard(Board board, char ch)
{
	Settings::LineStatus ind;
	int clearedLines = 0;

	for (int i = Settings::BOARD_HEIGHT - 1; i >= 0; i--)
	{
		ind = checkLine(board[i], ch);

		if (ind == Settings::LineStatus::EMPTY)
			return 0;

		if (ind == Settings::LineStatus::OCCUPIED)
		{
			deleteLineFromBoard(board, i);
			i++;
			clearedLines++;
		}
	}

	return clearedLines;
}

Settings::LineStatus checkLine(char* line, char ch)
{
	bool empty = true, occupied = true;

	for (int i = 0; i < Settings::BOARD_WIDTH; i++)
	{
		if (line[i] == ' ')
			occupied = false;
		else if (line[i] == ch)
			empty = false;
	}

	if (empty)
		return Settings::LineStatus::EMPTY;
	else if (occupied)
		return Settings::LineStatus::OCCUPIED;

	return Settings::LineStatus::PARTLY_OCCUPIED;
}

void deleteLineFromBoard(Board board, int index)
{
	for (index; index > 0; index--)
		copyLine(board[index], board[index - 1]);

	for (int i = 0; i < Settings::BOARD_WIDTH; i++)
		board[0][i] = ' ';
}

void copyLine(char* dest, char* src)
{
	for (int i = 0; i < Settings::BOARD_WIDTH; i++)
		dest[i] = src[i];
}

bool isValidCoord(int x, int y)
{
	if (x >= 0 && x < Settings::BOARD_WIDTH && y >= 0 && y < Settings::BOARD_HEIGHT)
		return true;

	return false;
}

Board copyBoard(Board cpy)
{
	char** res = new char* [Settings::BOARD_HEIGHT];

	for (int i = 0; i < Settings::BOARD_HEIGHT; i++)
		res[i] = new char[Settings::BOARD_WIDTH];

	for (int i = 0; i < Settings::BOARD_HEIGHT; i++)
		for (int j = 0; j < Settings::BOARD_WIDTH; j++)
			res[i][j] = cpy[i][j];

	return res;
}

int getMaxHeight(Board board)
{
	for (int i = 0; i < Settings::BOARD_HEIGHT; i++)
	{
		if (checkLine(board[i], 219) != Settings::LineStatus::EMPTY)
			return Settings::BOARD_HEIGHT - i;
	}

	return 0;
}

int getNumHoles(Board board)
{
	int numHoles = 0;

	for (int i = 0; i < Settings::BOARD_WIDTH; i++)
	{
		bool foundBlock = false;
		for (int j = 0; j < Settings::BOARD_HEIGHT; j++)
		{
			if (board[j][i] != ' ')
				foundBlock = true;
			else if (foundBlock)
				numHoles++;
		}
	}

	return numHoles;
}

int getBumpiness(Board board)
{
	int bumpiness = 0;
	int height1, height2;

	for (int i = 0; i < Settings::BOARD_WIDTH - 1; i++)
	{
		height1 = getCoulmnHeight(board, i);
		height2 = getCoulmnHeight(board, i + 1);

		bumpiness += abs(height1 - height2);
	}

	return bumpiness;
}

int getCoulmnHeight(Board board, int col)
{
	for (int i = 0; i < Settings::BOARD_HEIGHT; i++)
	{
		if (board[i][col] != ' ')
			return Settings::BOARD_HEIGHT - i;
	}

	return 0;
}