// Zachary Hughes
// CS2401 Spring 2017
// Checkers.cc

//Checkers implementation file with space

#include "Checkers.h"
#include "space.h"
#include "colors.h"
#include "game.h"
#include <iostream>
#include <cctype>
#include <cstdio>

using namespace std;
using namespace main_savitch_14;

Checkers::Checkers()
{
	restart();
	moves = 0;
}

//I really didn't like how I did it the first time. I think I made it too complicated
//I also think I didn't set every thing to something so I changed it
//Clears the board[8][8] then fills it with the beginning board.
//Doesn't display anything
void Checkers::restart()
{
	moves = 0;
	// goes through whole board
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			// this is for the playable spaces
			if((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
			{
				board[i][j].set_playable(true);
				board[i][j].set_black(false);
				board[i][j].set_red(false);
			}
			// nonplayable spaces
			else
			{
				board[i][j].set_playable(false);
				board[i][j].set_black(false);
				board[i][j].set_red(false);
			}
			// red pieces in the top
			if(i < 3 && board[i][j].is_playable())
			{
				board[i][j].set_red(true);
				board[i][j].set_black(false);
				board[i][j].set_empty(false);
				
			}
			//black pieces in the bottom
			else if(i > 4 && board[i][j].is_playable())
			{
				board[i][j].set_red(false);
				board[i][j].set_black(true);
				board[i][j].set_empty(false);
				
			}
			else
			{
				board[i][j].set_empty(true);
				board[i][j].set_black(false);
				board[i][j].set_red(false);
			}
			board[i][j].King_me_black(false);
			board[i][j].King_me_red(false);
		}
	}
}

//Actually writes the colors to the screen
void Checkers::display_status()
{
	int counter = 1;
	char t1 = 'A';
	for(int i = -1; i < 8; i++)
	{
		//these are for the letters on the side
		if(i < 0)
		{
			cout << " " << RESET;
		}
		else
		{
			cout << t1 << RESET;
			t1++;
		}
		for(int j = 0; j < 8; j++)
		{
			//printing out the number on top
			if(i == -1)
			{
				cout << " " << counter << " " << RESET;
				counter++;
			}
			//red checkers in the board
			else if(board[i][j].is_playable() && board[i][j].red() && !board[i][j].is_empty())
			{
				//if a king
				if(board[i][j].king_red())
				{
					cout << B_BLACK << " " << BOLD << RED << "X" << B_BLACK << " " << RESET;
				}
				else
				{
					cout << B_BLACK << " " << BOLD << RED << "O" << B_BLACK << " " << RESET;
				}
			}
			//black checkers in the board
			else if(board[i][j].is_playable() && board[i][j].black() && !board[i][j].is_empty())
			{
				if(board[i][j].king_black())
				{
					cout << B_BLACK << " " << BOLD << BLUE << "X" << B_BLACK << " " << RESET;
				}
				else
				{
					cout << B_BLACK << " " << BOLD << BLUE << "O" << B_BLACK << " " << RESET;
				}
			}
			// if theres nothing in the space that is playable
			else if(board[i][j].is_playable() && board[i][j].is_empty())
			{
				cout << B_BLACK << "   " << RESET;
			}
			// if it's not playable
			else if(!board[i][j].is_playable())
			{
				cout << B_RED << "   " << RESET;
			}
		}
		cout << endl;
	}
}

