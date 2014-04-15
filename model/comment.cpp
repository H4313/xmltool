#include "comment.h"

#include <string>
#include <iostream>

using namespace std;

Comment::Comment(string * c) : comment(c)
{}

Comment::Comment(Comment * c)
{
	comment = new string(c->getComment());
}

Comment * Comment::clone()
{
	return new Comment(this);
}

Comment::~Comment()
{
	if(comment) delete comment;
}

void Comment::display()
{
	if(comment)
		cout<<*comment<<endl;
}

string Comment::getComment()
{
	return (*comment);
}

