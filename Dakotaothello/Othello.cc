////////////////////////////////////////////////////////////////////////////////////////
//Name: Dakota Kiger
//Project: Final
//Description: Creating Othello
//Date: 11/27/2017
////////////////////////////////////////////////////////////////////////////////////////

#include "Othello.h"
#include <stdlib.h>

namespace main_savitch_14
{

/********************************************************************************************************************************************************
*******************************************************Creating the Board*******************************************************************************/
	void Othello::display_status()const
	{
		cout<<"     A    B    C    D    E    F    G    H";
		for (int i = 0; i < 8; i++)
		{
			cout<<endl<<B_BLACK<<"  "<<B_GREEN<<" ------------------------------------------";

			if (i == 0)
			{
				cout<<B_BLACK<<endl<<" 1";
			}
			else if (i == 1)
			{
				cout<<B_BLACK<<endl<<" 2";
			}
			else if (i == 2)
			{
				cout<<B_BLACK<<endl<<" 3";
			}
			else if (i == 3)
			{
				cout<<B_BLACK<<endl<<" 4";
			}
			else if (i == 4)
			{
				cout<<B_BLACK<<endl<<" 5";
			}
			else if (i == 5)
			{
				cout<<B_BLACK<<endl<<" 6";
			}
			else if (i == 6)
			{
				cout<<B_BLACK<<endl<<" 7";
			}
			else if (i == 7)
			{
				cout<<B_BLACK<<endl<<" 8";
			}
			cout<<B_GREEN<<" | ";

			for(int j = 0; j < 8; j++)
			{
				if( board[i][j].is_empty())
				{
					cout<<"  "<<" | " << B_GREEN;
				}
				else if( board[i][j].is_white())
				{
					cout<<B_WHITE<<"  "<< B_GREEN<<" | "<<B_GREEN;
				}
				else if( board[i][j].is_black())
				{
					cout<<B_BLACK<<"  "<<B_GREEN<<WHITE<<" | "<<B_GREEN;
				}
			}
			cout<<B_BLACK;
		}
		cout<<endl<<B_BLACK<<"  "<<B_GREEN<<" ------------------------------------------";
		cout<<B_BLACK;
		cout<<endl;

   		cout<< "This is turn: "<< move + 1 << endl;		//displaying to the player what turn it is
	}

/********************************************************************************************************************************************************
*******************************************************Legality Function********************************************************************************/

bool Othello::is_legal(const std::string& move_string)const
{
	int a, b;

	if(move_string == "pass" || move_string == "PASS" || move_string == "Pass")		//for pass function
		return true;

	if(move_string == " ")			//if answer is blank
		return false;

	b = ctoi(move_string.substr(0, 1));
   	a = atoi(move_string.substr(1, 2).c_str());
   	a--;

   	if(board[a][b].is_black() || board[a][b].is_white())
	{
		return false;
	}

	else if (last_mover() == COMPUTER)
	{
			if(board[a][b-1].is_black()) //Check left for black/white piece, depending on whose turn it is
			{
				for(int x_move = b; x_move > 0; x_move--)
				{
					if(board[a][x_move].is_white())
						return true;
				}
			}

		
			if(board[a][b+1].is_black()) //Check right for black/white piece, depending on whose turn it is
			{
				for(int x_move = b; x_move < 8; x_move++)
				{
					if(board[a][x_move].is_white())
						return true;
				}
			}

			if(board[a-1][b].is_black()) //Check up for black/white piece, depending on whose turn it is
			{
				for(int y_move = a; y_move > 0; y_move--)
				{
					if(board[y_move][b].is_white())
						return true;
				}
			}

			if(board[a+1][b].is_black()) //Check down for black/white piece, depending on whose turn it is
			{
				for(int y_move = a; y_move < 8; y_move++)
				{
					if(board[y_move][b].is_white())
						return true;
				}
			}
			
			if(board[a-1][b+1].is_black()) //Check diagonally up and to the right for black/white piece, depending on whose turn it is
			{
				for(int c = 0; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a-c][b+c].is_white())
						return true;
				}
			}

