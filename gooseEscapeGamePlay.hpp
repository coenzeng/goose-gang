//gooseEscapeGamePlay.hpp

#ifndef GOOSE_ESCAPE_GAMEPLAY
#define GOOSE_ESCAPE_GAMEPLAY
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include <fstream>

/*This file is all about the game world.  You will modify this to add
    constants and function prototypes.  Modify gooseGamePlay.cpp to
	actually add functionality.
*/

/*
    Declare constants to indicate various game world features in the board
    array.  Modify them to fit what you would like to do in the game.  You can
    change the type if you choose to store your game board as something other
    than intengers.
*/	
// Going further:  Learn how to use an enum for these values
const int EMPTY = 0;
const int SHALL_NOT_PASS = 1;
const int WINNER = 2;

/*
    A few examples of characters both for actors and for the game board
    itself are shown.
*/	
//display characters
const int PLAYER_CHAR = int('@');
const int MONSTER_CHAR = int('G');
const int WALL_CHAR = int('o');
const int WIN_CHAR = int('%'); //% sign, a special character used in the ancient game "Rogue"
const int POWER_CHAR = int('!');

/*
    Game play function prototypes are give below.
*/

// print the game board function protype
void printGameBoard(int map[NUM_BOARD_X][NUM_BOARD_Y]);

/*
    Do something when the goose captures the player
    
    If you want to attack or something else, this is the function you 
    need to change.  For example, maybe the two touch each other and
    then fight.  You could add a health to the Actor class that is
    updated.  Run, use weapons, it's up to you!
*/
bool captured(Actor const & player, Actor const & monster);

bool win(Actor const & player, int map[NUM_BOARD_X][NUM_BOARD_Y]);

bool powered_up(Actor const & player, Actor const & power);

void movePlayer(int key, Actor & player, bool powered, int map[][NUM_BOARD_Y]);

void chasePlayer(int key, Actor & goose, Actor & player, int map[][NUM_BOARD_Y]);

void movePower(Actor & power, int map[][NUM_BOARD_Y]);

int random_num(int max_num);

#endif

