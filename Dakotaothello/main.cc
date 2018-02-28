////////////////////////////////////////////////////////////////////////////////////////
//Name: Dakota Kiger
//Project: Final
//Description: Creating Othello
//Date: 11/27/2017
////////////////////////////////////////////////////////////////////////////////////////

#include "game.h"
#include "Othello.h"
#include <iostream>
using namespace std;
using namespace main_savitch_14;

int main()
{
	cout<<" Welcome to Othello! "<<endl;
	cout<<" You are Player 1. Your color is White."<<endl;
	
	game::who winner;

	Othello game;
	winner = game.play();

	cout<<"There are no more possible legal moves!"<<endl;
	game.num_pieces();

	if(winner == 2)
	{
		cout<<"The Computer is the winner!"<<endl;
	}
	else if(winner == 0)
	{
		cout<<"You win!"<<endl;
	}
	else if(winner == 1)
	{
		cout<<"It's a tie!"<<endl;
	}
	return 0;
}