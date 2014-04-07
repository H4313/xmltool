#ifndef __ATTRIBUTE_H
#define __ATTRIBUTE_H

#include <iostream>
#include <string>

using namespace std;

class Attribute
{
	private :
		string * name;
		string * value;
		
	public :
		Attribute(string * n, string * v);
		~Attribute();
};

#endif
