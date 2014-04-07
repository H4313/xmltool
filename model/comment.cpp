#include "comment.h"

#include <string>

using namespace std;

Comment::Comment(string * c) : comment(c)
{}

Comment::~Comment()
{
	if(comment) delete comment;
}

