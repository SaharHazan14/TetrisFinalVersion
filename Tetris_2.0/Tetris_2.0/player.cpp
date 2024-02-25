#include "player.h"
#include "general.h"

#include <iostream>

Player::Player(int playerNumber)
{
	this->playerNumber = playerNumber;
	this->board = createEmptyBoard();
}

Player::Player()
{
	this->playerNumber = 0;
	this->board = nullptr;
}

Player::~Player()
{
	if(!board)
		freeBoard(board);
}

void Player::printMyBoard() const
{
	if (playerNumber == Settings::PLAYER_1)
		printBoard(this->board, Settings::B1_MINX, Settings::B1_MINY);
	else
		printBoard(this->board, Settings::B2_MINX, Settings::B2_MINY);
}

bool Player::isOut() const
{
	if (checkLine(board[0], 219) != Settings::LineStatus::EMPTY)
		return true;

	return false;
}

void Player::printWinner() const
{
	system("cls");
	gotoxy(0, 0);
	std::cout << "Player " << playerNumber << " is the winner !!!" << std::endl;
}

void Player::clearBoard()
{
	for (int i = 0; i < Settings::BOARD_HEIGHT; i++)
		for (int j = 0; j < Settings::BOARD_WIDTH; j++)
			board[i][j] = ' ';
}

void Player::moveShape(Shape* shape, Settings::Direction key) const
{
	shape->move(key);
}