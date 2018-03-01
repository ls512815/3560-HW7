// Frank MacDonald
// November 27th 2017
// Final Project
// Cs2401
// Mr.Dolan
/*
*/
#ifndef OTHELLO_H
#define OTHELLO_H

#include "game.h"
#include "colors.h"
#include "space.h"
#include <string>
#include <cctype>
#include <cassert>
#include <queue>

namespace main_savitch_14
{
	class Othello : public game
	{
     	public:
      		Othello();
      		void restart();
      		void display_status() const;
      		bool is_legal(const string& move)const;
      		void make_move(const string& move);
      		bool is_game_over()const;
      		void compute_moves(queue<string>& moves)const;
      		game* clone()const;
      		int evaluate()const;
		game::who winning()const;
		std::string get_user_move()const;

   	private:
      		Space board[8][8];
		int passes = 0;
	};
}
#endif // OTHELLO_H
