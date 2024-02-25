#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "point.h"
#include "board.h"

int manageGame(Player *p1, Player *p2, bool newGame);
Shape* createNewShape(Board board, int BoardNum);

void printMenu(bool isGamePaused);
void printInstructionsTable();
char getPlayerChoice();
Settings::ComputerGameLevel getComputerLevel();

#endif