			if(board[a+1][b-1].is_black()) //Check diagonally down and to the left for black/white piece, depending on whose turn it is
			{
				for(int c = 0; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a+c][b-c].is_white())
						return true;
				}
			}

			if(board[a-1][b-1].is_black()) //Check diagonally up and to the left for black/white piece, depending on whose turn it is
			{
				for(int c = 0; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a-c][b-c].is_white())
						return true;
				}
			}

			if(board[a+1][b+1].is_black()) //Check diagonally down and to the right for black/white piece, depending on whose turn it is
			{
				for(int c = 0; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a+c][b+c].is_white())
						return true;
				}
			}
		
			return false;
	}
		
	
	

/**************************************************************************************************************************************************************************
*********************************************************************Switching the Whites and Blacks**********************************************************************/

	else
	{
			if(board[a][b-1].is_white()) //Check left for black/white piece, depending on whose turn it is
			{
				for(int x_move = b; x_move > 0; x_move--)
				{
					if(board[a][x_move].is_black())
						return true;
				}
			}
		

			if(board[a][b+1].is_white()) //Check right for black/white piece, depending on whose turn it is
			{
				for(int x_move = b; x_move < 8; x_move++)
				{

					if(board[a][x_move].is_black())
						return true;
				}
			}
		
			if(board[a-1][b].is_white()) //Check up for black/white piece, depending on whose turn it is
			{
				for(int y_move = a; y_move > 0; y_move--)
				{
					if(board[y_move][b].is_black())
						return true;
				}
			}

			if(board[a+1][b].is_white()) //Check down for black/white piece, depending on whose turn it is
			{
				for(int y_move = a; y_move < 8; y_move++)
				{
					if(board[y_move][b].is_black())
						return true;
				}
			}
			
			if(board[a-1][b+1].is_white()) //Check diagonally up and to the right for black/white piece, depending on whose turn it is
			{
				for(int c = 0; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a-c][b+c].is_black())
						return true;
				}
			}

			if(board[a+1][b-1].is_white()) //Check diagonally down and to the left for black/white piece, depending on whose turn it is
			{
				for(int c = 0; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a+c][b-c].is_black())
						return true;
				}
			}

			if(board[a-1][b-1].is_white()) //Check diagonally up and to the left for black/white piece, depending on whose turn it is
			{
				for(int c = 0; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a-c][b-c].is_black())
						return true;
				}
			}

			if(board[a+1][b+1].is_white()) //Check diagonally down and to the right for black/white piece, depending on whose turn it is
			{
				for(int c = 0; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a+c][b+c].is_black())
						return true;
				}
			}
		
		return false;
	}

}
			
