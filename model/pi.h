#ifndef __PI_H
#define __PI_H

#include "attribute.h"
#include "misc.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PI : public Misc
{
	private :
		string * target;
		vector<Attribute *> * attributes;
		
	public :
		PI(string * t, vector<Attribute *> * a);
		~PI();
};

#endif