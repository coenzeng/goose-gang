//gooseEscapeGamePlay.cpp

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

//print the game board function
void printGameBoard(int map[NUM_BOARD_X][NUM_BOARD_Y])
{	
	//CHANGE THIS FUNCTION 
	int winPointX=random_num(NUM_BOARD_X);
	int winPointY=random_num(NUM_BOARD_Y);
	
	terminal_put(winPointX,winPointY,WIN_CHAR);
	map[winPointX][winPointY]=WINNER;
	
	int wall_x_location = random_num(START_WALL);
	//START_WALL = 70, which is NUM_BOARD_X - WALL_LENGTH
	//if the start of the wall as any higher it would go off screen
	
	int wall_y_location = random_num(NUM_BOARD_Y);
	
	for (int index = 0; index < WALL_LENGTH; index++)
	{
		terminal_put(wall_x_location+index, wall_y_location, WALL_CHAR);
		map[wall_x_location + index][wall_y_location] = SHALL_NOT_PASS;
	}
}

bool captured(Actor const & player, Actor const & monster)
{
    return (player.get_x() == monster.get_x() 
         && player.get_y() == monster.get_y());
};

bool powered_up(Actor const & player, Actor const & power)
{
    return (player.get_x() == power.get_x() 
         && player.get_y() == power.get_y());
};

bool win(Actor const & player, int map[NUM_BOARD_X][NUM_BOARD_Y])
{
	return (map[player.get_x()][player.get_y()]==WINNER);
}

void movePlayer(int key, Actor & player, bool powered, int map[][NUM_BOARD_Y])
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
        
	if(powered)
	{
		//if powered up, player can move 2 spaces using WASD
		if (key == TK_W)
	        yMove = -2;
	    else if (key == TK_S)
	        yMove = 2;
	    else if (key == TK_A)
	        xMove = -2;
	    else if (key == TK_D)
	        xMove = 2;
	}   
	
    if (player.can_move(xMove, yMove) && 
	map[player.get_x() + xMove][player.get_y() + yMove] != SHALL_NOT_PASS)
        player.update_location(xMove, yMove);
}

void chasePlayer(int key, Actor & goose, Actor & player, int map[][NUM_BOARD_Y])
{
	int gooseXMove=0, gooseYMove=0;
	
	if(key==TK_UP || key==TK_DOWN || key==TK_W || key==TK_S)
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
	else if(key==TK_LEFT || key==TK_RIGHT || key==TK_A || key==TK_D)
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

void movePower(Actor & power, int map[][NUM_BOARD_Y])
{	
	int powerXMove = power.get_x() - power.get_prev_x();
	int powerYMove = power.get_y() - power.get_prev_y();
	
	if (power.get_prev_x() == 0)
	{	
		//this is true only for the first move, where previous_x == 0
		powerXMove = 1;
		powerYMove = 1;
	}
	
	//the following if statement allows the powerup to bounce off walls
	if (power.can_move(powerXMove, powerYMove) 
	&& map[power.get_x()+powerXMove][power.get_y()+powerYMove] != SHALL_NOT_PASS)
	{
		//if the path is clear, continue in the same direction
		powerXMove *= 1; 
		powerYMove *= 1;
	} else if (powerXMove == 1 && powerYMove == 1)
	{
		powerYMove *= -1;	
	} else if (powerXMove == 1 && powerYMove == -1)
	{
		powerXMove *= -1;
	}else if (powerXMove == -1 && powerYMove == -1)
	{	
		powerXMove *= -1;
	} else
	{
		powerYMove *= -1;
	}
	
	//if the powerup can't bounce in one direction it will try the opposite
	if (!power.can_move(powerXMove, powerYMove))
	{
		powerXMove *= -1;
		powerYMove *= -1;
	}
	
	//update location of powerup
	power.update_location(powerXMove, powerYMove);
}

int random_num(int max_num)
{
	return (rand() % max_num);
}