bool Checkers::is_legal(const string& move)
{
	string checker = move.substr(0,2);
	string move_to = move.substr(2,3);
	
	int checker_letter = int(tolower(checker[0]) - 'a');
	int checker_number = int(tolower(checker[1]) - '0');
	int letter_move_to = int(tolower(move_to[0]) - 'a');
	int number_move_to = int(tolower(move_to[1]) - '0');

	//must make numbers useable for us programmers!!
	checker_number--;
	number_move_to--;

	//not a playable move
	if(!board[letter_move_to][number_move_to].is_playable() || !board[checker_letter][checker_number].is_playable())
	{
		//cout << "\nNot a playable move\n";
		return false;
	}
	// is empty and the board number tells if black or red can go
	else if(board[letter_move_to][number_move_to].is_empty() && ((board[checker_letter][checker_number].red() && moves % 2 == 1) || (board[checker_letter][checker_number].black() && moves % 2 == 0)))
	{
		//just to clarify the red pieces are red. The black pieces are blue
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************
		if(make_jump(move)) //|| (checker_letter - letter_move_to > 1 || checker_letter - letter_move_to < -1))
		{
			//cout << "\nMust jump!\n";
			return false;
		}
		//red piece and not a king
		if(board[checker_letter][checker_number].red() && !board[checker_letter][checker_number].king_red())
		{
			//cout << "\nRed but not a king\n";
			// I found that if it's a red piece, theres a playable and non empty space
			// that the space is in front to the left or right that when you add
			// i and j that you get either the same number or a number + 2
			// I do this for all logic
			//*****************NOT JUMPING LEGAL MOVE*****************
			if(((checker_letter + checker_number) == (letter_move_to + number_move_to) || (checker_letter + checker_number) == (letter_move_to + number_move_to + 2) || (checker_letter + checker_number) == (letter_move_to + number_move_to - 2)) && checker_letter < letter_move_to)
			{
				//cout << "\nNot jumping red piece that's not a king\n";
				return true;
			}
			//*****************JUMPING LEGAL MOVE*****************
			// if it's actually jumping it is gonna be a few more spaces in the row
			else if((letter_move_to - checker_letter) > 1 && (number_move_to - checker_number > 1 || number_move_to - checker_number < -1) && board[letter_move_to][number_move_to].is_empty() && (board[checker_letter + 1][checker_number - 1].black() || board[checker_letter + 1][checker_number + 1].black()))
			{
			//	cout << "\nJumping move\n";
				int x = 0;
				int y = 0;
				while(((checker_letter + x != letter_move_to) && (checker_letter - x != letter_move_to)) || ((checker_number + y != number_move_to) && (checker_number - y != number_move_to)))
				{
					// if it's to the left
					if(number_move_to < checker_number)
					{
						//cout << "\nTHE BEST\n";
						// if it's left and below
						if(board[checker_letter + 1 + x][checker_number - 1 + y].black() && board[checker_letter + 2 + x][checker_number - 2 + y].is_empty() && checker_letter + 2 < 8 && checker_number - 2 > -1)
						{
							//cout << "\nLEFT\n";
							board[checker_letter + 1 + x][checker_number - 1 + y].set_empty(true);
							board[checker_letter + 1 + x][checker_number - 1 + y].set_black(false);
							x = x + 2;
							y = y - 2;
						}
						else
						{
							return false;
						}
					}
					// if it's to the right
					else if(number_move_to > checker_number)
					{
						//cout << "\nTHE WORST\n";
						if(board[checker_letter + 1 + x][checker_number + 1 + y].black() && board[checker_letter + 2 + x][checker_number + 2 + y].is_empty() && checker_letter + 2 < 8 && checker_number + 2 > 8)
						{
							//cout << "\nRIGHT\n";
							board[checker_letter + 1 + x][checker_number + 1 + y].set_empty(true);
							board[checker_letter + 1 + x][checker_number + 1 + y].set_black(false);
							x = x + 2;
							y = y + 2;
						}
						else
						{
							return false;
						}
					}
					else if(number_move_to == checker_number)
					{
						if(board[checker_letter + 1 + x][checker_number + 1 + y].black() && board[checker_letter + 2 + x][checker_number + 2 + y].is_empty() && checker_letter + 2 < 8 && checker_number + 2 > 8)
						{
							//cout << "\nRIGHT\n";
							board[checker_letter + 1 + x][checker_number + 1 + y].set_empty(true);
							board[checker_letter + 1 + x][checker_number + 1 + y].set_black(false);
							x = x + 2;
							y = y + 2;
						}
						else if(board[checker_letter + 1 + x][checker_number - 1 + y].black() && board[checker_letter + 2 + x][checker_number - 2 + y].is_empty() && checker_letter + 2 < 8 && checker_number - 2 > -1)
						{
							//cout << "\nLEFT\n";
							board[checker_letter + 1 + x][checker_number - 1 + y].set_empty(true);
							board[checker_letter + 1 + x][checker_number - 1 + y].set_black(false);
							x = x + 2;
							y = y - 2;
						}
						else
						{
							return false;
						}
					}
				}
				return true;
			}
		}
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************
		//red piece and a king
		else if(board[checker_letter][checker_number].red() && board[checker_letter][checker_number].king_red())
		{
			//*****************JUMPING LEGAL MOVE*****************
			// if it's actually jumping it is gonna be a few more spaces in the row
			if((letter_move_to - checker_letter) > 1 || (letter_move_to - checker_letter) < -1)
			{
				//cout << "\nJumping move with a red king\n";
				int x = 0;
				int y = 0;
				while(((checker_letter + x != letter_move_to) && (checker_letter - x != letter_move_to)) && ((checker_number + y != number_move_to) && (checker_number - y != number_move_to)))
				{
					// if it's to the left
					if((number_move_to < checker_number) > 1 || (checker_letter - letter_move_to) < 1)
					{
						//cout << "\nLEFT\n";
						// if it's left and above
						if(board[checker_letter - 1 + x][checker_number - 1 + y].black() && checker_letter > letter_move_to && board[checker_letter - 2 + x][checker_number - 2 + y].is_empty())
						{
							//cout << "\nABOVE LEFT\n";
							board[checker_letter - 1 + x][checker_number - 1 + y].set_empty(true);
							board[checker_letter - 1 + x][checker_number - 1 + y].set_black(false);
							x = x - 2;
							y = y - 2;
						}
						// if it's left and below
						else if(board[checker_letter + 1 + x][checker_number - 1 + y].black()  && checker_letter < letter_move_to && board[checker_letter + 2 + x][checker_number - 2 + y].is_empty())
						{
							//cout << "\nBELOW LEFT\n";
							board[checker_letter + 1 + x][checker_number - 1 + y].set_empty(true);
							board[checker_letter + 1 + x][checker_number - 1 + y].set_black(false);
							x = x + 2;
							y = y - 2;
						}
						else
						{
							return false;
						}
					}
					// if it's to the right
					else if(number_move_to > checker_number)
					{
						//cout << "\nRIGHT\n";
						// below and to the right
						if(board[checker_letter + 1 + x][checker_number + 1 + y].black() && board[checker_letter + 1 + x][checker_number + 1 + y].is_playable() && board[checker_letter + 2 + x][checker_number + 2 + y].is_empty())
						{
							//cout << "\nRIGHT BELOW\n";
							board[checker_letter + 1 + x][checker_number + 1 + y].set_empty(true);
							board[checker_letter + 1 + x][checker_number + 1 + y].set_black(false);
							x = x + 2;
							y = y + 2;
						}
						// above and to the right
						else if(board[checker_letter - 1 + x][checker_number + 1 + y].black() && board[checker_letter - 1 + x][checker_number + 1 + y].is_playable() && board[checker_letter - 2 + x][checker_number + 2 + y].is_empty())
						{
							//cout << "\nRIGHT ABOVE\n";
							board[checker_letter - 1 + x][checker_number + 1 + y].set_empty(true);
							board[checker_letter - 1 + x][checker_number + 1 + y].set_black(false);
							x = x - 2;
							y = y + 2;
						}
						else
						{
							return false;
						}
					}
					else if(number_move_to == checker_number)
					{
						//cout << "\nMORE THAN ONE JUMP\n";
						if(board[checker_letter + 1 + x][checker_number + 1 + y].black() && board[checker_letter + 2 + x][checker_number + 2 + y].is_empty() && board[checker_letter + 1 + x][checker_number + 1 + y].is_playable())
						{
							//cout << "\nRIGHT and BELOW\n";
							board[checker_letter + 1 + x][checker_number + 1 + y].set_empty(true);
							board[checker_letter + 1 + x][checker_number + 1 + y].set_black(false);
							x = x + 2;
							y = y + 2;
						}
						else if(board[checker_letter - 1 + x][checker_number + 1 + y].black() && board[checker_letter - 1 + x][checker_number + 1 + y].is_playable())
						{
							//cout << "\nRIGHT ABOVE\n";
							board[checker_letter - 1 + x][checker_number + 1 + y].set_empty(true);
							board[checker_letter - 1 + x][checker_number + 1 + y].set_black(false);
							x = x - 2;
							y = y + 2;
						}
						else if(board[checker_letter + 1 + x][checker_number - 1 + y].black() && board[checker_letter + 2 + x][checker_number - 2 + y].is_empty() && board[checker_letter + 1 + x][checker_number - 1 + y].is_playable())
						{
							//cout << "\nLEFT and BELOW\n";
							board[checker_letter + 1 + x][checker_number - 1 + y].set_empty(true);
							board[checker_letter + 1 + x][checker_number - 1 + y].set_black(false);
							x = x + 2;
							y = y - 2;
						}
						else if(board[checker_letter - 1 + x][checker_number - 1 + y].black() && board[checker_letter - 1 + x][checker_number - 1 + y].is_playable())
						{
							//cout << "\nABOVE LEFT\n";
							board[checker_letter - 1 + x][checker_number - 1 + y].set_empty(true);
							board[checker_letter - 1 + x][checker_number - 1 + y].set_black(false);
							x = x - 2;
							y = y - 2;
						}
						else
						{
							return false;
						}
					}
				}
				return true;
			}
			//*****************NOT JUMPING LEGAL MOVE*****************
			else if((checker_letter + checker_number) == (letter_move_to + number_move_to) || (checker_letter + checker_number) == (letter_move_to + number_move_to + 2) || (checker_letter + checker_number) == (letter_move_to + number_move_to - 2))
			{
				//cout << "\nNot jumping red piece that's a king\n";
				return true;
			}
		}
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************
		//black piece and not a king
		else if(board[checker_letter][checker_number].black() && !board[checker_letter][checker_number].king_black())
		{
			//*****************JUMPING LEGAL MOVE*****************
			// if it's actually jumping it is gonna be a few more spaces in the row
			if((checker_letter - letter_move_to) > 1)
			{
				//cout << "\nJumping move\n";
				int x = 0;
				int y = 0;
				while(((checker_letter + x != letter_move_to) && (checker_letter - x != letter_move_to)) || ((checker_number + y != number_move_to) && (checker_number - y != number_move_to)))
				{
					// if it's to the left
					if(number_move_to < checker_number)
					{
						//cout << "\nTHE BEST\n";
						// if it's left and above
						if(board[checker_letter - 1 + x][checker_number - 1 + y].red() && board[checker_letter - 1 + x][checker_number - 1 + y].is_playable())
						{
							//cout << "\nLEFT\n";
							board[checker_letter - 1 + x][checker_number - 1 + y].set_empty(true);
							board[checker_letter - 1 + x][checker_number - 1 + y].set_red(false);
							x = x - 2;
							y = y - 2;
						}
						else
						{
							return false;
						}
					}
					// if it's to the right
					else if(number_move_to > checker_number)
					{
						//cout << "\nTHE WORST\n";
						if(board[checker_letter - 1 + x][checker_number + 1 + y].red() && board[checker_letter - 1 + x][checker_number + 1 + y].is_playable())
						{
							//cout << "\nRIGHT\n";
							board[checker_letter - 1 + x][checker_number + 1 + y].set_empty(true);
							board[checker_letter - 1 + x][checker_number + 1 + y].set_red(false);
							x = x - 2;
							y = y + 2;
						}
						else
						{
							return false;
						}
					}
					else if(number_move_to == checker_number)
					{
				//cout << "\nX: " << x << "\nY: " << y << endl;
						if(board[checker_letter - 1 + x][checker_number + 1 + y].red() && board[checker_letter - 2 + x][checker_number + 2 + y].is_empty() && board[checker_letter - 1 + x][checker_number + 1 + y].is_playable())
						{
							//cout << "\nRIGHT\n";
							board[checker_letter - 1 + x][checker_number + 1 + y].set_empty(true);
							board[checker_letter - 1 + x][checker_number + 1 + y].set_red(false);
							x = x - 2;
							y = y + 2;
						}
						else if(board[checker_letter - 1 + x][checker_number - 1 + y].red() && board[checker_letter - 2 + x][checker_number - 2 + y].is_empty() && board[checker_letter - 1 + x][checker_number - 1 + y].is_playable())
						{
							//cout << "\nLEFT\n";
							board[checker_letter - 1 + x][checker_number - 1 + y].set_empty(true);
							board[checker_letter - 1 + x][checker_number - 1 + y].set_red(false);
							x = x - 2;
							y = y - 2;
						}
						else
						{
							return false;
						}
					}
				}
				return true;
			}
			// NOT JUMPING
			else if((((checker_letter + checker_number) == (letter_move_to + number_move_to)) || (checker_letter + checker_number) == (letter_move_to + number_move_to + 2) || (checker_letter + checker_number) == (letter_move_to + number_move_to - 2)) && checker_letter > letter_move_to)
			{
				//cout << "\nNot jumping black piece that's not a king\n";
				return true;
			}
		}
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************
		// black piece and a king
		else if(board[checker_letter][checker_number].black() && board[checker_letter][checker_number].king_black())
		{
			//*****************JUMPING LEGAL MOVE*****************
			// if it's actually jumping it is gonna be a few more spaces in the row O
			if((checker_letter - letter_move_to) > 1 || (checker_letter - letter_move_to) < -1)
			{
				//cout << "\nJumping move with a black king\n";
				int x = 0;
				int y = 0;
				while(((checker_letter + x != letter_move_to) && (checker_letter - x != letter_move_to)) && ((checker_number + y != number_move_to) && (checker_number - y != number_move_to)))
				{
					// if it's to the left
					if(number_move_to < checker_number)
					{
						//cout << "\nTHE LEFT SIDE\n";
						// if it's left and below
						if(board[checker_letter + 1 + x][checker_number - 1 + y].red() && board[checker_letter + 1 + x][checker_number - 1 + y].is_playable())
						{
							//cout << "\nLEFT AND BELOW\n";
							board[checker_letter + 1 + x][checker_number - 1 + y].set_empty(true);
							board[checker_letter + 1 + x][checker_number - 1 + y].set_red(false);
							x = x + 2;
							y = y - 2;
						}
						// if it's left and above
						if(board[checker_letter - 1 + x][checker_number - 1 + y].red() && board[checker_letter - 1 + x][checker_number - 1 + y].is_playable())
						{
							//cout << "\nLEFT and ABOVE\n";
							board[checker_letter - 1 + x][checker_number - 1 + y].set_empty(true);
							board[checker_letter - 1 + x][checker_number - 1 + y].set_red(false);
							x = x - 2;
							y = y - 2;
						}
						else
						{
							return false;
						}
					}
					// if it's to the right
					else if(number_move_to > checker_number)
					{
						//cout << "\nTHE WORST\n";
						// if it's right and above
						if(board[checker_letter - 1 + x][checker_number + 1 + y].red() && board[checker_letter - 1 + x][checker_number + 1 + y].is_playable() && checker_letter > letter_move_to)
						{
							//cout << "\nRIGHT and ABOVE\n";
							board[checker_letter - 1 + x][checker_number + 1 + y].set_empty(true);
							board[checker_letter - 1 + x][checker_number + 1 + y].set_red(false);
							x = x - 2;
							y = y + 2;
						}
						// if it's right and below
						else if(board[checker_letter + 1 + x][checker_number + 1 + y].red() && board[checker_letter + 1 + x][checker_number + 1 + y].is_playable() && checker_letter < letter_move_to)
						{
							//cout << "\nRIGHT AND BELOW\n";
							board[checker_letter + 1 + x][checker_number + 1 + y].set_empty(true);
							board[checker_letter + 1 + x][checker_number + 1 + y].set_red(false);
							x = x + 2;
							y = y + 2;
						}
						else
						{
							return false;
						}
					}
					else if(number_move_to == checker_number)
					{
						if(board[checker_letter - 1 + x][checker_number + 1 + y].red() && board[checker_letter - 2 + x][checker_number + 2 + y].is_empty())
						{
							//cout << "\nRIGHT\n";
							board[checker_letter - 1 + x][checker_number + 1 + y].set_empty(true);
							board[checker_letter - 1 + x][checker_number + 1 + y].set_red(false);
							x = x - 2;
							y = y + 2;
						}
						else if(board[checker_letter + 1 + x][checker_number + 1 + y].red())
						{
							//cout << "\nRIGHT AND BELOW\n";
							board[checker_letter + 1 + x][checker_number + 1 + y].set_empty(true);
							board[checker_letter + 1 + x][checker_number + 1 + y].set_red(false);
							x = x + 2;
							y = y + 2;
						}
						else if(board[checker_letter - 1 + x][checker_number - 1 + y].red() && board[checker_letter - 2 + x][checker_number - 2 + y].is_empty())
						{
							//cout << "\nLEFT\n";
							board[checker_letter - 1 + x][checker_number - 1 + y].set_empty(true);
							board[checker_letter - 1 + x][checker_number - 1 + y].set_red(false);
							x = x - 2;
							y = y - 2;
						}
						// if it's left and below
						if(board[checker_letter + 1 + x][checker_number - 1 + y].red())
						{
							//cout << "\nLEFT AND BELOW\n";
							board[checker_letter + 1 + x][checker_number - 1 + y].set_empty(true);
							board[checker_letter + 1 + x][checker_number - 1 + y].set_red(false);
							x = x + 2;
							y = y - 2;
						}
						else
						{
							return false;
						}
					}
				}
				return true;
			}
			else if((checker_letter + checker_number) == (letter_move_to + number_move_to) || (checker_letter + checker_number) == (letter_move_to + number_move_to + 2) || (checker_letter + checker_number) == (letter_move_to + number_move_to - 2))
			{
				//cout << "\nNot jumping black piece that's a king\n"; O
				return true;
			}
		}
		else
		{
			return false;
		}
		//cout << "\nIt's empty!\n";
	}
	else if((board[checker_letter][checker_number].red() && moves % 2 == 0) || (board[checker_letter][checker_number].black() && moves % 2 == 1))
	{
		//cout << "\nCan't play for the other team!\n";
		return false;
	}
	return false;
}

