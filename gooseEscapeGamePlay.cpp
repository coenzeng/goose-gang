#include <iostream>
#include <cmath>
#include <cstdlib> 
#include <fstream>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

extern Console out;
/*
With graphics, screens are given an x,y coordinate system with the origin
in the upper left corner.  So it means the coordinate axes are:
---------------->   x direction
|
|
|
|
|
V

y direction 
*/
	
/*
    Print the game world
    
    The functions should draw characters to present features of the game
    board, e.g. win location, obstacles, power ups
*/	
/*
void print_to_console(int map[][NUM_BOARD_Y])
{
	for (int index = 0; index < NUM_BOARD_X; index++)
	{
		for (int col_index = 0; col_index < NUM_BOARD_Y; col_index++)
			cout << map[index][col_index];
		cout << endl;
	}
}
*/
// print the game board function
//}
  //  terminal_put(x_location_on_board,y_location_on_board,WIN_CHAR);
//}

/*
    Do something when the goose captures the player
    
    If you want to attack or something else, this is the function you 
    need to change.  For example, maybe the two touch each other and
    then fight.  You could add a health to the Actor class that is
    updated.  Run, use weapons, it's up to you!
*/

bool captured(Actor const & player, Actor const & monster)
{
    return (player.get_x() == monster.get_x() 
         && player.get_y() == monster.get_y());
};

bool win(Actor const & player, Actor const & endpoint)
{
	return (player.get_x() == endpoint.get_x() 
         && player.get_y() == endpoint.get_y());
}

/*
    Move the player to a new location based on the user input.  You may want
    to modify this if there are extra controls you want to add.
    
    All key presses start with "TK_" then the character.  So "TK_A" is the a
    key being pressed.
    
    A look-up table might be useful.
    You could decide to learn about switch statements and use them here.
*/


void movePlayer(int key, Actor & player, int map[][NUM_BOARD_Y])
{
    int yMove = 0, xMove = 0;
    if (key == TK_UP)
        yMove = -1;
    else if (key == TK_DOWN)
        yMove = 1;
    else if (key == TK_LEFT)
        xMove = -1;
    else if (key == TK_RIGHT)
        xMove = 1;
        
    if (player.can_move(xMove, yMove) && 
	map[player.get_x() + xMove][player.get_y() + yMove] != SHALL_NOT_PASS)
        player.update_location(xMove, yMove);
}

void chasePlayer(int key, Actor & goose, Actor & player, int map[][NUM_BOARD_Y])
{
	int gooseXMove=0, gooseYMove=0;
	
	if(key==TK_UP || key==TK_DOWN)
	{
		if(goose.get_y() > player.get_y())
		{
			gooseYMove=-1;
		}
		else if(goose.get_y() < player.get_y())
		{
			gooseYMove=1;
		}
		
		if (map[goose.get_x()][goose.get_y()+gooseYMove] == SHALL_NOT_PASS)
		{
			//goose will jump over wall
			gooseYMove = gooseYMove * 2;
		}
	}
	else if(key==TK_LEFT || key==TK_RIGHT)
	{
		if(goose.get_x()>player.get_x())
		{
			gooseXMove=-1;
		}
		else if(goose.get_x()<player.get_x())
		{
			gooseXMove=1;
		}
	}

	if (goose.can_move(gooseXMove, gooseYMove) &&
	map[goose.get_x()+gooseXMove][goose.get_y()+gooseYMove] != SHALL_NOT_PASS)
	{
		goose.update_location(gooseXMove, gooseYMove);
	}
}

int random_num(int max_num, int used[MAX_OBJECTS])
{
	int random = (rand() % max_num) + 1;
	
	//check to see if number is in used array
	for (int index = 0; index < MAX_OBJECTS ; index++)
	{
		if (used[index] == random)
		{
			random = (rand() % max_num) + 1;
			index = 0;
		}
	}
	return random;
}

//this function is used for create_wall
int random_num(int max_num)
{
	return (rand() % max_num) + 1;
}

void create_wall(int map[][NUM_BOARD_Y])
{
	int x_location = random_num(START_WALL);
	//START_WALL = 70, which is NUM_BOARD_X - WALL_LENGTH
	//if the start of the wall as any higher it would go off screen
	
	int y_location = random_num(NUM_BOARD_Y);
	for (int index = 0; index < WALL_LENGTH; index++)
	{
		Actor wall(WALL_CHAR, x_location + index, y_location);
		map[x_location + index][y_location] = SHALL_NOT_PASS;
	}
}

