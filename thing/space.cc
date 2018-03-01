#include "space.h"
#include <iostream>
#include <fstream>
#include "colors.h"

using namespace std;

	Space::Space()
	{
		piece = ' ';

	}
	bool Space::is_white()const
	{
    		if(piece == 'o')
    		{
	        	return true;
    		}
    		else
    		{
        		return false;
    		}
	}
	bool Space::is_black()const
	{
    		if(piece == 'x')
    		{
        		return true;
    		}
    		else
    		{
        		return false;
    		}
	}
	bool Space::is_nothing()const
	{
    		if(piece != 'x' && piece != 'o')
       	        {
        		return true;
    		}
    		else
    		{
       			return false;
    		}

	}
	char Space::set_white()
	{
		 piece = 'o';
		 return piece;
	}
	char Space::set_black()
	{
		piece = 'x';
		return piece;   
	}	
	char Space::set_nothing()
	{	
		piece = ' ';
		return piece;
	}
	void Space::flip()
	{
		if(is_white())
		{
			set_black();
		}
		else if(is_black())
		{
			set_white();
		}
	
	}
	std::ostream& operator << (std::ostream& outs, Space piece)
	{
		if(piece.is_black())
		 {	
			outs << B_BLACK << " " << RESET;
		 }
		else if(piece.is_white())
		{
			outs << B_WHITE << " " << RESET;
		}
		else if(piece.is_nothing())
		{	
			outs << ' ';
		}
			return outs;
	}







