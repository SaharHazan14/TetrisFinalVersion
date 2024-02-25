#include "board.h"
#include "settings.h"
#include "general.h"
#include "point.h"
#include "shape.h"
#include "player.h"
#include "game.h"
#include "humanPlayer.h"
#include "computerPlayer.h"

#include <Windows.h>
#include <ctime>
#include <conio.h>
#include <iostream>

int main()
{
	srand(time(0));

	Player* p1 = nullptr, * p2 = nullptr;
	Settings::ComputerGameLevel cmp1lev, cmp2lev;

	printMenu(false);
	char choice = getPlayerChoice();

	int isGameEnded = -1;

	while (true)
	{
		while (isGameEnded == -1 && choice == '4')
			choice = _getch();

		switch (choice)
		{
		case '1':
			system("cls");
			p1 = new HumanPlayer(Settings::PLAYER_1);
			p2 = new HumanPlayer(Settings::PLAYER_2);
			isGameEnded = manageGame(p1, p2, true);
			break;
		case '2':
			system("cls");
			cmp2lev = getComputerLevel();
			system("cls");
			p1 = new HumanPlayer(Settings::PLAYER_1);
			p2 = new ComputerPlayer(Settings::PLAYER_2, cmp2lev);
			isGameEnded = manageGame(p1, p2, true);
			break;
		case '3':
			system("cls");
			cmp1lev = getComputerLevel();
			cmp2lev = getComputerLevel();
			system("cls");
			p1 = new ComputerPlayer(Settings::PLAYER_1, cmp1lev);
			p2 = new ComputerPlayer(Settings::PLAYER_2, cmp2lev);
			isGameEnded = manageGame(p1, p2, true);
			break;
		case '4':
			system("cls");
			isGameEnded = manageGame(p1, p2, false);
			break;
		case '8':
			printInstructionsTable();
			break;
		case '9':
			return 0;
		}

		if (isGameEnded == 0)
			return 0;

		if (choice != '8')
		{
			if (isGameEnded == Settings::ESC)
				printMenu(true);
			else
				printMenu(false);
		}
		choice = getPlayerChoice();	
	}

	return 0;
}