void Checkers::make_move(const string& move)
{
	//the positions of the place the checker is and where it wants to move
	string checker = move.substr(0,2);
	string move_to = move.substr(2,3);
	
	int checker_letter = int(tolower(checker[0]) - 'a');
	int checker_number = int(tolower(checker[1]) - '0');
	int letter_move_to = int(tolower(move_to[0]) - 'a');
	int number_move_to = int(tolower(move_to[1]) - '0');

	checker_number--;
	number_move_to--;

	bool was_king_b = false;
	bool was_king_r = false;

	if(board[checker_letter][checker_number].king_red())
	{
		was_king_r = true;
	}
	if(board[checker_letter][checker_number].king_black())
	{
		was_king_b = true;
	}

	//if it's a red piece
	if(board[checker_letter][checker_number].red())
	{
		//board[checker_letter][checker_number].set_empty(true);
		// I don't think I need to do anything else because if it's empty it will be 
		// black and nothign in it

		board[letter_move_to][number_move_to].set_red(true);
		board[letter_move_to][number_move_to].set_black(false);
		board[letter_move_to][number_move_to].set_empty(false);
		// if it's a king
		if(letter_move_to == 7)
		{
			//cout << "\nKing a red\n";
			board[letter_move_to][number_move_to].King_me_red(true);
			was_king_r = true;
		}
		else if(was_king_r)
		{
			board[letter_move_to][number_move_to].King_me_red(true);
		}
	}
	else if(board[checker_letter][checker_number].black())
	{
		board[letter_move_to][number_move_to].set_red(false);
		board[letter_move_to][number_move_to].set_black(true);
		board[letter_move_to][number_move_to].set_empty(false);
		// if it's a king for black
		if(letter_move_to == 0)
		{
			board[letter_move_to][number_move_to].King_me_black(true);
			was_king_b = true;
		}
		else if(was_king_b)
		{
			board[letter_move_to][number_move_to].King_me_black(true);
		}
	}
	// deletes piece
	board[checker_letter][checker_number].set_empty(true);
	board[checker_letter][checker_number].set_black(false);
	board[checker_letter][checker_number].set_red(false);
	moves++;
}

