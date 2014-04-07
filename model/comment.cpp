#include "comment.h"

#include <string>
#include <iostream>

using namespace std;

Comment::Comment(string * c) : comment(c)
{}

Comment::~Comment()
{
	if(comment) delete comment;
}

void Comment::display()
{
	if(comment)
		cout<<"<!--"<<*comment<<"-->"<<endl;
}