/********************************************************************************************************************************************************
*******************************************************Making A Move Function***************************************************************************/

    void Othello::make_move(const std::string& move_string)
    {
    	int count;

    	if(move_string == "pass" || move_string == "PASS" || move_string == "Pass")			//for pass function
    	{
    		pass_count++;
    		return;
    	}
    	else
    		pass_count = 0;

    	int a, b;
		b = ctoi(move_string.substr(0, 1));
    	a = atoi(move_string.substr(1, 2).c_str());
    	a--;

		if (last_mover() == COMPUTER)	
		{
			board[a][b].set_white();

			if(board[a][b-1].is_black()) //Check left for black/white piece, depending on whose turn it is
			{
				for(int x_move = b - 1; x_move > 0; x_move--)
				{
					if(board[a][x_move].is_white())
					{
						for(int i = b-1; i > x_move; i--)
							board[a][i].flip();
						break;
					}
				}
			}

		
			if(board[a][b+1].is_black()) //Check right for black/white piece, depending on whose turn it is
			{
				for(int x_move = b + 1; x_move < 8; x_move++)
				{
					if(board[a][x_move].is_white())
					{
						for(int i = b+1; i < x_move; i++)
							board[a][i].flip();
						break;
					}
				}
			}

			
			if(board[a-1][b].is_black()) //Check up for black/white piece, depending on whose turn it is
			{
				for(int y_move = a - 1; y_move > 0; y_move--)
				{
					if(board[y_move][b].is_white())
					{
						for(int i = a-1; i > y_move; i--)
							board[i][b].flip();
						break;
					}
				}
			}

			if(board[a+1][b].is_black()) //Check down for black/white piece, depending on whose turn it is
			{
				for(int y_move = a + 1; y_move < 8; y_move++)
				{
					if(board[y_move][b].is_white())
					{
						for(int i = a+1; i < y_move; i++)
							board[i][b].flip();
						break;
					}

				}
			}
			
			if(board[a-1][b+1].is_black()) //Check diagonally up and to the right for black/white piece, depending on whose turn it is
			{
				for(int c = 1; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a-c][b+c].is_white())
					{
						for(int i = 1; i < c; i++)
							board[a-i][b+i].flip();
						break;
					}
				}
			}

			if(board[a+1][b-1].is_black()) //Check diagonally down and to the left for black/white piece, depending on whose turn it is
			{
				for(int c = 1; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a+c][b-c].is_white())
					{
						for(int i = 1; i < c; i++)
							board[a+i][b-i].flip();
						break;
					}
				}
			}

			if(board[a-1][b-1].is_black()) //Check diagonally up and to the left for black/white piece, depending on whose turn it is
			{
				for(int c = 1; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a-c][b-c].is_white())
					{
						for(int i = 1; i < c; i++)
							board[a-i][b-i].flip();
						break;
					}
				}
			}

			if(board[a+1][b+1].is_black()) //Check diagonally down and to the right for black/white piece, depending on whose turn it is
			{
				for(int c = 1; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a+c][b+c].is_white())
					{
						for(int i = 1; i < c; i++)
							board[a+i][b+i].flip();
						break;
					}
				}
			}
		
		}
		
/**************************************************************************************************************************************************************************
*********************************************************************Switching the Whites and Blacks**********************************************************************/
		else
		{
			board[a][b].set_black();

			if(board[a][b-1].is_white()) //Check left for black/white piece, depending on whose turn it is
			{
				for(int x_move = b - 1; x_move > 0; x_move--)
				{
					if(board[a][x_move].is_black())
					{
						for(int i = b-1; i > x_move; i--)
							board[a][i].flip();
						break;
					}
				}
			}
		
			if(board[a][b+1].is_white()) //Check right for black/white piece, depending on whose turn it is
			{
				for(int x_move = b + 1; x_move < 8; x_move++)
				{

					if(board[a][x_move].is_black())
						{
						for(int i = b+1; i < x_move; i++)
							board[a][i].flip();
						break;
					}
				}
			}

			
			if(board[a-1][b].is_white()) //Check up for black/white piece, depending on whose turn it is
			{
				for(int y_move = a - 1; y_move > 0; y_move--)
				{
					if(board[y_move][b].is_black())
					{
						for(int i = a-1; i > y_move; i--)
							board[i][b].flip();
						break;
					}
				}
			}

			if(board[a+1][b].is_white()) //Check down for black/white piece, depending on whose turn it is
			{
				for(int y_move = a + 1; y_move < 8; y_move++)
				{
					if(board[y_move][b].is_black())
					{
						for(int i = a+1; i < y_move; i++)
							board[i][b].flip();
						break;
					}

				}
			}

			if(board[a-1][b+1].is_white()) //Check diagonally up and to the right for black/white piece, depending on whose turn it is
			{
				for(int c = 1; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a-c][b+c].is_black())
					{
						for(int i = 1; i < c; i++)
							board[a-i][b+i].flip();
						break;
					}
				}
			}

			if(board[a+1][b-1].is_white()) //Check diagonally down and to the left for black/white piece, depending on whose turn it is
			{
				for(int c = 1; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a+c][b-c].is_black())
					{
						for(int i = 1; i < c; i++)
							board[a+i][b-i].flip();
						break;
					}
				}
			}

			if(board[a-1][b-1].is_white()) //Check diagonally up and to the left for black/white piece, depending on whose turn it is
			{
				for(int c = 1; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a-c][b-c].is_black())
					{
						for(int i = 1; i < c; i++)
							board[a-i][b-i].flip();
						break;
					}
				}
			}

			if(board[a+1][b+1].is_white()) //Check diagonally down and to the right for black/white piece, depending on whose turn it is
			{
				for(int c = 1; (a+c < 8 || a-c >= 0 || b+c < 8 || b-c >= 0); c++)
				{
					if(board[a+c][b+c].is_black())
					{
						for(int i = 1; i < c; i++)
							board[a+i][b+i].flip();
						break;
					}
				}
			}
		
		}
		move++;				//moves on to next turn after move
    }

