#ifndef __ITEM_H
#define __ITEM_H

#include <iostream>
#include <string>

using namespace std;

class Item
{
	public :
		virtual void display() = 0;
		virtual Item * clone() = 0;
		virtual ~Item() {};
};

#endif