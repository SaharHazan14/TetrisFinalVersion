#include "game.h"
#include "settings.h"
#include "point.h"
#include "shape.h"
#include "board.h"
#include "general.h"

#include <Windows.h>
#include <process.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

int manageGame(Player *p1, Player *p2, bool newGame)
{
	char input = 0;
	Settings::Direction key1, key2;
	bool newS1 = true, newS2 = true;

	static Shape* s1 = createNewShape(p1->getBoard(), Settings::BOARD_1);
	static Shape* s2 = createNewShape(p2->getBoard(), Settings::BOARD_2);

	if (newGame)
	{
		p1->clearBoard();
		p2->clearBoard();

		delete s1;
		delete s2;

		s1 = createNewShape(p1->getBoard(), Settings::BOARD_1);
		s2 = createNewShape(p2->getBoard(), Settings::BOARD_2);
	}

	p1->printMyBoard();
	p2->printMyBoard();

	while (!p1->isOut() && !p2->isOut() && input != Settings::ESC)
	{
		for (int i = 0; i < 20; i++)
		{
			input = 0;

			s1->print(219);
			s2->print(219);

			Sleep(50);

			s1->print(' ');
			s2->print(' ');

			if (_kbhit())
			{
				input = _getch();
			}

			key1 = p1->getKey(input, s1, newS1); 
			key2 = p2->getKey(input, s2, newS2);

			newS1 = false;
			newS2 = false;

			p1->moveShape(s1, key1);
	     	p2->moveShape(s2, key2);

			if (input == Settings::ESC)
				break;
		}

		if (!s1->moveDown())
		{
			if (s1->isBomb())
				s1->preformBomb();
			else
				s1->putOnBoard();

			checkBoard(p1->getBoard(), 219);
			p1->printMyBoard();
			delete s1;
			s1 = createNewShape(p1->getBoard(), Settings::BOARD_1);
			newS1 = true;
		}

		if (!s2->moveDown())
		{
			if (s2->isBomb())
				s2->preformBomb();
			else
				s2->putOnBoard();

			checkBoard(p2->getBoard(), 219);
			p2->printMyBoard();
			delete s2;
			s2 = createNewShape(p2->getBoard(), Settings::BOARD_2);
			newS2 = true;
		}

	}

	if (input == Settings::ESC)
	{
		system("cls");
		return input;
	}

	if (!p1->isOut())
		p1->printWinner();
	else
		p2->printWinner();

	return 0;
}

Shape* createNewShape(Board board, int BoardNum)
{
	Shape* res;
	
	double xCenter, yCenter;

	Point* points = new Point[4];
	int sign;

	for (int i = 0; i < 4; i++)
	{
		Point curr(0, 0, board, BoardNum);
		points[i] = curr;
	}

	sign = rand() % 20;
	
	if(sign != 0)
		sign = rand() % 7 + 1;

	switch (sign)
	{
	case 0: // BOMB
		points[0].setCoord(6, 0);
		points[1].setCoord(6, 0);
		points[2].setCoord(6, 0);
		points[3].setCoord(6, 0);
		xCenter = 6;
		yCenter = 0;
		break;
	case 1:
		points[0].setCoord(5, 0); // *
		points[1].setCoord(5, 1); // ***
		points[2].setCoord(6, 1); // (5, 1)
		points[3].setCoord(7, 1);
		xCenter = 6;
		yCenter = 1;
		break;
	case 2:
		points[0].setCoord(7, 0); //   *
		points[1].setCoord(7, 1); // ***
		points[2].setCoord(6, 1); // (6, 1)
		points[3].setCoord(5, 1);
		xCenter = 6;
		yCenter = 1;
		break;
	case 3:
		points[0].setCoord(5, 0); // **
		points[1].setCoord(6, 0); // **
		points[2].setCoord(5, 1); // (5.5,0.5)
		points[3].setCoord(6, 1);
		xCenter = 5.5;
		yCenter = 0.5;
		break;
	case 4:
		points[0].setCoord(4, 1); // ****
		points[1].setCoord(5, 1); // (5.5, 1.5)
		points[2].setCoord(6, 1);
		points[3].setCoord(7, 1);
		xCenter = 5.5;
		yCenter = 1.5;
		break;
	case 5:
		points[0].setCoord(5, 1); //  **
		points[1].setCoord(6, 0); // **
		points[2].setCoord(6, 1); // (6, 1)
		points[3].setCoord(7, 0);
		xCenter = 6;
		yCenter = 1;
		break;
	case 6:
		points[0].setCoord(5, 0); // **
		points[1].setCoord(6, 0); //  **
		points[2].setCoord(6, 1); // (6, 1)
		points[3].setCoord(7, 1);
		xCenter = 6;
		yCenter = 1;
		break;
	case 7:
		points[0].setCoord(5, 1); //  *
		points[1].setCoord(6, 0); // ***
		points[2].setCoord(6, 1); // (6, 1)
		points[3].setCoord(7, 1);
		xCenter = 6;
		yCenter = 1;
		break;
	}

	res = new Shape(points, xCenter, yCenter, board, BoardNum);

	return res;
}

// Menu:

void printMenu(bool isGamePaused) 
{
	std::cout << "Menu: " << std::endl;
	std::cout << "(1) Start a new game - Human vs Human" << std::endl;
	std::cout << "(2) Start a new game - Human vs Computer" << std::endl;
	std::cout << "(3) Start a new game - Computer vs Computer" << std::endl;
	if ((isGamePaused))
	{
		std::cout << "(4) Continue a paused game" << std::endl;
	}
	std::cout << "(8) Present instructions and keys" << std::endl;
	std::cout << "(9) EXIT" << std::endl << std::endl;
}


void printInstructionsTable() 
{
	std::cout << "Keys: " << std::endl;
	std::cout << "\t\t\t" << "Left Player" << "\t" << "Right Player" << std::endl;

	std::string leftCol[] = { "LEFT", "RIGHT", "Rotate Clockwise", "Rotate Counterclockwise", "Drop", "" };
	std::string centerCol[] = { "a or A", "d or D", "s or S", "w or W", "x or X","" };
	std::string rightCol[] = { "j or J", "l (small L) or L", "k or K", "i or I", "m or M", "" };

	for (int i = 0; i < 6; ++i) {
		if (i == 3 || i == 2)
		{
			std::cout << leftCol[i] << "\t" << centerCol[i] << "\t\t" << rightCol[i] << std::endl;
		}
		else
		{
			std::cout << leftCol[i] << "\t\t\t" << centerCol[i] << "\t\t" << rightCol[i] << std::endl;
		}

	}
}

char getPlayerChoice() 
{
	char choice = _getch();

	while (!(choice == '1' || choice == '2' || choice == '8' || choice == '9' || choice == '3' || choice == '4'))
	{
		std::cout << "Invalid choice, please enter a number from the menu" << std::endl;
		choice = _getch();
	}

	return choice;
}

Settings::ComputerGameLevel getComputerLevel()
{
	char choice;

	std::cout << "Choose computer's game level:" << std::endl;
	std::cout << "(1) Best (2) Good (3) Novice" << std::endl;
	choice = _getch();

	while (choice != '1' && choice != '2' && choice != '3')
	{
		std::cout << "Invalid choice, please enter a number from the menu" << std::endl;
		choice = _getch();
	}

	switch (choice)
	{
	case '1':
		return Settings::ComputerGameLevel::BEST;
	case '2':
		return Settings::ComputerGameLevel::GOOD;
	case '3':
		return Settings::ComputerGameLevel::NOVICE;
	}
}