/********************************************************************************************************************************************************
*******************************************************Restart Function*********************************************************************************/

   	void Othello::restart()				//restarts the game to initial board setup 
   	{
   		move = 0;
   		pass_count = 0;

   		for(int i = 0; i < 8; i++)
   		{
   			for(int j = 0; j < 8; j++)
   			{
   				board[i][j].set_empty();
   			}
   		}

   		board[3][3].set_white();
   		board[4][4].set_white();
   		board[4][3].set_black();
   		board[3][4].set_black();
   		cout<<WHITE;
   	}

/********************************************************************************************************************************************************
*******************************************************char to int Function*****************************************************************************/

   	int Othello::ctoi(std::string c)const				//This function helps process the input of the user directly from the board locations
   	{
   		if(c == "A" || c == "a")
   		{
   			return 0;
   		}
   		else if(c == "B" || c == "b")
   		{
   			return 1;
   		}
   		else if(c == "C" || c == "c")
   		{
   			return 2;
   		}
   		else if(c == "D" || c == "d")
   		{
   			return 3;
   		}
   		else if(c == "E" || c == "e")
   		{
   			return 4;
   		}
   		else if(c == "F" || c == "f")
   		{
   			return 5;
   		}
   		else if(c == "G" || c == "g")
   		{
   			return 6;
   		}
   		else if(c == "H" || c == "h")
   		{
   			return 7;
   		}
   	}

/********************************************************************************************************************************************************
*******************************************************Game Over Function*******************************************************************************/

   	bool Othello::is_game_over()const				//function for if any rules are met to end the game
   	{	
   		if(pass_count > 2)
   		{
   			return true;
   		}
   		else
   		{
   			for(int i = 0; i < 8; i++)
   			{
   				for( int j = 0; j < 8; j++)
   				{
   					if(board[i][j].is_empty())
   					{
   						return false;
   					}
   				}
   			}
   			return true;
   		}
   		cout<<"GAME OVER!";
   	}

/********************************************************************************************************************************************************
*******************************************************AI Compute Moves Function************************************************************************/


	void Othello::compute_moves(std::queue<std::string>& moves)const
	{
		for(char i = 'A'; i < 'I'; ++i)
		{
			for(char j = '1'; j < '9'; ++j)
			{	
				char temp[2];
				temp[0] = i;
				temp[1] = j;
				string move = temp;
				if(is_legal(move))
					moves.push(move);
			}
		}

		if(moves.empty())
			moves.push("pass");
	}
    		
/********************************************************************************************************************************************************
*******************************************************Evaluate Function********************************************************************************/
   
   int Othello::evaluate()const
   {
   		int score = 0;
   		for(int i = 0; i < 8; i++)
   		{
   			for(int j = 0; j < 8; j++)
   			{
   				if(board[i][j].is_black())
   					score++;

   				else if(board[i][j].is_white())
   					score--;
   			}
   		}

   		return score;
	}

/********************************************************************************************************************************************************
*******************************************************Piece Counter Function***************************************************************************/

	void Othello::num_pieces()const
	{
		int b = 0;
		int w = 0;
		for(int i = 0; i < 8; i++)
   		{
   			for(int j = 0; j < 8; j++)
   			{
   				if(board[i][j].is_black())
   					b++;

   				else if(board[i][j].is_white())
   					w++;
   			}
   		}

   		cout<<"There are this many black pieces: "<<b<<endl;
   		cout<<"There are this many white pieces: "<<w<<endl;

	}
}