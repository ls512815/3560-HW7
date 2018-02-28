////////////////////////////////////////////////////////////////////////////////////////
//Name: Dakota Kiger
//Project: Final
//Description: Creating Othello
//Date: 11/27/2017
////////////////////////////////////////////////////////////////////////////////////////

#ifndef OTHELLO_GAME
#define OTHELLO_GAME

#include "game.h"
#include "space.h"
#include <iostream>
#include "colors.h"

namespace main_savitch_14
{
	class Othello: public game
	{
		
	public:
		Othello()
		{	restart();
			move = 0;
			pass_count = 0;
		}
		void display_status()const;
    		// Evaluate a board position:
		bool is_legal(const std::string& move)const;
			//Determines if move is legal
    	void make_move(const std::string& move);
    		// Have the next player make a specified move
   		void restart();
   			// Restart the game from the beginning:
   		bool is_game_over()const;
    	// Return true if the given move is legal for the next player:
    	int ctoi(std::string c)const;

    	void set_move(int x){move = x;}
    	int get_move(){return move;}

		game* clone()const{return new Othello (*this);};
        	// Compute all the moves that the next player can make:
    	void compute_moves(std::queue<std::string>& moves)const;
    		// Display the status of the current game:
		// NOTE: positive values are good for the computer.
    	int evaluate()const;
    	// Return true if the current game is finished:

    	void num_pieces()const;
    	//counts the number of black and white pieces at the end of the game to see who wins
    	

    private:
    	Space board[8][8];
    	int move;
    	int pass_count;

    	
	};

}

#endif