bool Checkers::is_game_over()
{
	int black_piece = 0;
	int red_piece = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(board[i][j].red() && !board[i][j].is_empty())
			{
				red_piece++;
			}
			if(board[i][j].black() && !board[i][j].is_empty())
			{
				black_piece++;
			}
		}
	}
	if(black_piece == 0)
	{
		return true;
	}
	if(red_piece == 0)
	{
		return true;
	}
	return false;
}

bool Checkers::make_jump(const string& move)
{
	string checker = move.substr(0,2);
	string move_to = move.substr(2,3);
	
	int checker_letter = int(tolower(checker[0]) - 'a');
	int checker_number = int(tolower(checker[1]) - '0');
	int letter_move_to = int(tolower(move_to[0]) - 'a');
	//int number_move_to = int(tolower(move_to[1]) - '0');
	
	checker_number--;

	if(letter_move_to - checker_letter > 1 || letter_move_to - checker_letter < -1)
	{
		//cout << "\nHEH\n";
		return false;
	}

	//cout << endl << checker_letter << endl << letter_move_to << endl;

	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			// if it's a piece
			if(board[i][j].is_playable() && !board[i][j].is_empty())
			{
				// if it's a red piece and not a king
				if(board[i][j].red() && !board[i][j].king_red())
				{
					// if it's the red persons turn
					if(moves % 2 == 1)
					{
						// it's gotta be on the board so i + j has to be less than 14 or less.
						// if it's black below to the right and they are empty
						if(board[i + 1][j + 1].black() && board[i + 2][j + 2].is_empty() && board[i + 1][j + 1].is_playable() && board[i + 2][j + 2].is_playable())
						{
				//cout << "\nS\n" << i << endl << j << endl;
							return true;
						}
						// if it's black and below to the left and they are empty
						else if(board[i + 1][j - 1].black() && board[i + 2][j - 2].is_empty() && board[i + 1][j - 1].is_playable() && board[i + 2][j - 2].is_playable())
						{
				//cout << "\nF\n" << i << endl << j << endl;
							return true;
						}
					}
				}
				else if(board[i][j].red() && board[i][j].king_red())
				{
					if(moves % 2 == 1)
					{
						// if it's black below to the right and they are empty
						if(board[i + 1][j + 1].black() && board[i + 2][j + 2].is_empty() && board[i + 1][j + 1].is_playable() && board[i + 2][j + 2].is_playable())
						{
							return true;
						}
						// if it's black and below to the left and they are empty
						else if(board[i + 1][j - 1].black() && board[i + 2][j - 2].is_empty() && board[i + 1][j - 1].is_playable() && board[i + 2][j - 2].is_playable())
						{
							return true;
						}
						// king stuff, above the piece
						else if(board[i - 1][j + 1].black() && board[i - 2][j + 2].is_empty() && board[i - 1][j + 1].is_playable() && board[i - 2][j + 2].is_playable())
						{
							return true;
						}
						else if(board[i - 1][j - 1].black() && board[i - 2][j - 2].is_empty() && board[i - 1][j - 1].is_playable() && board[i - 2][j - 2].is_playable())
						{
							return true;
						}
					}
				}
				else if(board[i][j].black() && !board[i][j].king_black())
				{
					if(moves % 2 == 0)
					{
						// if its above 
						if(board[i - 1][j + 1].red() && board[i - 2][j + 2].is_empty() && board[i - 1][j + 1].is_playable() && board[i - 2][j + 2].is_playable())
						{
				//cout << "\nEF\n" << i << endl << j << endl;
							return true;
						}
						else if(board[i - 1][j - 1].red() && board[i - 2][j - 2].is_empty() && board[i - 1][j - 1].is_playable() && board[i - 2][j - 2].is_playable())
						{
				//cout << "\nFE\n" << i << endl << j << endl;
							return true;
						}
					}
				}
				else if(board[i][j].black() && board[i][j].king_black())
				{
					if(moves % 2 == 0)
					{ 
						// above them
						if(board[i - 1][j + 1].red() && board[i - 2][j + 2].is_empty() && board[i - 1][j + 1].is_playable() && board[i - 2][j + 2].is_playable())
						{
							return true;
						}
						else if(board[i - 1][j - 1].red() && board[i - 2][j - 2].is_empty() && board[i - 1][j - 1].is_playable() && board[i - 2][j - 2].is_playable())
						{
							return true;
						}
						else if(board[i + 1][j - 1].red() && board[i + 2][j - 2].is_empty() && board[i + 1][j - 1].is_playable() && board[i + 2][j - 2].is_playable())
						{
							return true;
						}
						else if(board[i + 1][j + 1].red() && board[i + 2][j + 2].is_empty() && board[i + 1][j + 1].is_playable() && board[i + 2][j + 2].is_playable())
						{
							return true;
						}
					}
				}
			} // end of the empty statement
		}
	}
	return false;
}

