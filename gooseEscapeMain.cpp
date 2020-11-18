#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

//set up the console.   Don't modify this line!
Console out;

int main()
{
	//Set up the window.  Don't edit these two lines
    terminal_open();
  	terminal_set(SETUP_MESSAGE);
/*
    The code below provides a skeleton of the game play.  You will need to
    write code for setting up the game board, and playing the game itself.
    You can modify the code given as needed.
    
    Call the functions that you have written in the game play file, and that
    you have added to the Actor class.
*/
    //ensures random setup on every compile
    srand(time(NULL)); 
	
	// Declare the array that will hold the game board "map"
  	int map[NUM_BOARD_X][NUM_BOARD_Y] = {0};
  	
  	//create wall of 10 units
  	create_wall(map);
  	
  	//make player
	Actor player(PLAYER_CHAR, random_num(NUM_BOARD_X), random_num(NUM_BOARD_Y));  
	
	//make monster
	Actor monster(MONSTER_CHAR, random_num(NUM_BOARD_X), random_num(NUM_BOARD_Y));
	
	//make win point
	Actor endpoint(WIN_CHAR, random_num(NUM_BOARD_X), random_num(NUM_BOARD_Y));
	
    map[endpoint.get_x()][endpoint.get_y()] = WINNER; 
  	
    // Call the function to print the game board??

	// Printing the instructions
    out.writeLine("Escape the Goose! " + monster.get_location_string() + player.get_location_string());
	out.writeLine("Use the arrow keys to move");
	out.writeLine("If the goose catches you, you lose!");
	out.writeLine("Be careful! Sometimes the goose can jump through walls!");

/*
    This is the main game loop.  It continues to let the player give input
    as long as they do not press escape or close, they are not captured by
    the goose, and they didn't reach the win tile
*/
/*
    All key presses start with "TK_" then the character.  So "TK_A" is the "a"
    key being pressed.
*/
    int keyEntered = TK_A;  // can be any valid value that is not ESCAPE or CLOSE
    
    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE 
		&& !captured(player,monster) && !win(player, endpoint))
	{
	    // get player key press
	    keyEntered = terminal_read();

        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
        {
            // move the player
            movePlayer(keyEntered, player, map);
			
			//goose chases the player
			chasePlayer(keyEntered, monster, player, map); 
        }
        
  	}

    if (keyEntered != TK_CLOSE)
    {
      	//once we're out of the loop, the game is over
        out.writeLine("Game has ended");
    	
        if (captured(player, monster))
        	out.writeLine("The goose has caught you!");
        else
        	out.writeLine("You win!");
	
    	// Wait until user closes the window
        while (terminal_read() != TK_CLOSE);
    }

	//game is done, close it  
    terminal_close();
}
