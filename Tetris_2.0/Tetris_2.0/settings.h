#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
public:
	static constexpr int BOARD_WIDTH = 12;
	static constexpr int BOARD_HEIGHT = 18;

	static constexpr char BOARD_1 = '1'; 
	static constexpr char BOARD_2 = '2';

	static constexpr int B1_MINX = 0;
	static constexpr int B1_MINY = 0;

	static constexpr int B2_MINX = 30;
	static constexpr int B2_MINY = 0;

	static constexpr int PLAYER_1 = 1;
	static constexpr int PLAYER_2 = 2;

	static constexpr int ESC = 27;

	enum class Direction { LEFT, RIGHT, DOWN, DROP, ROTATE_CLOCKWISE, ROTATE_COUNTERCLOCKWSIE, STAM };
	enum class LineStatus { PARTLY_OCCUPIED, OCCUPIED, EMPTY };
	enum class ComputerGameLevel { BEST, GOOD, NOVICE };
};

struct HowToMove {
	int toRight;
	int toRotate;
};

#endif
