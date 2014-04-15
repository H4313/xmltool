#ifndef __MISC_H
#define __MISC_H

#include "item.h"

#include <iostream>

using namespace std;

class Misc : public Item
{
	public :
		virtual Misc * clone() = 0;
		virtual void display() = 0;
		virtual ~Misc() {};
};

#endif