game* Checkers::clone()
{
	return new Checkers(*this);
}

game::who Checkers::winning()
{
	int value = evaluate();

	if(value < 0)
	{
		return COMPUTER;
	}
	else if(value > 0)
	{
		return HUMAN;
	}
	else if(value == 0)
	{
		return NEUTRAL;
	}
	// I run -Wall and this was annoying me so I returned this
	return NEUTRAL;
}

void Checkers::compute_moves(queue<string> &moves)
{
	string temp = "    ";
	char i;
	char j;
	char k;
	char l;

	for(i = 'A'; i < 'I'; i++)
	{
		for(j = '1'; j < '9'; j++)
		{
			for(k = 'A'; k < 'I'; k++)
			{
				for(l = '1'; l < '9'; l++)
				{
					int checker_letter = int(tolower(i) - 'a');
					int checker_number = int(tolower(j) - '0');
					int letter_move_to = int(tolower(k) - 'a');
					int number_move_to = int(tolower(l) - '0');
	
					checker_number--;
					number_move_to--;

					temp[0] = i;
					temp[1] = j;
					temp[2] = k;
					temp[3] = l;
					if(is_legal(temp))
					{
						if(board[checker_letter][checker_number].is_playable() && board[letter_move_to][number_move_to].is_playable() && board[letter_move_to][number_move_to].is_empty() && board[checker_letter][checker_number].red())
						{
							if(board[checker_letter + 1][checker_number + 1].black() || board[checker_letter + 1][checker_number - 1].black())
							{
								moves.push(temp);
							}
							else if(!make_jump(temp) && k - i == 1 && (l - j == 1 || l - j == -1))
							{
								moves.push(temp);
							}
						}
					}
				}
			}
		}
	}
}

int Checkers::evaluate()
{
	int black_piece = 0;
	int red_piece = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(board[i][j].red() && !board[i][j].is_empty())
			{
				red_piece++;
			}
			if(board[i][j].black() && !board[i][j].is_empty())
			{
				black_piece++;
			}
		}
	}
	
	return (black_piece - red_piece);
}

game::who Checkers::last_mover()const
{
	return (moves % 2 == 1 ? HUMAN : COMPUTER);
}
