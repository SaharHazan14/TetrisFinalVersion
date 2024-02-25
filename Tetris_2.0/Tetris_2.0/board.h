#ifndef BOARD_H
#define BOARD_H

#include "settings.h"

typedef char** Board;

Board createEmptyBoard();
void freeBoard(Board board);

void printBorder(int x, int y);
void printBoard(Board board, int x, int y);

int checkBoard(Board board, char ch);
Settings::LineStatus checkLine(char* line, char ch);
void deleteLineFromBoard(Board board, int index);
void copyLine(char* dest, char* src);

bool isValidCoord(int x, int y);

Board copyBoard(Board cpy);

int getMaxHeight(Board board);
int getNumHoles(Board board);
int getBumpiness(Board board);
int getCoulmnHeight(Board board, int col);

#endif
