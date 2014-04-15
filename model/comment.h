#ifndef __COMMENT_H
#define __COMMENT_H

#include "misc.h"

#include <iostream>
#include <string>

using namespace std;

class Comment : public Misc
{
	private :
		string * comment;
		
	public :
		Comment(string * c);
		Comment(Comment * c);
		Comment * clone();
		~Comment();
		void display();
		string getComment();
};

#endif