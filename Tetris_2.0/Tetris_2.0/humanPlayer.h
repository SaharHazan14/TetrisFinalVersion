#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(int playerNumber) : Player(playerNumber) {};
	Settings::Direction getKey(char input, Shape* shape, bool newShape) override;
};

#endif