#include "othello.h"
#include <iostream>
#include <queue>
#include <cassert>
#include <string>
#include <cctype>

using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::toupper;


namespace main_savitch_14
{
    //This is the default constructor for the othello class. It calls to restart function to reset it to its base form
    Othello::Othello()
    {
	cout << YELLOW << " WELCOME TO FRANK'S OTHELLO GAME! GOOD LUCK AND HAVE FUN!!\n";
	cout << endl;
	cout << YELLOW << " ENTER A LETTER FIRST THEN A NUMBER SO ITS COL-ROW";
	cout << endl;
	cout << " HUMAN is black AND COMPUTER/PLAYER TWO is white";
	cout << endl;
        restart();
    }
    //*******************************************************************************************
    void Othello::restart()
    {
	int i,j;
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			board[i][j].set_nothing(); // this makes the board completely empty
		}
	}

        board[3][4].set_white();
        board[3][3].set_black();
        board[4][3].set_white();
        board[4][4].set_black();
    }
    //*******************************************************************************************
    void Othello::display_status()const
    {	
	cout << YELLOW << "Your legal moves are: ";
	queue<string> moves;
	compute_moves(moves); //Outputs my avaliable moves.
	while(!moves.empty())
	{
		cout << moves.front() << " ";
		moves.pop();
	}
	

	int var = 65;
	cout << endl;
	cout << RED  << "  " << "  1    2    3    4    5    6    7    8" << endl;
	
	cout << ' ' << BLUE  << B_GREEN << '|' << RESET;
	for(int i = 0; i < 7; i++)
	{
		cout << B_GREEN;
		cout << BLUE << '-' << '-' << '-' << '-' << '|';
		cout << RESET << BLUE;
	}
	cout << BLUE  << B_GREEN << '-' << '-' << '-' << '-' << '|' << RESET << endl;

	for(int i = 0; i < 7; i++)
	{
		cout << RED << static_cast<char>(var+i) << BLUE;
		for(int j = 0; j < 8; j++)
		{
			cout << B_GREEN << '|' << " " << " " << board[i][j] << B_GREEN << " "<< RESET << BLUE;	
		}
			cout << B_GREEN << '|' << RESET <<endl;
			cout << ' ' << B_GREEN << BLUE <<'|' << RESET;
			cout << BLUE;	
		for(int k = 0; k < 7; k++)
		{
			cout << B_GREEN << '-' << '-' << '-' << '-' << '|'  << BLUE;
		}
		cout << B_GREEN << '-' << '-' << '-' << '-' << '|' << RESET << endl;
	}
	cout << RED <<'H' << BLUE << B_GREEN;
	for(int i = 0; i < 8; i++)
	{
		cout << B_GREEN << '|' << " " << " " << board[7][i] << B_GREEN << " " << BLUE;
		//cout << RESET << BLUE;	
	}
	cout << B_GREEN << '|' << RESET << BLUE << endl;
	cout << ' ' << B_GREEN << '|'  << BLUE;
	for(int o = 0; o < 7; o++)
	{
		cout << B_GREEN << '-' << '-' << '-' << '-' << '|' << BLUE;
	}
	cout << B_GREEN << '-' << '-' << '-' << '-' << '|';
	cout << "" << WHITE << RESET << endl;
       
    }
    //*******************************************************************************************
    bool Othello::is_legal(const string& move)const
    {
      if(move == "DOLAN")
      {
	  return true;
      }
      int row = int(move[1] - 49); //x also row
      int col = int(toupper(move[0]) - 65); //y also column 
                                                                   
        if(!board[col][row].is_nothing())// makes sure you aren't jumping on another piece
	{
		return false;		
	}		
	if(next_mover() == game::HUMAN) //BLACKS MOVE
 	{
		if(board[col-1][row-1].is_white())
		{
			for(int i = 1; (col - i >= 0 && row - i >= 0 ); ++i)//checks diagonial up left
			{  
			   if(col-i < 0 || row-i < 0)break;	
				if(board[col-i][row-i].is_nothing())
				{
					break;
				}
				else if(board[col-i][row-i].is_black())
				{
					return true;
				}
			}
		}
		if(board[col-1][row].is_white())   
		{
			for(int i = col-1; i >= 0; --i)//checks up
			{
				 if(i < 0 || row < 0)break;	
				if(board[i][row].is_nothing())
				{
					break;
				}
				else if(board[i][row].is_black())
				{
					return true;
				}
			}
		} 
		if(board[col][row-1].is_white())   
		{
			for(int i = row-1; i >= 0; --i)//checks left
			{
				 if(col < 0 || i < 0)break;	
				if(board[col][i].is_nothing())
				{
					break;
				}
				else if(board[col][i].is_black())
				{
					return true;
				}
			}
		}
		if(board[col+1][row+1].is_white())
		{
			for(int i = 1; (col + i <= 8 && row + i <= 8 ); ++i)//checks diagonial down right
			{	
				if(col+i < 0 || row+i < 0)break;	
				if(board[col+i][row+i].is_nothing())
				{
					break;
				}
				else if(board[col+i][row+i].is_black())
				{
					return true;
				}
			}
		}
		if(board[col+1][row].is_white())   
		{
			for(int i = col+1; i < 8; ++i)//checks up
			{
				if(i < 0 || row < 0)break;	
				if(board[i][row].is_nothing())
				{
					break;
				}
				else if(board[i][row].is_black())
				{
					return true;
				}
			}
		}
		if(board[col][row+1].is_white())   
		{
			for(int i = row+1; i < 8; ++i)//checks right
			{
				if(col < 0 || i < 0)break;	
				if(board[col][i].is_nothing())
				{
					break;
				}
				else if(board[col][i].is_black())
				{
					return true;
				}
			}
		}
		if(board[col-1][row+1].is_white())
		{	
			for(int i = 1; (col - i >= 0 || row + i < 8 ); ++i)//checks diagonial up right
			{       if(col-i < 0 || row+i < 0)break;	
				if(board[col-i][row+i].is_nothing())
				{
					break;
				}
				else if(board[col-i][row+i].is_black())
				{
					return true;
				}
			}	
		}
		if(board[col+1][row-1].is_white())
		{
			for(int i = 1; (col + i < 8 || row - i >= 0 ); ++i)//checks diagonial down left
			{	
			        if(col+i < 0 || row+i < 0)break;	
				if(board[col+i][row-i].is_nothing())
				{
					break;
				}
				else if(board[col+i][row-i].is_black())
				{
					return true;
				}
			}

		}
	}
	else if(next_mover() == game::COMPUTER)
 	{

		if(board[col-1][row-1].is_black())
		{
			for(int i = 1; (col - i >= 0 && row - i >= 0 ); ++i)//checks diagonial up left
			{       if(col-i < 0 || row-i < 0)break;	
				if(board[col-i][row-i].is_nothing())
				{
					break;
				}
				else if(board[col-i][row-i].is_white())
				{
					return true;
				}
			}
		}
		if(board[col-1][row].is_black())   
		{
			for(int i = col-1; i >= 0; --i)//checks up
			{
			        if(i < 0 || row < 0)break;	
				if(board[i][row].is_nothing())
				{
					break;
				}
				else if(board[i][row].is_white())
				{
					return true;
				}
			}
		} 
		if(board[col][row-1].is_black())   
		{
			for(int i = row-1; i >= 0; --i)//checks left
			{
			        if(col < 0 || i < 0)break;	
				if(board[col][i].is_nothing())
				{
					break;
				}
				else if(board[col][i].is_white())
				{
					return true;
				}
			}
		}
		if(board[col+1][row+1].is_black())
		{
			for(int i = 1; (col + i <= 8 && row + i <= 8 ); ++i)//checks diagonial down right
			{
			        if(col+i < 0 || row+i < 0)break;		
				if(board[col+i][row+i].is_nothing())
				{
					break;
				}
				else if(board[col+i][row+i].is_white())
				{
					return true;
				}
			}
		}
		if(board[col+1][row].is_black())   
		{
			for(int i = col+1; i < 8; ++i)//checks down
			{
			        if(i < 0 || row < 0)break;	
				if(board[i][row].is_nothing())
				{
					break;
				}
				else if(board[i][row].is_white())
				{
					return true;
				}
			}
		}
		if(board[col][row+1].is_black())   
		{
			for(int i = row+1; i < 8; ++i)//checks right
			{
			        if(col < 0 || i < 0)break;	
				if(board[col][i].is_nothing())
				{
					break;
				}
				else if(board[col][i].is_white())
				{
					return true;
				}
			}
		}
		if(board[col-1][row+1].is_black())
		{	
			for(int i = 1; (col - i >= 0 || row + i < 8 ); ++i)//checks diagonial up right
			{      
			        if(col-i < 0 || row+i < 0)break;	
				if(board[col-i][row+i].is_nothing())
				{
					break;
				}
				else if(board[col-i][row+i].is_white())
				{
					return true;
				}
			}	
		}
		if(board[col+1][row-1].is_black())
		{
			for(int i = 1; (col + i < 8 || row - i >= 0 ); ++i)//checks diagonial down left
			{
			        if(col+i < 0 || row+i < 0)break;		
				if(board[col+i][row-i].is_nothing())
				{
					break;
				}
				else if(board[col+i][row-i].is_white())
				{
					return true;
				}
			}

		}
	}
	return false;
    }
