// Frank MacDonald
// November 27th 2017
// Final Project
// Cs2401
// Mr.Dolan
/*
*/
#ifndef SPACE_H
#define SPACE_H
#include "space.h"
#include <iostream>
#include <fstream>
#include "colors.h"

	class Space
	{
    	public:
        	Space();
        	bool is_white()const;
        	bool is_black()const;
        	bool is_nothing()const;
		char set_nothing();
        	char set_white();
        	char set_black();
        	void flip();
		friend std::ostream& operator << (std::ostream& outs, Space piece);

   	 private:
		char piece;

	};
		
#endif // SPACE_H
