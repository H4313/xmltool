#ifndef __ELEMENT_H
#define __ELEMENT_H

#include "attribute.h"
#include "item.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Element : public Item
{
	private :
		string * name;
		vector<Attribute *> * attributes;
		vector<Item *> * items;
		
	public :
		Element(string * n, vector<Attribute *> * a, vector<Item *> * i);
		~Element();
};

#endif