/* 1   2   3   4   5   6   7   8
 |---|---|---|---|---|---|---|---|
A|00 |01 |02 |03 |04 |05 |06 |07 |
 |---|---|---|---|---|---|---|---|
B|10 |11 |12 |13 |14 |15 |16 |17 |
 |---|---|---|---|---|---|---|---|
C|20 |21 |22 |23 |24 |25 |26 |27 |
 |---|---|---|---|---|---|---|---|
D|30 |31 |32 | X | O |35 |36 |37 |
 |---|---|---|---|---|---|---|---|
E|40 |41 |42 | O | X |45 |46 |47 |
 |---|---|---|---|---|---|---|---|
F|50 |51 |52 |53 |54 |55 |56 |57 |
 |---|---|---|---|---|---|---|---|
G|60 |61 |62 |63 |64 |65 |66 |67 |
 |---|---|---|---|---|---|---|---|
H|70 |71 |72 |73 |74 |75 |76 |77 |
 |---|---|---|---|---|---|---|---|
*/
    //*******************************************************************************************
    void Othello::make_move(const string& move)
    {
	int col,row;
	row = int(move[1] - 49);
	col = int(toupper(move[0]) - 'A');
	if(move == "DOLAN")
	{
		passes++;
		game::make_move(move);
		return;
	}
     	else if(next_mover() == game::HUMAN) //BLACKS MOVE
 	{
		board[col][row].set_black();

		if(board[col-1][row-1].is_white())
		{
			for(int i = 1; (col - i >= 0 && row - i >= 0 ); ++i)//checks diagonial up left
			{
			        if(col-i < 0 || row-i < 0)break;		
				if(board[col-i][row-i].is_nothing())
				{
					break;
				}
				else if(board[col-i][row-i].is_black())
				{
					for(int j = 1; j != i; ++j)
					{
						board[col-j][row-j].flip();
					}
						break;
				}
			}
		}
		if(board[col-1][row].is_white())   
		{
			for(int i = col-1; i >= 0; --i)//checks up
			{
			        if(i < 0 || row < 0)break;	
				if(board[i][row].is_nothing())
				{
					break;
				}
				else if(board[i][row].is_black())
				{
					for(int set = i+1; set < col; ++set)
					{
						board[set][row].flip();
					}
						break;
				}
			}
		} 
		if(board[col][row-1].is_white())   
		{
			for(int i = row-1; i >= 0; --i)//checks left
			{
			        if(col < 0 || i < 0)break;	
				if(board[col][i].is_nothing())
				{
					break;
				}
				else if(board[col][i].is_black())
				{
					for(int set = i+1; set < row; ++set)
					{
						board[col][set].flip();
					}
						break;
				}
			}
		}
		if(board[col+1][row+1].is_white())
		{
			for(int i = 1; (col + i <= 8 && row + i <= 8 ); ++i)//checks diagonial down right
			{	
			        if(col+i < 0 || row+i < 0)break;	
				if(board[col+i][row+i].is_nothing())
				{
					break;
				}
				else if(board[col+i][row+i].is_black())
				{
					for(int j = 1; j != i; ++j)
					{
						board[col+j][row+j].flip();
					}
						break;
				}
			}
		}
		if(board[col+1][row].is_white())   
		{
			for(int i = col+1; i < 8; ++i)//checks up
			{
			        if(i < 0 || row < 0)break;	
				if(board[i][row].is_nothing())
				{
					break;
				}
				else if(board[i][row].is_black())
				{
					for(int set = i-1; set > col; --set)
					{
						board[set][row].flip();
					}
						break;
				}
			}
		}
		if(board[col][row+1].is_white())   
		{
			for(int i = row+1; i < 8; ++i)//checks right
			{
		                if(col < 0 || i < 0)break;	
				if(board[col][i].is_nothing())
				{
					break;
				}
				else if(board[col][i].is_black())
				{
					for(int set = i-1; set > row; --set)
					{
						board[col][set].flip();
					}
						break;
				}
			}
		}
		if(board[col-1][row+1].is_white())
		{	
			for(int i = 1; (col - i >= 0 || row + i < 8 ); ++i)//checks diagonial up right
			{	
		                if(col-i < 0 || row+i < 0)break;	
				if(board[col-i][row+i].is_nothing())
				{
					break;
				}
				else if(board[col-i][row+i].is_black())
				{
					for(int j = 1; j != i; ++j)
					{
						board[col-j][row+j].flip();
					}
						break;
				}
			}	
		}
		if(board[col+1][row-1].is_white())
		{
			for(int i = 1; (col + i < 8 || row - i >= 0 ); ++i)//checks diagonial down left
			{	
		                if(col+i < 0 || row-i < 0)break;	
				if(board[col+i][row-i].is_nothing())
				{
					break;
				}
				else if(board[col+i][row-i].is_black())
				{
					for(int j = 1; j != i; ++j)
					{
						board[col+j][row-j].flip();
					}
						break;
				}
			}

		}
	}
	else if(next_mover() == game::COMPUTER)
 	{
		board[col][row].set_white();

		if(board[col-1][row-1].is_black())
		{
			for(int i = 1; (col - i >= 0 && row - i >= 0 ); ++i)//checks diagonial up left
			{
	                        if(col-i < 0 || row-i < 0)break;		
				if(board[col-i][row-i].is_nothing())
				{
					break;
				}
				else if(board[col-i][row-i].is_white())
				{
					for(int j = 1; j != i; ++j)
					{
						board[col-j][row-j].flip();
					}
						break;
				}
			}
		}
		if(board[col-1][row].is_black())   
		{
			for(int i = col-1; i >= 0; --i)//checks up
			{
                                if(i < 0 || row < 0)break;	
				if(board[i][row].is_nothing())
				{
					break;
				}
				else if(board[i][row].is_white())
				{
					for(int set = i+1; set < col; ++set)
					{
						board[set][row].flip();
					}
						break;
				}
			}
		} 
		if(board[col][row-1].is_black())   
		{
			for(int i = row-1; i >= 0; --i)//checks left
			{
	                        if(col < 0 || i < 0)break;	
				if(board[col][i].is_nothing())
				{
					break;
				}
				else if(board[col][i].is_white())
				{
					for(int set = i+1; set < row; ++set)
					{
						board[col][set].flip();
					}
						break;
				}
			}
		}
		if(board[col+1][row+1].is_black())
		{
			for(int i = 1; (col + i <= 8 && row + i <= 8 ); ++i)//checks diagonial down right
			{
			        if(col+i < 0 || row+i < 0)break;		
				if(board[col+i][row+i].is_nothing())
				{
					break;
				}
				else if(board[col+i][row+i].is_white())
				{
					for(int j = 1; j != i; ++j)
					{
						board[col+j][row+j].flip();
					}
						break;
				}
			}
		}
		if(board[col+1][row].is_black())   
		{
			for(int i = col+1; i < 8; ++i)//checks down
			{
			        if(i < 0 || row < 0)break;	
				if(board[i][row].is_nothing())
				{
					break;
				}
				else if(board[i][row].is_white())
				{
					for(int set = i-1; set > col; --set)
					{
						board[set][row].flip();
					}
						break;
				}
			}
		}
		if(board[col][row+1].is_black())   
		{
			for(int i = row+1; i < 8; ++i)//checks right
			{
			        if(col < 0 || i < 0)break;	
				if(board[col][i].is_nothing())
				{
					break;
				}
				else if(board[col][i].is_white())
				{
					for(int set = i-1; set > row; --set)
					{
						board[col][set].flip();
					}
						break;
				}
			}
		}
		if(board[col-1][row+1].is_black())
		{	
			for(int i = 1; (col - i >= 0 || row + i < 8 ); ++i)//checks diagonial up right
			{
			        if(col-i < 0 || row+i < 0)break;		
				if(board[col-i][row+i].is_nothing())
				{
					break;
				}
				else if(board[col-i][row+i].is_white())
				{
					for(int j = 1; j != i; ++j)
					{
						board[col-j][row+j].flip();
					}
						break;
				}
			}	
		}
		if(board[col+1][row-1].is_black())
		{
			for(int i = 1; (col + i < 8 || row - i >= 0 ); ++i)//checks diagonial down left
			{
			        if(col+i < 0 || row-i < 0)break;		
				if(board[col+i][row-i].is_nothing())
				{
					break;
				}
				else if(board[col+i][row-i].is_white())
				{
					for(int j = 1; j != i; ++j)
					{
						board[col+j][row-j].flip();
					}
						break;
				}
			}

		}
	}
	passes = 0;
	game::make_move(move);
    }
    //*******************************************************************************************
    game* Othello::clone()const
    {
        return new Othello(*this);
    }
    //*******************************************************************************************
    game::who Othello::winning()const
    {
	int row,col;
	int whitecount,blackcount;

	for(row = 0; row < 9; row++)
	{
		for(col = 0; col < 9; col++)
		{
			if(board[col][row].is_black())
			blackcount++;
			if(board[col][row].is_white())
			whitecount++;
		}
	}
		cout << "Whitecount =" << whitecount << endl;
		cout << "Blackcount =" << blackcount << endl;
		if(blackcount > whitecount)
		{
			cout << "THE HUMAN WINS!!!!!!!\n";
			return game::HUMAN;
		}
		if(blackcount < whitecount)
		{
			cout << "TOO BAD THE COMPUTER WON!!!!\n";
			return game::COMPUTER;	
		}
		if((blackcount = whitecount))
		{
			cout << "THIS GAME IS A DRAW RARE BUT POSSIBLE!!!\n";
			return game::NEUTRAL;
		}

    }
    //*******************************************************************************************
    bool Othello::is_game_over()const
    {
	if(moves_completed() == 64)
	{
		return true;
	}
	else if(passes >= 2)
	{
		return true;
	}
	else
	{
		return false;
	}
    }
    //*******************************************************************************************
    void Othello::compute_moves(queue<string>& moves)const
    {
	string move = "  ";	

	for(char i = '1'; i < '9'; i++)//row
	{
		for(char j = 'A'; j < 'I'; j++)//column
		{
			move[1] = i;
			move[0] = j;
		
			if(is_legal(move))
			{
				moves.push(move);	
			}
		}	
	}
		if(moves.empty())
		{
			moves.push("DOLAN");
		}


    }
    //*******************************************************************************************
    int Othello::evaluate()const
    {
	int blackcount,whitecount;

	for(int i = 0; i < 8; i++)
	{	
		for(int j = 0; j < 8; j++)
		{
			if(whitecount)
			{
				whitecount++;
			}
			if(blackcount)
			{
				blackcount++;
			}
		}
	}
		int chance = whitecount - blackcount;

	return chance;
    }
    //*******************************************************************************************
    string Othello::get_user_move()const //OVERLOADED the get_user_move function from game
    {
    	if(next_mover() == game::HUMAN)
     	{
        	cout << GREEN <<  "Player One's move" << endl;
         	string answer;
         	cout << "Enter your move: " << RESET;
         	getline(cin,answer);
		toupper(answer[0]);
         	return answer;
      	}
      	if(next_mover() == game::COMPUTER)
      	{
         	cout << GREEN <<  "Player two's move" << endl;
        	string answer;
        	cout << "Enter your move: " << RESET;
         	getline(cin,answer);
		toupper(answer[0]);
         	return answer;
      	}
	else
	{
		return(0);
   	}

    }
}

