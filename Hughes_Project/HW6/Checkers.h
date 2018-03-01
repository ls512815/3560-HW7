// Zachary Hughes
// CS2401 Spring 2017
// Checkers.h

//Checkers header file

#ifndef CHECKERS_H
#define CHECKERS_H

#include "space.h"
#include <string>
#include "game.h"
#include "colors.h"

class Checkers:public main_savitch_14::game
{
	public:
		Checkers();
		void restart(); // restarts game from the beginning
		void display_status(); // status of the game
		bool is_legal(const std::string& move); // true if legal move for next player
		void make_move(const std::string& move); // makes a move specified
		bool is_game_over();
		bool make_jump(const std::string& move);
		//Part 3
		game* clone();
		who winning();
		void compute_moves(std::queue<std::string> &moves);
		int evaluate();
		who last_mover()const;
	private:
		space board[8][8];
		int moves;
};

#endif
