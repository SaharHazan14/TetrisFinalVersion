#include "computerPlayer.h"
#include "general.h"
#include "board.h"
#include <Windows.h>

Settings::Direction ComputerPlayer::getKey(char input, Shape *shape, bool newShape) 
{
	if (newShape)
	{
		nextMove = getOptimalMove(shape);
	}

	if (nextMove.toRotate > 0)
	{
		nextMove.toRotate--;
		return Settings::Direction::ROTATE_CLOCKWISE;
	}

	if (nextMove.toRight > 0)
	{
		nextMove.toRight--;
		return Settings::Direction::RIGHT;
	}

	if (nextMove.toRight < 0)
	{
		nextMove.toRight++;
		return Settings::Direction::LEFT;
	}

	return Settings::Direction::DROP;
}

HowToMove ComputerPlayer::getOptimalMove(Shape* shape) const 
{
	if (shape->isBomb() && level == Settings::ComputerGameLevel::BEST)
		return getOptimalBombMove(shape);

	HowToMove res;
	
	int minX = shape->getMinX();
    int maxX = shape->getMaxX();
	int fix = 0, currFix =0;
	int shapeWidth = maxX - minX + 1;
	int score = -10000, currentScore = 0;

	Board cpyBoard = copyBoard(shape->getBoard());
	
	Shape currentShape(*shape);
	currentShape.setBoard(cpyBoard, '0');

	Shape tempShape(currentShape);

	res.toRight = 0;
	res.toRotate = 0;

	for (int i = 0; i < minX; i++)
		tempShape.move(Settings::Direction::LEFT);
		
	for (int rot = 0; rot < 4; rot++)
	{
		for (int col = 0; col <= Settings::BOARD_WIDTH - shapeWidth; col++)
		{
			currentShape = tempShape;

			for (int i = 0; i < col; i++)
			{
				currentShape.move(Settings::Direction::RIGHT);
			}

			currentShape.move(Settings::Direction::DROP);
			currentShape.putOnBoard();
			currentScore = calcScore(cpyBoard);

			if (currentScore > score)
			{
				res.toRight = col;
				res.toRotate = rot;
				score = currentScore;
				currFix = fix;
			}

			currentShape.removeFromBoard();
		}

		if (fix > 0)
		{
			for(int i =0; i < fix; i++)
				tempShape.move(Settings::Direction::RIGHT);
		}

		tempShape.move(Settings::Direction::ROTATE_CLOCKWISE);
		shapeWidth = tempShape.getMaxX() - tempShape.getMinX() + 1;
		
		fix = tempShape.getMinX();
		
		for (int i =0; i < fix; i++)
			tempShape.move(Settings::Direction::LEFT);
	}

	res.toRight -= minX + currFix;
	freeBoard(cpyBoard);

	return res;
}

HowToMove ComputerPlayer::getOptimalBombMove(Shape* shape) const
{
	HowToMove res;
	res.toRight = 0;
	res.toRotate = 0;

	int currMax, max = 0, col = 0;
	Board cpyBoard = copyBoard(shape->getBoard());

	Shape tempBomb(*shape);
	tempBomb.setBoard(cpyBoard, '0');

	int minX = tempBomb.getMinX();

	for (int i = 0; i < minX; i++)
		tempBomb.move(Settings::Direction::LEFT);

	Shape startPos(tempBomb);

	for (int i = 0; i <= Settings::BOARD_WIDTH - 1; i++)
	{
		for (int j = 0; j < i; j++)
		{
			tempBomb.move(Settings::Direction::RIGHT);
		}

		tempBomb.move(Settings::Direction::DROP);
		currMax = calcDeletedBlocks(&tempBomb);

		if (currMax > max)
		{		
			max = currMax;
			col = i;
		}

		tempBomb = startPos;
	}

	res.toRight = col - shape->getMinX();

	return res;
}

int ComputerPlayer::calcScore(Board board) const
{
	int score = 0;
	Board tmp = copyBoard(board);
	
	int linesCleared = checkBoard(tmp, 219);
	score += linesCleared * 100000;

	int maxHeight = getMaxHeight(tmp);
	score -= maxHeight * 10;

	int numHoles = getNumHoles(tmp);
	score -= numHoles * 5;

	switch (level)
	{
	case Settings::ComputerGameLevel::NOVICE:
		if (rand() % 10 == 0)
			score -= 100;
		break;
	case Settings::ComputerGameLevel::GOOD:
		if (rand() % 40 == 0)
			score -= 100;
		break;
	case Settings::ComputerGameLevel::BEST:
		break;
	}

	freeBoard(tmp);
	return score;
}

int ComputerPlayer::calcDeletedBlocks(Shape* bomb) const
{
	Board board = bomb->getBoard();
	int blocks = 0;

	int x = bomb->getXcenter();
	int y = bomb->getYcenter();
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

	for (int i = x - left; i <= x + right; i++)
		for (int j = y - up; j <= y + down; j++)
		{
			if (board[j][i] != ' ')
				blocks++;
		}

	return blocks;
}