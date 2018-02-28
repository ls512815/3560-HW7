////////////////////////////////////////////////////////////////////////////////////////
//Name: Dakota Kiger
//Project: Final
//Description: Creating Othello
//Date: 11/27/2017
////////////////////////////////////////////////////////////////////////////////////////



#ifndef SPACE_OTHELLO
#define SPACE_OTHELLO

#include <iostream>
#include <string>

using namespace std;


class Space
{
public:
	Space(){value = 0;}
	
	bool is_white()const;
	bool is_black()const;
	bool is_empty()const;

	bool set_white(){value = 1;}
	bool set_black(){value = 2;}
	bool set_empty(){value = 0;}

	int get_value(){return value;}
	void flip();

private:
	int value;

};

#endif