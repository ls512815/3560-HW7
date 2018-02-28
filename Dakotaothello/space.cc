////////////////////////////////////////////////////////////////////////////////////////
//Name: Dakota Kiger
//Project: Final
//Description: Creating Othello
//Date: 11/27/2017
////////////////////////////////////////////////////////////////////////////////////////

#include "space.h"
using namespace std;


	bool Space::is_white()const
	{
		if(value == 1)
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
		if(value == 2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Space::is_empty()const
	{
		if(value == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Space::flip()
	{
		if(value == 1)
		{
			value = 2;
		}
		else if (value == 2)
		{
			value = 1;
		}
	}