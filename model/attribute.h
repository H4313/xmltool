#ifndef __ATTRIBUTE_H
#define __ATTRIBUTE_H

#include <iostream>
#include <string>

using namespace std;

class Attribute
{
	public : //temporaire (sorana)
		string * name;
		string * value;
		
	public :
		Attribute(string * n, string * v);
		~Attribute();
		string GetName();
		string GetValue();
		void display();
};

#endif
