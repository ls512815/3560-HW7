// Zachary Hughes
// CS2401 Spring 2017
// space.cc

// Space implementation file

#include "space.h"

bool space::is_playable()const
{
	return playable;
}

bool space::red()const
{
	return is_red;
}

bool space::black()const
{
	return is_black;
}

bool space::is_empty()const
{
	return empty;
}

bool space::king_red()const
{
	return is_king_red;
}

bool space::king_black()const
{
	return is_king_black;
}

void space::set_empty(bool temp)
{
	empty = temp;
}

void space::set_playable(bool temp)
{
	playable = temp;
}

void space::set_red(bool temp)
{
	is_red = temp;
}

void space::set_black(bool temp)
{
	is_black = temp;
}

void space::King_me_red(bool temp)
{
	is_king_red = temp;
}

void space::King_me_black(bool temp)
{
	is_king_black = temp;
}
