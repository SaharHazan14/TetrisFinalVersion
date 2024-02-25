#include "humanPlayer.h"
#include "general.h"

#include <conio.h>

Settings::Direction HumanPlayer::getKey(char input, Shape* shape, bool newShape)
{
	if (input == 0)
		return Settings::Direction::STAM;

	return getDirection(input, shape->getBoardNumber());
}