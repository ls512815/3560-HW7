// Zachary Hughes
// CS2401 Spring 2017
// space.h

//space header file

#ifndef SPACE_H
#define SPACE_H

class space
{
	public:
		//accessors
		bool is_playable()const;
		bool red()const;
		bool black()const;
		bool is_empty()const;
		bool king_red()const;
		bool king_black()const;
		//setters
		void set_empty(bool temp);
		void set_playable(bool temp);
		void set_red(bool temp);
		void set_black(bool temp);
		void King_me_red(bool temp);
		void King_me_black(bool temp);
	private:
		bool is_red; // if it's not red then it's black
		bool is_black; // if it's black if not its red
		bool is_king_red; // king or not for red
		bool is_king_black; // king or not for black
		bool playable; // if there's anything in the space or not
		bool empty;
};

#endif
