#ifndef COMPUTERPLAYER_H
#define COMPUTEROLAYER_H

#include "player.h"

class ComputerPlayer : public Player 
{
private:
	Settings::ComputerGameLevel level;
	HowToMove nextMove;
	HowToMove getOptimalBombMove(Shape* shape) const;
	int calcScore(Board board) const;
	int calcDeletedBlocks(Shape* bomb) const;
public:
	ComputerPlayer(int playerNumber, Settings::ComputerGameLevel level) : Player(playerNumber) { this->level = level; }
	Settings::Direction getKey(char input, Shape* shape, bool newShape) override;

	HowToMove getOptimalMove(Shape* shape) const;
};

#endif