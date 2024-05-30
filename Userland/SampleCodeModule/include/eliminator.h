#ifndef _ELIMINATOR_H_
#define _ELIMINATOR_H_
#include <stdbool.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 760
#define PLAYER_SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define DEFAULT_LEVEL 1
#define DEFAULT_SPEED 2
#define DEFAULT_PLAYERS 2

void eliminator();
void printStart();
void printMenu();
void printSettings();
void menu();
void changeSettings();
void startGameTwoPlayers();
void startGameOnePlayer();
void drawSegment();
void handleInput();
void initializeGame();
void initializeGameTwoPlayers();
bool updateSnake(Snake * snake);
void updateGameOnePlayer();
void updateGameTwoPlayers();
void drawDeathCounter();
void drawMargins();
void gameOver();



#endif
