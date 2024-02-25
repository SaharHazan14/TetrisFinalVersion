#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "shape.h"

class Player
{
private:
	int playerNumber;
	Board board;
public:
	Player(int playerNumber);
	Player();
	~Player();
	int getNumber() const { return playerNumber; }
	Board getBoard() const { return board; }
	void setNumber(int playerNumber) { this->playerNumber = playerNumber; }
	void setBoard(Board board) { this->board = board; }
	void printMyBoard() const;
	bool isOut() const;
	void printWinner() const;
	void clearBoard();
	void moveShape(Shape* shape, Settings::Direction key) const;

	virtual Settings::Direction getKey(char input, Shape* shape, bool newShape) = 0;
};

#endif
